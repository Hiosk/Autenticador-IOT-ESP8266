#include <LiquidCrystal_I2C.h>

#include "Keypad.h"
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {D1, D2, D3, D4}; 
byte colPins[COLS] = {D5, D6, D7, D8}; 


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

char cpf[16];

void setup() {
  Serial.begin(9600); // Inicializa serial monitor
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Informe o CPF:");
}

void loop() {
  lcd.setCursor(0, 0);
  char key = keypad.getKey();
  if (key){
    if(key == 'A') {
      if(strlen(cpf) != 11) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("CPF Invalido");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Informe o CPF:");
        lcd.setCursor(0, 1);
        lcd.print(cpf);
        Serial.println(cpf);
      }
    }
    else if(key == 'C') {
      memset(cpf,0,strlen(cpf));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Informe o CPF:");
      lcd.setCursor(0, 1);
      lcd.print(cpf);
      Serial.println(cpf);
    }
    else if(key == 'B') {
      cpf[strlen(cpf)-1] = '\0';
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Informe o CPF:");
      lcd.setCursor(0, 1);
      lcd.print(cpf);
      Serial.println(cpf);
    }
    else {
      strncat(cpf, &key, 1);
      lcd.setCursor(0, 1);
      lcd.print(cpf);
      Serial.println(cpf);
    }
  }
}
