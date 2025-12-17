# 🔨 Compilação

Guia para compilar o firmware Lele Origin.

---

## 📋 Requisitos

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO Extension](https://platformio.org/install/ide?install=vscode)

---

## 🔧 Configuração

1. Abra a pasta do projeto no VS Code
2. Aguarde o PlatformIO baixar as dependências

---

## 🏗️ Compilando

### Via Interface
1. Clique no PlatformIO (barra lateral)
2. **CYD-2USB → Build**

### Via Terminal
```bash
pio run -e CYD-2USB
```

---

## 📤 Upload

### Via Interface
Clique em **Upload** no PlatformIO

### Via Terminal
```bash
pio run -e CYD-2USB -t upload
```

### Via esptool
```bash
esptool.py --port COM3 write_flash 0x00000 firmware.bin
```

---

## 🔍 Monitor Serial

```bash
pio device monitor
```
Baud rate: 115200

---

## 🐛 Problemas Comuns

| Problema | Solução |
|----------|---------|
| Porta não encontrada | Instale driver CH340/CP2102 |
| Memória insuficiente | Use versão LITE |
| Permissão negada (Linux) | `sudo usermod -a -G dialout $USER` |
