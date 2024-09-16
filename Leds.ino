void Leds::inicia_pin()
{
    pinMode(PIN_LED_IN_BOARD_LECTURAS, OUTPUT); 

    for (byte bit = 0; bit < LAST_BIT_LEDS+1; bit++) 
    {   
        byte pin_led = _bit_to_pin(bit);
        pinMode(pin_led, OUTPUT);
    }
}

byte Leds::coge_estado_cuando_forzado_on()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI 
        return LED_BLINK_FAST;
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (Menu::get_valor(LEDS_RELES_FORZADO_ON) == 1) return LED_BLINK_SLOW;
        if (Menu::get_valor(LEDS_RELES_FORZADO_ON) == 2) return LED_BLINK_FAST;
    #endif
    return LED_BLINK_FAST;
}

byte Leds::coge_estado_cuando_forzado_off()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI 
        return LED_BLINK_FAST;
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (Menu::get_valor(LEDS_RELES_FORZADO_OFF) == 1) return LED_BLINK_SLOW;
        if (Menu::get_valor(LEDS_RELES_FORZADO_OFF) == 2) return LED_BLINK_FAST;
    #endif
    return LED_BLINK_FAST;
}

byte Leds::_bit_to_pin(byte bit)
{
    switch(bit)
    {
        case BIT_LED_LECTURAS:                          return PIN_LED_LECTURAS;
        case BIT_LED_ALARMAS:                           return PIN_LED_ALARMAS;
        case BIT_LED_BOMBA_1:                           return PIN_LED_BOMBA_1;
        #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI 
            case BIT_LED_BOMBA_1_PULSADA:                   return PIN_LED_BOMBA_1_PULSADA;
            case BIT_LED_CALENTADOR_REFRIGERADOR:       return PIN_LED_CALENTAR;
        #endif
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case BIT_LED_CALENTADOR:                    return PIN_LED_CALENTAR;
            case BIT_LED_AGUA:                          return PIN_LED_AGUA;
            case BIT_LED_REFRIGERADOR:                  return PIN_LED_ENFRIAR;
            case BIT_LED_BOMBA_2:                       return PIN_LED_BOMBA_2;
            case BIT_LED_BOMBA_3:                       return PIN_LED_BOMBA_3;
            case BIT_LED_SERIALDATA:                    return PIN_LED_SERIALDATA;
        #endif
    }
    return 0;
}

void Leds::set_bit(byte bit, byte valor)
{
    if (bit > LAST_BIT_LEDS) return;
    Leds_bits_state[bit] = valor;
}

void Leds::set_bits(byte valor)
{
    for (byte bit = 0; bit < LAST_BIT_LEDS; bit++) 
    {
        set_bit(bit, valor);
    }
}


/* 
**************************

    REFRESCO DE LAS INTERMITENCIAS

**************************
*/    
void Leds::refresca_tiks()
{
    // CADA 150ms INTERMITENTES RAPIDOS
    if ( FC::if_zero_or_diff_to_millis(Leds_refresh_150_timer_, 150) )
    {
        Leds_tick_fast = !Leds_tick_fast;
        Leds_refresh_150_timer_ = millis();
        refresca_leds();
    }

    // CADA 500ms INTERMITENTES LENTOS
    if ( FC::if_zero_or_diff_to_millis(Leds_refresh_500_timer_, 500) )
    {
        Leds_tick_slow = !Leds_tick_slow;
        Leds_refresh_500_timer_ = millis();
        refresca_leds();
    }
}

/* 
**************************

    REFRESCO DE TODOS LOS LEDS

**************************
*/    
void Leds::refresca_leds()
{
    for(byte bit = 0; bit < LAST_BIT_LEDS; bit++)
    {
        refresca_led(bit, Leds_bits_state[bit]);
    }
}

