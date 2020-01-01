#include <EEPROM.h>


const 
    char secu1[4]="1234";
    char secu2[4]="4321";
    char secu3[4]="1122";
    char secu4[4]="2211";
    char secu5[4]="1111";
    
void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
 
int eeAddres = 0;  
 
EEPROM.put(eeAddres, secu1);
eeAddres=sizeof(secu1);
EEPROM.put(eeAddres,secu2);
eeAddres=eeAddres+sizeof(secu2);
EEPROM.put(eeAddres,secu3);
eeAddres=eeAddres+sizeof(secu3);
EEPROM.put(eeAddres,secu4);
eeAddres=eeAddres+sizeof(secu4);
EEPROM.put(eeAddres,secu5);
Serial.print("Written custom data type!");
}


void loop() {
  /* Empty loop */
}
