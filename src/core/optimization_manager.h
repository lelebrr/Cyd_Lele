/**
 * @file optimization_manager.h
 * @brief Gerenciador de Otimizações do Sistema Lele Origin
 * @author Lele Origin Team
 * @version 2.0
 */

#ifndef OPTIMIZATION_MANAGER_H
#define OPTIMIZATION_MANAGER_H

#include <Arduino.h>
#include <vector>
#include <WiFi.h>
#include <esp_bt.h>

// ============================================================================
// ENUMS E CONSTANTES DE OTIMIZAÇÃO
// ============================================================================

/**
 * @brief Modos de otimização do sistema
 */
enum OptimizationMode {
    MODE_PERFORMANCE = 0,  ///< Prioriza performance
    MODE_BALANCED,         ///< Equilibra performance e energia
    MODE_POWERSAVE,        ///< Prioriza economia de energia
    MODE_IDLE              ///< Modo ocioso máximo
};

/**
 * @brief Componentes otimizáveis
 */
enum OptimizableComponent {
    COMPONENT_CPU = 0,
    COMPONENT_WIFI,
    COMPONENT_BLE,
    COMPONENT_DISPLAY,
    COMPONENT_MEMORY,
    COMPONENT_SENSORS,
    COMPONENT_RF,
    COMPONENT_USB
};

/**
 * @brief Configurações de otimização
 */
struct OptimizationConfig {
    uint32_t cpuFrequency;      // Frequência CPU em MHz
    uint8_t wifiPower;          // Potência WiFi (0-20.5 dBm)
    bool wifiSleep;             // Sleep mode WiFi
    uint8_t blePower;           // Potência BLE
    bool bleSleep;              // Sleep mode BLE
    bool displayDim;            // Dim display
    uint16_t displayTimeout;    // Timeout display em segundos
    bool psramEnabled;          // Uso de PSRAM
    uint32_t sensorInterval;    // Intervalo sensores em ms
    bool rfLowPower;            // Modo baixa potência RF
    bool usbOptimized;          // Otimização USB
};

// ============================================================================
// CLASSE BUFFER POOL
// ============================================================================

/**
 * @brief Pool de buffers reutilizáveis para otimização de memória
 */
class BufferPool {
private:
    static const size_t MAX_BUFFERS = 10;
    static const size_t BUFFER_SIZE = 1024;
    uint8_t buffers[MAX_BUFFERS][BUFFER_SIZE];
    bool used[MAX_BUFFERS];
    SemaphoreHandle_t mutex;

public:
    BufferPool() {
        memset(used, 0, sizeof(used));
        mutex = xSemaphoreCreateMutex();
    }

    uint8_t* getBuffer() {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            for (size_t i = 0; i < MAX_BUFFERS; i++) {
                if (!used[i]) {
                    used[i] = true;
                    xSemaphoreGive(mutex);
                    return buffers[i];
                }
            }
            xSemaphoreGive(mutex);
        }
        return nullptr; // Pool esgotado
    }

    bool releaseBuffer(uint8_t* buffer) {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            for (size_t i = 0; i < MAX_BUFFERS; i++) {
                if (buffers[i] == buffer) {
                    used[i] = false;
                    xSemaphoreGive(mutex);
                    return true;
                }
            }
            xSemaphoreGive(mutex);
        }
        return false;
    }

    size_t getBufferSize() const { return BUFFER_SIZE; }
    size_t getAvailableBuffers() const {
        size_t count = 0;
        for (bool u : used) if (!u) count++;
        return count;
    }
    size_t getMaxBuffers() const { return MAX_BUFFERS; }
};

// ============================================================================
// CLASSE CONNECTION POOL
// ============================================================================

/**
 * @brief Pool de conexões WiFi reutilizáveis
 */
class ConnectionPool {
private:
    static const size_t MAX_CONNECTIONS = 5;
    WiFiClient clients[MAX_CONNECTIONS];
    bool inUse[MAX_CONNECTIONS];
    SemaphoreHandle_t mutex;

public:
    ConnectionPool() {
        memset(inUse, 0, sizeof(inUse));
        mutex = xSemaphoreCreateMutex();
    }

    WiFiClient* getClient() {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            for (size_t i = 0; i < MAX_CONNECTIONS; i++) {
                if (!inUse[i] || !clients[i].connected()) {
                    if (!clients[i].connected()) {
                        clients[i].stop(); // Fecha conexão antiga se existir
                    }
                    inUse[i] = true;
                    xSemaphoreGive(mutex);
                    return &clients[i];
                }
            }
            xSemaphoreGive(mutex);
        }
        return nullptr; // Pool esgotado
    }

    bool releaseClient(WiFiClient* client) {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            for (size_t i = 0; i < MAX_CONNECTIONS; i++) {
                if (&clients[i] == client) {
                    inUse[i] = false;
                    client->stop(); // Fecha conexão
                    xSemaphoreGive(mutex);
                    return true;
                }
            }
            xSemaphoreGive(mutex);
        }
        return false;
    }
};

// ============================================================================
// CLASSE PRINCIPAL OPTIMIZATION MANAGER
// ============================================================================

