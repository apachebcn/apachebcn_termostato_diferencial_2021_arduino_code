void Menu_imprimir_fila::_imprime_derecha_int_con_prefijo(int texto, char prefijo, byte fila)
{
    byte len = FC::Int_len(texto) + 1;
    lcd.setCursor(PANTALLA_ANCHO_PX - len, fila); 
    lcd.write(prefijo); lcd.print(texto);
}

void Menu_imprimir_fila::_imprime_derecha_int_con_sufijo(int texto, char sufijo, byte fila)
{
    byte len = FC::Int_len(texto) + 1;
    lcd.setCursor(PANTALLA_ANCHO_PX - len, fila); 
    lcd.print(texto); lcd.write(sufijo);
}

void Menu_imprimir_fila::_imprime_derecha_int_con_sufijo(int texto, const __FlashStringHelper* sufijo, byte fila)
{
    byte len_1 = FC::Int_len(texto);
    byte len_2 = FC::FlashStringHelper_len(sufijo, PANTALLA_ANCHO_PX);
    lcd.setCursor(PANTALLA_ANCHO_PX - (len_1+len_2), fila); 
    lcd.print(texto); lcd.print(sufijo);
}

void Menu_imprimir_fila::_imprime_derecha_prefijo_y_dir(int texto, char prefijo, byte fila)
{
    byte len = FC::Int_len(texto) + 4 + 1;
    lcd.setCursor(PANTALLA_ANCHO_PX - len, fila); 
    lcd.print(prefijo);
    lcd.print(F("DIR-"));
    lcd.print(texto);
}

void Menu_imprimir_fila::_imprime_derecha(int texto, byte fila)
{
    lcd.setCursor(PANTALLA_ANCHO_PX - FC::Int_len(texto), fila); 
    lcd.print(texto);
}

void Menu_imprimir_fila::_imprime_derecha(char* texto, byte fila)
{
    byte len = strlen(texto);
    lcd.setCursor(PANTALLA_ANCHO_PX - len, fila); 
    lcd.print(texto);
}

void Menu_imprimir_fila::_imprime_derecha(char caracter, byte fila)
{
    lcd.setCursor(PANTALLA_ANCHO_PX - 1, fila); 
    lcd.write(caracter);
}

void Menu_imprimir_fila::_imprime_derecha(const __FlashStringHelper* texto, byte fila)
{
    byte len = FC::FlashStringHelper_len(texto, PANTALLA_ANCHO_PX);
    lcd.setCursor(PANTALLA_ANCHO_PX - len, fila); lcd.print(texto);
}

void Menu_imprimir_fila::imprimir(int menu_pos_id, byte fila)
{
    if (menu_pos_id < 1) 
    {
        Pantalla::borrar_fila(fila); 
        return;
    }

    Pantalla::borrar_fila(fila);
    etiqueta(menu_pos_id);
    post_etiqueta(menu_pos_id);
    valor(Menu::get_valor(menu_pos_id), menu_pos_id, fila);
}

void Menu_imprimir_fila::etiqueta(int menu_pos_id)
{
    lcd.print(config_get_label(menu_pos_id));
}

void Menu_imprimir_fila::post_etiqueta(int menu_pos_id)
{

    if (Menu::elemento_type(menu_pos_id) == MENU_TYPE_GROUP)
    {
        Menu_dispositivos_disponibles::imprimir(menu_pos_id);
    }

    // IMPRIMIR CONFIGURACIÓN RELES (AUTO:x ON:x OFF:x)
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if(menu_pos_id == G_RELES)
        {
            configuracion_reles();
            return;
        }
    #endif
}

