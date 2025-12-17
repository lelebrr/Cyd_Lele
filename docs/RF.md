# 📻 RF (Rádio Frequência)

Documentação das funcionalidades de RF, CC1101 e NRF24 do Lele Origin.

---

## 🔧 Módulos Suportados

| Módulo | Frequência | Uso |
|--------|-----------|-----|
| CC1101 | 300-928 MHz | SubGhz (controles, sensores) |
| RF433 | 433 MHz | Controles simples |
| NRF24L01 | 2.4 GHz | Dispositivos wireless |

---

## 📡 CC1101 (SubGhz)

### Scan/Copy
Captura sinais RF e permite replay.

**Frequências comuns:**
- 315 MHz (EUA)
- 433 MHz (Europa, Brasil)
- 868 MHz (Europa)
- 915 MHz (EUA)

**Como usar:**
1. Conecte o módulo CC1101
2. Acesse **RF → Scan/Copy**
3. Selecione a frequência
4. Pressione o botão do controle original
5. O sinal é capturado

### Custom SubGhz
Carrega e reproduz sinais salvos em formato compatível com Flipper Zero.

**Formatos suportados:**
- `.sub` (Flipper Zero)
- `.txt` (RAW)

**Como usar:**
1. Copie os arquivos para o SD Card (pasta `/subghz/`)
2. Acesse **RF → Custom SubGhz**
3. Selecione o arquivo
4. Reproduza o sinal

### Spectrum
Analisador de espectro para visualizar atividade RF.

**Faixas disponíveis:**
- 300-348 MHz
- 387-464 MHz
- 779-928 MHz

### Jammer Full
Envia onda quadrada contínua na frequência selecionada.

> [!CAUTION]
> Jammers são ilegais na maioria dos países. Use apenas em ambientes isolados para testes.

### Jammer Intermittent
Envia sinal PWM intermitente.

### Replay
Reproduz o último sinal capturado.

---

## 🛠️ Configuração CC1101

Acesse **RF → Config** para ajustar:

| Opção | Descrição |
|-------|-----------|
| RF TX Pin | GPIO de transmissão (GDO0) |
| RF RX Pin | GPIO de recepção |
| RF Module | Tipo de módulo (CC1101/RF433) |
| RF Frequency | Frequência de operação |

**Pinagem padrão CC1101:**

| CC1101 | CYD-2USB |
|--------|----------|
| GDO0 | GPIO 22 |
| CSN | GPIO 27 |
| MOSI | GPIO 23 |
| SCK | GPIO 18 |
| MISO | GPIO 19 |
| VCC | 3.3V |
| GND | GND |

---

## 📡 NRF24L01 (2.4GHz)

### NRF24 Jammer
Interfere em comunicações 2.4GHz.

**Alvos potenciais:**
- Mouses/teclados wireless
- Drones
- Dispositivos IoT

### 2.4G Spectrum
Analisador de espectro para banda 2.4GHz.

**Canais:**
- 0-125 (2400-2525 MHz)

### Mousejack
Ataque a mouses e teclados wireless vulneráveis.

> [!NOTE]
> Funcionalidade em desenvolvimento.

---

## 🛠️ Configuração NRF24

**Pinagem padrão NRF24:**

| NRF24 | CYD-2USB |
|-------|----------|
| CE | GPIO 22 |
| CSN | GPIO 27 |
| MOSI | GPIO 23 |
| SCK | GPIO 18 |
| MISO | GPIO 19 |
| VCC | 3.3V |
| GND | GND |

> [!WARNING]
> **Tensão**: O NRF24L01 opera em 3.3V. Nunca conecte 5V!

---

## 📁 Formato de Arquivos

### Flipper Zero (.sub)
```
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 12 34 56
```

### RAW (.txt)
```
RAW_Data: 500 -500 500 -500 ...
```

---

## 📚 Protocolos Suportados

| Protocolo | Uso |
|-----------|-----|
| Princeton | Controles genéricos |
| Nice FLO | Portões Nice |
| CAME | Portões CAME |
| Linear | Controles Linear |
| Holtek | Controles baratos |
| PT2262 | Sensores, alarmes |