/* 
**************************

    REFRESCO DE UN LED

**************************
*/    
void Leds::refresca_led(byte bit, byte value_state)
{
    if (bit > LAST_BIT_LEDS) 
    {
        return;
    }
    switch(value_state)
    {
        case LED_BLINK_FAST: 
            value_state = Leds_tick_fast;
            break;
        case LED_BLINK_SLOW: 
            value_state = Leds_tick_slow;
            break;
    }

    byte pin_led = _bit_to_pin(bit);

    switch(value_state)
    {
        case LED_OFF:
            digitalWrite(pin_led, 0);
            break;
        case LED_ON:  
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                analogWrite(pin_led, _brillo_map(Menu::get_valor(LEDS_BRILLO)));
            #endif
            #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
                digitalWrite(pin_led, 1);
            #endif
            break;
    }
}


/* 
**************************

    CALCULAR BRILLO LEDS

**************************
*/    
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
byte Leds::_brillo_map(byte percent)
{
    byte n = map(percent, 0, 10, 
                0, //tension minima
                30); //tension maxima
    return n;
}
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
/* 
**************************

    MUESTRA DE BRILLO CUANDO SE EDITA DESDE EL MENU

**************************
*/    
void Leds::brillo_refresca_muestra(int edicion_valor)
{
    byte pin_led_bomba_1 = _bit_to_pin(BIT_LED_BOMBA_1);
    byte pin_led_bomba_2 = _bit_to_pin(BIT_LED_BOMBA_2);

    analogWrite(pin_led_bomba_1, _brillo_map(Menu::get_valor(LEDS_BRILLO)));
    analogWrite(pin_led_bomba_2, _brillo_map(edicion_valor));
    FC::FC::FC::delayMilisegundos(200);
    analogWrite(pin_led_bomba_1, 0);
    analogWrite(pin_led_bomba_2, 0);
}
#endif

void Leds::test()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        _test_MEGA();
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        _test_MINI();
    #endif
}

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    void Leds::_test_MINI()
    {
        set_bits(1); refresca_leds();        
        FC::delayMilisegundos(50);
        set_bits(0); refresca_leds();
    }
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void Leds::_test_MEGA()
    {
        int brillo_mem = Menu::get_valor(LEDS_BRILLO);
        byte brillo_temp;
        set_bits(1);
        for(brillo_temp= 0; brillo_temp < 6; brillo_temp++)
        {
            Menu::set_valor(LEDS_BRILLO, brillo_temp);
            refresca_leds();
            FC::delayMilisegundos(20);
        }
        for(brillo_temp= 6; brillo_temp > 0; brillo_temp--)
        {
            Menu::set_valor(LEDS_BRILLO, brillo_temp);
            refresca_leds();
            FC::delayMilisegundos(20);
        }
        set_bits(0); refresca_leds();
        Menu::set_valor(LEDS_BRILLO, brillo_mem);
    }
#endif

void Leds::latido(bool valor)
{
    if (valor == 1)
    {
        digitalWrite(PIN_LED_LECTURAS, HIGH);
    }
    else
    {
        refresca_led(BIT_LED_LECTURAS, Leds_bits_state[BIT_LED_LECTURAS]);
    }
}

void Leds::set_alarmas(byte estado_led)                       
{
    set_bit(BIT_LED_ALARMAS, estado_led);
}

void Leds::set_lecturas(byte estado_led)                       
{
    set_bit(BIT_LED_LECTURAS, estado_led);
}

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void Leds::set_calentador(byte estado_led)                 
    {
        set_bit(BIT_LED_CALENTADOR, estado_led);
    }

    void Leds::set_refrigerador(byte estado_led)               
    {
        set_bit(BIT_LED_REFRIGERADOR, estado_led);
    }
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    void Leds::set_calentador_refrigerador(byte estado_led)               
    {
        set_bit(BIT_LED_CALENTADOR_REFRIGERADOR, estado_led);
    }
#endif

void Leds::set_bomba(byte bomba_id, byte estado_led)                         
{
    set_bit(BIT_LED_BOMBA_1+(bomba_id), estado_led);
}

void Leds::set_bomba_pulsada(byte bomba_id, byte estado_led)             
{
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        set_bit(BIT_LED_BOMBA_1_PULSADA+(bomba_id), estado_led);
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        set_bit(BIT_LED_BOMBA_1+(bomba_id), estado_led);
    #endif
}

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void Leds::set_agua(byte estado_led)                       
    {
        set_bit(BIT_LED_AGUA, estado_led);
    }
#endif
