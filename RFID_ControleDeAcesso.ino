
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

#include <Servo.h>
#define SERVO 3 // Porta Digital 3 PWM
Servo s;
int pos;
int registro = 0;
int j = 90;

#define endereco  0x27 // Endereços comuns: 0x27, 0x3F
#define colunas   16
#define linhas    2
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

void setup() {
  lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.clear();
  lcd.print("     JACOB     ");
  lcd.setCursor(0, 1);
  lcd.print("   TECNOLOGIA   ");
  
  Serial.begin(9600); //INICIALIZA A SERIAL
  SPI.begin(); //INICIALIZA O BARRAMENTO SPI
  rfid.PCD_Init(); //INICIALIZA MFRC522

  s.attach(SERVO);
  s.write(90);
  }

void loop() {


  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
  return;
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Identificador (UID) da tag: "); 
  Serial.println(strID); 
  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1(); 

  if (strID == "E0:1B:7C:0A" ){

     lcd.clear();
      lcd.print("   BEM VINDO!   ");
      lcd.setCursor(0, 1);
      lcd.print("ACESSO LIBERADO");
      delay(500);
    
    for (int j = 90; j > 0; j--) {
      s.write(j);
      delay(25);
    }
      
      lcd.print("   BEM VINDO!   ");
      lcd.setCursor(0, 1);
      lcd.print("ACESSO LIBERADO");
      delay(4000);

    for (int j = 0; j < 90; j++) {
      s.write(j);
      delay(25);
      
    }
      lcd.clear();
      lcd.print(" APROXIME O SEU ");
      lcd.setCursor(0, 1);
      lcd.print("   CARTAO...    ");
     
  }

  if (strID != "E0:1B:7C:0A" ){

    lcd.clear();
    lcd.print(" ACESSO NEGADO! ");
  }
      delay(1500);
      lcd.clear();
      lcd.print(" APROXIME O SEU ");
      lcd.setCursor(0, 1);
      lcd.print("   CARTAO...    ");

 
}
