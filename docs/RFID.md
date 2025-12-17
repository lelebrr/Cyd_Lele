# 💳 RFID/NFC

Documentação das funcionalidades RFID e NFC do Lele Origin.

---

## 🔧 Módulos Suportados

| Módulo | Frequência | Protocolo |
|--------|-----------|-----------|
| PN532 | 13.56 MHz | NFC (MIFARE, NTAG, etc.) |
| PN532 Killer | 13.56 MHz | NFC + Magic cards |
| MFRC522 | 13.56 MHz | MIFARE |
| Reader 125kHz | 125 kHz | EM4100, HID |

---

## 📖 Leitura de Tags

### Read Tag (13.56 MHz)
Lê cartões NFC de alta frequência.

**Tipos suportados:**
- MIFARE Classic 1K/4K
- MIFARE Ultralight
- NTAG213/215/216
- ISO14443-A

**Informações obtidas:**
- UID (Identificador único)
- SAK (Select Acknowledge)
- ATQA (Answer To Request A)
- Tipo de cartão
- Dados dos setores (se não protegido)

**Como usar:**
1. Conecte o módulo PN532
2. Acesse **RFID → Read Tag**
3. Aproxime o cartão do leitor
4. Os dados são exibidos na tela

### Read 125kHz
Lê cartões de baixa frequência.

**Tipos suportados:**
- EM4100
- HID Prox II
- Indala

---

## 📝 Escrita de Tags

### Clone Tag
Clona um cartão para outro cartão gravável.

**Requisitos:**
- Cartão original (para leitura)
- Cartão Magic/UID gravável (para escrita)

**Como usar:**
1. Leia o cartão original
2. Acesse **RFID → Clone Tag**
3. Aproxime o cartão gravável
4. Confirme a clonagem

### Write NDEF
Grava registros NDEF em tags NFC.

**Tipos de registros:**
- URL
- Texto
- vCard
- WiFi

### Write Data
Grava dados brutos em setores específicos.

### Erase Data
Apaga dados de tags graváveis.

---

## 💾 Gerenciamento de Arquivos

### Save File
Salva o dump do cartão no SD Card.

**Formato:** `.json` com estrutura legível

### Load File
Carrega um dump salvo para escrita ou análise.

---

## 🔐 Chameleon

Modo de emulação compatível com Chameleon Mini/Tiny.

**Funcionalidades:**
- Emular tags lidas
- Trocar entre múltiplas tags
- Log de comunicações

---

## 🎮 Amiibolink

Emulação de Amiibos para Nintendo Switch/3DS.

**Como usar:**
1. Obtenha dumps de Amiibo (`.bin`)
2. Copie para o SD Card
3. Acesse **RFID → Amiibolink**
4. Selecione o Amiibo
5. Aproxime do console

---

## 🛠️ Configuração

Acesse **RFID → Config** para ajustar:

| Opção | Descrição |
|-------|-----------|
| RFID Module | Tipo de módulo conectado |

**Pinagem PN532 (I2C):**

| PN532 | CYD-2USB |
|-------|----------|
| SDA | GPIO 27 |
| SCL | GPIO 22 |
| VCC | 3.3V |
| GND | GND |

---

## 📚 Tipos de Cartões

### MIFARE Classic
| Variante | Memória | Setores | Uso |
|----------|---------|---------|-----|
| 1K | 1024 bytes | 16 | Acesso, transporte |
| 4K | 4096 bytes | 40 | Uso geral |

### MIFARE Ultralight
| Variante | Memória | Páginas | Uso |
|----------|---------|---------|-----|
| UL | 64 bytes | 16 | Tickets descartáveis |
| UL C | 192 bytes | 48 | Tickets com criptografia |

### NTAG
| Variante | Memória | Uso |
|----------|---------|-----|
| 213 | 144 bytes | NFC Tags básicas |
| 215 | 504 bytes | Amiibos |
| 216 | 888 bytes | Dados maiores |

---

## ⚠️ Notas Importantes

> [!WARNING]
> **Cartões de transporte**: Clonar cartões de transporte pode ser ilegal. Use apenas para fins educacionais.

> [!NOTE]
> **Chaves padrão**: Muitos cartões MIFARE Classic usam chaves padrão (FFFFFFFFFFFF). O Lele tenta automaticamente.

> [!TIP]
> **Magic cards**: Para clonar o UID, você precisa de cartões "Magic" que permitem escrita do bloco 0.
