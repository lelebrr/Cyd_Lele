# 🦎 Lele Origin 1.0

<p align="center">
  <strong>Firmware versátil para ESP32 focado em operações de segurança ofensiva</strong>
</p>

---

## 📋 Sobre

O **Lele Origin** é um firmware ESP32 com múltiplas funcionalidades ofensivas para profissionais de segurança e entusiastas. Desenvolvido especificamente para a placa **CYD-2USB**.

### ✨ Funcionalidades Principais

| Módulo | Recursos | Ataques |
|--------|----------|---------|
| 📡 **WiFi** | Scan, Evil Portal, Wardriving | 40 (CVE-2024, PMKID) |
| 📶 **BLE** | Scan, spam, BrakTooth | 24 (4 combos) |
| 🔌 **USB** | BadUSB, Payloads, HID | 10 |
| 📻 **RF** | CC1101, NRF24, SubGhz | replay |
| 💳 **RFID** | Leitura, clonagem, NDEF | - |
| 📺 **IR** | TV-B-Gone, 40+ marcas | 1 |
| 💡 **LEDs** | 16 efeitos WS2812B | - |
| 🌡️ **Temp** | DS18B20, alertas | - |

**Total: 75+ ataques implementados**

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
