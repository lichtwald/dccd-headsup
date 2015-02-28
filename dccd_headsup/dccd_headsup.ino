// Subaru WRX STI DCCD gauge display

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif

#define PIN 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
  prevTime = millis();
}

void oc(){
  //Opening Ceremony
  
  //Set Color
  color = 0xFF0000;
  
  uint8_t  i;
  
    for(i=0; i<16; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
      pixels.setPixelColor(   i, c); // First eye
      pixels.setPixelColor(31-i, c); // Second eye (flipped)
 
      pixels.show();
      offset++;
      delay(50);
    }
  
}

void loop() {
  //Main loop
  uint8_t  i;
  uint32_t t;

  t = micros();
  
}