/**
 * @brief Gerenciador central de otimizações do sistema
 */
class OptimizationManager {
private:
    OptimizationMode currentMode;
    OptimizationConfig currentConfig;
    BufferPool bufferPool;
    ConnectionPool connectionPool;

    // Estado dos componentes
    bool bleActive;
    bool wifiActive;
    bool rfActive;
    bool usbActive;
    bool attackActive;

    // Timers para otimização
    unsigned long lastOptimizationCheck;
    unsigned long lastPowerCheck;

    // Métricas de performance
    uint32_t cpuTime;
    uint32_t wifiTime;
    uint32_t bleTime;
    size_t memoryUsed;
    size_t psramUsed;

public:
    OptimizationManager() :
        currentMode(MODE_BALANCED),
        bleActive(false), wifiActive(false), rfActive(false), usbActive(false), attackActive(false),
        lastOptimizationCheck(0), lastPowerCheck(0),
        cpuTime(0), wifiTime(0), bleTime(0), memoryUsed(0), psramUsed(0) {

        // Configurações padrão balanced
        currentConfig = {
            .cpuFrequency = 160,
            .wifiPower = 15,      // 15 dBm
            .wifiSleep = false,
            .blePower = ESP_PWR_LVL_P7,
            .bleSleep = false,
            .displayDim = false,
            .displayTimeout = 300, // 5 minutos
            .psramEnabled = psramFound(),
            .sensorInterval = 1000, // 1 segundo
            .rfLowPower = true,
            .usbOptimized = true
        };
    }

    // ============================================================================
    // MÉTODOS PÚBLICOS
    // ============================================================================

    /**
     * @brief Inicializa o gerenciador de otimizações
     */
    void begin() {
        setMode(currentMode); // Aplica configurações iniciais
        logOptimization("Optimization Manager initialized");
    }

    /**
     * @brief Define o modo de otimização
     */
    void setMode(OptimizationMode mode) {
        currentMode = mode;

        switch (mode) {
            case MODE_PERFORMANCE:
                currentConfig.cpuFrequency = 240;
                currentConfig.wifiPower = 20;
                currentConfig.wifiSleep = false;
                currentConfig.blePower = ESP_PWR_LVL_P9;
                currentConfig.bleSleep = false;
                currentConfig.displayDim = false;
                currentConfig.rfLowPower = false;
                break;

            case MODE_BALANCED:
                currentConfig.cpuFrequency = 160;
                currentConfig.wifiPower = 15;
                currentConfig.wifiSleep = true;
                currentConfig.blePower = ESP_PWR_LVL_P7;
                currentConfig.bleSleep = true;
                currentConfig.displayDim = false;
                currentConfig.rfLowPower = true;
                break;

            case MODE_POWERSAVE:
                currentConfig.cpuFrequency = 80;
                currentConfig.wifiPower = 8;
                currentConfig.wifiSleep = true;
                currentConfig.blePower = ESP_PWR_LVL_P3;
                currentConfig.bleSleep = true;
                currentConfig.displayDim = true;
                currentConfig.rfLowPower = true;
                break;

            case MODE_IDLE:
                currentConfig.cpuFrequency = 40;
                currentConfig.wifiPower = 2;
                currentConfig.wifiSleep = true;
                currentConfig.blePower = ESP_PWR_LVL_N0;
                currentConfig.bleSleep = true;
                currentConfig.displayDim = true;
                currentConfig.rfLowPower = true;
                break;
        }

        applyOptimizations();
        logOptimization("Mode changed to: " + String(mode));
    }

    /**
     * @brief Atualiza estado dos componentes
     */
    void updateComponentState(OptimizableComponent component, bool active) {
        switch (component) {
            case COMPONENT_BLE: bleActive = active; break;
            case COMPONENT_WIFI: wifiActive = active; break;
            case COMPONENT_RF: rfActive = active; break;
            case COMPONENT_USB: usbActive = active; break;
            default: break;
        }

        // Se ataque ativo, força modo performance
        if (bleActive || wifiActive || rfActive || usbActive) {
            attackActive = true;
            if (currentMode != MODE_PERFORMANCE) {
                setMode(MODE_PERFORMANCE);
            }
        } else {
            attackActive = false;
        }
    }

    /**
     * @brief Loop principal de otimização (chamar no loop principal)
     */
    void loop() {
        unsigned long now = millis();

        // Verificação periódica de otimização (a cada 30 segundos)
        if (now - lastOptimizationCheck > 30000) {
            optimizeDynamically();
            lastOptimizationCheck = now;
        }

        // Verificação de energia (a cada 5 minutos)
        if (now - lastPowerCheck > 300000) {
            optimizePowerConsumption();
            lastPowerCheck = now;
        }
    }

    /**
     * @brief Obtém buffer otimizado do pool
     */
    uint8_t* getOptimizedBuffer() {
        return bufferPool.getBuffer();
    }

    /**
     * @brief Libera buffer para o pool
     */
    bool releaseOptimizedBuffer(uint8_t* buffer) {
        return bufferPool.releaseBuffer(buffer);
    }

