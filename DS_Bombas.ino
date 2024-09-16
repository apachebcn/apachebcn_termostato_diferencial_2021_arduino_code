void Bombas::init()
{
    for(int bomba_id = 0; bomba_id < TOTAL_SONDAS_COLECTORES; bomba_id++)
    {
/*
        Bombas_vars[bomba_id].actuando = 0;
        Bombas_vars[bomba_id].actuando_pulso = 0;
        Bombas_vars[bomba_id].pulso_timer_ = 0;
*/
    }
}

void Bombas::actualizar(byte bomba_id)
{
    int dispositivo_id;
    if (FC::is_debug(DEBUG_BOMBAS)) 
    {
        Serial_debug::println();
        Serial_debug::println(F("-- DEBUG ALGORITMO BOMBA"));
        Serial_debug::write(' '); Serial_debug::write('#'); Serial_debug::write(bomba_id+1);
        Serial_debug::write(' '); Serial_debug::write('-'); Serial_debug::write('-');
    }

    dispositivo_id = (DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id);
    Dispositivos.set_salida_valor(dispositivo_id, 0);
    _calculo_proceso(bomba_id);
    if (FC::is_debug(DEBUG_BOMBAS)) 
    {
        Serial_debug::write(' ');
        Serial_debug::write('['); 
        Serial_debug::print(F("Estado")); Serial_debug::write('=');
        switch(Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id))
        {
            case TRUE:    Serial_debug::print(F("ON")); break;
            case FALSE:   Serial_debug::print(F("OFF")); break;
        }
        Serial_debug::write(']'); Serial_debug::write(' ');
        Serial_debug::println();
    }
}

void Bombas::_calculo_proceso(int bomba_id)
{
    int dispositivo_id = (DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id);

    if (Dispositivos.inactivo(dispositivo_id))
    {
        _serial_print_mensaje_dispositivo_no_activado(dispositivo_id, Dispositivos.nombre(dispositivo_id));
        return;
    }
    if (!Dispositivos.disponible(dispositivo_id))
    {
        _serial_print_mensaje_dispositivo_no_disponible(dispositivo_id, Dispositivos.nombre(dispositivo_id));
        return;
    }

    /*
    *
    * PROCESAR PROTECCION DE COLECTORES (ANTICONGELACION)
    * Si la sonda es menor del valor configurado, mantiene en marcha la bomba
    */
    if (Dispositivos.get_entrada_valor(DISPOSITIVO_DE_ENTRADA_COLECTOR_1 + bomba_id) < Menu::get_valor(CONTROL_BOMBA_1_RUN_SI_COLECTOR_MENOR_DE_TEMP, bomba_id))
    {
        Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id, 1);
        if (FC::is_debug(DEBUG_BOMBAS)) 
        {
            Serial_debug::print(F("Forzado automatico porque")); Serial_debug::write(' ');
            Serial_debug::print(F("Proteccion termica del colector, porque temp_col("));
            Serial_debug::print(Dispositivos.get_entrada_valor(DISPOSITIVO_DE_ENTRADA_COLECTOR_1 + bomba_id));

            Serial_debug::write(')'); Serial_debug::write(' '); Serial_debug::write('<'); Serial_debug::write(' ');
            Serial_debug::print(F("bomba_run_si_col_menor_de_temp")); Serial_debug::write('(');
            Serial_debug::print(Menu::get_valor(CONTROL_BOMBA_1_RUN_SI_COLECTOR_MENOR_DE_TEMP, bomba_id));
            Serial_debug::println();
        }
        Dispositivos.set_salida_valor(dispositivo_id, 1);
        return;
   }

    /*
    *
    * PROCESAR PROTECCION DE DEPOSITOS DELICADOS (COMUNMENTE DE PLASTICO DESPRESURIZADOS)
    * Si la sonda es mayor del valor configurado, mantiene parada la bomba
    */
    float col_temp;
    float dep_temp;
    int diff;


