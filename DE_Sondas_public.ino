void Sondas::actualiza_pin()
{
    if (_activado())
    {
        pinMode(PIN_SONDAS, INPUT); 
    }
    else
    {
        pinMode(PIN_SONDAS, 0); 
    }
}

void Sondas::init()
{
    byte sonda_id;
    byte dir_bit;

    for (sonda_id = 0; sonda_id < LAST_SONDA; sonda_id++)
    {
        for (dir_bit = 0; dir_bit < 8; dir_bit++)
        {
            SondasElementos[sonda_id].dir[dir_bit] = 0;
        }
    }

    for(sonda_id = 0; sonda_id < TOTAL_SONDAS_COLECTORES; sonda_id++)
    {
        for(dir_bit = 0; dir_bit < 8; dir_bit++)
        {
            Sondas_colector_dir[sonda_id][dir_bit] = 0;
        }
    }
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        for(sonda_id = 0; sonda_id < TOTAL_SONDAS_ZONAS; sonda_id++)
        {
            for(dir_bit = 0; dir_bit < 8; dir_bit++)
            {
                Sondas_zona_dir[sonda_id][dir_bit] = 0;
            }
        }
    #endif

    for(dir_bit = 0; dir_bit < 8; dir_bit++)
    {
        Sondas_deposito_dir[dir_bit] = 0;
    }

    for(dir_bit = 0; dir_bit < 8; dir_bit++)
    {
        Sondas_ztermostato_dir[dir_bit] = 0;
    }
}

bool Sondas::test_dir(byte* sonda_addr)
{
    if (!test_addr_dir(sonda_addr)) return FALSE;
    return TRUE;
}

void Sondas::lcd_print_addr_dir(byte* dir)
{
    for(byte p = 0; p < 8; p++)
    {
        if (dir[p] < 16) 
        {
            lcd.write('0');
        }
        lcd.print(dir[p], HEX);
    }
}

void Sondas::lcd_print_addr_sonda_id(int sonda_id)
{
    if (sonda_id < 0)
    {
        for(byte i=0; i < 16; i++) 
        {
            lcd.write('0');
        }
        return;
    }
    lcd_print_addr_dir(SondasElementos[sonda_id].dir);
}

void Sondas::serial_print_addr_dir(byte* dir)
{
    #ifndef ABLE_SERIAL_DEBUG
        return;
    #endif
    for(byte p = 0; p < 8; p++)
    {
        if (dir[p] < 16) 
        {
            Serial.write('0');
        }
        Serial.print(dir[p], HEX);
    }
}

void Sondas::serial_print_addr_sonda_id(int sonda_id)
{
    #ifndef ABLE_SERIAL_DEBUG
        return;
    #endif
    if (sonda_id < 0 or sonda_id > (LAST_SONDA-1))
    {
        for(byte i=0; i < 16; i++) 
        {
            Serial.write('0');
        }
        return;
    }
    serial_print_addr_dir(SondasElementos[sonda_id].dir);
}

float Sondas::convert_temp(int temp)
{
    float celsius = temp * 0.0625;
    if (Menu::get_valor(SONDAS_ESCALA) == 0) //Celsius
    {
        return celsius;
    }
    float farenheit = celsius * 9 / 5 + 32;
    return farenheit;
}

bool Sondas::test_addr_dir(byte* dir)
{
    for(byte dir_bit = 0; dir_bit < 8; dir_bit++)
    {
        if (dir[dir_bit] != 0) 
        {
            return TRUE;
        }
    }
    return FALSE;
}

int Sondas::buscar_addr_dir(byte* dir)
{
    if (!test_addr_dir(dir)) return -1;
    for(byte sonda_id = 0; sonda_id < (Sondas_total_escaneadas); sonda_id++)
    {
        if (comparar_addr_dir(SondasElementos[sonda_id].dir, dir)) 
        {
            return sonda_id;
        }
    }
    return -1;
}

bool Sondas::comparar_addr_dir(byte* src_dir, byte* dst_dir)
{
    for(byte dir_bit = 0; dir_bit < 8; dir_bit++)
    {
        if (src_dir[dir_bit] != dst_dir[dir_bit])
        {
            return FALSE;
        }
    }
    return TRUE;
}

