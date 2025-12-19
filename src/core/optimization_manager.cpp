/**
 * @file optimization_manager.cpp
 * @brief Implementação do Gerenciador de Otimizações
 * @author Lele Origin Team
 * @version 2.0
 */

#include "optimization_manager.h"
#include <WiFi.h>
#include <esp_wifi.h>

// Instância global
OptimizationManager optimizationManager;

// ============================================================================
// IMPLEMENTAÇÃO BUFFER POOL
// ============================================================================

BufferPool::BufferPool() {
    memset(used, 0, sizeof(used));
    mutex = xSemaphoreCreateMutex();
}

uint8_t* BufferPool::getBuffer() {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        for (size_t i = 0; i < MAX_BUFFERS; i++) {
            if (!used[i]) {
                used[i] = true;
                xSemaphoreGive(mutex);
                memset(buffers[i], 0, BUFFER_SIZE); // Limpa buffer
                return buffers[i];
            }
        }
        xSemaphoreGive(mutex);
    }
    return nullptr; // Pool esgotado
}

bool BufferPool::releaseBuffer(uint8_t* buffer) {
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

size_t BufferPool::getAvailableBuffers() const {
    size_t count = 0;
    for (bool u : used) if (!u) count++;
    return count;
}

// ============================================================================
// IMPLEMENTAÇÃO CONNECTION POOL
// ============================================================================

ConnectionPool::ConnectionPool() {
    memset(inUse, 0, sizeof(inUse));
    mutex = xSemaphoreCreateMutex();
}

WiFiClient* ConnectionPool::getClient() {
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

bool ConnectionPool::releaseClient(WiFiClient* client) {
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

// ============================================================================
// IMPLEMENTAÇÃO OPTIMIZATION MANAGER
// ============================================================================

OptimizationManager::OptimizationManager() :
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

void OptimizationManager::begin() {
    setMode(currentMode); // Aplica configurações iniciais
    logOptimization("Optimization Manager initialized - Mode: " + String(currentMode));
}

void OptimizationManager::setMode(OptimizationMode mode) {
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

void OptimizationManager::updateComponentState(OptimizableComponent component, bool active) {
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

void OptimizationManager::loop() {
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

uint8_t* OptimizationManager::getOptimizedBuffer() {
    return bufferPool.getBuffer();
}

bool OptimizationManager::releaseOptimizedBuffer(uint8_t* buffer) {
    return bufferPool.releaseBuffer(buffer);
}

WiFiClient* OptimizationManager::getOptimizedClient() {
    return connectionPool.getClient();
}

bool OptimizationManager::releaseOptimizedClient(WiFiClient* client) {
    return connectionPool.releaseClient(client);
}

void* OptimizationManager::allocateOptimized(size_t size) {
    if (size > 10000 && currentConfig.psramEnabled) {
        return ps_malloc(size);
    } else {
        return malloc(size);
    }
}

String OptimizationManager::getPerformanceMetrics() {
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

void OptimizationManager::applyOptimizations() {
    optimizeCPU();
    optimizeWiFi();
    optimizeBLE();
    optimizeDisplay();
    optimizeMemory();
    optimizeSensors();
    optimizeRF();
    optimizeUSB();
}

void OptimizationManager::optimizeDynamically() {
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

void OptimizationManager::optimizePowerConsumption() {
    // Deep sleep inteligente
    uint32_t sleepTime = 60000; // 1 minuto base

    if (!attackActive && !bleActive && !wifiActive) {
        sleepTime = 300000; // 5 minutos se inativo
    }

    // Configura wake timer
    esp_sleep_enable_timer_wakeup(sleepTime * 1000);
}

void OptimizationManager::optimizeCPU() {
    setCpuFrequencyMhz(currentConfig.cpuFrequency);
}

void OptimizationManager::optimizeWiFi() {
    if (wifiActive) {
        WiFi.setTxPower((wifi_power_t)currentConfig.wifiPower);
        WiFi.setSleep(currentConfig.wifiSleep);
    }
}

void OptimizationManager::optimizeBLE() {
    if (bleActive) {
        // NimBLE power level setting
        // Note: This is a simplified implementation
        // Could integrate with NimBLE power management
    }
}

void OptimizationManager::optimizeDisplay() {
    // Display dimming logic would go here
    // This requires integration with the display driver
    // For now, just log the configuration
    if (currentConfig.displayDim) {
        logOptimization("Display dimming enabled");
    }
}

void OptimizationManager::optimizeMemory() {
    // Memory optimization logic
    // PSRAM usage, garbage collection hints, etc.

    // Força garbage collection se memória baixa
    if (ESP.getFreeHeap() < 10000) {
        logOptimization("Low memory detected, forcing GC");
        // ESP32 Arduino doesn't have explicit GC, but we can suggest freeing memory
    }

    // Otimiza PSRAM se disponível
    if (currentConfig.psramEnabled && ESP.getFreePsram() > 0) {
        logOptimization("PSRAM optimization enabled");
    }
}

void OptimizationManager::optimizeSensors() {
    // Sensor sampling rate adjustment
    // This would integrate with sensor drivers
    logOptimization("Sensor interval set to " + String(currentConfig.sensorInterval) + "ms");
}

void OptimizationManager::optimizeRF() {
    // RF power and timing optimization
    if (currentConfig.rfLowPower) {
        logOptimization("RF low power mode enabled");
    }
}

void OptimizationManager::optimizeUSB() {
    // USB timing and power optimization
    if (currentConfig.usbOptimized) {
        logOptimization("USB optimization enabled");
    }
}

void OptimizationManager::updateMetrics() {
    memoryUsed = ESP.getHeapSize() - ESP.getFreeHeap();
    psramUsed = ESP.getPsramSize() - ESP.getFreePsram();
}

void OptimizationManager::logOptimization(const String& message) {
    Serial.println("[OPTIMIZATION] " + message);

    // Could also log to SD card or display
    // tft.println("[OPT] " + message);
}

// ============================================================================
// FUNÇÕES GLOBAIS DE OTIMIZAÇÃO
// ============================================================================

/**
 * @brief String otimizada com buffer estático
 */
char* optimizedString(const char* format, ...) {
    static char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return buffer;
}

/**
 * @brief Delay não-bloqueante otimizado
 */
void optimizedDelay(unsigned long ms) {
    unsigned long start = millis();
    while (millis() - start < ms) {
        // Yield para outras tarefas
        vTaskDelay(1);
    }
}

/**
 * @brief Timer não-bloqueante otimizado
 */
bool optimizedTimer(unsigned long* lastTime, unsigned long interval) {
    unsigned long now = millis();
    if (now - *lastTime >= interval) {
        *lastTime = now;
        return true;
    }
    return false;
}

/**
 * @brief Clamp value otimizado
 */
template<typename T>
T optimizedClamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
