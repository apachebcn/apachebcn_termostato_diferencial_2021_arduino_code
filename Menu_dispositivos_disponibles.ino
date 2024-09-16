void Menu_dispositivos_disponibles::imprimir(int menu_pos_id)
{
    byte bucle;
    byte total_on = 0;

    switch(menu_pos_id)
    {
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case G_DISPOSITIVOS_DE_ENTRADA:
                _imprimir_elemento(_contar_grupo_dispositivos_de_entrada());
                return;
        #endif 

        case G_DISPOSITIVOS_DE_SALIDA:
            _imprimir_elemento(_contar_grupo_dispositivos_de_salida());
            return;

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case AGUA_RELE_NUM:
                _imprimir_elemento(_contar_agua());
                return;
        #endif 

        case G_SONDAS:
            _imprimir_elemento(_contar_grupo_sondas());
            return;

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case G_BOMBAS:
                _imprimir_elemento(_contar_grupo_bombas());
                _imprimir_reles_bombas();
                return;
        #endif

        case G_CALENTADOR_DEPOSITO:
            _imprimir_elemento(_contar_calentador());
            return;

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case G_REFRIGERAR_COLECTORES:
                _imprimir_elemento(_contar_grupo_refrigeradores());
                return;
        #endif

        case G_EVENTOS:
            _imprimir_elemento(_contar_grupo_eventos());
            return;
    }

    for(bucle = 0; bucle < TOTAL_SONDAS_COLECTORES; bucle++)
    {
        if (menu_pos_id == Menu_grupal::get_id(G_BOMBA_1, bucle))
        {
            _imprimir_elemento(_contar_bomba_id(bucle));
            return;
        }

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            if (menu_pos_id == Menu_grupal::get_id(G_REFRIGERAR_COLECTOR_1, bucle))
            {
                _imprimir_elemento(_contar_refrigerador(bucle));
                return;
            }
        #endif
    }

    for(bucle = 0; bucle < TOTAL_EVENTOS; bucle++)
    {
        if (menu_pos_id == Menu_grupal::get_id(G_EVENTO_1, bucle))
        {
            _imprimir_info_extendida_evento(bucle);
            return;
        }
    }


    if (total_on) {lcd.write(' '); lcd.write('+'); lcd.print(total_on);}
}

/*
*
*   CONTADORES SINGULARES
*
*/
bool Menu_dispositivos_disponibles::_contar_sonda_colector_id(byte col_id)
{
    if (!Dispositivos.disponible(DISPOSITIVO_DE_ENTRADA_COLECTOR_1+col_id)) return 0;
    return 1;
}

bool Menu_dispositivos_disponibles::_contar_sonda_zona_id(byte zona_id)
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (!Dispositivos.disponible(DISPOSITIVO_DE_ENTRADA_ZONA_1+zona_id)) return 0;
        return 1;
    #endif
}

bool Menu_dispositivos_disponibles::_contar_bomba_id(byte col_id)
{
    if (!Dispositivos.disponible(DISPOSITIVO_DE_SALIDA_BOMBA_1+col_id)) return 0;
    if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_BOMBA_1+col_id) < 0) return 0;
    return 1;
}

bool Menu_dispositivos_disponibles::_contar_agua()
{
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    if (!Dispositivos.disponible(DISPOSITIVO_DE_SALIDA_AGUA)) return 0;
    if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_AGUA) < 0) return 0;
    return 1;
#endif
    return 0;
}

bool Menu_dispositivos_disponibles::_contar_calentador()
{
    if (!Dispositivos.disponible(DISPOSITIVO_DE_SALIDA_CALENTADOR)) return 0;
    if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_CALENTADOR) < 0) return 0;
    return 1;
}

bool Menu_dispositivos_disponibles::_contar_refrigerador(byte col_id)
{
    if (!Dispositivos.disponible(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1+col_id)) return 0;
    if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1+col_id) < 0) return 0;
    return 1;
}

