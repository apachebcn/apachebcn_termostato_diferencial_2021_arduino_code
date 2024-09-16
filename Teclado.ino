#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    void Teclado::inicia_pin()
    {
        pinMode (PIN_TECLA_OK,      INPUT);
        pinMode (PIN_TECLA_ATRAS,   INPUT);
        pinMode (PIN_TECLA_ARRIBA,  INPUT);
        pinMode (PIN_TECLA_ABAJO,   INPUT);
    }
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void Teclado::inicia_pin()
    {
        pinMode (PIN_TECLA_OK,      INPUT);
        pinMode (PIN_TECLA_ATRAS,   INPUT);
    }
#endif

void Teclado::bloquear()
{
    Teclado_locked_keys = !Teclado_locked_keys;
    Buzzer::beep_bloqueo();
    lcd.setCursor(PANTALLA_ANCHO_PX-1, PANTALLA_ALTO_PX-1);
    if (Teclado_locked_keys)
    {
        Pantalla::insertar_info_msg(MENSAJE_BLOQUEAR_TECLADO);
        front_pantalla();
    }
}

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    byte Teclado::get_rotary_encoder()
    {
        long Rotary1_value = Rotary_1.read();
        if (Rotary1_value != 0)
        {
            if (Rotary1_value > ROTARY_PASOS)
            {
                Rotary_1.write(0);
                if (Menu_editando)
                {
                    return SIGN_TECLA_ABAJO;
                }
                return SIGN_TECLA_ARRIBA;
            }
            else if (Rotary1_value < -ROTARY_PASOS)
            {
                Rotary_1.write(0);
                if (Menu_editando)
                {
                    return SIGN_TECLA_ARRIBA;
                }
                return SIGN_TECLA_ABAJO;
            }
        }
        return 0;
    }
#endif


bool Teclado::_revivir_pantalla()
{
    if (!Pantalla_luz && !Teclado_locked_keys)
    {
        Pantalla::encender();
        FC::delayMilisegundos(100);
        reset();
        return 1;
    }
    return 0;
}

void Teclado::reset()
{
    Teclado_tecla_soltada = 0;
    Teclado_tecla_pulsada = 0;
    Teclado_tecla_sosteniendo = 0;
    Teclado_sosteniendo_timer_ = 0;
}

void Teclado::procesar_teclas()
{
    byte tecla = 0;
    if (digitalRead(PIN_TECLA_OK) == HIGH) 
    {
        tecla = SIGN_TECLA_OK;
    }
    if (digitalRead(PIN_TECLA_ATRAS) == HIGH) 
    {
        tecla = SIGN_TECLA_ATRAS;
    }

    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        if (digitalRead(PIN_TECLA_ARRIBA) == HIGH) 
        {
            tecla = SIGN_TECLA_ARRIBA;
        }
        if (digitalRead(PIN_TECLA_ABAJO) == HIGH) 
        {
            tecla = SIGN_TECLA_ABAJO;
        }
    #endif

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        //Leer rotary-encoder del mega_2560
        byte rotary_key = get_rotary_encoder();
        if (rotary_key) 
        {
            if (_revivir_pantalla()) 
            {
                return;
            }
            procesar_teclas_cortas(rotary_key);
            return;
        }
    #endif

    Teclado_tecla_soltada = 0;
    if (tecla)
    {
        if (_revivir_pantalla()) return;
        FC::delayMilisegundos(20); //Pausa antirebote
        if (!Teclado_tecla_pulsada)
        {
            Teclado_sosteniendo_timer_ = millis(); //Empieza a contar el sostener tecla desde la primera pulsación
            Teclado_tecla_sosteniendo = 0;
        }
        Teclado_tecla_pulsada = tecla;
        Teclado_tecla_soltada = 0;
    }
    else
    {
        Teclado_tecla_sosteniendo = 0;
        Teclado_sosteniendo_timer_ = 0;
        if (Teclado_tecla_pulsada) 
        {
            Teclado_tecla_soltada = Teclado_tecla_pulsada;
        }
        Teclado_tecla_pulsada = 0;
    }
    
    if (Teclado_sosteniendo_timer_ && millis() - Teclado_sosteniendo_timer_ > 1000)
    {
        Teclado_tecla_sosteniendo = tecla;
    }
    
    if (Teclado_tecla_soltada)
    {
        procesar_teclas_cortas(Teclado_tecla_soltada);
        reset();
        FC::delayMilisegundos(20); //Pausa antirebote
        return;
    }
    
    if (Teclado_tecla_sosteniendo)
    {
        procesar_teclas_largas(Teclado_tecla_sosteniendo);
        return;
    }
}

