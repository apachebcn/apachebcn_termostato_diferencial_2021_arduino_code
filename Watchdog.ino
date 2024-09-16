void watchdogSetup()
{
    cli();  // disable all interrupts
    wdt_reset(); // reset the WDT timer
    MCUSR &= ~(1<<WDRF);  // because the data sheet said to
    /*
    WDTCSR configuration:
    WDIE = 1 :Interrupt Enable
    WDE = 1  :Reset Enable - I won't be using this on the 2560
    WDP3 = 0 :For 1000ms Time-out
    WDP2 = 1 :bit pattern is
    WDP1 = 1 :0110  change this for a different
    WDP0 = 0 :timeout period.
    */
    // Enter Watchdog Configuration mode:
    WDTCSR = (1<<WDCE) | (1<<WDE);
    // Set Watchdog settings: interrupte enable, 0110 for timer
    WDTCSR = (1<<WDIE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0);
    sei();
    DogWatch_update();
}

ISR(WDT_vect) // Watchdog timer interrupt.
{
    int time_passed = (millis()/1000) - (resetTime/1000);
//Serial.println(time_passed);
    byte time_top = TIMEOUTPERIOD / 1000;
    if(time_passed > time_top || time_passed < 0)
    {

        #ifdef ABLE_SERIAL_DEBUG
            Serial_debug::print(F("WATCHDOG RESET!"));
        #endif

        DogWatch_update();
        resetFunc();     // This will call location zero and cause a reboot.
    }
    else
    {
        //Serial_debug::print(F("WatchDog remain ")); Serial.println(time_top - time_passed);
    }
}
























