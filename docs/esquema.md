# 🔌 Esquema de Conexões – Fechadura Eletrônica RFID

Este documento descreve as conexões entre o **ESP32**, o módulo **RFID RC522**, o **LCD I2C**, o **módulo relé** e o **buzzer**.

---

## 📡 RFID RC522 → ESP32
| RFID RC522 | ESP32 |
|------------|-------|
| SDA        | GPIO 5  |
| SCK        | GPIO 18 |
| MOSI       | GPIO 23 |
| MISO       | GPIO 19 |
| RST        | GPIO 22 |
| 3.3V       | 3.3V   |
| GND        | GND    |

> ⚠️ Importante: o módulo RC522 deve ser alimentado em **3.3V**, não em 5V.

---

## 📺 LCD I2C (20x4) → ESP32
| LCD I2C | ESP32 |
|---------|-------|
| SDA     | GPIO 2 |
| SCL     | GPIO 4 |
| VCC     | 5V     |
| GND     | GND    |

> O endereço padrão do LCD I2C usado no projeto é `0x27`.

---

## 🔒 Módulo Relé → ESP32
| Relé | ESP32 |
|------|-------|
| IN   | GPIO 21 |
| VCC  | 5V      |
| GND  | GND     |

O relé é responsável por acionar a **trava solenoide** ou **fechadura elétrica**.  
O pino **IN** recebe sinal digital do ESP32 para abrir/fechar a trava.

---

## 🎵 Buzzer → ESP32
| Buzzer | ESP32 |
|--------|-------|
| Sinal  | GPIO 15 |
| VCC    | 3.3V / 5V |
| GND    | GND |

> O buzzer emite sons diferentes para acesso **liberado** ou **recusado**.
