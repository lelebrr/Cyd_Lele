# ⚡ Início Rápido

Guia para começar a usar o Lele Origin 1.0 na sua placa CYD-2USB.

---

## 📦 O Que Você Precisa

- Placa **CYD-2USB** (ESP32 com display 2.8" touchscreen)
- Cabo USB para programação
- Computador com Windows, Linux ou macOS

---

## 🔧 Instalação

### Método 1: Web Flasher (Mais Fácil)

1. Acesse o Web Flasher no navegador Chrome/Edge
2. Conecte a placa CYD-2USB via USB
3. Selecione a porta COM correta
4. Clique em "Flash" e aguarde

### Método 2: Compilação Local

Consulte o guia [Compilação](COMPILACAO.md) para instruções detalhadas.

### Método 3: esptool.py

```bash
esptool.py --port COM3 write_flash 0x00000 Lele-CYD-2USB.bin
```

---

## 🎮 Primeiro Uso

### Navegação

- **Toque no display**: Selecionar opções
- **Deslize**: Navegar entre menus
- **Pressione e segure**: Opções adicionais

### Menu Principal

Após a inicialização, você verá o menu principal com as seguintes opções:

| Ícone | Função |
|-------|--------|
| 📡 | WiFi - Ferramentas de rede sem fio |
| 📶 | BLE - Bluetooth Low Energy |
| 📻 | RF - SubGhz e NRF24 |
| 💳 | RFID - Leitura de cartões NFC |
| 📺 | IR - Controle infravermelho |
| ⚙️ | Config - Configurações do sistema |

---

## 🔌 Conexões de Hardware

### Módulos Externos Suportados

| Módulo | Uso | Pinos Recomendados |
|--------|-----|-------------------|
| CC1101 | SubGhz RF | GDO0:22, SS:27 |
| NRF24 | 2.4GHz | CE:22, SS:27 |
| PN532 | RFID/NFC | I2C (SDA:27, SCL:22) |
| IR LED | Transmissor | GPIO 22 ou 27 |
| IR Receiver | Receptor | GPIO 35 |

---

## ⚡ Dicas Rápidas

1. **Conectar WiFi**: Menu WiFi → Connect to WiFi → Selecione sua rede
2. **Ajustar Brilho**: Config → Brightness
3. **Mudar Orientação**: Config → Orientation
4. **Ver Informações**: Pressione e segure no menu principal

---

## 📚 Próximos Passos

- Explore as [Funcionalidades](FUNCIONALIDADES.md) disponíveis
- Configure o [Hardware](HARDWARE.md) adicional
- Aprenda sobre [Ataques WiFi](WIFI.md)
