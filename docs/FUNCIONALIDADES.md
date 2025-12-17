# 🎯 Funcionalidades

Lista completa de funcionalidades disponíveis no Lele Origin 1.0.

---

## 📡 WiFi

| Função | Descrição |
|--------|-----------|
| Connect to WiFi | Conectar a uma rede WiFi |
| WiFi AP | Criar ponto de acesso |
| Disconnect WiFi | Desconectar da rede |
| **WiFi Atks** | Ataques WiFi |
| ↳ Beacon Spam | Criar redes falsas |
| ↳ Target Atk | Ataque direcionado |
| ↳ Deauth Flood | Desautenticação em massa |
| Wardriving | Mapeamento de redes |
| TelNet | Cliente Telnet |
| SSH | Cliente SSH |
| RAW Sniffer | Captura de pacotes |
| TCP Client | Cliente TCP |
| TCP Listener | Servidor TCP |
| Evil Portal | Portal cativo falso |
| Scan Hosts | Varredura de hosts |
| Wireguard | Túnel VPN |
| Lelegotchi | Modo Pwnagotchi |

---

## 📶 Bluetooth (BLE)

| Função | Descrição |
|--------|-----------|
| BLE Scan | Varredura de dispositivos |
| Bad BLE | Scripts Ducky via BLE |
| iOS Spam | Spam em iPhones |
| Windows Spam | Spam em Windows |
| Samsung Spam | Spam em Samsung |
| Android Spam | Spam em Android |
| Spam All | Spam em todos |

---

## 📻 RF (Rádio Frequência)

| Função | Descrição |
|--------|-----------|
| Scan/Copy | Captura de sinais |
| Custom SubGhz | Sinais personalizados |
| Spectrum | Analisador de espectro |
| Jammer Full | Jammer onda quadrada |
| Jammer Intermittent | Jammer PWM |
| Replay | Reproduzir sinais |
| **Config** | Configurações |
| ↳ RF TX Pin | Pino de transmissão |
| ↳ RF RX Pin | Pino de recepção |
| ↳ RF Module | Módulo (CC1101/RF433) |
| ↳ RF Frequency | Frequência |

---

## 💳 RFID/NFC

| Função | Descrição |
|--------|-----------|
| Read Tag | Ler cartão NFC |
| Read 125kHz | Ler cartão 125kHz |
| Clone Tag | Clonar cartão |
| Write NDEF | Gravar registros NDEF |
| Amiibolink | Emulação Amiibo |
| Chameleon | Modo Chameleon |
| Write Data | Gravar dados |
| Erase Data | Apagar dados |
| Save File | Salvar em arquivo |
| Load File | Carregar arquivo |

---

## 📺 Infravermelho (IR)

| Função | Descrição |
|--------|-----------|
| TV-B-Gone | Desligar TVs |
| IR Receiver | Capturar sinais IR |
| Custom IR | Sinais personalizados |
| **Config** | Configurações |
| ↳ IR TX Pin | Pino de transmissão |
| ↳ IR RX Pin | Pino de recepção |

**Protocolos suportados**: NEC, NECext, SIRC, SIRC15, SIRC20, Samsung32, RC5, RC5X, RC6

---

## 📻 NRF24 (2.4GHz)

| Função | Descrição |
|--------|-----------|
| NRF24 Jammer | Jammer 2.4GHz |
| 2.4G Spectrum | Analisador de espectro |
| Mousejack | Ataque Mousejack (em desenvolvimento) |

---

## 📻 FM Radio

| Função | Descrição |
|--------|-----------|
| Broadcast Standard | Transmissão padrão |
| Broadcast Reserved | Transmissão reservada |
| Broadcast Stop | Parar transmissão |

---

## 📝 Scripts

| Função | Descrição |
|--------|-----------|
| JavaScript Interpreter | Executar scripts JS |

---

## 🔧 Outros