void Menu_imprimir_fila::valor(int menu_valor, int menu_pos_id, byte fila)
{
    int valor_tmp;
    int sonda_id;
    byte menu_type = Menu::elemento_type(menu_pos_id);

    // TIPO FUNCTION NO IMPRIMIR NADA
    if (menu_type == MENU_TYPE_FUNCTION)
    {
        return;
    }

    // TIPO MENU_TYPE_DISPOSITIVO_RELE_ACCION:
    if (menu_type == MENU_TYPE_DISPOSITIVO_RELE_ACCION)
    {
        switch(menu_valor)
        { 
            case 0:      _imprime_derecha(F("NO"), fila); break;
            case 1:     _imprime_derecha(F("SI"), fila); break;
            default:    _imprime_derecha(F("?"), fila); break;
        }
        return;
    }

    // TIPO DISPOSITIVO IMPRIMIR SU NOMBRE
    if (menu_type == MENU_TYPE_DISPOSITIVO)
    {
        if (menu_valor < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID))
        {
            if (Menu_editando)
            {
                _imprime_derecha(F("Sel"), fila);
            }
            else
            {
                _imprime_derecha(F("-"), fila);
            }
            return;
        }
        _imprime_derecha(Dispositivos.nombre_corto(menu_valor), fila);
        return;
    }

    // TIPO SONDA (DIR-X)
    if (menu_type == MENU_TYPE_SONDA_SELECTOR)
    {
        sonda_id = Menu::reget_sonda_id(menu_pos_id)+1;
        _imprime_derecha_prefijo_y_dir(sonda_id, ' ', fila);
        return;
    }

    // TIPO RELE_ESTADO
    if (menu_type == MENU_TYPE_RELE_ESTADO)
    {
        switch(menu_valor)
        { 
            case RELE_FLAG_FORZADO_ON:      _imprime_derecha(F("F-ON"), fila); break;
            case RELE_FLAG_FORZADO_OFF:     _imprime_derecha(F("F-OFF"), fila); break;
            default:                        _imprime_derecha(F("AUTO"), fila); break;
        }
        return;
    }

    //TIPO MENU_TYPE_RELE_FORZADO_MODO_LED
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (menu_type == MENU_TYPE_RELE_FORZADO_MODO_LED)
        {
            switch(menu_valor)
            { 
                case MEGA_RELE_FORZADO_LED_OFF:     _imprime_derecha(F("OFF"), fila); break;
                case MEGA_RELE_FORZADO_LED_SLOW:    _imprime_derecha(F("Lento"), fila); break;
                case MEGA_RELE_FORZADO_LED_FAST:    _imprime_derecha(F("Rapido"), fila); break;
            }
            return;
        }
    #endif

    //TIPO MENU_TYPE_EVENTO_RELE_ACCION
    if (menu_type == MENU_TYPE_EVENTO_RELE_ACCION)
    {
        switch(menu_valor)
        {
            case 0: _imprime_derecha(F("OFF"), fila); break;
            case 1: _imprime_derecha(F("ON"), fila); break;
            default: _imprime_derecha('?', fila); break;
        }
        return;
    }

    //TIPO MENU_TYPE_BAUD
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (menu_type == MENU_TYPE_BAUD)
        {
            switch(menu_valor)
            {
                case 0: _imprime_derecha(F("2K4"), fila); break;
                case 1: _imprime_derecha(F("4K8"), fila); break;
                case 2: _imprime_derecha(F("9K6"), fila); break;
                case 3: _imprime_derecha(F("14K4"), fila); break;
                case 4: _imprime_derecha(F("19K2"), fila); break;
                case 5: _imprime_derecha(F("28K8"), fila); break;
                case 6: _imprime_derecha(F("38K4"), fila); break;
                case 7: _imprime_derecha(F("57K6"), fila); break;
                case 8: _imprime_derecha(F("76K8"), fila); break;
                case 9: _imprime_derecha(F("115K2"), fila); break;
                case 10: _imprime_derecha(F("250K"), fila); break;
                case 11: _imprime_derecha(F("500K"), fila); break;
                case 12: _imprime_derecha(F("1M"), fila); break;
                case 13: _imprime_derecha(F("2M"), fila); break;
                default: _imprime_derecha(F("500K"), fila); break;
           }
           return;
        }
    #endif


    // TIPO RELE_ESTADO
    if (Menu::elemento_type(menu_pos_id) == MENU_TYPE_RELE_SELECTOR)
    {
        _imprime_derecha_int_con_prefijo(menu_valor, '#', fila);
        return;
    }

    // EVENTO_1_DIFF_OFF
    if (menu_pos_id == EVENTO_1_DIFF_OFF)
    {
        if (menu_valor < 1)
        {
            _imprime_derecha(F("OFF"), fila);
        }
        _imprime_derecha(menu_valor, fila);
        return;
    }

    // AGUA ESCALA (Lt/Pt)
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (menu_pos_id == AGUA_ESCALA)
        {
            if (menu_valor == 0) _imprime_derecha(F("LT"), fila);
            if (menu_valor == 1) _imprime_derecha(F("PT"), fila);
            return;
        }
    #endif

    //SONDAS ESCALA (C/F)
    if (menu_pos_id == SONDAS_ESCALA)
    {
        if (menu_valor == 0) _imprime_derecha(F("C"), fila);
        if (menu_valor == 1) _imprime_derecha(F("F"), fila);
        return;
    }

    // IMPRIMIR VALOR CON SIMBOLO SEGUNDOS
    for(valor_tmp = 0; valor_tmp < TOTAL_SONDAS_COLECTORES; valor_tmp++)
    {
        if (menu_pos_id == Menu_grupal::get_id(CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_BOMBEO, valor_tmp)
            || menu_pos_id == Menu_grupal::get_id(CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_PAUSA, valor_tmp)
            || menu_pos_id == TIEMPO_LECTURAS_SEGUNDOS 
            || menu_pos_id == TIEMPO_LUZ_PANTALLA_SEGUNDOS 
            || menu_pos_id == TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS
            || menu_pos_id == TIEMPO_MENU_LIBERAR_SEGUNDOS
            )
        {
            _imprime_derecha_int_con_sufijo(menu_valor, '"', fila);
            return;
        }
    }

    // IMPRIMIR VALOR CON SIMBOLO GRADOS
    for(valor_tmp = 0; valor_tmp < TOTAL_SONDAS_COLECTORES; valor_tmp++)
    {
        if (menu_pos_id == Menu_grupal::get_id(CONTROL_BOMBA_1_DIFF_TO_ON, valor_tmp)
            || menu_pos_id == Menu_grupal::get_id(CONTROL_BOMBA_1_DIFF_TO_OFF, valor_tmp)
            || menu_pos_id == Menu_grupal::get_id(REFRIGERAR_COLECTOR_1_SI_TEMP_SUPERIOR_A, valor_tmp)
            || menu_pos_id == CALENTADOR_DEPOSITO_SI_TEMP_INFERIOR_A)
        {
            _imprime_derecha_int_con_sufijo(menu_valor, 223, fila);
            return;
        }
    }

    // IMPRIMIR VALOR CON (LT)
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (menu_pos_id == AGUA_CAPACIDAD_TOTAL || menu_pos_id == AGUA_TECHO_VIRTUAL || menu_pos_id == AGUA_SUELO_VIRTUAL)
        {
            _imprime_derecha_int_con_sufijo(menu_valor, F("LT"), fila);
            return;
        }
    #endif

    for(valor_tmp = 0; valor_tmp < TOTAL_EVENTOS; valor_tmp++)
    {
        if (menu_pos_id == Menu_grupal::get_id(EVENTO_1_OPERACION, valor_tmp))
        {
            switch(menu_valor)
            {
                case 0: _imprime_derecha('<', fila); break;
                case 1: _imprime_derecha('>', fila); break;
            }
            return;
        }
    }

    // SI NO ACERTADO EN CASOS ANTERIORES Y ES UN VALOR INT, IMPRIMIR 
    switch(menu_type)
    {
        case MENU_TYPE_0_TO_2:
        case MENU_TYPE_0_TO_4:
        case MENU_TYPE_0_TO_6:
        case MENU_TYPE_0_TO_10:
        case MENU_TYPE_0_TO_255:
        case MENU_TYPE_1_TO_30:
        case MENU_TYPE_1_TO_255:
        case MENU_TYPE_0_TO_100:
        case MENU_TYPE_1_TO_100:
        case MENU_TYPE_1_TO_32000:
        case MENU_TYPE_2_TO_255:
        case MENU_TYPE_MINUS_255_TO_255:
            _imprime_derecha(menu_valor, fila);
    }

    // TIPO GRUPO
    if (menu_type == MENU_TYPE_GROUP)
    {
        // SIGUIENTE FILA ES TIPO ACTIVAR Y LA SIGUENTE ES SONDA_SELECTOR, MOSTRAR LA DIRECCIÓN DE LA SONDA Y SU DISPONIBILIDAD CON FECLA ARRIBA/ABAJO
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            if (Menu::elemento_type(menu_pos_id+1) == MENU_TYPE_ACTIVAR && Menu::elemento_type(menu_pos_id+2) == MENU_TYPE_SONDA_SELECTOR)
            {
                sonda_id = Menu::reget_sonda_id(menu_pos_id+2)+1;
                if (Menu::get_valor(menu_pos_id+1))
                {
                    _imprime_derecha_prefijo_y_dir(sonda_id, ICON_UP, fila);
                }
                else
                {
                    _imprime_derecha_prefijo_y_dir(sonda_id, ICON_DOWN, fila);
                }
                return;
            }
        #endif
        // SIGUENTE FILA ES TIPO ACTIVAR (HEREDAR SU VALOR BOOLEANO SI/NO)
        if (Menu::elemento_type(menu_pos_id+1) == MENU_TYPE_ACTIVAR)
        {
            menu_valor = Menu::get_valor(menu_pos_id+1);
            if (menu_valor == 0) _imprime_derecha(F("NO"), fila);
            if (menu_valor == 1) _imprime_derecha(F("SI"), fila);
            return;
        }
    }

    // TIPO ACTIVAR o BOOL (SI/NO)
    if (menu_type == MENU_TYPE_ACTIVAR || menu_type == MENU_TYPE_BOOL)
    {
        if (menu_valor == 0) _imprime_derecha(F("NO"), fila);
        if (menu_valor == 1) _imprime_derecha(F("SI"), fila);
        return;
    }
}

void Menu_imprimir_fila::configuracion_reles()
{
    if (!Menu::get_valor(RELES_ON_OFF))
    {
        lcd.write(' '); lcd.print(F("OFF"));
        return;
    }
    byte sum_auto = 0;
    byte sum_si = 0;
    byte sum_no = 0;
    for(byte num_rele = 0; num_rele < TOTAL_RELES; num_rele++)
    {
        byte menu_valor = Menu::get_valor(RELE_ESTADO_1 + num_rele);
        switch(menu_valor)
        {
            case RELE_FLAG_FORZADO_ON: sum_si++; break;
            case RELE_FLAG_FORZADO_OFF: sum_no++; break;
            default: sum_auto++; break;
        }
    }

    lcd.write(' '); lcd.write('A'); lcd.print(sum_auto);
    lcd.write(' '); lcd.write(ICON_UP); lcd.print(sum_si);
    lcd.write(' '); lcd.write(ICON_DOWN); lcd.print(sum_no);
}

