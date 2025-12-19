> 📅 **Última atualização:** 2025-12-19

## 📖 Índice de Documentação

| Documento | Descrição |
|-----------|-----------|
| [Início Rápido](INICIO_RAPIDO.md) | Como começar a usar o Lele |
| [**Hardware**](HARDWARE.md) | **Especificações, pinouts e conexões** |
| [Estrutura do Projeto](ESTRUTURA.md) | Mapa de todas as pastas e arquivos |
| [Funcionalidades](FUNCIONALIDADES.md) | Lista completa de recursos |
| [Ataques](ATAQUES.md) | Documentação técnica de todos os ataques |
| [USB & Fault Injection](USB_ATTACKS.md) | BadUSB, HID e Fault Injection |
| [WiFi](WIFI.md) | Ataques e ferramentas WiFi |
| [Bluetooth](BLE.md) | Funcionalidades BLE |
| [RF/SubGhz](RF.md) | CC1101, NRF24 e RF433 |
| [Iluminação](LEDS.md) | LEDs WS2812B e efeitos |
| [RFID/NFC](RFID.md) | Leitura e clonagem de tags |
| [Infravermelho](IR.md) | TV-B-Gone e controle IR |
| [Configuração](CONFIGURACAO.md) | Ajustes e preferências |
| [Compilação](COMPILACAO.md) | Como compilar o firmware |
| [Contribuidores](CONTRIBUIDORES.md) | Créditos e agradecimentos |

---

## 🔧 Lista de Componentes do Projeto

### Módulos Principais

| Componente | Modelo | Interface |
|------------|--------|-----------|
| 🖥️ Placa Principal | CYD-2USB (ESP32 2.8" Touch) | - |
| 📡 GPS | NEO-6M + Antena Externa | UART |
| 💳 NFC/RFID | PN532 V3 Red | I2C |
| 📻 RF SubGHz | CC1101 + Antena SMA 433MHz | SPI |
| 📡 RF 2.4GHz | NRF24L01+PA+LNA | SPI |
| 🌡️ Temperatura | DS18B20 TO-92 | 1-Wire |
| 🔴 Infravermelho | YS-IRTM | UART |
| 💾 Armazenamento | SD Card 128GB C10 | SPI |
| 🔊 Áudio | Speaker 4Ω 1.25W | Dedicado |
| 🔋 Alimentação | 18650 Shield V9 (4 bat) | 5V |

### Componentes Passivos Necessários

| Componente | Valor | Para |
|------------|-------|------|
| Resistor | 4.7kΩ 1/4W | DS18B20 pull-up |
| Capacitor | 10-100µF 16V | NRF24L01 estabilidade |
| Capacitor | 100nF 25V (x3) | Desacoplamento |
| Level Shifter | BSS138 4ch | YS-IRTM (5V↔3.3V) |
| Diodo | 1N5817 Schottky | Proteção polaridade |
| Fusível | PTC 500mA | Proteção curto |
| Switches | SPST (x5) | Liga/desliga módulos |

> **Detalhes completos em [HARDWARE.md](HARDWARE.md)**

---

## 🚀 Sobre o Lele Origin

O Lele Origin nasceu da necessidade de ter uma ferramenta versátil e acessível para profissionais de segurança. Baseado no excelente trabalho do projeto Lele, foi adaptado especificamente para a placa **CYD-2USB** (ESP32 com display touchscreen).

### Características Principais

- 📡 **WiFi**: Scan, ataques, Evil Portal, Wardriving
- 📶 **Bluetooth**: Scan, spam, Bad BLE
- 🔌 **RF/SubGhz**: CC1101, NRF24, replay de sinais
- 💳 **RFID/NFC**: Leitura, clonagem, emulação
- 📺 **Infravermelho**: TV-B-Gone, gravação e replay
- 🎮 **Scripts**: Interpretador JavaScript
- 🌡️ **Sensores**: Temperatura das baterias
- 📍 **GPS**: Wardriving e localização

---

## ⚠️ Aviso Legal

O Lele Origin é uma ferramenta para operações de segurança ofensiva e Red Team, distribuída sob os termos da Licença Pública Geral Affero (AGPL).

**Destina-se apenas para testes de segurança legais e autorizados.** O uso deste software para atividades maliciosas ou não autorizadas é estritamente proibido.

Ao baixar, instalar ou usar o Lele, você concorda em cumprir todas as leis e regulamentos aplicáveis. Os desenvolvedores não assumem nenhuma responsabilidade pelo uso indevido do software.

**Use por sua conta e risco.**
