// ESP8266 as I2C master


// I2C works with any gpio from D1 to D8 -- 2 pin needed 1 for SDA and another for clock
#define SDA D4
#define SCL D5
#include <Wire.h>


void setup() {
 Serial.begin(115200); /* begin serial for debug */
 Wire.begin(SDA, SCL); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
 //Wire.begin(S3, S2); /* join i2c bus with SDA=S3 and SCL=S2 of NodeMCU */  not available in Nodemcu
}

void loop() {
 Wire.beginTransmission(8); /* begin with device address 8 */
 Wire.write("Hello Arduino");  /* sends hello string */
 Wire.endTransmission();    /* stop transmitting */

 Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
 while(Wire.available()){
    char c = Wire.read();
  Serial.print(c);
 }
 Serial.println();
 delay(1000);
 Serial.println("inI2c World Master");
}
