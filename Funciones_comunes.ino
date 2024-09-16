void FC::delayMilisegundos(int tiempo)                
{
    unsigned long d_start = millis();           
    for (;;) 
    {
        unsigned long elapsed = millis() - d_start;  
        if (elapsed >= (unsigned int)tiempo)    
        {                
            return;
        }
    }
}

void FC::delayMicrosegundos(int tiempo)
{
    unsigned long d_start = micros();           
    for (;;) 
    {
        unsigned long elapsed = micros() - d_start;  
        if (elapsed >= (unsigned int)tiempo)    
        {                
            return;
        }
    }
}

bool FC::if_zero_or_diff_to_millis(unsigned long var, unsigned long diff)
{
    if (!var) return 1;
    return FC::if_diff_to_millis(var, diff);    
}

bool FC::if_diff_to_millis(unsigned long var, unsigned long diff)
{
    unsigned long elapsed = millis() - var;
    if (elapsed >= diff) return 1;
    return 0;
}

byte FC::FlashStringHelper_len(const __FlashStringHelper* flash_txt, byte max_len)
{
    byte longitud = strlen_P((char*)flash_txt);
    if (longitud > max_len) longitud = max_len;
    return longitud;
}

byte FC::Int_len(long valor)
{
    byte len = 1;
    if (abs(valor) > 9) len++;
    if (abs(valor) > 99) len++;
    if (abs(valor) > 999) len++;
    if (abs(valor) > 9999) len++;
    if (abs(valor) > 99999) len++;
    if (abs(valor) > 999999) len++;
    if (valor < 0) len++;
    return len;
}

void FC::reset_remoto()
{
    Pantalla::encender();
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Pantalla::borrar_fila(2); 
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        Pantalla::borrar_fila(0); 
    #endif
    lcd.print(F("REINICIO EN "));
    for(byte secs = 3; secs > 0; secs--)
    {
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            Pantalla::borrar_fila(3); 
        #endif
        #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
            Pantalla::borrar_fila(1); 
        #endif
        lcd.print(F("  "));
        lcd.print(secs);
        lcd.print(F(" SEGUNDOS"));
        if (secs) FC::delayMilisegundos(1000);
    }
    resetFunc();
}

bool FC::is_debug(int debug_menu_id)
{
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        return FALSE;
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (!Menu::get_valor(SERIAL_DEBUG_ON_OFF)) return FALSE;
        if (!Menu::get_valor(debug_menu_id)) return FALSE;
        return TRUE;
    #endif
    return FALSE;
}
