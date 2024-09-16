/* 
**************************

    ENTRADA EN MENU

**************************
*/
void Menu::entrar()
{
    Menu_editor::finaliza_modo_edicion();
    Pantalla::encender();
    Menu_pos = 1;
    Menu_activo = 1;
    Menu_editando = 0;
    Buzzer::beep();
    imprimir();
}

/* 
**************************

    SALIDA DEL MENU

**************************
*/
void Menu::salir()
{
    Menu_editor::finaliza_modo_edicion();
    Pantalla::borrar();
    Pantalla::encender();
    lcd.noBlink();
    Menu_activo = 0;
    Buzzer::beep();
    front_pantalla();
}

int Menu::get_entrada_valor_minimo(int elemento_id)
{
    _comprobar_elemento_id(elemento_id);
    switch(elemento_type(elemento_id))
    {
        case MENU_TYPE_SONDA_SELECTOR:
        case MENU_TYPE_DISPOSITIVO:
            return DISPOSITIVO_DE_ENTRADA_PRIMER_ID-1;
        case MENU_TYPE_BOOL:
        case MENU_TYPE_RELE_ESTADO:
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case MENU_TYPE_RELE_FORZADO_MODO_LED:
            case MENU_TYPE_BAUD:
        #endif
        case MENU_TYPE_DISPOSITIVO_RELE_ACCION:
        case MENU_TYPE_ACTIVAR:
        case MENU_TYPE_RELE_SELECTOR:
        case MENU_TYPE_EVENTO_RELE_ACCION:
        case MENU_TYPE_0_TO_2:
        case MENU_TYPE_0_TO_4:
        case MENU_TYPE_0_TO_6:
        case MENU_TYPE_0_TO_10:
        case MENU_TYPE_0_TO_255:
        case MENU_TYPE_0_TO_100:
            return 0;
        case MENU_TYPE_1_TO_30:
        case MENU_TYPE_1_TO_255:
        case MENU_TYPE_1_TO_100:
        case MENU_TYPE_1_TO_32000:
            return 1;
        case MENU_TYPE_2_TO_255:
            return 2;
        case MENU_TYPE_MINUS_255_TO_255:     
            return -255;
    }
    return 0;
}

int Menu::get_entrada_valor_minimo(int elemento_id, int grupo_id)
{
    _comprobar_elemento_id(elemento_id);
    elemento_id = Menu_grupal::get_id(elemento_id, grupo_id);
    return get_entrada_valor_minimo(elemento_id);
}

int Menu::get_entrada_valor_maximo(int elemento_id)
{
    _comprobar_elemento_id(elemento_id);
    switch(elemento_type(elemento_id))
    {
        case MENU_TYPE_DISPOSITIVO:
            return DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA-1;
        case MENU_TYPE_ACTIVAR:
        case MENU_TYPE_DISPOSITIVO_RELE_ACCION:
        case MENU_TYPE_BOOL:
        case MENU_TYPE_EVENTO_RELE_ACCION:
            return 1;
            break;
        case MENU_TYPE_SONDA_SELECTOR:   
            return LAST_SONDA;
            break;
        case MENU_TYPE_RELE_SELECTOR:                
            return TOTAL_RELES;
            break;
        case MENU_TYPE_RELE_ESTADO:             
            return 2;
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case MENU_TYPE_BAUD:
                return 13;
            case MENU_TYPE_RELE_FORZADO_MODO_LED:
                return 2;
        #endif
        case MENU_TYPE_0_TO_2:              return 2;
        case MENU_TYPE_0_TO_4:              return 4;
        case MENU_TYPE_0_TO_6:              return 6;
        case MENU_TYPE_0_TO_10:             return 10;
        case MENU_TYPE_0_TO_255:            return 255;
        case MENU_TYPE_1_TO_30:             return 30;
        case MENU_TYPE_1_TO_255:            return 255;
        case MENU_TYPE_2_TO_255:            return 255;
        case MENU_TYPE_0_TO_100:            return 100;
        case MENU_TYPE_1_TO_100:            return 100;
        case MENU_TYPE_MINUS_255_TO_255:    return 255;
        case MENU_TYPE_1_TO_32000:          return 32000;
    }
    return 0;
}

int Menu::get_entrada_valor_maximo(int elemento_id, int grupo_id)
{
    _comprobar_elemento_id(elemento_id);
    elemento_id = Menu_grupal::get_id(elemento_id, grupo_id);
    return get_entrada_valor_maximo(elemento_id);
}

int Menu::get_valor(int elemento_id)
{
    _comprobar_elemento_id(elemento_id);
    return MenuElementos[elemento_id].valor;
}

