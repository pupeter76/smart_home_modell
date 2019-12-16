#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include <Keypad.h>
#include <dht.h>

#define jelszo_hossz 5
#define DHT11_pin 10

int tengely=0;
int temphum;

char Data[jelszo_hossz];
char goodcode[jelszo_hossz] = "1234";
byte data_szamlalo=0, code_szamlalo=0;
bool goodpass;

const byte sor = 4; 
const byte oszlop = 3; 
char tasta [sor][oszlop] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte sorPins[sor] = {22, 23, 24, 25}; 
byte oszlopPins[oszlop] = {26, 27, 28}; 


Keypad billpad = Keypad(makeKeymap(tasta), sorPins, oszlopPins, sor, oszlop); 

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo_test;

dht DHT;

void setup()
{
  servo_test.attach(13);
  servo_test.write(0);
  lcd.init(); 
  lcd.backlight();
}

void nyit() {
    for (tengely=0; tengely<180; tengely++){
    servo_test.write(tengely);
    delay(5);
       }
}

void zar() {
    for (tengely=180; tengely>0; tengely--){
    servo_test.write(tengely);
    delay(5);
         }
}

void temper() {
  temphum=DHT.read11(DHT11_pin);
  lcd.clear();
  lcd.print("Temperature: ");
  lcd.print(DHT.temperature);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print(" %");
  delay(1500);
}

  
void loop(){
       lcd.setCursor(0,0);
       lcd.print("Password:");
    
  char bill = billpad.getKey();
  if (bill) {
    Data[data_szamlalo]=bill;
    lcd.setCursor(data_szamlalo,1);
    lcd.print(Data[data_szamlalo]);
    data_szamlalo++;
  }
  if (data_szamlalo==jelszo_hossz-1){
        lcd.clear();
        data_szamlalo=0; code_szamlalo=0;
     if(!strcmp(Data,goodcode)) {
      lcd.print("Correct");
      delay(500);
      if (tengely==0)  {
        lcd.clear();
        lcd.print("deadlock opening");
        nyit();
        delay(500);
        lcd.clear();
      }
      else {
        lcd.clear();
        lcd.print("deadlock closing");
        zar();
        delay(500);
        lcd.clear();
      }
      delay(1000);
      
  }
  }
  }
