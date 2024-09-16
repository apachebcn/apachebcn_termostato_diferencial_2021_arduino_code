unsigned long resetTime = 0;
#define DogWatch_update() resetTime = millis();  // This macro will reset the timer

#include <avr/wdt.h>

#define TIMEOUTPERIOD 60000

void watchdogSetup();
