bool Menu_dispositivos_disponibles::_contar_evento(byte evento_id)
{
    int dispositivo_id = 0;
    if (!Menu::get_valor(EVENTO_1_ON_OFF, evento_id)) return 0;
    dispositivo_id = Menu::get_valor(EVENTO_1_DISPOSITIVO, evento_id);
    if (dispositivo_id < 0) return 0;
    if (!Dispositivos.disponible(dispositivo_id)) return 0;
    if (!Menu::get_valor(EVENTO_1_RELE_NUM, evento_id)) return 0;
    return 1;
}

/*
*
*   CONTADORES GRUPALES
*
*/

byte Menu_dispositivos_disponibles::_contar_grupo_sondas()
{
    byte total_on = 0;
    for(byte col_id = 0; col_id < TOTAL_SONDAS_COLECTORES; col_id++)
    {
        if (_contar_sonda_colector_id(col_id)) total_on++;
    }
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        for(byte zona_id = 0; zona_id < TOTAL_SONDAS_ZONAS; zona_id++)
        {
            if (_contar_sonda_zona_id(zona_id)) total_on++;
        }
    #endif
    if (Dispositivos.disponible(DISPOSITIVO_DE_ENTRADA_DEPOSITO)) total_on++;
    if (Dispositivos.disponible(DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO)) total_on++;
    return total_on;
}

byte Menu_dispositivos_disponibles::_contar_grupo_bombas()
{
    byte total_on = 0;
    for(byte bomba_id = 0; bomba_id < TOTAL_SONDAS_COLECTORES; bomba_id++)
    {
        total_on += _contar_bomba_id(bomba_id);
    }
    return total_on;
}

byte Menu_dispositivos_disponibles::_contar_grupo_refrigeradores()
{
    byte total_on = 0;
    for(byte col_id = 0; col_id < TOTAL_SONDAS_COLECTORES; col_id++)
    {
        total_on += _contar_refrigerador(col_id);
    }
    return total_on;
}

byte Menu_dispositivos_disponibles::_contar_grupo_eventos()
{
    byte total_on = 0;
    for(byte evento_id = 0; evento_id < TOTAL_EVENTOS; evento_id++)
    {
        total_on += _contar_evento(evento_id);
    }
    return total_on;
}

byte Menu_dispositivos_disponibles::_contar_grupo_dispositivos_de_entrada()
{
    return _contar_agua()+_contar_grupo_sondas();
}

byte Menu_dispositivos_disponibles::_contar_grupo_dispositivos_de_salida()
{
    return _contar_grupo_bombas()+_contar_grupo_refrigeradores()+_contar_calentador();
}


/*
*
*   CONTADORES INFORMACION EXTENDIDA DE EVENTO_X
*
*/
void Menu_dispositivos_disponibles::_imprimir_info_extendida_evento(byte evento_id)
{
    if (!_contar_evento(evento_id)) return;

    lcd.write(' '); 
/*
    if (Menu::get_valor(EVENTO_1_ON_OFF, evento_id))
    {
        lcd.write(ICON_UP);
    }
    else
    {
        lcd.write(ICON_DOWN);
    }

    lcd.write(' '); 
*/

    lcd.print(Dispositivos.nombre_corto(Menu::get_valor(EVENTO_1_DISPOSITIVO, evento_id)));

    lcd.write(' '); 
    switch(Menu::get_valor(EVENTO_1_OPERACION, evento_id))
    {
        case 0: lcd.write('<'); break;
        case 1: lcd.write('>'); break;
    }

    lcd.write(' '); lcd.write('#');
    lcd.print(Menu::get_valor(EVENTO_1_RELE_NUM, evento_id));
}

void Menu_dispositivos_disponibles::_imprimir_elemento(byte total_on)
{
    if (!total_on) return;
    lcd.write(' '); 
    lcd.write('+'); 
    lcd.print(total_on);
}

void Menu_dispositivos_disponibles::_imprimir_reles_bombas()
{
    if (not _contar_grupo_bombas())
    {
        return;
    }

    lcd.write(' '); 
    byte total_on = 0;
    for(byte bomba_id = 0; bomba_id < TOTAL_SONDAS_COLECTORES; bomba_id++)
    {
        if (_contar_bomba_id(bomba_id))
        {
            lcd.write('#'); 
            lcd.write(Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_BOMBA_1+bomba_id));
        }
    }
}
