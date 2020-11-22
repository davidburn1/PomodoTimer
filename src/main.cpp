#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN D5
#define BTN1 D2

uint8_t state = 2; //0=resting, 1=working, 2=idle 
uint32_t stateStartTime = 0;

uint32_t workTimer = 25*60*1000; // 25 mins work
uint32_t restTimer = 5*60*1000; // 5 mins rest

uint8_t brightness = 0;
float progress = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, PIXELS_PIN, NEO_GRB + NEO_KHZ800);



void whitePixelPattern(){
    pixels.clear();
    for(uint8_t i=0; i<24; i++) { 
      float angle = (3*(float)i)/24 + ((float)millis()/2000); // pixel position, and time dependent terms
      brightness = 10*(1+sin(angle*2*PI)) + 2;
      pixels.setPixelColor(i, pixels.ColorHSV(0, 0, brightness));
    }
    pixels.show();   
}

void timerPattern(uint16_t hue, float progress){
    pixels.clear();
    for(uint8_t i=0; i<24; i++) { 
      brightness = 10*(1+tanh(( progress - ((float)i/24) )*100)) +2;
      pixels.setPixelColor(i, pixels.ColorHSV(hue, 255, brightness));
    }
    pixels.show();   
}



void setup() {
  pinMode(PIXELS_PIN, OUTPUT);
  pinMode(BTN1, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("");

  pixels.begin();
  pixels.show(); 
}



void loop() {

  if (state == 2){ // idle state
    whitePixelPattern();

    if (digitalRead(BTN1) == 0) { 
      // When button is pressed, move into the working state
      state = 1;
      stateStartTime = millis();
    }


  } else if (state == 1){ // working state
    progress = ((float)(millis()-stateStartTime)/(float)workTimer);
    timerPattern(0, progress);

    if (progress >= 1) {
      // Move to the rest state after the workTime time has passed
      state = 0;
      stateStartTime = millis();
    }


  } else if (state == 0) { // resting state
    progress = ((float)(millis()-stateStartTime)/(float)restTimer);
    timerPattern(21845, progress); //green

    if (progress >= 1) {
        // Move back to the idle state after the restTimer time has passed
        state = 2;
        stateStartTime = millis();
    }
  }

}