| Função | Descrição |
|--------|-----------|
| Mic Spectrum | Analisador de áudio |
| QRCodes | Gerar QR Codes |
| ↳ Custom | QR personalizado |
| ↳ PIX | QR Code PIX |
| SD Card Mngr | Gerenciador de arquivos |
| LittleFS Mngr | Gerenciador interno |
| WebUI | Interface web |
| Megalodon | Ferramenta Megalodon |
| BADUsb | Scripts USB maliciosos |
| iButton | Leitor iButton |
| LED Control | Controle de LEDs |

---

## ⏰ Relógio

| Função | Descrição |
|--------|-----------|
| RTC Support | Suporte a RTC |
| NTP Adjust | Sincronizar via internet |
| Manual Adjust | Ajuste manual |

---

## 🔗 Connect (ESP-NOW)

| Função | Descrição |
|--------|-----------|
| Send File | Enviar arquivo |
| Receive File | Receber arquivo |
| Send Commands | Enviar comandos |
| Receive Commands | Receber comandos |

---

## ⚙️ Configurações

| Função | Descrição |
|--------|-----------|
| Brightness | Brilho da tela |
| Dim Time | Tempo para escurecer |
| Orientation | Orientação da tela |
| UI Color | Cor da interface |
| Boot Sound | Som de inicialização |
| Clock | Configurar relógio |
| Sleep | Modo de espera |
| Restart | Reiniciar dispositivo |

---

## 💡 Iluminação (LEDs RGB WS2812B)

> Menu dedicado para controle de 4 LEDs RGB endereçáveis

### Opções Disponíveis

| Opção | Descrição |
|-------|-----------|
| **Ligar/Desligar** | Controle geral dos LEDs |
| **Cor** | 9 cores predefinidas (vermelho, verde, azul, amarelo, ciano, magenta, branco, laranja, roxo) |
| **Selecionar LED** | Controle individual (LED 1-4) ou todos simultaneamente |
| **Efeitos** | 8 animações diferentes |
| **Brilho** | 5 níveis (10%, 25%, 50%, 75%, 100%) |
| **Notificações** | Configurar feedback visual para eventos |
| **Testar LEDs** | Sequência de teste RGBW |

### Efeitos Disponíveis

| Efeito | Descrição |
|--------|-----------|
| Estático | Cor fixa sem animação |
| Piscar | Liga/desliga alternadamente |
| Fade | Transição suave de intensidade |
| Arco-Íris | Ciclo de cores do espectro |
| Respirar | Efeito pulsante suave |
| Scanner | Movimento tipo Knight Rider |
| Aleatório | Cores randômicas |
| Perseguir | Padrão alternado em movimento |

### Notificações Visuais

O sistema pode usar os LEDs para feedback visual:
- 🔴 **Erro**: Vermelho piscando
- 🟢 **Sucesso**: Verde piscando
- 🟡 **Aviso**: Amarelo piscando
- 🔵 **Captura**: Azul pulsando

---

## 🌡️ Sensor de Temperatura

> Monitoramento da temperatura das baterias com alertas configuráveis

**Localização:** Config → Sensor Temperatura

### Funcionalidades

| Opção | Descrição |
|-------|-----------|
| **Status** | Exibe se sensor foi detectado e temperatura atual |
| **Temp. Máxima** | Define limite crítico (40°C, 45°C, 50°C, 55°C) |
| **Tipo de Alerta** | LED, Tela, Som ou Todos |
| **Ação ao Atingir** | Avisar, Pausar operações ou Desligar módulos |
| **Na Barra** | Exibir temperatura na barra superior |
| **Salvar Config** | Persistir configurações |

### Sistema Fail-Safe

O sistema funciona **mesmo sem o sensor conectado**:
- Detecta automaticamente se DS18B20 está presente
- Exibe "Não Encontrado" se ausente
- Não impede o uso de outras funções
- Bibliotecas OneWire/DallasTemperature são opcionais

### Limites de Temperatura

| Nível | Temperatura | Ação |
|-------|-------------|------|
| **Normal** | < 35°C | Operação normal |
| **Aviso** | 35-44°C | Alerta amarelo |
| **Crítico** | 45-49°C | Alerta vermelho |
| **Desligamento** | ≥ 50°C | Ação configurada |
