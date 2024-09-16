void Reles::init()
{
    for(byte i = 0; i < TOTAL_RELES; i++)
    {
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            Reles_activado_por_dispositivo[i] = RELE_ACTIVADO_NADA;
        #endif
        Reles_estado[i] = 0;
    }

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        /*
        *   SETEO DE RELES FORZADOS CONFIGURADOS EN MENU
        *
        */
        for(byte rele_id = 0; rele_id < TOTAL_RELES; rele_id++)
        {
            byte menu_rele_estado = Menu::get_valor(RELE_ESTADO_1+rele_id);
            switch(menu_rele_estado)
            {
                case RELE_FLAG_AUTO_OFF:
                case RELE_FLAG_AUTO_ON:
                    break;
                case RELE_FLAG_FORZADO_ON:
                case RELE_FLAG_FORZADO_OFF:
                    Reles_estado[rele_id] = menu_rele_estado;
            }
        }
    #endif
}

bool Reles::disponible()
{
    return (bool)Menu::get_valor(RELES_ON_OFF);
}

void Reles::set_valor(int rele_id, byte nuevo_estado, byte desde_dispositivo_num)
{
    if (rele_id < 0) return;
    if (rele_id > TOTAL_RELES) return;
    if (FC::is_debug(DEBUG_RELES)) 
    {
        Serial_debug::println();
        Serial_debug::print(F("-- DEBUG RELES --"));
        Serial_debug::print(F("Setea rele #")); Serial_debug::print(rele_id+1); 
        Serial_debug::print(F(" a ")); _serial_print_debug_estado(nuevo_estado);
        Serial_debug::write(' '); Serial_debug::write('['); 
        _serial_print_debug_dispositivo_activado_desde_rele(desde_dispositivo_num);
        Serial_debug::write(']'); 
    }
    Reles_estado[rele_id] = nuevo_estado;

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (Menu::get_valor(RELE_ESTADO_1+rele_id) == RELE_FLAG_FORZADO_ON)
        {
            Reles_estado[rele_id] = RELE_FLAG_FORZADO_ON;
            if (FC::is_debug(DEBUG_RELES)) 
            {
                Serial_debug::write(' '); Serial_debug::print(F("Pero prevalece el forzado"));
                Serial_debug::write(' '); Serial_debug::print(F("ON"));
            }
        }
        if (Menu::get_valor(RELE_ESTADO_1+rele_id) == RELE_FLAG_FORZADO_OFF)
        {
            Reles_estado[rele_id] = RELE_FLAG_FORZADO_OFF;
            if (FC::is_debug(DEBUG_RELES)) 
            {
                Serial_debug::write(' '); Serial_debug::print(F("Pero prevalece el forzado"));
                Serial_debug::write(' '); Serial_debug::print(F("OFF"));
            }
        }
    #endif
    if (FC::is_debug(DEBUG_RELES)) 
    {
        Serial_debug::println();
    }
}

void Reles::set_valores(byte nuevo_estado)
{
    for(byte i = 0; i < TOTAL_RELES; i++)
    {
        set_valor(i, nuevo_estado, RELE_ACTIVADO_NADA);
    }
}

byte Reles::get_valor(int rele_id)
{
    if (rele_id < 0) return 0;
    if (rele_id > TOTAL_RELES) return 0;
    return Reles_estado[rele_id];
}

void Reles::test()
{
    bool abortar = 0;
    byte num_rele;
    unsigned long time_start;
    if (!disponible())
    {
        _activar();
    }

    //Reles off
    for(num_rele = 0; num_rele < TOTAL_RELES; num_rele++) _actuar_testing(num_rele, RELE_FLAG_AUTO_OFF);

    for(num_rele = 0; num_rele < TOTAL_RELES; num_rele++)
    {
        if (abortar) break;
        Pantalla::borrar_fila(0); lcd.write('#'); lcd.print(num_rele+1);
        Buzzer::beep();

        //Rele on
        _actuar_testing(num_rele, RELE_FLAG_AUTO_ON);
        time_start = millis();           
        for (;;) 
        {
            if (digitalRead(PIN_TECLA_ATRAS) == HIGH) abortar = 1;
            if (abortar || (millis() - time_start) >= 1000)
            {                
                break;
            }
        }

        //Rele off
        _actuar_testing(num_rele, RELE_FLAG_AUTO_OFF);
        time_start = millis();           
        for (;;) 
        {
            if (digitalRead(PIN_TECLA_ATRAS) == HIGH) abortar = 1;
            if (abortar || (millis() - time_start) >= 1000)
            {                
                break;
            }
        }

        DogWatch_update();
    }

    //Reles off
    for(num_rele = 0; num_rele < TOTAL_RELES; num_rele++) _actuar_testing(num_rele, RELE_FLAG_AUTO_OFF);

    if (!disponible())
    {
        _desactivar();
    }
}

void Reles::_serial_print_debug_estado(byte estado)
{
    switch(estado)
    {
        case RELE_FLAG_FORZADO_ON:
            Serial_debug::print(F("FORZADO ON"));
            break;
        case RELE_FLAG_FORZADO_OFF:
            Serial_debug::print(F("FORZADO OFF"));
            break;
        case RELE_FLAG_AUTO_ON:
            Serial_debug::print(F("ON"));
            break;
        case RELE_FLAG_AUTO_OFF:
            Serial_debug::print(F("OFF"));
            break;
    }
}

void Reles::_serial_print_debug_dispositivo_activado_desde_rele(int rele_id)
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        byte colector_num;

        for(colector_num = 0; colector_num < TOTAL_SONDAS_COLECTORES; colector_num++)
        {
            if (rele_id == (RELE_ACTIVADO_POR_BOMBA_1 + colector_num))
            {
                Serial_debug::print(F("Bomba")); Serial_debug::write(' '); Serial_debug::print(rele_id-RELE_ACTIVADO_POR_BOMBA_1+colector_num);
                return;
            }
            if (rele_id == (RELE_ACTIVADO_POR_REFRIGERAR_COLECTOR_COLECTOR_1 + colector_num))
            {
                Serial_debug::print(F("Refrigerador de colector #")); Serial_debug::write(' '); Serial_debug::print(rele_id-RELE_ACTIVADO_POR_REFRIGERAR_COLECTOR_COLECTOR_1+colector_num);
                return;
            }
            if (rele_id == (RELE_ACTIVADO_POR_EVENTO_1 + colector_num))
            {
                Serial_debug::print(F("Refrigerador de colector #")); Serial_debug::write(' '); Serial_debug::print(rele_id-RELE_ACTIVADO_POR_EVENTO_1+colector_num);
                return;
            }
        }

        switch(rele_id)
        {
            case RELE_ACTIVADO_INICIO:
                Serial_debug::print(F("Posicionamiento de inicio"));
                break;

            case RELE_ACTIVADO_POR_CALENTADOR_DEPOSITO:
                Serial_debug::print(F("Calentador de deposito"));
                break;

            case RELE_ACTIVADO_POR_AGUA:
                Serial_debug::print(F("Agua"));
                break;
        }
    #endif
}
