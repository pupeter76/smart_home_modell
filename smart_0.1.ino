#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include <Keypad.h>
#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_MOSI   51
#define OLED_CLK    52
#define OLED_DC    48
#define OLED_CS    12
#define OLED_RESET 49


#define jelszo_hossz 5
#define DHT11_pin 10

int tengely=0;
int temphum;

char Data[jelszo_hossz];
char Tempdat[2];
char goodcode[jelszo_hossz] = "1234";
byte data_szamlalo=0, code_szamlalo=0;
bool goodpass, megvan;
char vissz,vissz1,vissz2;
char secu[4]="0000";

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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


Keypad billpad = Keypad(makeKeymap(tasta), sorPins, oszlopPins, sor, oszlop); 

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo_test;

dht DHT;

void setup() {
  
  servo_test.attach(9);
  servo_test.write(0);
  lcd.init(); 
  lcd.backlight();
  
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC); 
  display.clearDisplay();
  display.display();
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

void temper_lcd(){
  temphum=DHT.read11(DHT11_pin);
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Humi: ");
  lcd.print(DHT.humidity);
  lcd.print(" %");
  delay(1500);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Set temperature (#)");
  display.println("Back to main    (*)");
  display.display();
  char vissz,bill;   
    do {
    char bill=billpad.getKey();
    if (bill) {
       vissz=bill;
          }
  }
  while  ((vissz!='#') && (vissz!='*'));
  if (vissz=='#') {
    temper_set();
  }
  }

void temper_set(){
  char bill;
  char vissz1;
  byte szamlalo=0;
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Set temperature : ");
  display.display();
  do {
   
    char bill=billpad.getKey();
    vissz1=bill;
    
    if ((bill) && (vissz1!='#') && (vissz1!='*')) {
       Tempdat[szamlalo]=vissz1;
       display.print(Tempdat[szamlalo]);
       display.display();
       szamlalo++;
    }
    if (szamlalo==2) {
      display.println();
      display.println("OK?"); 
      display.println("No/Yes: */#:");
      display.display();
      char vissz2;
      szamlalo=0;
      do {
       char bill=billpad.getKey();
       vissz2=bill;
       if ((vissz2=='#') || (vissz2=='*')) {
          display.print(vissz2);
          delay(500); 
          display.display();
          if (vissz2=='*') {
             display.clearDisplay();
             display.setCursor(0,0);
             display.println("Set temperature : ");
             display.display();
          }
          if (vissz2=='#') {
            vissz1='#';
            }
          }
       }
       while ((vissz2!='#') && (vissz2!='*'));
      }
      }
  while ((vissz1 !='#') && (vissz2!='#'));
  delay(1000);

  if (DHT.temperature>atoi(Tempdat)) {
             display.clearDisplay();
             display.setTextSize(2);
             display.setCursor(0,0);
             display.println("  COOLING  ");
             display.display();  
             delay(1000);
  }
  else {
             display.clearDisplay();
             display.setTextSize(2);
             display.setCursor(0,0);
             display.println("  HEATING ");
             display.display();  
             delay(1000);                 
  }

  Serial.println(Tempdat);
  Serial.print(atoi(Tempdat));
  
    }
  
   
void secur(){
       data_szamlalo=0;
       for (int i=0; i<jelszo_hossz-1; i++) {
        Data[i]='*';
        }
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Password:");
       boolean megvan=false;
  do {  
  char bill = billpad.getKey();
  if (bill) {
    Data[data_szamlalo]=bill;
    lcd.setCursor(data_szamlalo,1);
    lcd.print(Data[data_szamlalo]);
    data_szamlalo++;
  }
  if (data_szamlalo==jelszo_hossz-1) {
        lcd.clear();
        data_szamlalo=0; 
        int sz=0;
        int address=0;
        boolean megvan=false;
       while ((sz<5)  && (megvan==false)){
        EEPROM.get(address,secu);
        Serial.println(secu);
        if (atoi(Data)==atoi(secu)) 
        {
          megvan=true;
        }
        address=address+sizeof(secu);
        sz++;
       }
      if (megvan==true) {
      lcd.print("Correct");
      delay(500);
      if (tengely==0)  {
        display.setTextSize(2);             
        display.clearDisplay();  
        display.setTextColor(WHITE);
        display.setCursor(0,0);            
        display.println("Deadlock  opening");
        display.display();
        nyit();
        delay(1000);
        display.clearDisplay();
        break;
          }
      else {
        display.setTextSize(2);             
        display.clearDisplay();  
        display.setTextColor(WHITE);
        display.setCursor(0,0);            
        display.println("Deadlock  closing");
        display.display();
        zar();
        delay(1000);
        display.clearDisplay();
        break;
         }
      delay(1000);
      
  }
    else {
      lcd.clear();
      lcd.print("Pass isn't mutch");
      delay(1000);
      lcd.clear();
      break;
    }
  }
    }
    while (megvan==false);
     
  }

void loop()
{
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0,0);            
   display.println("SECURITY      (1)");
   display.println("TEMPERATURE   (2)");
   display.println("LIGHT         (3)");
   display.println("PANIC BUTTON  (4)");
   display.println("CHANGE PASS   (5)"); 
   display.display();
   lcd.setCursor(0,0);
   lcd.print("MENU (number): ");
   char bill = billpad.getKey();
   if (bill) {
    lcd.setCursor(0,1);
    lcd.print(bill);
    delay(500);
    switch (bill) {
      case '1' :
          secur();
          break;
      case '2' : 
          temper_lcd(); 
           lcd.clear();
           display.clearDisplay();
           display.display();
          break;
        
               }
    }
}
