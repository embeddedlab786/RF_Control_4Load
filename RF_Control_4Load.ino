#include "RCSwitch.h"
#include <EEPROM.h>

RCSwitch mySwitch = RCSwitch();

#define Relay1 3 // Load1 Pin Out
#define Relay2 4 // Load2 Pin Out
#define Relay3 5 // Load3 Pin Out
#define Relay4 6 // Load4 Pin Out

int load1, load2, load3, load4;

void setup() {

Serial.begin(9600);

mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

load1 = EEPROM.read(1);
load2 = EEPROM.read(2);
load3 = EEPROM.read(3);
load4 = EEPROM.read(4);

pinMode(Relay1, OUTPUT); digitalWrite(Relay1, load1); 
pinMode(Relay2, OUTPUT); digitalWrite(Relay2, load2); 
pinMode(Relay3, OUTPUT); digitalWrite(Relay3, load3); 
pinMode(Relay4, OUTPUT); digitalWrite(Relay4, load4); 
delay(100);  
}

void loop() {
  
if (mySwitch.available()>0) {  
unsigned long int RF_data =  mySwitch.getReceivedValue() ;
Serial.println(RF_data);

switch(RF_data){
  case 5592512: mySwitch.disableReceive();
                load1 = !load1;
                EEPROM.write(1, load1);
                break;
                
  case 5592368: mySwitch.disableReceive();
                load2 = !load2;
                EEPROM.write(2, load2);
                break;
                              
  case 5592332: mySwitch.disableReceive();
                load3 = !load3;
                EEPROM.write(3, load3);
                break; 
                
   case 5592323: mySwitch.disableReceive();
                load4 = !load4;
                EEPROM.write(4, load4);
                break;                

}

digitalWrite(Relay1, load1); 
digitalWrite(Relay2, load2); 
digitalWrite(Relay3, load3); 
digitalWrite(Relay4, load4);

unsigned long time_now = millis();
int ck = 500;
while(millis()<time_now + ck){;}
  mySwitch.resetAvailable();
  mySwitch.enableReceive(0);
  }
}
