void Dispositivos_alarmas::init()
{
    int dispositivo_id;
    for(dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        set_alarma(dispositivo_id, 0);
        set_alarma_recordada(dispositivo_id, 0);
        set_alarma_silenciada(dispositivo_id, 0);
    }
}

byte Dispositivos_alarmas::get_alarma(int dispositivo_id)
{
    int bit = Dispositivos._bit_dispositivo(dispositivo_id);
    return _alarmas_bits_[bit];
}

byte Dispositivos_alarmas::get_alarma_recordada(int dispositivo_id)
{
    int bit = Dispositivos._bit_dispositivo(dispositivo_id);
    return _alarmas_recordadas_bits_[bit];
}

byte Dispositivos_alarmas::get_alarma_silenciada(int dispositivo_id)
{
    int bit = Dispositivos._bit_dispositivo(dispositivo_id);
    return _alarmas_silenciadas_bits_[bit];
}

void Dispositivos_alarmas::set_alarma(int dispositivo_id, byte valor)
{
    int bit = Dispositivos._bit_dispositivo(dispositivo_id);
    _alarmas_bits_[bit] = valor;
}

void Dispositivos_alarmas::set_alarma_recordada(int dispositivo_id, byte valor)
{
    int bit = Dispositivos._bit_dispositivo(dispositivo_id);
    _alarmas_recordadas_bits_[bit] = valor;
}

void Dispositivos_alarmas::set_alarma_silenciada(int dispositivo_id, byte valor)
{
    int bit = Dispositivos._bit_dispositivo(dispositivo_id);
    _alarmas_silenciadas_bits_[bit] = valor;
}


void Dispositivos_alarmas::set_estado(int dispositivo_id, byte alarma_estado)
{
    bool nueva_alarma = 0;
    switch(alarma_estado)
    {
        case ALARMA_OFF:
            if (get_alarma(dispositivo_id) > ALARMA_OFF) 
            {
                //Finalizada alarma (on->off)
//                set_alarma_recordada(dispositivo_id, get_alarma(dispositivo_id));
//                set_alarma_silenciada(dispositivo_id, 0);
            }
            set_alarma(dispositivo_id, alarma_estado);
            break;

        case ALARMA_POR_ERROR:
        case ALARMA_POR_EVENTO_DE_DECESO:
        case ALARMA_POR_EVENTO_DE_EXCESO:
            if (get_alarma(dispositivo_id) == ALARMA_OFF) 
            {
                //Nueva alarma (off->on)
                nueva_alarma = 1;
            }
            else
            if (get_alarma(dispositivo_id) != alarma_estado) 
            {
                //Nueva alarma (on->on) pero distinto estado
                nueva_alarma = 1;
            }
            else
            {
                //Alarma ya existía (on->on)
            }
            if (nueva_alarma)
            {
                set_alarma_silenciada(dispositivo_id, 0);
                set_alarma_recordada(dispositivo_id, alarma_estado);
                set_alarma(dispositivo_id, alarma_estado);
                Dispositivos_alarmas_inicio_buzzer_timer_ = millis();
            }
            break;
    }

    if (nueva_alarma)
    {
        Pantalla::encender();
        Buzzer::beep_error();
    }

}

void Dispositivos_alarmas::silenciar()
{
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        if (get_alarma(dispositivo_id))
        {
            set_alarma_silenciada(dispositivo_id, 1);
        }
    }
}

void Dispositivos_alarmas::reset()
{
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        set_alarma(dispositivo_id, 0);
        set_alarma_recordada(dispositivo_id, 0);
        set_alarma_silenciada(dispositivo_id, 0);
    }
}

bool Dispositivos_alarmas::existe_alarma_no_silenciada()
{
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        if (!get_alarma(dispositivo_id)) continue;
        if (!get_alarma_silenciada(dispositivo_id)) return TRUE;
    }
    return FALSE;
}

bool Dispositivos_alarmas::todas_silenciadas()
{
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        if (get_alarma_silenciada(dispositivo_id)) return FALSE;
    }
    return TRUE;
}

bool Dispositivos_alarmas::existe_alarma_recordada()
{
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        if (get_alarma_recordada(dispositivo_id)) return TRUE;
    }
    return FALSE;
}

void Dispositivos_alarmas::actuar()
{
    Leds::set_alarmas(LED_OFF);
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        if (get_alarma(dispositivo_id) > ALARMA_OFF) 
        {
            Leds::set_alarmas(LED_BLINK_FAST);
        }
        else
        {
            if (get_alarma_recordada(dispositivo_id))
            {
                Leds::set_alarmas(LED_ON);
            }
        }
    }
    }

const __FlashStringHelper*  Dispositivos_alarmas::nombre(byte alarma_id)
{
    switch(alarma_id)
    {
        case ALARMA_OFF:                    return F("OFF");
        case ALARMA_POR_ERROR:              return F("ON POR ERROR");
        case ALARMA_POR_EVENTO_DE_DECESO:   return F("ON POR EVENTO DE DECESO");
        case ALARMA_POR_EVENTO_DE_EXCESO:   return F("ON POR EVENTO DE EXCESO");
    }
    return F("?");
}

void Dispositivos_alarmas::serial_print_debug()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

        if (!FC::is_debug(DEBUG_ALARMAS)) return;
        Serial_debug::println(); Serial_debug::println(F("-- DEBUG ALARMAS --"));
        for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
        {
            Serial_debug::print(F("Dispositivo: "));               
            Serial_debug::print(Dispositivos.nombre(dispositivo_id));
            Serial_debug::print(F("; Alarma: "));                  
            Serial_debug::print(nombre(get_alarma(dispositivo_id)));
            Serial_debug::print(F("; Recordada: "));               
            Serial_debug::print(nombre(get_alarma_recordada(dispositivo_id)));
            Serial_debug::print(F("; Silenciada: "));          
            Serial_debug::print(get_alarma_silenciada(dispositivo_id));
            Serial_debug::println();
        }

    #endif
}