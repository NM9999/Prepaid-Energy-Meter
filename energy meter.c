#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerialmySerial(3, 2); // RX, TX

LiquidCrystallcd(8, 9, 10, 11, 12, 13);
constintpulsePin = A0;     // the number of the pushpulse pin
intpulseState = 0;         // variable for reading the pushpulse status
constint relay =A1;
byterunit=0;
bytecunit=0;
int address = 0;
int address1 = 1;
String instring;
charinchar=0;
String pin;
String bal;
void setup() 
{
Serial.begin(9600);
mySerial.begin(9600);
pinMode(pulsePin, INPUT);
pinMode(relay, OUTPUT);
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("PREPAID ENERGY");
lcd.setCursor(5, 1);
lcd.print("METER");
delay(5000);
Serial.println("AT");
delay(1000);
Serial.println("AT+CNMI=2,2,0,0,0");
delay(1000);
Serial.println("AT+CMGF=1");
delay(1500);
lcd.clear();
}

void loop() 
{
pulseState = digitalRead(pulsePin);

if (pulseState == LOW) 
  {
cunit=EEPROM.read(address1);
cunit=cunit+1;
EEPROM.write(address1, cunit);
while(pulseState == LOW) 
    {
pulseState = digitalRead(pulsePin);
     }
   }
if(cunit>1)
  {
runit=EEPROM.read(address);
runit=runit-1;
EEPROM.write(address,runit);
cunit=0;
   }

if(cunit=5)
  {
lcd.setCursor(0, 1);
lcd.print("Please recharge...");
lcd.print(runit);
Serial.println("AT");
delay(500);
Serial.println("AT+CMGF=1");
delay(1500);
Serial.println("AT+CMGS=\"+918080970747\"\r");
delay(1500);
Serial.println("please recharge your meter.....");
delay(1500);
Serial.println((char)26);
delay(1500);
   }

runit = EEPROM.read(address);
lcd.setCursor(0, 0);
lcd.print("Remain unit ");
lcd.print(runit);

if(runit>1)
{
digitalWrite(relay,HIGH);
  }
if(runit<1)
{
digitalWrite(relay,LOW);
  }

while(Serial.available()>0)
{

inchar=Serial.read();
if(inchar=='@')
  {
while(inchar!='#')
    {
//      Serial.println(inchar); 
delay(10);
inchar=Serial.read();
instring+=inchar;
    }

pin=instring.substring(0, 4);
bal=instring.substring(5, 8);

int n1 = bal.toInt();
  //    Serial.println(n1);  
if(pin=="1357")
    {
runit=EEPROM.read(address);
runit=runit+(n1/5);
EEPROM.write(address,runit);
   // Serial.println("ok"); 
Serial.println("AT");
delay(500);
Serial.println("AT+CMGF=1");
delay(1500);
Serial.println("AT+CMGS=\"+918080970747\"\r");
delay(1500);
Serial.println("recharge successful.....");
delay(1500);
Serial.println((char)26);
delay(1500);
      }
  }
  }
//  Serial.println(pin); 
//  Serial.println(bal);  
}
