
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void Pantalla_atajos::print_pantalla_atajos(int cursor)
    {
        switch(cursor)
        {
            case 1:
                if (Pantalla_vista_atajos_item == VISTA_ATAJOS_LAST) break;
                Pantalla_vista_atajos_item++;
                break;
            case -1:
                if (Pantalla_vista_atajos_item == 0) break;
                Pantalla_vista_atajos_item--;
                break;
        }
        int fila;
        int rele_id;
        int rele_state;
        Pantalla::borrar();
        for(fila = 0; fila < PANTALLA_ALTO_PX; fila++)
        {
            if (Pantalla_vista_atajos_item+fila > VISTA_ATAJOS_LAST) continue;
            lcd.setCursor(0, fila);
            switch(Pantalla_vista_atajos_item+fila)
            {
                case VISTA_ATAJOS_ACTIVAR_RELES: 
                    lcd.print(F("Activar Reles: ")); 
                    if (Menu::get_valor(RELES_ON_OFF)) lcd.print(W_SI); else lcd.print(W_NO);
                    break;
                case VISTA_ATAJOS_MOSTRAR_RELES: 
                    lcd.print(F("Mostrar Reles: "));
                    if (Menu::get_valor(RELES_VISOR)) lcd.print(W_SI); else lcd.print(W_NO);
                    break;
                case VISTA_ATAJOS_FORZAR_AGUA: 
                    lcd.print(F("Forzar Agua: ")); 
                    break;
                case VISTA_ATAJOS_FORZAR_BOMBA_1: 
                    lcd.print(F("Forzar Bomba 1: ")); 
//                    if (Bombas_vars[0].forzada) lcd.print(W_SI); else lcd.print(W_NO);
                    break;
                case VISTA_ATAJOS_FORZAR_BOMBA_2: 
                    lcd.print(F("Forzar Bomba 2: ")); 
//                    if (Bombas_vars[1].forzada) lcd.print(W_SI); else lcd.print(W_NO);
                    break;
                case VISTA_ATAJOS_FORZAR_BOMBA_3: 
                    lcd.print(F("Forzar Bomba 3: ")); 
//                    if (Bombas_vars[2].forzada) lcd.print(W_SI); else lcd.print(W_NO);
                    break;
                default:
                    rele_id = Pantalla_vista_atajos_item-VISTA_ATAJOS_FORZAR_RELE_1+fila; 
                    lcd.print(F("Forzar REL ")); 
                    lcd.print(rele_id+1); lcd.print(F(": "));
                    rele_state = Menu::get_valor(RELE_ESTADO_1+rele_id);
                    switch(rele_state)
                    {
                        case RELE_FLAG_AUTO_OFF:    
                        case RELE_FLAG_AUTO_ON:     lcd.print(F("AUTO")); break;
                        case RELE_FLAG_FORZADO_ON:  lcd.print(F("F-ON")); break;
                        case RELE_FLAG_FORZADO_OFF: lcd.print(F("F-OFF")); break;
                    }
                    break;
            }
        }
        lcd.blink();
        lcd.setCursor(0,0);
    }

    void Pantalla_atajos::print_pantalla_atajos_validar()
    {
        int rele_id;
        int rele_state;
        switch(Pantalla_vista_atajos_item)
        {
            case VISTA_ATAJOS_ACTIVAR_RELES: 
                Menu::set_valor(RELES_ON_OFF, !Menu::get_valor(RELES_ON_OFF));
                Reles::actualiza_pin();
                reset_front_timer();
                break;
            case VISTA_ATAJOS_MOSTRAR_RELES: 
                Menu::set_valor(RELES_VISOR, !Menu::get_valor(RELES_VISOR));
                break;
            case VISTA_ATAJOS_FORZAR_BOMBA_1: 
                //Bombas::accion_forzar(0);
                reset_front_timer();
                break;
            case VISTA_ATAJOS_FORZAR_BOMBA_2: 
                //Bombas::accion_forzar(1);
                reset_front_timer();
                break;
            case VISTA_ATAJOS_FORZAR_BOMBA_3: 
                //Bombas::accion_forzar(2);
                reset_front_timer();
                break;
            case VISTA_ATAJOS_FORZAR_AGUA: 
                //Agua::accion_forzar();
                reset_front_timer();
                break;
            default:
                if (!Menu::get_valor(RELES_ON_OFF)) {Buzzer::beep_error();break;}
                rele_id = Pantalla_vista_atajos_item-VISTA_ATAJOS_FORZAR_RELE_1; 
                rele_state = Menu::get_valor(RELE_ESTADO_1+rele_id);
                switch(rele_state)
                {
                    case RELE_FLAG_AUTO_OFF:
                    case RELE_FLAG_AUTO_ON:
                        rele_state = RELE_FLAG_FORZADO_ON;
                        break;
                    case RELE_FLAG_FORZADO_ON:
                        rele_state = RELE_FLAG_FORZADO_OFF;
                        break;
                    case RELE_FLAG_FORZADO_OFF:
                        rele_state = RELE_FLAG_AUTO_OFF;
                        break;
                }
                Menu::set_valor(RELE_ESTADO_1+rele_id, rele_state);
                reset_front_timer();
                break;

        }
        print_pantalla_atajos(0);
    }    
#endif
