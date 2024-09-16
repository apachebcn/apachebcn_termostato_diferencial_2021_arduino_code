void Teclado::procesar_teclas_cortas(byte key_push)
{
    if (Teclado_ignorar_teclado_corto) 
    {
        Teclado_ignorar_teclado_corto = 0;
        FC::delayMilisegundos(50);
        return;
    }

    Pantalla::encender();
    Teclado_ultimo_evento_timer_ = millis();
 
    if (Teclado_locked_keys)
    {
        Pantalla::insertar_info_msg(MENSAJE_BLOQUEAR_TECLADO);
        front_pantalla();
        return;
    }
   
    if (Menu_activo)
    {
        Menu_eventos::tecla(key_push);
        return;
    }
    switch (key_push) 
    {
        case SIGN_TECLA_OK:
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                /*
                * MEGA: Conmutar fila de pantalla atajos
                */
                if (Pantalla_vista_atajos_activado)
                {
                    Pantalla_atajos::print_pantalla_atajos_validar();
                    reset();
                    return;
                }
            #endif
            Menu::entrar();
            break;

        case SIGN_TECLA_ATRAS:
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

            switch(Pantalla_modo_vista)
            {
                case VISTA_NORMAL: 
                    if (Dispositivos_alarmas.existe_alarma_no_silenciada())
                    {
                        Buzzer::beep_ultracorto();
                        digitalWrite(PIN_BUZZER, 0); 
                        Dispositivos_alarmas.silenciar();
                        reset_front_timer();
                        Pantalla::insertar_info_msg(MENSAJE_INFO_SILENCIAR);
                    }
                    break;
                case VISTA_STAT_MIN:
                    Dispositivos.reset_valor_mins();
                    Buzzer::beep_ultracorto();
                    reset_front_timer();
                    Pantalla::insertar_info_msg(MENSAJE_INFO_RESET);
                    break;
                case VISTA_STAT_MAX:
                    Dispositivos.reset_valor_maxs();
                    Buzzer::beep_ultracorto();
                    reset_front_timer();
                    Pantalla::insertar_info_msg(MENSAJE_INFO_RESET);
                    break;
                case VISTA_ALARMAS:
                    if (Dispositivos_alarmas.existe_alarma_no_silenciada())
                    {
                        Buzzer::beep_ultracorto();
                        digitalWrite(PIN_BUZZER, 0); 
                        Dispositivos_alarmas.silenciar();
                        reset_front_timer();
                        Pantalla::insertar_info_msg(MENSAJE_INFO_SILENCIAR);
                    }
                    else
                    {
                        Dispositivos_alarmas.reset();
                        Buzzer::beep_ultracorto();
                        reset_front_timer();
                        Pantalla::insertar_info_msg(MENSAJE_INFO_RESET);
                    }
                    break;
                case VISTA_SONDAS:
                    Sondas::scan();
                    Buzzer::beep_ultracorto();
                    reset_front_timer();
                    break;
            }
            break;

        case SIGN_TECLA_ARRIBA:
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                /*
                * MEGA: Sube fila en pantalla atajos
                */
                if (Pantalla_vista_atajos_activado)
                {
                    Pantalla_atajos::print_pantalla_atajos(-1);
                    Buzzer::beep_ultracorto();
                    reset();
                    return;
                }
            #endif

            // CAMBIA VISTA DE PANTALLA
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                decrementa_vista();
                Buzzer::beep_ultracorto();
            #endif
            #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
                incrementa_vista();
                Buzzer::beep_ultracorto();
            #endif
            break;

        case SIGN_TECLA_ABAJO:
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                /*
                * MEGA: Baja fila en pantalla atajos
                */
                if (Pantalla_vista_atajos_activado)
                {
                    Pantalla_atajos::print_pantalla_atajos(1);
                    Buzzer::beep_ultracorto();
                    reset();
                    return;
                }
            #endif

            // CAMBIA VISTA DE PANTALLA
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                incrementa_vista();
                Buzzer::beep_ultracorto();
            #endif
            #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
                decrementa_vista();
                Buzzer::beep_ultracorto();
            #endif
            break;
    }
}

void Teclado::incrementa_vista()
{
    if (Pantalla_modo_vista < VISTA_LAST) 
    {
        Pantalla_modo_vista++;
        front_pantalla();
    }
}

void Teclado::decrementa_vista()
{
    if (Pantalla_modo_vista > 0)
    {
        Pantalla_modo_vista--;
        front_pantalla();
    }
}