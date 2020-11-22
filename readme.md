ESP Pomodoro timer
==========

The Pomodoro Technique is a popular time management approach. It helps you keep focus and avoid distractions by dividing up work into 25 minute intervals which are separated by short 5 minute breaks. Each one of these intervals is called a pomodoro. For further information on the Pomodoro technique, see https://en.wikipedia.org/wiki/Pomodoro_Technique.

This project is an implementation of a Pomodoro timer on an ESP8266 using a NeoPixels ring. The project is simple, avoiding many of the advanced features and distractions available in other Pomodoro timer implementations. Also, this stand alone timer does not require any device such as a phone or computer to run it. The NeoPixels provide an elegant visual indication of the progress through each of the work - break intervals. 


## Use
Once powered up the timer is in an idle state.  To start a Pomodoro, you press the button and the timer will enter the 'work' state and the lights turn red. As the time progresses through the work period, the lights become brighter indicating the time passed like a clock.  

Once the work interval has finished, the rest period starts and the lights change to green. The lights become brighter in a similar clock style indicating the progress through the break period. Once the break period ends, the timer then reverts to the idle state where you can then press the button to start the next Pomodoro.


## Components
* 1 x ESP8266 
* 1 x Push Button 
* 1 x 24 LED NeoPixels ring


## Prerequisites
* Platformio IDE
* Neopixels library: adafruit/Adafruit NeoPixel @ 1.6.0


## Installation
Typically a pomodoro timer alternates between 25 minute work periods and 5 minute break periods. Howver, if you want to change this you can adjust the definitions for workTime and restTimer:

```c
uint32_t workTimer = 25*60*1000; // 25 mins work
uint32_t restTimer = 5*60*1000; // 5 mins rest
```
