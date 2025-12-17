# 🔧 Módulos de Ataque - Lele Origin 1.0

Documentação dos módulos de ataque funcionais.

---

## 📊 Resumo

| Categoria | Ataques |
|-----------|---------|
| WiFi | 40 |
| BLE Spam | 7 |
| USB | 10 |
| IR | 1 |
| **Total** | **58** |

---

## 🌐 WiFi

### Ataques CVE 2024 (20 ataques DoS/CVE)

| Ataque | CVE/Base | Alvo |
|--------|----------|------|
| MediaTek SoftAP DoS | CVE-2024-20017 | Netgear, Xiaomi, Ubiquiti |
| SSID Confusion | CVE-2023-52424 | Redes mistas WPA2/WPA3 |
| FragAttacks 2024 | FragAttacks | APs não patchados |
| Auth Flood DoS | 2024 variant | TP-Link, Asus antigos |
| Disassoc Flood | WPA3 effective | APs WPA3 |
| Beacon Fuzzing | Tag overflow | MediaTek, Realtek |
| Channel Hop Deauth | Storm | Dual-band |
| Mgmt Frame Crash | Fuzzing 2025 | Firmwares vulneráveis |

### Captura Avançada (20 ataques)

| Ataque | Técnica | Sucesso |
|--------|---------|---------|
| PMKID Clientless | 2018-2025 | Alto em roaming |
| Multi-Target PMKID | Batch | Em massa |
| Handshake Passivo | Sniffing | 100% em ativas |
| Deauth + Capture | Clássico | Muito alto |
| Evil Twin Downgrade | WPA3→WPA2 | Em transition mode |

---

## 📶 BLE Spam (7 ataques - OTIMIZADO)

> **OTIMIZADO**: 3.5x mais rápido que versão padrão!

| Ataque | Descrição | Status |
|--------|-----------|--------|
| Applejuice | iOS popup spam | ✅ Otimizado |
| SourApple | iOS crash | ✅ Otimizado |
| Spam Windows | Swift Pair popup | ✅ Otimizado |
| Spam Samsung | SmartThings popup | ✅ Otimizado |
| Spam Android | Fast Pair popup | ✅ Otimizado |
| Spam Todos | Todos os modos | ✅ Otimizado |
| Spam Personalizado | Payload custom | ✅ Otimizado |

---

## 🔌 USB (10 payloads)

| Payload | Função | Status |
|---------|--------|--------|
| BadUSB Script | Ducky scripts | ✅ Funcional |
| Reverse Shell | Shell reverso PS | ✅ Funcional |
| WiFi Stealer | Exporta senhas WiFi | ✅ Funcional |
| Browser Creds | Extrai senhas | ✅ Funcional |
| Disable Defender | Desativa AV | ✅ Funcional |

---

## 📺 IR

### TV Nuke

40+ marcas suportadas: Samsung, LG, Sony, Philips, Panasonic, etc.

---

## ⚠️ Avisos

> [!WARNING]
> **Uso educacional apenas!**
> Todos os ataques devem ser usados somente em dispositivos autorizados.