// ... FALTA EL CODIGO


    col_temp = Dispositivos.get_entrada_valor(DISPOSITIVO_DE_ENTRADA_COLECTOR_1 + bomba_id);
    dep_temp = Dispositivos.get_entrada_valor(DISPOSITIVO_DE_ENTRADA_DEPOSITO);

    switch(Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id))
    {
        case TRUE: //CAMBIO DE ESTADO A TRUE
            diff = Menu::get_valor(CONTROL_BOMBA_1_DIFF_TO_OFF, bomba_id);
            if ((diff+dep_temp) >= col_temp)
            {
                /*
                * CAMBIO DE ESTADO A FALSE
                */
                Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id, 0);

                // Reseteo parametros de bomba pulsada por cambio de estado
                //Bombas_vars[bomba_id].actuando_pulso = 0;
                //Bombas_vars[bomba_id].pulso_timer_ = 0;

                if (FC::is_debug(DEBUG_BOMBAS)) 
                {
                    Serial_debug::write(' ');
                    Serial_debug::print(F("cambia a OFF.")); Serial_debug::write(' ');
                    Serial_debug::print(F("Porque (diff+dep_temp) >= col_temp"));
                    Serial_debug::write(';'); Serial_debug::write(' ');
                    Serial_debug::print(F("col_temp")); Serial_debug::write('=');
                    Serial_debug::print(col_temp);
                    Serial_debug::write(';'); Serial_debug::write(' ');
                    Serial_debug::print(F("temp_dep")); Serial_debug::write('=');
                    Serial_debug::print(dep_temp);
                    Serial_debug::write(';'); Serial_debug::write(' ');
                    Serial_debug::print(F("diff")); Serial_debug::write('=');
                    Serial_debug::print(diff);
                    Serial_debug::write(' ');
                }
            }
            break;

        default: 
            diff = Menu::get_valor(CONTROL_BOMBA_1_DIFF_TO_ON, bomba_id);
            if (col_temp >= (diff+dep_temp))
            {
                /*
                * CAMBIO DE ESTADO A TRUE
                */
                Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id, 1);

                // Reseteo parametros de bomba pulsada por cambio de estado
                //Bombas_vars[bomba_id].actuando_pulso = 0;
                //Bombas_vars[bomba_id].pulso_timer_ = 0;

                if (FC::is_debug(DEBUG_BOMBAS)) 
                {
                    Serial_debug::write(' ');
                    Serial_debug::print(F("cambia a ON.")); Serial_debug::write(' ');
                    Serial_debug::print(F("col_temp >= (diff+dep_temp)"));
                    Serial_debug::write(';'); Serial_debug::write(' ');
                    Serial_debug::print(F("col_temp")); Serial_debug::write('=');
                    Serial_debug::print(col_temp);
                    Serial_debug::write(';'); Serial_debug::write(' ');
                    Serial_debug::print(F("temp_dep")); Serial_debug::write('=');
                    Serial_debug::print(dep_temp);
                    Serial_debug::write(';'); Serial_debug::write(' ');
                    Serial_debug::print(F("diff")); Serial_debug::write('=');
                    Serial_debug::print(diff);
                    Serial_debug::write(' ');
                }
            }
            break;
    }

    switch(Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id))
    {
        case TRUE:
            Dispositivos.set_salida_valor(dispositivo_id, 1);
            break;
        case FALSE:
            Dispositivos.set_salida_valor(dispositivo_id, 0);
    }
}

void Bombas::accion_forzar(int bomba_id)
{
/*
    if (Bombas_vars[bomba_id].forzada)
    {
        Bombas_vars[bomba_id].forzada = 0;
        return;
    }
    int rele_id;
    if (!Menu::get_valor(SONDAS_ON_OFF)) {Buzzer::beep_error();return;}
    if (!Menu::get_valor(RELES_ON_OFF)) {Buzzer::beep_error();return;}
    if (!Sondas::test_addr_dir(Sondas_colector_dir[bomba_id])) {Buzzer::beep_error();return;}
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (!Menu::get_valor(SONDA_COLECTOR_1_ON_OFF, bomba_id)) {Buzzer::beep_error();return;}
    #endif
    rele_id = Menu::get_valor(BOMBA_1_RELE_NUM, bomba_id);
    rele_id--;
    if (rele_id < 0) {Buzzer::beep_error();return;}
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (Menu::get_valor(RELE_ESTADO_1, rele_id) > RELE_FLAG_AUTO_ON) {Buzzer::beep_error();return;}
    #endif
    Bombas_vars[bomba_id].forzada = 1;
    Buzzer::beep();
    return;
*/
}


void Bombas::_serial_print_mensaje_dispositivo_no_activado(int dispositivo_id, const __FlashStringHelper*  dispositivo_nombre)
{
    if (FC::is_debug(DEBUG_BOMBAS)) 
    {
        Serial_debug::print(F("Inhibido porque")); Serial_debug::write(':'); Serial_debug::write(' ');
        Serial_debug::write('['); 
        Serial_debug::print(dispositivo_nombre);
        Serial_debug::write(' '); 
        Serial_debug::print(F("APAGADO")); 
        Serial_debug::write(']');
    }
}

void Bombas::_serial_print_mensaje_dispositivo_no_disponible(int dispositivo_id, const __FlashStringHelper*  dispositivo_nombre)
{
    if (FC::is_debug(DEBUG_BOMBAS)) 
    {
        Serial_debug::print(F("Inhibido porque")); Serial_debug::write(':'); Serial_debug::write(' ');
        Serial_debug::write('['); 
        Serial_debug::print(dispositivo_nombre);
        Serial_debug::write(' '); 
        Serial_debug::print(F("NO DISPONIBLE")); 
        Serial_debug::write(']');
    }
}

