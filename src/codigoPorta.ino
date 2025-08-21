/* MUDANÇAS: 
 * - funções foram trazidas para frente por causa de escopo
 * - ao invés de colocar mais um if else manualmente na verificação, ele faz isso através de um loop, isso ajuda na hora de 
 *   criar ou remover acesso de membros, além de deixar o código mais organizado
 * - foi criada uma lista de usuarios
*/
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

  
// Definindo pinos
#define SS_PIN 5      // SDA do RFID
#define RST_PIN 22    // RST do RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int buzzerPin = 15;  // Defina o pino que o buzzer está conectado

LiquidCrystal_I2C lcd(0x27,20, 4); 
char st[20];


// Structs ajudam na organização de dados. Eles são similares a classes, mas mais simples
struct membro   
{
  String uid;
  String nome;
  String apelido;
  uint8_t cursorPosX; //Posição do cursor LCD
  uint8_t cursorPosY;
};

// Para adicionar ou remover membros, é só colocar os dados nessa lista em ordem:
// uid, nome, apelido, posição X do cursor LCD, posição Y do cursor LCD
membro listaMembros[] = {
  {"00 00 00 00", "Default", "Default", 0, 0}, //Membro DEFAULT, ele nunca deve ser usado, se ele for, algo deu errado
  {"73 17 6D FA", "Presidente", "Presidente", 2, 0},
  {"F3 C7 50 FA", "Presidente", "Presidente", 2, 0},
  {"02 92 6D B4", "Ceolin", "Ceolin", 2, 0 },
  {"5B 73 42 F0", "JP", "JP", 0, 0},
  {"0E F3 4A A0", "Vini", "Vini", 0, 0},
  {"AE 06 4B A0", "Leone", "Leone", 0, 0},
  {"72 38 53 13", "Correa", "Correa", 4, 0},
  {"F2 38 53 4A", "Eliton", "Eliton", 0, 0},
  {"EE 00 25 A0", "Bispo", "Bispo", 0, 0},
  {"A0 50 69 50", "Matheus", "Matheus", 5, 0},
  {"C1 C5 7D 44", "Marcolino", "Marcolino", 0, 0 },
  {"5B F1 14 F0", "Schemes", "Schemes", 0, 0}
};

void mensageminicial()
{
  lcd.clear();
  lcd.setCursor(0,0);            //lcd.setCursor(0,0);
  lcd.print("PLUS ENERGY");
  Serial.println("PLUS ENERGY"); 
  lcd.setCursor(0,1);
  lcd.print("Leia seu cartao");
  Serial.println("Leia seu cartao"); 
}

void playTone(int frequency, int duration) {
  ledcWriteTone(0, frequency);  // Define a frequência
  delay(duration);              // Toca a nota pela duração especificada
  ledcWriteTone(0, 0);          // Para o som
  delay(50);                    // Pequena pausa entre as notas
}

void LIBERADO()
{       
  digitalWrite(21, LOW);  // ativa rele, abre a trava solenoide
  lcd.setCursor(0,1);
  lcd.print("Acesso Liberado");
  Serial.print("Acesso Liberado"); 
  digitalWrite(21, HIGH); // desativa rele, fecha a trava solenoide
  playTone(622, 300);
  playTone(740, 300);
  playTone(988, 350);     
  digitalWrite(21, HIGH); // desativa rele, fecha a trava solenoide
  lcd.setCursor(0,1);
  lcd.print("   Bem-vindo!   ");
  Serial.print("   Bem-vindo!   "); 
  delay(3000);
  lcd.clear();
  mensageminicial();
}

void RECUSADO()
{ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("XXXX Acesso XXXX");
  lcd.setCursor(0,1);
  lcd.print("XXX Recusado XXX");
  //tone(8,131,100); //DS5
  //delay(150);
  //tone(8,131,100); //FS5
  //delay(150);

  lcd.setCursor(0,0);
  lcd.print("     Acesso     ");
  lcd.setCursor(0,1);
  lcd.print("    Recusado    "); 
  //tone(8,65,300); //DS5
  //delay(300);

  lcd.setCursor(0,0);
  lcd.print("XXXX Acesso XXXX");
  lcd.setCursor(0,1);
  lcd.print("XXX Recusado XXX"); 
  delay(400);

  lcd.setCursor(0,0);
  lcd.print("     Acesso     ");
  lcd.setCursor(0,1);
  lcd.print("    Recusado    "); 
  delay(300);

  lcd.setCursor(0,0);
  lcd.print("XXXX Acesso XXXX");
  lcd.setCursor(0,1);
  lcd.print("XXX Recusado XXX"); 
  delay(400);

  lcd.setCursor(0,0);
  lcd.print("     Acesso     ");
  lcd.setCursor(0,1);
  lcd.print("    Recusado    "); 
  delay(300);
  
  lcd.setCursor(0,0);
  lcd.print("XXXX Acesso XXXX");
  lcd.setCursor(0,1);
  lcd.print("XXX Recusado XXX"); 
  delay(1000);

  lcd.clear();
  mensageminicial();
}

void setup() 
{
  Serial.begin(115200);   // Inicia a serial
  Wire.begin(2, 4);
  SPI.begin();          // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  // Configura o canal PWM (canal 0), e o pino do buzzer
  /*ledcSetup(0, 2000, 8);   // Canal 0, base de 2000 Hz, 8 bits de resolução
  ledcAttachPin(buzzerPin, 0); */ // Conecta o canal PWM ao pino do buzzer
  pinMode(21, OUTPUT);
  lcd.init();
  lcd.backlight(); // Liga o bac  klight do LCD
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  mensageminicial();
}

void abrirPorta(membro membro) {
  Serial.println("Ola " + membro.nome + "!"); 
  Serial.println();
  lcd.clear();
  lcd.setCursor(membro.cursorPosX, membro.cursorPosY);
  lcd.print(membro.apelido);
  LIBERADO();
}
 
void loop() 
{
  digitalWrite(21, HIGH);
  // Procura por cartao RFID
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona o cartao RFID
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  delay(1500);
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  

  int loopSize = 15;
  bool isMembroEncontrado = false;
  //0 é o membro default, caso ele aparecer, algo deu errado na verificação
  int membroIndex = 0;
  String uidRef = conteudo.substring(1);

  for (int i = 1; i <= loopSize; i++){
    if (uidRef == listaMembros[i].uid){
      isMembroEncontrado = true;
      membroIndex = i;
      break;
    }
  }

  if (isMembroEncontrado) {
    abrirPorta(listaMembros[membroIndex]);
  } else {
    RECUSADO();
  }

}


