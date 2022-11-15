#include <LiquidCrystal_I2C.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "hiosk";
const char* password = "06032001";

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
char senha[16];

int optCpfSenha = 0;

void setup() {
  Serial.begin(9600); // Inicializa serial monitor
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao wifi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado à rede WiFi com endereço IP: ");
  Serial.println(WiFi.localIP());
  
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Informe o CPF:");
}

void autenticar() {
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, "http://192.168.1.207:3000/autenticar");

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "cpf=" + String(cpf) + "&senha=" + String(senha);

    int httpResponseCode = http.POST(httpRequestData);
    
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println(http.getString());

    memset(cpf,0,strlen(cpf));
    memset(cpf,0,strlen(senha));
    lcd.clear();
    optCpfSenha = 0;

    memset(cpf,0,strlen(cpf));
    memset(senha,0,strlen(senha));
    
    lcd.print(http.getString());
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("Informe o CPF:");
    lcd.setCursor(0, 1);
    
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void loop() {
  lcd.setCursor(0, 0);
  char key = keypad.getKey();
  if (key){
    if(key == 'A') {
        if(optCpfSenha == 0) {
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
        } else {
          optCpfSenha = 1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Informe o senha:");
        }
      } else {
        autenticar();
      }
      
    }
    else if(key == 'C') {
      if(optCpfSenha == 0) {
        memset(cpf,0,strlen(cpf));
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Informe o CPF:");
        lcd.setCursor(0, 1);
        lcd.print(cpf);
        Serial.println(cpf);
      } else {
        memset(senha,0,strlen(senha));
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Informe a senha:");
        lcd.setCursor(0, 1);
        lcd.print(senha);
        Serial.println(senha);
      }
    }
    else if(key == 'B') {
      if(optCpfSenha == 0) {
        cpf[strlen(cpf)-1] = '\0';
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Informe o CPF:");
        lcd.setCursor(0, 1);
        lcd.print(cpf);
        Serial.println(cpf);
      } else {
        senha[strlen(senha)-1] = '\0';
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Informe a senha:");
        lcd.setCursor(0, 1);
        lcd.print(senha);
        Serial.println(senha);
      }
    }
    else {
      if(optCpfSenha == 0) {
        strncat(cpf, &key, 1);
        lcd.setCursor(0, 1);
        lcd.print(cpf);
        Serial.println(cpf);
      } else {
        strncat(senha, &key, 1);
        lcd.setCursor(0, 1);
        lcd.print(senha);
        Serial.println(senha);
      }
      
    }
  }
}
