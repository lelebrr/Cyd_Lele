/**
 * @file ui_skimmer.cpp
 * @brief Tela de Detecção de Skimmers BLE
 * 
 * Interface gráfica para o detector de skimmers.
 * Mostra dispositivos suspeitos com nível de ameaça colorido.
 */

#include "ui_skimmer.h"
#include "../core/globals.h"
#include "../hardware/skimmer_detector.h"
#include "../hardware/ble_driver.h"
#include "ui_menu_ble.h"

static lv_obj_t *_screen = nullptr;
static lv_obj_t *_list = nullptr;
static lv_obj_t *_lbl_status = nullptr;
static lv_obj_t *_btn_scan = nullptr;
static lv_obj_t *_spinner = nullptr;
static lv_obj_t *_alert_panel = nullptr;
static lv_timer_t *_timer = nullptr;
static bool _active = false;

// Cores por nível de ameaça
static const uint32_t THREAT_COLORS[] = {
    0x00FF00,  // NONE - Verde
    0x80FF00,  // LOW - Amarelo-verde
    0xFFFF00,  // MEDIUM - Amarelo
    0xFF8000,  // HIGH - Laranja
    0xFF0000   // CRITICAL - Vermelho
};

static const char* THREAT_LABELS[] = {
    "OK",
    "BAIXO",
    "MÉDIO", 
    "ALTO",
    "CRÍTICO"
};

static void update_list() {
    if (!_list) return;
    
    lv_obj_clean(_list);
    
    const auto& devices = skimmerDetector.getSuspiciousDevices();
    
    if (devices.empty()) {
        if (skimmerDetector.getStatus() == SKIMMER_CLEAR) {
            lv_obj_t *item = lv_list_add_text(_list, "✅ Área limpa - Nenhum skimmer detectado");
            lv_obj_set_style_text_color(item, lv_color_hex(0x00FF00), 0);
        } else if (skimmerDetector.getStatus() == SKIMMER_SCANNING) {
            lv_list_add_text(_list, "🔍 Escaneando...");
        } else {
            lv_list_add_text(_list, "Pressione SCAN para iniciar");
        }
        return;
    }
    
    for (const auto& dev : devices) {
        // Cria item da lista
        char mac_str[20];
        snprintf(mac_str, 20, "%02X:%02X:%02X:%02X:%02X:%02X",
            dev.mac[0], dev.mac[1], dev.mac[2], dev.mac[3], dev.mac[4], dev.mac[5]);
        
        // Símbolo baseado no threat level
        const char* symbol = "⚠️";
        if (dev.threat >= THREAT_HIGH) symbol = "☠️";
        else if (dev.threat >= THREAT_MEDIUM) symbol = "⚠️";
        else symbol = "❓";
        
        char label[64];
        snprintf(label, 64, "%s %s", symbol, dev.name[0] ? dev.name : "Desconhecido");
        
        lv_obj_t *btn = lv_list_add_btn(_list, LV_SYMBOL_WARNING, label);
        
        // Descrição
        char desc[96];
        snprintf(desc, 96, "%s | RSSI: %ddBm | %s", 
            mac_str, dev.rssi, THREAT_LABELS[dev.threat]);
        
        lv_obj_t *lbl_desc = lv_label_create(btn);
        lv_label_set_text(lbl_desc, desc);
        lv_obj_set_style_text_font(lbl_desc, &lv_font_montserrat_10, 0);
        lv_obj_align(lbl_desc, LV_ALIGN_BOTTOM_LEFT, 30, 0);
        
        // Cor baseada no threat level
        uint32_t color = THREAT_COLORS[dev.threat];
        lv_obj_set_style_bg_color(btn, lv_color_hex(color), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_30, 0);
        lv_obj_set_style_border_color(btn, lv_color_hex(color), 0);
        lv_obj_set_style_border_width(btn, 2, 0);
        
        // Razão em terceira linha
        lv_obj_t *lbl_reason = lv_label_create(btn);
        lv_label_set_text(lbl_reason, dev.reason);
        lv_obj_set_style_text_font(lbl_reason, &lv_font_montserrat_10, 0);
        lv_obj_set_style_text_color(lbl_reason, lv_color_hex(color), 0);
        lv_obj_align(lbl_reason, LV_ALIGN_BOTTOM_LEFT, 30, 12);
    }
}