int Menu::get_valor(int elemento_id, int grupo_id)
{
    _comprobar_elemento_id(elemento_id);
    elemento_id = Menu_grupal::get_id(elemento_id, grupo_id);
    return get_valor(elemento_id);
}

byte Menu::elemento_type(int elemento_id)
{
    _comprobar_elemento_id(elemento_id);
    return MenuElementos[elemento_id].type;
}

void Menu::set_valor(int elemento_id, int valor)
{
    _comprobar_elemento_id(elemento_id);
    int type = elemento_type(elemento_id);
    switch(type)
    {
        case MENU_TYPE_GROUP:
        case MENU_TYPE_FUNCTION:
            return;

        case MENU_TYPE_SONDA_SELECTOR:
        case MENU_TYPE_DISPOSITIVO:
        case MENU_TYPE_DISPOSITIVO_RELE_ACCION:
        case MENU_TYPE_ACTIVAR:
        case MENU_TYPE_BOOL:
        case MENU_TYPE_EVENTO_RELE_ACCION:
        case MENU_TYPE_RELE_SELECTOR:

        case MENU_TYPE_RELE_ESTADO:

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case MENU_TYPE_BAUD:
            case MENU_TYPE_RELE_FORZADO_MODO_LED:
        #endif
        case MENU_TYPE_0_TO_2:
        case MENU_TYPE_0_TO_4:
        case MENU_TYPE_0_TO_6:
        case MENU_TYPE_0_TO_10:
        case MENU_TYPE_0_TO_255:
        case MENU_TYPE_0_TO_100:
        case MENU_TYPE_1_TO_100:
        case MENU_TYPE_1_TO_30:
        case MENU_TYPE_1_TO_255:
        case MENU_TYPE_2_TO_255:
        case MENU_TYPE_1_TO_32000:
        case MENU_TYPE_MINUS_255_TO_255:
            break;

        default:
            _error_grave_desbordamiento_de_tipo(F("UNKNOWN TYPE ID"), elemento_id, type);
    }

    if (valor > get_entrada_valor_maximo(elemento_id))
    {
        valor = get_entrada_valor_maximo(elemento_id);
    }
    if (valor < get_entrada_valor_minimo(elemento_id))
    {
        valor = get_entrada_valor_minimo(elemento_id);
    }
    MenuElementos[elemento_id].valor = valor;
}

void Menu::elemento_insertar(int elemento_id, int abajo, int derecha, byte type, int valor_defecto)
{
    _comprobar_elemento_id(elemento_id);
    if (elemento_id > Menu_nodo_ultimo)
    {
        Menu_nodo_ultimo = elemento_id;
    }

    MenuElementos[elemento_id].valor = valor_defecto;
    MenuElementos[elemento_id].type = type;
    MenuElementos[elemento_id].derecha = derecha;
    MenuElementos[elemento_id].abajo = abajo;
/*
Serial_debug::print(elemento_id);
Serial_debug::print(": ");
Serial_debug::print("type-");
Serial_debug::print(type);
Serial_debug::println();
*/
}

void Menu::_error_grave_desbordamiento_de_tipo(const __FlashStringHelper* label, int elemento_id, int valor)
{
    lcd.clear(); 
    lcd.print(elemento_id); 
    lcd.write(' '); 
    lcd.print(label); 
    lcd.setCursor(0,1); 
    lcd.print(valor);
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        lcd.setCursor(0,2);
        lcd.write(' '); lcd.print(_type_label(elemento_type(elemento_id)));
    #endif
    Buzzer::beep_error();

    /*
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (IS_SERIAL_DEBUG_SETUP())
        {
            Serial_debug::println(F("Error grave"));
            Serial_debug::print(F("menu_id=")); Serial_debug::println(elemento_id);
            Serial_debug::print(F("label=")); Serial_debug::println(label);
            Serial_debug::print(F("type=")); Serial_debug::println(_type_label(elemento_type(elemento_id)));
            Serial_debug::print(F("valor=")); Serial_debug::println(Valor);
        }
    #endif
    */

    FC::delayMilisegundos(10000);
    resetFunc();
}

int Menu::_tiene_elemento_arriba(int menu_pos_id)
{
    if (menu_pos_id > MENU_ELEMENTOS_TOTAL) 
    {
        return 0;
    }
    for (int bucle = 1; bucle < (MENU_ELEMENTOS_TOTAL+1); bucle++)
    {
        if (MenuElementos[bucle].abajo == menu_pos_id)
        {
            return bucle;
        }
    }
    return 0;
}

