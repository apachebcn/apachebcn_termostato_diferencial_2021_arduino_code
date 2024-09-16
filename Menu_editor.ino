/* 
**************************

    INICIA MODO EDICION

**************************
*/
void Menu_editor::inicia_modo_edicion()
{
    lcd.blink();
    Menu_editando = 1;

    lcd.clear();
    Menu_imprimir_fila::etiqueta(Menu_pos);
    
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Pantalla::borrar_fila(3);
        lcd.print(F("<- ")); lcd.print(W_AT); lcd.write(' '); lcd.print(W_OK); lcd.print(F(" ->")); 
    #endif

    Menu_edicion_valor = Menu::get_valor(Menu_pos);
    Menu_eventos::al_editar_valor();
    print_valor_editable();
}


/* 
**************************

    FINALIZA MODO EDICION

**************************
*/
void Menu_editor::finaliza_modo_edicion()
{
    Menu_editando = 0;
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        lcd.noBlink();
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        lcd.setCursor(0, 0);
        lcd.blink();
    #endif
    Teclado::reset();
}

/* 
**************************

    MOSTRAR VALOR EN MODO EDICION

**************************
*/
void Menu_editor::print_valor_editable()
{
    if (Menu::elemento_type(Menu_pos) == MENU_TYPE_SONDA_SELECTOR)
    {
        /* 
        **************************

            MOSTRAR VALOR DE SONDAS

        **************************
        */
        print_sonda();
        return;
    }

    Pantalla::borrar_fila(PANTALLA_ALTO_PX-1);
    lcd.print(F("[EDIT]"));
    Menu_imprimir_fila::valor(Menu_edicion_valor, Menu_pos, PANTALLA_ALTO_PX-1);
    lcd.setCursor(PANTALLA_ANCHO_PX-1, PANTALLA_ALTO_PX-1);
}

void Menu_editor::tecla(byte tecla)
{
    int valor;
    switch (tecla)
    {
        case SIGN_TECLA_ATRAS:
            Menu::imprimir();
            Menu_editor::finaliza_modo_edicion();
            break;

        case SIGN_TECLA_OK: 
            Menu_eventos::al_validar_valor();
            break;

        case SIGN_TECLA_ARRIBA:
            valor = Menu::get_entrada_valor_maximo(Menu_pos);
            if (Menu::elemento_type(Menu_pos) == MENU_TYPE_SONDA_SELECTOR)
            {
                valor = Sondas_total_escaneadas;
            }

            if (Menu_edicion_valor < valor) 
            {
                Menu_edicion_valor++;
            }
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                Buzzer::beep_ultracorto();
            #endif
            Menu_editor::print_valor_editable();
            Menu_eventos::al_modificar_valor();
            break;

        case SIGN_TECLA_ABAJO:
            valor = Menu::get_entrada_valor_minimo(Menu_pos);
            if (Menu::elemento_type(Menu_pos) == MENU_TYPE_SONDA_SELECTOR)
            {
                valor = 0;
            }

            if (Menu_edicion_valor > valor) 
            {
                Menu_edicion_valor--;
            }
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                Buzzer::beep_ultracorto();
            #endif
            Menu_editor::print_valor_editable();
            Menu_eventos::al_modificar_valor();
            break;
    }
}

void Menu_editor::print_sonda()
{
    int sonda_id = (Menu_edicion_valor-1);
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Pantalla::borrar_fila(1); 
        if (Menu_edicion_valor > 0)
        {
            lcd.setCursor(0, 1);
            lcd.write('#');
            lcd.print(Menu_edicion_valor);
            lcd.write(' ');
            lcd.print(F("Temp: "));
            lcd.print(Sondas::lee_la_sonda_num(sonda_id, 0));
            lcd.write((char)223);
            if (Menu::get_valor(SONDAS_ESCALA))
            {
                lcd.write('F');
            }
            else
            {
                lcd.write('C');
            }
            lcd.setCursor(0, 2);
            Sondas::lcd_print_addr_sonda_id(sonda_id);
        }
        else
        {
            Pantalla::borrar_fila(2);
            lcd.setCursor(5, 2);
            lcd.print(F("NINGUNA"));
        }
    #endif
    #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
        Pantalla::borrar_fila(0);
        lcd.write('#');
        lcd.print(Menu_edicion_valor);
        if (Menu_edicion_valor > 0)
        {
            lcd.write(' ');
            lcd.print(Sondas::lee_la_sonda_num(sonda_id, 0));
            lcd.write((char)223);
            if (Menu::get_valor(SONDAS_ESCALA))
            {
                lcd.write('F');
            }
            else
            {
                lcd.write('C');
            }
        }

        Pantalla::borrar_fila(1);
        if (Menu_edicion_valor > 0)
        {
            Sondas::lcd_print_addr_sonda_id(sonda_id);
        }
        else
        {
            lcd.print(F("NINGUNA"));
        }
    #endif
}