static void update_status() {
    if (!_lbl_status) return;
    
    SkimmerStatus status = skimmerDetector.getStatus();
    ThreatLevel threat = skimmerDetector.getHighestThreat();
    int count = skimmerDetector.getSuspiciousCount();
    
    char text[64];
    
    switch (status) {
        case SKIMMER_IDLE:
            lv_label_set_text(_lbl_status, "🛡️ Detector Pronto");
            lv_obj_set_style_text_color(_lbl_status, lv_color_hex(0xFFFFFF), 0);
            break;
            
        case SKIMMER_SCANNING:
            lv_label_set_text(_lbl_status, "🔍 Escaneando área...");
            lv_obj_set_style_text_color(_lbl_status, lv_color_hex(0x00FFFF), 0);
            break;
            
        case SKIMMER_CLEAR:
            lv_label_set_text(_lbl_status, "✅ ÁREA LIMPA");
            lv_obj_set_style_text_color(_lbl_status, lv_color_hex(0x00FF00), 0);
            break;
            
        case SKIMMER_ALERT:
            snprintf(text, 64, "⚠️ ALERTA: %d dispositivo(s) suspeito(s)!", count);
            lv_label_set_text(_lbl_status, text);
            lv_obj_set_style_text_color(_lbl_status, lv_color_hex(THREAT_COLORS[threat]), 0);
            break;
    }
    
    // Painel de alerta piscante para ameaças críticas
    if (_alert_panel) {
        if (threat >= THREAT_HIGH) {
            lv_obj_clear_flag(_alert_panel, LV_OBJ_FLAG_HIDDEN);
            // Animação piscante
            static bool blink = false;
            blink = !blink;
            lv_obj_set_style_bg_opa(_alert_panel, blink ? LV_OPA_50 : LV_OPA_20, 0);
        } else {
            lv_obj_add_flag(_alert_panel, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

static void timer_cb(lv_timer_t *t) {
    if (!_active) return;
    
    skimmerDetector.update();
    update_status();
    
    // Atualiza lista se scan terminou
    if (skimmerDetector.getStatus() != SKIMMER_SCANNING) {
        if (_spinner) {
            lv_obj_del(_spinner);
            _spinner = nullptr;
        }
        update_list();
    }
}

static void btn_scan_cb(lv_event_t *e) {
    // Inicia scan
    if (_spinner) lv_obj_del(_spinner);
    _spinner = lv_spinner_create(_screen, 1000, 60);
    lv_obj_set_size(_spinner, 50, 50);
    lv_obj_center(_spinner);
    
    lv_obj_clean(_list);
    lv_list_add_text(_list, "🔍 Procurando skimmers...");
    
    skimmerDetector.startScan(10);  // 10 segundos
}

static void btn_back_cb(lv_event_t *e) {
    ui_skimmer_hide();
    ui_menu_ble_show();
}

void ui_skimmer_init() {
    _screen = lv_obj_create(nullptr);
    lv_obj_set_style_bg_color(_screen, lv_color_hex(0x000000), 0);
    
    // Painel de alerta (inicialmente oculto)
    _alert_panel = lv_obj_create(_screen);
    lv_obj_set_size(_alert_panel, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(_alert_panel, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(_alert_panel, LV_OPA_20, 0);
    lv_obj_set_style_border_width(_alert_panel, 0, 0);
    lv_obj_add_flag(_alert_panel, LV_OBJ_FLAG_HIDDEN);
    
    // Header
    lv_obj_t *lbl_title = lv_label_create(_screen);
    lv_label_set_text(lbl_title, "🔍 Detector de Skimmers");
    lv_obj_align(lbl_title, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_style_text_color(lbl_title, lv_color_hex(0x00FFFF), 0);
    lv_obj_set_style_text_font(lbl_title, &lv_font_montserrat_14, 0);
    
    // Status
    _lbl_status = lv_label_create(_screen);
    lv_label_set_text(_lbl_status, "🛡️ Detector Pronto");
    lv_obj_align(_lbl_status, LV_ALIGN_TOP_MID, 0, 25);
    lv_obj_set_style_text_font(_lbl_status, &lv_font_montserrat_12, 0);
    
    // Lista de dispositivos suspeitos
    _list = lv_list_create(_screen);
    lv_obj_set_size(_list, lv_pct(100), lv_pct(65));
    lv_obj_align(_list, LV_ALIGN_TOP_MID, 0, 45);
    lv_obj_set_style_bg_color(_list, lv_color_hex(0x111111), 0);
    lv_obj_set_style_border_color(_list, lv_color_hex(0x333333), 0);
    
    lv_list_add_text(_list, "Pressione SCAN para iniciar");
    
    // Botão Scan
    _btn_scan = lv_btn_create(_screen);
    lv_obj_align(_btn_scan, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_set_size(_btn_scan, 90, 40);
    lv_obj_set_style_bg_color(_btn_scan, lv_color_hex(0x00AA00), 0);
    lv_obj_t *lbl_scan = lv_label_create(_btn_scan);
    lv_label_set_text(lbl_scan, "🔍 SCAN");
    lv_obj_center(lbl_scan);
    lv_obj_add_event_cb(_btn_scan, btn_scan_cb, LV_EVENT_CLICKED, nullptr);
    
    // Botão Back
    lv_obj_t *btn_back = lv_btn_create(_screen);
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    lv_obj_set_size(btn_back, 80, 40);
    lv_obj_set_style_bg_color(btn_back, lv_color_hex(0x444444), 0);
    lv_obj_t *lbl_back = lv_label_create(btn_back);
    lv_label_set_text(lbl_back, "← VOLTAR");
    lv_obj_center(lbl_back);
    lv_obj_add_event_cb(btn_back, btn_back_cb, LV_EVENT_CLICKED, nullptr);
    
    // Dica
    lv_obj_t *lbl_tip = lv_label_create(_screen);
    lv_label_set_text(lbl_tip, "💡 Detecta HC-05/06, módulos BT suspeitos em ATMs");
    lv_obj_align(lbl_tip, LV_ALIGN_BOTTOM_MID, 0, -55);
    lv_obj_set_style_text_font(lbl_tip, &lv_font_montserrat_10, 0);
    lv_obj_set_style_text_color(lbl_tip, lv_color_hex(0x888888), 0);
}

void ui_skimmer_show() {
    if (!_screen) ui_skimmer_init();
    
    _active = true;
    lv_scr_load(_screen);
    
    skimmerDetector.begin();
    
    _timer = lv_timer_create(timer_cb, 500, nullptr);
}

void ui_skimmer_hide() {
    _active = false;
    skimmerDetector.stop();
    
    if (_timer) {
        lv_timer_del(_timer);
        _timer = nullptr;
    }
    
    if (_spinner) {
        lv_obj_del(_spinner);
        _spinner = nullptr;
    }
}

bool ui_skimmer_is_active() {
    return _active;
}