void Sondas::copiar_sonda_id_a(int sonda_id, byte* dst_dir)
{
    for(byte dir_bit = 0; dir_bit < 8; dir_bit++)
    {
        if (sonda_id > -1)
        {
            dst_dir[dir_bit] = SondasElementos[sonda_id].dir[dir_bit];
        }
        else
        {
            dst_dir[dir_bit] = 0;
        }
    }
}

void Sondas::esperar_disponibilidad()
{
    if (!Sondas::_activado())
    {
        Buzzer::beep_error(); 
        return;
    }

    //if (!Sondas_total_escaneadas) return;

    byte total_veces = 40;
    byte veces = 1;
    while (veces < (total_veces+1))
    {
        if (!Menu_activo)
        {
            Pantalla::borrar_fila(PANTALLA_ALTO_PX-1);
            lcd.print(F("Esperando sondas "));
        }
        if (FC::is_debug(DEBUG_SONDAS))
        {
            Serial_debug::print(F("Esperando sondas "));
            Serial_debug::print(veces); Serial_debug::write('/'); Serial_debug::println(total_veces);
        }

        bool sondas_ok = 1;
//        if (veces % 2) scan();
        for(byte sonda_id=0; sonda_id < Sondas_total_escaneadas; sonda_id++)
        {
            if (!Sondas::test_addr_dir(SondasElementos[sonda_id].dir)) sondas_ok = 0;
            if (Sondas::(SondasElementos[sonda_id].dir, 0) == VALOR_RESET_O_ERROR) sondas_ok = 0;
            //if (Sondas::busca_dir(SondasElementos[0].dir, 0) < 0) sondas_ok = 0;
        }
        if (sondas_ok)
        {
            Pantalla::borrar_fila(PANTALLA_ALTO_PX-1);
            lcd.print(F("Sondas OK")); 
            FC::delayMilisegundos(200);
            return;
        }
        FC::delayMilisegundos(500);
        veces++;
    }
    Pantalla::borrar_fila(PANTALLA_ALTO_PX-1);
    lcd.print(F("Sondas ERROR")); 
    Buzzer::beep_error(); 
    return;
}

