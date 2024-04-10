
#include <SDS011.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
float p10,p25;
int error;
SDS011 my_sds;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define I2C_SDA  4
#define I2C_SCL  5
#define SDS011 my_sds;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String quality ="";
void setup() {
  my_sds.begin(3,4);
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
    
}
void loop() {
      error; my_sds.read(&p25,&p10);

  if (! error) {
   Serial.println("P2.5: "+String(p25));
    Serial.println("P10:  "+String(p10));
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,30);
    display.println("PM2.5");
    display.setCursor(67,30);
    display.println(p25);
    display.setCursor(0,46);
    display.println("PM10");
    display.setCursor(67,46);
    display.println(p10);
    display.display();
    display.clearDisplay();   
  }
    if(p25<12){
    quality = "GOOD!";
  }
    else if (p25>12 && p25<35){
    quality = "OK";
  }
    else if (p25 >35 && p25<50){
    quality =  "Poor!";
  }
    else if (p25 >50){
    quality  = "Toxic!";
  }

  
  display.setTextSize(1);  
  display.setFont();
  display.setCursor(0,1);
  display.println("Air Quality:");
  display.setTextSize(2);
  display.setCursor(60,12);
  display.println(quality);
  
  delay(100);
}
