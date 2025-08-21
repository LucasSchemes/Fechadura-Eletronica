# 🔐 Fechadura Eletrônica RFID com ESP32

Este projeto implementa uma fechadura eletrônica utilizando **ESP32**, **leitor RFID (MFRC522)**, **LCD I2C** e um **módulo relé** para controlar a trava.  
O sistema possui autenticação baseada em cartões RFID cadastrados em uma lista de membros.

---

## ⚙️ Funcionalidades
- Autenticação via cartão RFID.
- Lista de usuários cadastrados (fácil adicionar/remover).
- Exibição de mensagens no display LCD.
- Controle de relé para abrir/fechar a fechadura.
- Sinalização sonora via buzzer.
- Mensagens de status no monitor serial.

---

## 🔌 Componentes Utilizados
- ESP32
- Leitor RFID **MFRC522**
- Display LCD 20x4 com interface **I2C**
- Módulo Relé (para a trava)
- Buzzer

---

## 📜 Como usar
1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/fechadura-eletronica-rfid.git
   
   
2. Abra a pasta src/ e carregue o código fechadura_rfid.ino no Arduino IDE ou PlatformIO.

3. Instale as bibliotecas necessárias:
MFRC522
LiquidCrystal_I2C
Wire

4. Ajuste os pinos conforme seu hardware (SS, RST, buzzer, relé).

5. Grave no ESP32 e aproxime um cartão RFID para testar.