int Menu::_tiene_elemento_izquierda(int menu_pos_id)
{
    if (menu_pos_id > MENU_ELEMENTOS_TOTAL) return 0;
    for (int bucle = 1; bucle < (MENU_ELEMENTOS_TOTAL+1); bucle++)
    {
        if (MenuElementos[bucle].derecha == menu_pos_id)
        {
            return bucle;
        }
    }
    return 0;
}

int Menu::_tiene_elemento_atras(int menu_pos_id)
{
    int tmp = menu_pos_id;
    int izquierda = 0;
    int maximo_arriba = 0;
    do {
        maximo_arriba = tmp;
        tmp = _tiene_elemento_arriba(maximo_arriba);
    } while (tmp);

    if (!maximo_arriba) maximo_arriba = menu_pos_id;
    izquierda = _tiene_elemento_izquierda(maximo_arriba);
    if (izquierda) return izquierda;
    if (maximo_arriba) return maximo_arriba;
    izquierda = _tiene_elemento_izquierda(menu_pos_id);
    return 0;
}

int Menu::_tiene_elemento_abajo(int menu_pos_id)
{
    if (menu_pos_id < 1) return 0;
    int tmp_pos = MenuElementos[menu_pos_id].abajo;
    if (tmp_pos > 0 && tmp_pos != menu_pos_id && tmp_pos <= MENU_ELEMENTOS_TOTAL) return tmp_pos;
    return 0;
}

int Menu::_tiene_elemento_derecha(int menu_pos_id)
{
    if (menu_pos_id < 1) return 0;
    int tmp_pos = MenuElementos[menu_pos_id].derecha;
    if (tmp_pos > 0 && tmp_pos != menu_pos_id && tmp_pos <= MENU_ELEMENTOS_TOTAL) return tmp_pos;
    return 0;
}

void Menu::imprimir()
{
    Menu_imprimir_fila::imprimir(Menu_pos, 0);

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    int prevision_abajo_id;

    prevision_abajo_id = _tiene_elemento_abajo(Menu_pos);
    Menu_imprimir_fila::imprimir(prevision_abajo_id, 1);

    prevision_abajo_id = _tiene_elemento_abajo(prevision_abajo_id);
    Menu_imprimir_fila::imprimir(prevision_abajo_id, 2);
#endif

    mostrar_nav_icons();

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        lcd.setCursor(0,0);
        lcd.blink();
    #endif
}

void Menu::mostrar_nav_icons()
{
    Pantalla::borrar_fila(3);
    lcd.setCursor(5,3);
    if (Menu_pos == 1 || _tiene_elemento_arriba(Menu_pos)) {lcd.write(ICON_UP); lcd.write(' ');}
    if (_tiene_elemento_izquierda(Menu_pos)) {lcd.print(W_AT); lcd.write(' ');}

    if (elemento_type(Menu_pos) == MENU_TYPE_FUNCTION || is_config_type_editable(Menu_pos)) 
    {
        lcd.print(W_OK); 
        lcd.write(' ');
    }

    if (Menu_pos == MENU_ELEMENTOS_TOTAL || _tiene_elemento_abajo(Menu_pos)) {lcd.write(ICON_DOWN); lcd.write(' ');}

    if (_tiene_elemento_derecha(Menu_pos)) 
    {
        lcd.setCursor(PANTALLA_ANCHO_PX-3, PANTALLA_ALTO_PX-1);
        lcd.print(F("OK"));
        lcd.write(ICON_RIGHT); 
    }
}

bool Menu::functions(int menu_pos)
{
    if (menu_pos == C_ABOUT)
    {
        Pantalla::ver_about();
        return 0;
    }

    lcd.setCursor(PANTALLA_ANCHO_PX-1, 0); lcd.write(ICON_WAITING);
    switch(menu_pos)
    {
        case C_SETUP_GUARDAR:
            Buzzer::beep();
            Menu_eprom::save();
            break;
        case C_SETUP_BORRAR:
            Buzzer::beep();
            Menu_eprom::erase();
            FC::delayMilisegundos(200);
            break;
        case C_RESET:
            Buzzer::beep();
            lcd.clear();
            FC::reset_remoto();
            break;         
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        case C_TEST_LCD_7:
            Buzzer::beep();
            Lcd7::test();
            break;
        case C_TEST_RELES:
            Reles::test();
            break;
        case C_TEST_BUZZER:
            Buzzer::test(1);
            break;
        case C_TEST_LEDS:
            Buzzer::beep();
            Leds::test();
            break;
#endif
    }       

    lcd.setCursor(PANTALLA_ANCHO_PX-1,1); 
    lcd.write(' ');

    return 1;
}

