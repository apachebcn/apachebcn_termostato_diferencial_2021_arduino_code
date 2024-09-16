void Pantalla::_print_pantalla_alarmas_valor(int dispositivo_entrada_id)
{
    if (Dispositivos_alarmas.get_alarma(dispositivo_entrada_id))
    {
        if (Dispositivos_alarmas.get_alarma_silenciada(dispositivo_entrada_id))
        {
            lcd.print(F("MUTE"));
        }
        else
        {
            lcd.print(F("ON"));
        }
    }
    else
    {
        if (Dispositivos_alarmas.get_alarma_recordada(dispositivo_entrada_id))
        {
            lcd.print(F("MEM"));
        }
    }
}

void Pantalla::_imprime_dispositivo_valor(byte modo_vista, byte posX, byte posY, int dispositivo_entrada_id, char icono_dispositivo, char icono_caracter_sufijo, bool decimales)
{
    float valor;
    char icono_dispositivo_accion = Dispositivos.get_estado_icono(dispositivo_entrada_id);

    switch(modo_vista)
    {
        case VISTA_STAT_MIN:
            valor = Dispositivos.get_entrada_valor_min(dispositivo_entrada_id);
            break;
        case VISTA_STAT_MAX:
            valor = Dispositivos.get_entrada_valor_max(dispositivo_entrada_id);
            break;
        default:
            valor = Dispositivos.get_entrada_valor(dispositivo_entrada_id);
            break;
    }


    int valor_int = (int)valor;
    if (decimales)
    {
        sprintf(Pantalla_buffer_segmento, "%c%c%d.%d%c", icono_dispositivo, icono_dispositivo_accion, valor_int, _get_dec(valor), icono_caracter_sufijo);
    }
    else
    {
        sprintf(Pantalla_buffer_segmento, "%c%c%d%c", icono_dispositivo, icono_dispositivo_accion, valor_int, icono_caracter_sufijo);
    }

    for(byte l=strlen(Pantalla_buffer_segmento); l<(PANTALLA_ANCHO_PX/2); l++) 
    {
        Pantalla_buffer_segmento[l] = ' ';
    }

    lcd.setCursor(posX, posY);
    lcd.print(Pantalla_buffer_segmento);
}

void Pantalla::_imprime_dispositivo_inactivado(byte posX, byte posY, char icono_dispositivo)
{
    for(byte i=0; i<(PANTALLA_ANCHO_PX/2); i++)
    {
        switch(i)
        {
            case 0: 
                Pantalla_buffer_segmento[0] = icono_dispositivo;
                break;
            case 1:
            case (PANTALLA_ANCHO_PX/2)-1:
                Pantalla_buffer_segmento[i] = ' ';
                break;
            default:
                Pantalla_buffer_segmento[i] = '-';
        }
    }

    lcd.setCursor(posX, posY);
    lcd.print(Pantalla_buffer_segmento);
}

void Pantalla::_imprime_dispositivo_indisponible(byte posX, byte posY, char icono_dispositivo)
{
    //Imprime N/D
    for(byte i=0; i<(PANTALLA_ANCHO_PX/2); i++)
    {
        switch(i)
        {
            case 0: 
                Pantalla_buffer_segmento[0] = icono_dispositivo;
                break;
            case 1:
            case (PANTALLA_ANCHO_PX/2)-1:
                Pantalla_buffer_segmento[i] = ' ';
                break;
            case 4:
                Pantalla_buffer_segmento[i] = 'N';
                break;
            case 5:
                Pantalla_buffer_segmento[i] = '/';
                break;
            case 6:
                Pantalla_buffer_segmento[i] = 'D';
                break;
            default:
                Pantalla_buffer_segmento[i] = '-';
        }
    }

    lcd.setCursor(posX, posY);
    lcd.print(Pantalla_buffer_segmento);
}

void Pantalla::_imprime_dispositivo_error(byte posX, byte posY, char icono_dispositivo)
{
    for(byte i=0; i<(PANTALLA_ANCHO_PX/2); i++)
    {
        switch(i)
        {
            case 0: 
                Pantalla_buffer_segmento[0] = icono_dispositivo;
                break;
            case 2: Pantalla_buffer_segmento[i] = 'E'; break;
            case 3: case 4: Pantalla_buffer_segmento[i] = 'R'; break;
            default:
                Pantalla_buffer_segmento[i] = ' ';
        }
    }

    lcd.setCursor(posX, posY);
    lcd.print(Pantalla_buffer_segmento);
}

void Pantalla::_imprime_dispositivo_id(byte modo_vista, byte posX, byte posY, bool decimales, int dispositivo_entrada_id, char icono_dispositivo, char icono_caracter_sufijo)
{

    if (Dispositivos.error(dispositivo_entrada_id))
    {
        // ERROR
        _imprime_dispositivo_error(posX, posY, icono_dispositivo);
        return;
    }

    if (Dispositivos.inactivo(dispositivo_entrada_id))
    {
        // NO ACTIVADO
        _imprime_dispositivo_inactivado(posX, posY, icono_dispositivo);
        return;
    }

    if (!Dispositivos.disponible(dispositivo_entrada_id))
    {
        // NO DISPONIBLE
        _imprime_dispositivo_indisponible(posX, posY, icono_dispositivo);
        return;
    }

    // ICONO STOP PARA INDICAR QUE EL DISPOSITIVO ESTÁ ESPERANDO UNA ACCIÓN
    bool esperando_accion = 0;
    if (Dispositivos.get_estado_icono(dispositivo_entrada_id) == ' ')
    {
        esperando_accion = 0;
        int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_entrada_id);
        switch(dispositivo_grupo_id)
        {
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                case DISPOSITIVO_DE_ENTRADA_AGUA:
                    if (Dispositivos.disponible(DISPOSITIVO_DE_ENTRADA_AGUA)) esperando_accion = 1;
                    if (Dispositivos_eventos.disponible(DISPOSITIVO_DE_ENTRADA_AGUA)) esperando_accion = 1;
                    break;
                case DISPOSITIVO_DE_ENTRADA_ZONA_1:
                    if (Dispositivos_eventos.disponible(DISPOSITIVO_DE_ENTRADA_ZONA_1+(dispositivo_entrada_id-dispositivo_grupo_id))) esperando_accion = 1;
                    break;
            #endif
            case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:

                if (Dispositivos.disponible(DISPOSITIVO_DE_SALIDA_BOMBA_1 +(dispositivo_entrada_id-dispositivo_grupo_id))) esperando_accion = 1;
                if (Dispositivos.disponible(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1+(dispositivo_entrada_id-dispositivo_grupo_id))) esperando_accion = 1;
                if (Dispositivos_eventos.disponible(DISPOSITIVO_DE_ENTRADA_COLECTOR_1+(dispositivo_entrada_id-dispositivo_grupo_id))) esperando_accion = 1;
                break;
            case DISPOSITIVO_DE_ENTRADA_DEPOSITO:
                if (Dispositivos.disponible(DISPOSITIVO_DE_SALIDA_CALENTADOR)) esperando_accion = 1;
                if (Dispositivos_eventos.disponible(DISPOSITIVO_DE_ENTRADA_DEPOSITO)) esperando_accion = 1;
                break;
            case DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO:
                if (Dispositivos_eventos.disponible(DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO)) esperando_accion = 1;
                break;
        }
        if (esperando_accion)
        {
            Dispositivos.set_estado_icono(dispositivo_entrada_id, ICON_STOP);
        }
    }
    _imprime_dispositivo_valor(modo_vista, posX, posY, dispositivo_entrada_id, icono_dispositivo, icono_caracter_sufijo, decimales);
}

