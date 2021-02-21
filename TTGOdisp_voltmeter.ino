//ESP 32 TTG0 T-DISPLAY Voltmeter
//
//James Steven Dulangon     
//


#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define analogInPin 15                

void setup()
{
    Serial.begin(115200);
    pinMode(analogInPin, INPUT);
    tft.init();
    tft.setRotation(1);

     tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(0, 0);
    tft.setTextFont(4);
    tft.setTextSize(1);
    tft.println("VOLTAGE READING:");
}

void displayReading(float va)
{
  yield();
  tft.setTextSize(2);
  tft.drawFloat(va, 2, 50, 50);
  tft.drawChar('V',160,50);
}
void loop()
{   
  
  
  uint8_t num_sample = 30;
  int sum = 0;  

   while (0 < num_sample) 
   {            
      int analogValue = analogRead(analogInPin);
      sum += analogValue;
      num_sample--;                                
      delay(3);
   }
    
   float ave = (float)sum/30.0;
   float vout = (ave*3.29)/ 4096.0 ;
   float va = (vout / (10000.0/110000.0));

   displayReading(va);

   delay(100);
}
