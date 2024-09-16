void Teclado::procesar_teclas_largas(byte& tecla_sosteniendo)
{
    Teclado_ignorar_teclado_corto = 1;
    if (!Teclado_locked_keys) 
    {
        Pantalla::encender();
    }

    Teclado_ultimo_evento_timer_ = millis();
    
    switch(tecla_sosteniendo)
    {
        case SIGN_TECLA_ATRAS:
            //Salir del menu
            if (Menu_activo) 
            {
                Menu::salir();
                reset();
                return;
            }
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                /*
                * MEGA: Salir de pantalla atajos
                */
                if (Pantalla_vista_atajos_activado)
                {
                    Pantalla_vista_atajos_activado = 0;
                    lcd.noBlink();
                    Buzzer::beep();
                    front_pantalla();
                    reset();
                    return;
                }
            #endif
            if (Teclado_sosteniendo_timer_ 
            && millis() - Teclado_sosteniendo_timer_  > 2000)
            {
                bloquear();
                reset();
                return;
            }
            break;

        case SIGN_TECLA_OK:
            if (Teclado_locked_keys) return;
            if (Menu_activo) 
            {
                return;
            }
            #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
                /*
                * MINI: Forzar bomba-1
                */
                Bombas::accion_forzar(0);
                reset_front_timer();
                reset();
                return;
            #endif
                
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                /*
                * MEGA: Entrar en pantalla atajos
                */
                if (!Pantalla_vista_atajos_activado)
                {
                    Pantalla::print_centrado(F("ATAJOS"), DISPLAY_INFO_POS_Y);
                    Buzzer::beep();
                    FC::delayMilisegundos(500);
                    Pantalla_vista_atajos_activado = 1;
                    Pantalla_atajos::print_pantalla_atajos(0);
                    reset();
                    return;
                }
            #endif
            break;

        case SIGN_TECLA_ARRIBA:
            if (Teclado_locked_keys) return;
            if (Menu_activo) 
            {
                Menu_eventos::tecla(tecla_sosteniendo);
                return;
            }
            #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
                /*
                * MINI: Visor relés
                */
                Menu::set_valor(RELES_VISOR, !Menu::get_valor(RELES_VISOR));
                Buzzer::beep();
                reset(); 
                front_pantalla();
                return;
            #endif
            break;

        case SIGN_TECLA_ABAJO:
            if (Teclado_locked_keys) return;
            if (Menu_activo) 
            {
                Menu_eventos::tecla(tecla_sosteniendo);
                return;
            }
            break;
    }
}