void Sondas::scan()
{

    if (!_activado()) 
    {
        Serial_debug::println(F("Sondas OFF"));
        return;
    }

    if (FC::is_debug(DEBUG_SONDAS))
    {
        Serial_debug::println();
        Serial_debug::println(); Serial_debug::println(F("-- DEBUG SONDAS (scan) --"));
        Serial_debug::println(F("Sondas memorizadas antes de este escaneo:"));
        for (byte sonda_id = 0; sonda_id < LAST_SONDA; sonda_id++)
        {
            Serial_debug::write('#'); Serial_debug::print(sonda_id+1); Serial_debug::write(':'); 
            Serial_debug::write(' '); 
            serial_print_addr_sonda_id(sonda_id); 
            Serial_debug::println();
        }
    }

    if (!Menu_activo)
    {
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            if (!Pantalla_vista_atajos_activado)
        #endif
        {
            Pantalla::print_centrado(F("SCANING..."), DISPLAY_INFO_POS_Y);
        }
    }

    byte dir_bit;
    byte sonda_id;

    if (FC::is_debug(DEBUG_SONDAS))
    {
        Serial_debug::println(F("Escaneando sondas"));
    }

    int sonda_id_escaneando = -1;
    byte sonda_escaneada_dir[8];
    while(dallas_sondas_wires.search(sonda_escaneada_dir)) 
    {
        sonda_id_escaneando++;
        if (sonda_id_escaneando == LAST_SONDA)
        {
            break;
        } 

        if (FC::is_debug(DEBUG_SONDAS))
        {
            Serial_debug::print(F("Escaneando Sonda")); 
            Serial_debug::write(' '); Serial_debug::write('#'); 
            Serial_debug::print(sonda_id_escaneando+1); 
            Serial_debug::write(' ');
        }

        if ( OneWire::crc8( sonda_escaneada_dir, 7) != sonda_escaneada_dir[7]) 
        {
            if (FC::is_debug(DEBUG_SONDAS)) Serial_debug::println(F("CRC Error"));
            continue;
        }

        switch(sonda_escaneada_dir[0]) 
        {
            case 0x10:
                if (FC::is_debug(DEBUG_SONDAS))
                {
                    Serial_debug::print(F("Chip DS18S20 (or old DS1820). "));
                }
                break;
            case 0x28:
                if (FC::is_debug(DEBUG_SONDAS))
                {
                    Serial_debug::print(F("Chip DS18B20. "));
                }
                break;
            case 0x22:
                if (FC::is_debug(DEBUG_SONDAS))
                {
                    Serial_debug::print(F("Chip DS1822. "));
                }
                break;
            default:
                if (FC::is_debug(DEBUG_SONDAS))
                {
                    Serial_debug::print(F("Chip no familia DS18x20 "));
                }
                continue;
        }
 
        _WriteScratchPad(sonda_escaneada_dir); // write scratchpad configuration, ask for a 9, 10, 11 or 12 bits resolution

        /*
            int sonda_id = buscar_addr_dir(sonda_escaneada_dir);

            if (FC::is_debug(DEBUG_SONDAS))
            {
                serial_print_addr_dir(sonda_escaneada_dir); Serial_debug::write(' ');
                Serial_debug::print("[Coincide con la sonda memorizada: "); Serial_debug::print(sonda_id); Serial_debug::write(']'); Serial_debug::write(' ');
            }

            if (sonda_id > -1 && sonda_id == sonda_id_escaneando)
            {
                if (FC::is_debug(DEBUG_SONDAS)) Serial_debug::println();
                continue;
            }

            if (sonda_id < 0 && sonda_id != sonda_id_escaneando)
            {
                if (FC::is_debug(DEBUG_SONDAS)) Serial_debug::print(F(" [SONDA CAMBIADA, RESET DE VALORES]")); 
                //SONDA NUEVA O HA CAMBIADO DE POSICION
                SondasElementos[sonda_id_escaneando].temp = VALOR_RESET_O_ERROR;
                SondasElementos[sonda_id_escaneando].stat_min = VALOR_RESET_O_ERROR;
                SondasElementos[sonda_id_escaneando].stat_max = VALOR_RESET_O_ERROR;
            }
        */

        if (FC::is_debug(DEBUG_SONDAS)) Serial_debug::println(F(" Copiando direccion"));

        for(byte dir_bit = 0; dir_bit < 8; dir_bit++)
        {
            SondasElementos[sonda_id_escaneando].dir[dir_bit] = sonda_escaneada_dir[dir_bit];
        }
    }

    dallas_sondas_wires.reset_search();
    Sondas_total_escaneadas = sonda_id_escaneando+1;

    if (FC::is_debug(DEBUG_SONDAS))
    {
        Serial_debug::print(F("Fin escaneo. Total Sondas="));
        Serial_debug::println(Sondas_total_escaneadas); 
        Serial_debug::println(F("-- DEBUG SONDAS (lee temp) --"));
        for(sonda_id=0; sonda_id < Sondas_total_escaneadas; sonda_id++)
        {
            Serial_debug::write('#'); Serial_debug::print(sonda_id+1); Serial_debug::write(':'); Serial_debug::write(' '); 
            lee_la_sonda_num(sonda_id, 1);
            Serial_debug::write('.');
            Serial_debug::println();
        }
        Serial_debug::println(F("Fin lectura"));
    }

}

float Sondas::lee_la_sonda_dir(byte* dir, bool usa_debug)
{
    float temp;
    temp = _lee_temp(dir, usa_debug);
    if (temp == VALOR_RESET_O_ERROR) temp = _lee_temp(dir, usa_debug);
    if (temp == VALOR_RESET_O_ERROR) return VALOR_RESET_O_ERROR;
    return convert_temp(temp);
}

float Sondas::lee_la_sonda_num(int sonda_num, bool usa_debug)
{
    float temp;
    temp = _lee_temp(SondasElementos[sonda_num].dir, usa_debug);
    if (temp == VALOR_RESET_O_ERROR) temp = _lee_temp(SondasElementos[sonda_num].dir, usa_debug);
    if (temp == VALOR_RESET_O_ERROR) return VALOR_RESET_O_ERROR;
    return convert_temp(temp);
}