bool Menu::is_config_type_editable(int menu_id)
{
    switch(elemento_type(menu_id))
    {
        case MENU_TYPE_GROUP: 
        case MENU_TYPE_FUNCTION:
            return 0;
        case MENU_TYPE_DISPOSITIVO_RELE_ACCION:
        case MENU_TYPE_DISPOSITIVO:
        case MENU_TYPE_ACTIVAR:
        case MENU_TYPE_BOOL:
        case MENU_TYPE_EVENTO_RELE_ACCION:
        case MENU_TYPE_SONDA_SELECTOR:
        case MENU_TYPE_RELE_SELECTOR:
        case MENU_TYPE_RELE_ESTADO:
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case MENU_TYPE_BAUD:
            case MENU_TYPE_RELE_FORZADO_MODO_LED:
        #endif
        case MENU_TYPE_0_TO_2:
        case MENU_TYPE_0_TO_4:
        case MENU_TYPE_0_TO_6:
        case MENU_TYPE_0_TO_10:
        case MENU_TYPE_0_TO_255:
        case MENU_TYPE_1_TO_30:
        case MENU_TYPE_1_TO_255:
        case MENU_TYPE_0_TO_100:
        case MENU_TYPE_1_TO_100:
        case MENU_TYPE_2_TO_255:
        case MENU_TYPE_1_TO_32000:
        case MENU_TYPE_MINUS_255_TO_255:
            return 1;
    }
    return 0;
}

int Menu::reget_sonda_id(int menu_pos_id)
{
    int valor_tmp;
    // SI EL VALOR ES UNA SONDA DE DEPOSITO
    if (menu_pos_id  == SONDA_DEPOSITO_DIR)
    {
        return Sondas::buscar_addr_dir(Sondas_deposito_dir);
    }

    // SI EL VALOR ES UNA SONDA DE ZTERMOSTATO
    if (menu_pos_id  == SONDA_ZTERMOSTATO_DIR)
    {
        return Sondas::buscar_addr_dir(Sondas_ztermostato_dir);
    }

    // SI EL VALOR ES UNA SONDA DE COLECTORES
    for(valor_tmp = 0; valor_tmp < TOTAL_SONDAS_COLECTORES; valor_tmp++)
    {
        if (menu_pos_id == Menu_grupal::get_id(SONDA_COLECTOR_1_DIR, valor_tmp))
        {
            return Sondas::buscar_addr_dir(Sondas_colector_dir[valor_tmp]);
        }
    }

    // SI EL VALOR ES UNA SONDA DE ZONAS
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        for(valor_tmp = 0; valor_tmp < TOTAL_SONDAS_ZONAS; valor_tmp++)
        {
            if (menu_pos_id  == Menu_grupal::get_id(SONDA_ZONA_1_DIR, valor_tmp))
            {
                return Sondas::buscar_addr_dir(Sondas_zona_dir[valor_tmp]);
                break;
            }
        }

        // SI EL VALOR ES UNA SONDA DE LCD7
        if (menu_pos_id  == LCD_7_DIR)
        {
            return Sondas::buscar_addr_dir(Sondas_lcd7_dir);
        }

    #endif

    return -1;
}

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void Menu::volcar()
    {

        Serial_debug::print(F("Total nodes:")); Serial_debug::println(MENU_ELEMENTOS_TOTAL);
        for(int elemento_id = 1; elemento_id < MENU_ELEMENTOS_TOTAL+1; elemento_id++)
        {
            Serial_debug::print(F("ID = ")); Serial_debug::print(elemento_id); Serial_debug::print(F("; "));

            Serial_debug::print(F("LABEL = '")); Serial_debug::print(config_get_label(elemento_id)); Serial_debug::print(F("'; "));

            Serial_debug::print(F("TYPE = "));  Serial_debug::print(_type_label(elemento_type(elemento_id))); Serial_debug::print(F("; "));

            Serial_debug::print(F("VALOR = ")); Serial_debug::print(get_valor(elemento_id)); Serial_debug::print(F("; "));

            Serial_debug::print(F("RANGO = ")); 
            Serial_debug::print(get_entrada_valor_minimo(elemento_id));
            Serial_debug::print(F("<>")); 
            Serial_debug::print(get_entrada_valor_maximo(elemento_id));
            Serial_debug::print(F("; "));

            Serial_debug::print(F("ABAJO = ")); 
            Serial_debug::print(MenuElementos[elemento_id].abajo); Serial_debug::print(F("'; "));

            Serial_debug::print(F("DERECHA = ")); 
            Serial_debug::print(MenuElementos[elemento_id].derecha); Serial_debug::print(F("'; "));
            Serial_debug::println();
        }

    }

    const __FlashStringHelper* Menu::_type_label(int type)
    {
        switch(type)
        {
            case MENU_TYPE_GROUP:                       return F("TYPE_GROUP");
            case MENU_TYPE_FUNCTION:                    return F("TYPE_FUNCTION");
            case MENU_TYPE_DISPOSITIVO_RELE_ACCION:     return F("TYPE_DISPOSITIVO_RELE_ACCION");
            case MENU_TYPE_DISPOSITIVO:                 return F("TYPE_DISPOSITIVO");
            case MENU_TYPE_ACTIVAR:                     return F("TYPE_ACTIVAR");
            case MENU_TYPE_BOOL:                        return F("TYPE_BOOL");
            case MENU_TYPE_EVENTO_RELE_ACCION:          return F("TYPE_EVENTO_RELE_ACCION");
            case MENU_TYPE_SONDA_SELECTOR:              return F("TYPE_SONDA_SELECTOR");
            case MENU_TYPE_RELE_SELECTOR:               return F("TYPE_RELE_SELECTOR");
            case MENU_TYPE_BAUD:                        return F("TYPE_SERIAL_DATA");
            case MENU_TYPE_RELE_ESTADO:                 return F("TYPE_RELE_ESTADO");
            case MENU_TYPE_RELE_FORZADO_MODO_LED:       return F("TYPE_RELE_FORZADO_MODO_LED");
            case MENU_TYPE_0_TO_2:                      return F("TYPE_0_TO_2");
            case MENU_TYPE_0_TO_4:                      return F("TYPE_0_TO_4");
            case MENU_TYPE_0_TO_6:                      return F("TYPE_0_TO_6");
            case MENU_TYPE_0_TO_10:                     return F("TYPE_0_TO_10");
            case MENU_TYPE_0_TO_255:                    return F("TYPE_0_TO_255");
            case MENU_TYPE_0_TO_100:                    return F("TYPE_0_TO_100");
            case MENU_TYPE_1_TO_100:                    return F("TYPE_1_TO_100");
            case MENU_TYPE_1_TO_30:                     return F("TYPE_1_TO_30");
            case MENU_TYPE_1_TO_255:                    return F("TYPE_1_TO_255");
            case MENU_TYPE_2_TO_255:                    return F("TYPE_2_TO_255");
            case MENU_TYPE_1_TO_32000:                  return F("TYPE_1_TO_32000");
            case MENU_TYPE_MINUS_255_TO_255:            return F("TYPE_MINUS_255_TO_255");
        }
        return 0;
    }
