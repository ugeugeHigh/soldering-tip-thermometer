#include <Wire.h>
#include <M5AtomS3.h>
//#include <M5Stack.h>
const int i2c_addr = 0x67;
const int i2c_addr_r = 0xCF;
extern uint8_t kote_re[];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("start");
  AtomS3.begin();
  AtomS3.Lcd.begin();
  AtomS3.Lcd.setRotation(2);
  //AtomS3.Lcd.drawString("Hello!", 10, 10, 4); 
  Wire.begin(38,39);// SDA,SCL
  AtomS3.Lcd.setBrightness(10);
  AtomS3.Lcd.drawJpg(kote_re,3934,0,0);
  delay(5000);
         
}

void loop() {

  
  float Th = read_temperature(0x00);
  //float Td = read_temperature(0x01);
  //float Tc = read_temperature(0x02);
  Serial.print("Th");
  Serial.println(Th);
  /*
  Serial.print("Td");
  Serial.println(Td);
  Serial.print("Tc");
  Serial.println(Tc);
  */
  AtomS3.Lcd.drawString(String(Th), 5,40, 6);
  delay(1000);
}

float read_temperature(int addr) {
  float Temperature;
  byte UpperByte;
  byte LowerByte;
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(i2c_addr);
  Wire.write(addr);//Th
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr,2);
  while (Wire.available()) {
    UpperByte = Wire.read();
    delay(1);
    LowerByte = Wire.read();

    Serial.print("upper:");
    Serial.println(int(UpperByte));
    Serial.print("Lower");
    Serial.println(int(LowerByte));
  }

  Temperature = (float(UpperByte) * 16 + float(LowerByte) / 16);
  
  Serial.println(Temperature);
  
  /*
  
  if((UpperByte & 0x80) == 0x80) {
    Temperature = (float(UpperByte) * 16 + float(LowerByte) / 16) - 4096;
    Serial.println(Temperature);
  } else {
    Temperature = (float(UpperByte) * 16 + float(LowerByte) / 16);
    Serial.println(Temperature);
  }*/
  
  
  return Temperature;
}