    /**
     * @brief Obtém cliente WiFi otimizado do pool
     */
    WiFiClient* getOptimizedClient() {
        return connectionPool.getClient();
    }

    /**
     * @brief Libera cliente WiFi para o pool
     */
    bool releaseOptimizedClient(WiFiClient* client) {
        return connectionPool.releaseClient(client);
    }

    /**
     * @brief Aloca memória otimizada (usa PSRAM se disponível)
     */
    void* allocateOptimized(size_t size) {
        if (size > 10000 && currentConfig.psramEnabled) {
            return ps_malloc(size);
        } else {
            return malloc(size);
        }
    }

    /**
     * @brief Obtém métricas de performance
     */
    String getPerformanceMetrics() {
        char metrics[512];
        snprintf(metrics, sizeof(metrics),
            "CPU: %lu MHz | WiFi: %u dBm | BLE: %u | "
            "Mem: %lu/%lu KB | PSRAM: %lu KB | Buffers: %lu/%lu",
            (unsigned long)currentConfig.cpuFrequency,
            (unsigned int)currentConfig.wifiPower,
            (unsigned int)currentConfig.blePower,
            (unsigned long)memoryUsed / 1024,
            (unsigned long)ESP.getHeapSize() / 1024,
            (unsigned long)psramUsed / 1024,
            (unsigned long)bufferPool.getAvailableBuffers(),
            (unsigned long)bufferPool.getMaxBuffers());

        return String(metrics);
    }

private:
    // ============================================================================
    // MÉTODOS PRIVADOS
    // ============================================================================

    /**
     * @brief Aplica todas as otimizações atuais
     */
    void applyOptimizations() {
        optimizeCPU();
        optimizeWiFi();
        optimizeBLE();
        optimizeDisplay();
        optimizeMemory();
        optimizeSensors();
        optimizeRF();
        optimizeUSB();
    }

    /**
     * @brief Otimização dinâmica baseada no uso
     */
    void optimizeDynamically() {
        // Ajusta CPU baseado na atividade
        if (attackActive) {
            if (currentConfig.cpuFrequency < 160) {
                currentConfig.cpuFrequency = 160;
                setCpuFrequencyMhz(currentConfig.cpuFrequency);
            }
        } else {
            if (currentConfig.cpuFrequency > 80) {
                currentConfig.cpuFrequency = 80;
                setCpuFrequencyMhz(currentConfig.cpuFrequency);
            }
        }

        // Otimiza WiFi baseado na conectividade
        if (WiFi.status() == WL_CONNECTED) {
            currentConfig.wifiSleep = true; // Modem sleep quando conectado
        } else {
            currentConfig.wifiSleep = false; // Sem sleep quando desconectado
        }
        WiFi.setSleep(currentConfig.wifiSleep);

        // Atualiza métricas
        updateMetrics();
    }

    /**
     * @brief Otimização de consumo de energia
     */
    void optimizePowerConsumption() {
        // Deep sleep inteligente
        uint32_t sleepTime = 60000; // 1 minuto base

        if (!attackActive && !bleActive && !wifiActive) {
            sleepTime = 300000; // 5 minutos se inativo
        }

        // Configura wake timer
        esp_sleep_enable_timer_wakeup(sleepTime * 1000);
    }

    /**
     * @brief Otimiza CPU
     */
    void optimizeCPU() {
        setCpuFrequencyMhz(currentConfig.cpuFrequency);
    }

    /**
     * @brief Otimiza WiFi
     */
    void optimizeWiFi() {
        if (wifiActive) {
            WiFi.setTxPower((wifi_power_t)currentConfig.wifiPower);
            WiFi.setSleep(currentConfig.wifiSleep);
        }
    }

    /**
     * @brief Otimiza BLE
     */
    void optimizeBLE() {
        if (bleActive) {
            // NimBLE power level setting
            // Note: This is a simplified implementation
        }
    }

    /**
     * @brief Otimiza display
     */
    void optimizeDisplay() {
        // Display dimming logic would go here
        // This requires integration with the display driver
    }

    /**
     * @brief Otimiza gerenciamento de memória
     */
    void optimizeMemory() {
        // Memory optimization logic
        // PSRAM usage, garbage collection hints, etc.
    }

    /**
     * @brief Otimiza sensores
     */
    void optimizeSensors() {
        // Sensor sampling rate adjustment
    }

    /**
     * @brief Otimiza RF
     */
    void optimizeRF() {
        // RF power and timing optimization
    }

    /**
     * @brief Otimiza USB
     */
    void optimizeUSB() {
        // USB timing and power optimization
    }

    /**
     * @brief Atualiza métricas de performance
     */
    void updateMetrics() {
        memoryUsed = ESP.getHeapSize() - ESP.getFreeHeap();
        psramUsed = ESP.getPsramSize() - ESP.getFreePsram();
    }

    /**
     * @brief Log de otimizações
     */
    void logOptimization(const String& message) {
        Serial.println("[OPTIMIZATION] " + message);
        // Could also log to SD card or display
    }
};

// ============================================================================
// INSTÂNCIA GLOBAL
// ============================================================================

extern OptimizationManager optimizationManager;

#endif // OPTIMIZATION_MANAGER_H
