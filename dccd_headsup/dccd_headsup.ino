// Subaru WRX STI DCCD gauge display
// Signal to be measured is a 1 kHz
// Duty cycle of 100% is full lock

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif

//Pin 0 is neopixel i2c
#define PIN 0

//Analog pins are numbered differently than the board shows
//Analog Pin 1 is Digital Pin 2 is Analog Pin 1
//Analog Pin 2 is Digital Pin 4
//Analog Pin 3 is Digital Pin 3
#define A0 2
#define A1 3


//Thresold for considering high vs low
//Typically AVR uses 3V

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN);

uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;

unsigned long time1;
unsigned long time2;

uint32_t getPowerColor(int level)
{
  uint8_t r = (uint8_t)(((level+0.0)/100.0)*255);
  uint8_t g = (uint8_t)(((100-level+0.0)/100.0)*255);
  uint8_t b = (uint8_t)(((level+0.0)/0.0)*255);
  uint32_t c = strip.Color(r,g,b);
  
  return c;
}

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
  
	for (int level = 0; level <= 100; level += 1)
	{
		for (int i=0; i < pixels.numPixels(); i+=1) {
		pixels.setPixelColor(i, 0);        //turn every third pixel off
		}
		for(uint16_t i=0; i<((strip.numPixels()*(level/100.0))/2); i++) {
			pixels.setPixelColor(i, getPowerColor(level));
			pixels.setPixelColor(pixels.numPixels() - i, getPowerColor(level));
		}
		pixels.show();
		delay(50);
	}
	delay (100);
  
  uint8_t  i;
  
    for(i=0; i<16; i++) {
      uint32_t c = 0;
      pixels.setPixelColor(   i, c); // First eye
      pixels.setPixelColor(31-i, c); // Second eye (flipped)
 
      pixels.show();
      delay(50);
    }
  
}

//States:
//None -- waiting for a high signal
//High -- High state measured, waiting for low
//Low -- Low state measured, upon next high calculate
//Calculate & Write

//We can't assume a common ground, so to find the voltage it requires
//Subtracting A0 from A1

void loop() {
  //Main loop
  uint8_t  i;
  uint32_t t;

  time1 = micros();
  
  uint16_t a0read;
  uint16_t a1read;
  
  a0read = analogRead(A0);
  a1read = analogRead(A1);
  
}
