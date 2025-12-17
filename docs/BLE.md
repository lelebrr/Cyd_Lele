# 📶 Bluetooth Low Energy (BLE)

Documentação das funcionalidades Bluetooth do Lele Origin.

---

## 🔍 BLE Scan

Varredura de dispositivos Bluetooth Low Energy próximos.

**Informações coletadas:**
- Nome do dispositivo
- Endereço MAC
- RSSI (força do sinal)
- Serviços anunciados

**Como usar:**
1. Acesse **BLE → BLE Scan**
2. Aguarde a varredura
3. Toque em um dispositivo para mais detalhes

---

## ⌨️ Bad BLE

Executa scripts Ducky via Bluetooth, simulando um teclado BLE.

**Funcionalidades:**
- Emula teclado Bluetooth
- Executa scripts Rubber Ducky
- Compatível com todos os sistemas operacionais

**Como usar:**
1. Acesse **BLE → Bad BLE**
2. Selecione um script do SD Card ou LittleFS
3. Pareie o dispositivo com o alvo
4. Execute o script

> [!NOTE]
> Scripts devem estar em formato Ducky Script (.txt)

---

## 📱 BLE Spam

Envia pacotes de propaganda BLE para dispositivos próximos.

### iOS Spam
Spam de notificações em dispositivos Apple (iPhone, iPad).

**Tipos de notificação:**
- AirPods
- Apple TV
- HomePod
- Dispositivos personalizados

### Windows Spam
Spam de notificações em dispositivos Windows.

**Tipos:**
- Swift Pair (pareamento rápido)
- Dispositivos de áudio

### Samsung Spam
Spam em dispositivos Samsung Galaxy.

**Tipos:**
- Galaxy Buds
- SmartTag
- Watch

### Android Spam
Spam em dispositivos Android genéricos.

**Tipos:**
- Fast Pair
- Dispositivos de áudio

### Spam All
Executa todos os tipos de spam simultaneamente.

---

## 🎮 Como Usar o Spam

1. Acesse **BLE → [Tipo de Spam]**
2. O spam inicia automaticamente
3. Dispositivos próximos receberão notificações
4. Toque na tela para parar

> [!WARNING]
> Use apenas para testes em ambientes controlados. Spam pode ser irritante e ilegal em alguns contextos.

---

## ⚙️ Configurações BLE

O Lele configura automaticamente o BLE, mas você pode ajustar:

- **TX Power**: Potência de transmissão
- **Advertising Interval**: Intervalo de anúncios

---

## 📚 Protocolos Suportados

| Protocolo | Descrição |
|-----------|-----------|
| BLE 4.2 | Bluetooth Low Energy padrão |
| Fast Pair | Google Fast Pair |
| Swift Pair | Microsoft Swift Pair |
| Apple Continuity | Protocolo Apple para AirDrop, etc. |
