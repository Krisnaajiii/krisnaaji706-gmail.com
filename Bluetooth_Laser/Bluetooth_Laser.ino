#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <SoftwareSerial.h>
String datapengukuran,datalaser;
char inByte;
int button=5;
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial LRF_Port (rxPin, txPin);
//SoftwareSerial blutut(8, 9);//software serial #2: RX = digital pin 8, TX = digital pin 9

void setup()
{
 Serial.begin(9600);
 //blutut.begin(9600);
 LRF_Port.begin(19200);                            // start serial communication between the LRF and Arduino
 lcd.begin();
 lcd.setCursor(0,0);
 lcd.print("Pengukuran Laser ");
 lcd.setCursor(5,1);
 lcd.print("UNJ ");
 delay(1000);
pinMode(button,INPUT);
Serial.println("--- Pengukuran Laser ---");
 delay(100);
}
void ukurlaser(){
 LRF_Port.write("D");
 delay(3000);    
 Serial.print("Ukur Distance  ");
 datalaser=LRF_Port.readStringUntil(13);
 datapengukuran=datalaser.substring(4,11);
 Serial.print(datapengukuran);
 Serial.println();
}
void nyalalaser(){
LRF_Port.write("O");   
delay(100); 
//Serial.print("Laser Nyala");
LRF_Port.readStringUntil(13);

LRF_Port.write("D");
 delay(3000);    
 Serial.print("Ukur Distance  ");
 datalaser=LRF_Port.readStringUntil(13);
 datapengukuran=datalaser.substring(3,9);
 Serial.print(datapengukuran);

 LRF_Port.write("C");   
delay(100);
 //Serial.print("Laser Mati");
LRF_Port.readStringUntil(13);
Serial.println();
}
void matilaser(){
LRF_Port.write("C");   
delay(100);
 //Serial.print("Laser Mati");
LRF_Port.readStringUntil(13);
Serial.println();
}
void hmi(){
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("Distance Laser : ");
  lcd.setCursor(3,1);
  lcd.print(datapengukuran);
}
void loop()
{
 hmi();
 int but =digitalRead(button);
 if (but==LOW){
 ukurlaser();        
 }
//blutut.listen();
  // while there is data coming in, read it
  // and send to the hardware serial port:
  if (Serial.available()>0) {
    inByte = Serial.read();
switch (inByte) {
case 'D':ukurlaser();break;
case 'O':nyalalaser();break;
case 'C':matilaser();break;
//case 'L':goLeft();break;;
  }
//  LRF_Port.listen();
//  // while there is data coming in, read it
//  // and send to the hardware serial port:
//   while ( LRF_Port.available() > 0) {
//   inByte =  LRF_Port.read();
//    Serial.write(inByte);
  }
}