#endif

void Menu::_comprobar_elemento_id(int elemento_id)
{
    if (elemento_id > MENU_ELEMENTOS_TOTAL)
    {
        print_err(elemento_id, 1);
    }
    if (elemento_id < 0)
    {
        print_err(elemento_id, 2);
    }
}

void Menu::print_err(int menu_id, byte code_num, const __FlashStringHelper* var_name, int value)
{
    Pantalla::borrar();
    lcd.print(F("MT#")); lcd.print(code_num);
    lcd.print(F(" id=")); lcd.print(menu_id);
    lcd.setCursor(0,1);
    lcd.print(var_name); lcd.write('='); lcd.print(value); 
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Serial_debug::println();
        Serial_debug::print(F("--"));
        Serial_debug::print(F(" ERROR "));
        Serial_debug::print(F("MT#")); Serial_debug::print(code_num); 
        Serial_debug::println(F("--"));
        Serial_debug::print(F("id")); Serial_debug::write('='); Serial_debug::println(menu_id);
        Serial_debug::print(var_name); Serial_debug::write('='); Serial_debug::println(value);
    #endif
    Buzzer::beep_error();
    FC::delayMilisegundos(2000); 
}

void Menu::print_err(int menu_id, byte code_num)
{
    Pantalla::borrar();
    lcd.print(F("MT#")); lcd.print(code_num);
    lcd.print(F(" id=")); lcd.print(menu_id);
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Serial_debug::println();
        Serial_debug::print(F("--"));
        Serial_debug::print(F(" ERROR "));
        Serial_debug::print(F("MT#")); Serial_debug::print(code_num); 
        Serial_debug::println(F("--"));
        Serial_debug::print(F("id")); Serial_debug::write('='); Serial_debug::println(menu_id);
    #endif
    Buzzer::beep_error();
    FC::delayMilisegundos(2000); 
}

