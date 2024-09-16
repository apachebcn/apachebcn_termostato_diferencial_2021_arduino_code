void Menu_eventos::tecla(byte tecla)
{
    if (!Menu_activo) return;
    if (Menu_editando)
    {
        Menu_editor::tecla(tecla);
        return;
    }

    int mover_a_id = 0;
    switch (tecla)
    {
        case SIGN_TECLA_ATRAS:
            if (Menu_pos < 2)
            {
                Menu::salir();
                return;
            }
            mover_a_id = Menu::_tiene_elemento_atras(Menu_pos);
            break;

        case SIGN_TECLA_OK:
            if (Menu::is_config_type_editable(Menu_pos))
            {
                Menu_editor::inicia_modo_edicion();
                return;
            }
            else if (Menu::elemento_type(Menu_pos) == MENU_TYPE_FUNCTION)
            {
                if (Menu::functions(Menu_pos))
                {
                    Pantalla::borrar_fila(0);
                    Menu_imprimir_fila::etiqueta(Menu_pos);
                }
                return;
            }
            else
            {
                mover_a_id = Menu::_tiene_elemento_derecha(Menu_pos);
            }
            break;

        case SIGN_TECLA_ARRIBA:
            if (Menu_pos <= 1)
            {
                mover_a_id = MENU_ELEMENTOS_TOTAL;
                break;
            }
            mover_a_id = Menu::_tiene_elemento_arriba(Menu_pos);
            break;

        case SIGN_TECLA_ABAJO:
            if (Menu_pos >= MENU_ELEMENTOS_TOTAL)
            {
                mover_a_id = 1;
                break;
            }
            mover_a_id = Menu::_tiene_elemento_abajo(Menu_pos);
            break;
    }

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if(tecla == SIGN_TECLA_ARRIBA || tecla == SIGN_TECLA_ABAJO)
        {
            Buzzer::beep_ultracorto();
        }
    #endif

    if (mover_a_id > 0)
    {
        Menu_pos = mover_a_id;
        Menu::imprimir();
    }
    else
    {
    }

}

void Menu_eventos::validar_sonda()
{
    int sonda_id = (Menu_edicion_valor-1);
    switch(Menu_pos)
    {
        case SONDA_COLECTOR_1_DIR:
            Sondas::copiar_sonda_id_a(sonda_id, Sondas_colector_dir[0]);
            return;
        case SONDA_DEPOSITO_DIR:
            Sondas::copiar_sonda_id_a(sonda_id, Sondas_deposito_dir);
            return;
        case SONDA_ZTERMOSTATO_DIR:
            Sondas::copiar_sonda_id_a(sonda_id, Sondas_ztermostato_dir);
            return;
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case LCD_7_DIR:
                Sondas::copiar_sonda_id_a(sonda_id, Sondas_lcd7_dir);
                return;
        #endif
    }

    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        byte idx;
        byte diff;
        diff = SONDA_COLECTOR_2_DIR-SONDA_COLECTOR_1_DIR;
        for(idx=0; idx<TOTAL_SONDAS_COLECTORES; idx++)
        {
            if (SONDA_COLECTOR_1_DIR+(diff*idx) == Menu_pos)
            {
                Sondas::copiar_sonda_id_a(sonda_id, Sondas_colector_dir[idx]);
                return;
            }
        }
        diff = SONDA_ZONA_2_DIR-SONDA_ZONA_1_DIR;
        for(idx=0; idx<TOTAL_SONDAS_ZONAS; idx++)
        {
            if (SONDA_ZONA_1_DIR+(diff*idx) == Menu_pos)
            {
                Sondas::copiar_sonda_id_a(sonda_id, Sondas_zona_dir[idx]);
                return;
            }
        }
    #endif
}

void Menu_eventos::al_editar_valor()
{
    if (Menu::Menu::elemento_type(Menu_pos) == MENU_TYPE_SONDA_SELECTOR)
    {
        Pantalla::print_centrado(F("Escaneando sondas"), 1);
        Sondas::scan();
        Pantalla::borrar_fila(1);
        Menu_edicion_valor = Menu::reget_sonda_id(Menu_pos)+1;
        Menu::set_valor(Menu_pos, Menu_edicion_valor);
        if (Menu_edicion_valor < 1)
        {
            Pantalla::print_centrado(F("Sel.sonda"), 1);
        }
        return;
    }
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        switch(Menu_pos)
        {
            case LEDS_BRILLO: 
                break;
        }
    #endif
}

void Menu_eventos::al_modificar_valor()
{
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        switch(Menu_pos)
        {
            case LEDS_BRILLO: 
                Leds::brillo_refresca_muestra(Menu_edicion_valor);
                break;
            case LCD_7_BRILLO:
                Menu::set_valor(LCD_7_BRILLO, Menu_edicion_valor);
                Lcd7::refresca_pantallas(); 
                break;
            case LCD_7_DIR:
                validar_sonda();
                Lcd7::actualiza_pin();
                imprime_lcd7();
                break;
        }
    #endif
}

void Menu_eventos::al_validar_valor()
{
    MenuElementos[Menu_pos].valor = Menu_edicion_valor;
    switch(Menu_pos)
    {
        case SONDAS_ON_OFF:
            Sondas::scan();
            Reles::actualiza_pin();
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                Agua::actualiza_pin();
                Lcd7::actualiza_pin();
            #endif
            break;
        case RELES_ON_OFF:
            Reles::actualiza_pin();
            break;
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case BUZZER_ON_OFF:
                Buzzer::actualiza_pin();
                break;
            case LCD_7_ON_OFF:
                Lcd7::actualiza_pin();
                imprime_lcd7();
                break;

            case SERIAL_DEBUG_ON_OFF:
            case SERIAL_DEBUG_BAUD:
            case SERIAL_ON_OFF:
            case SERIAL_BAUD:
            case SERIAL_OUT_ON_OFF:
            case SERIAL_IN_ON_OFF:
                Pantalla::borrar();
                lcd.print(F("Guardar y reiniciar")); lcd.write(ICON_WAITING);
                Buzzer::beep_error();
                Menu_eprom::save();
                Pantalla::borrar();
                FC::reset_remoto();
                break;
        #endif
    }
    validar_sonda();
    Menu_editor::finaliza_modo_edicion();
    Menu::imprimir();
    reset_front_timer();
}