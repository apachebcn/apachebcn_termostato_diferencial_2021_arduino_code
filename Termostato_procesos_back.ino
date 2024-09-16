void back_procesos()
{

    corriendo_procesos_back = 1;


    /*
    *   ACTUAR ALARMAS
    */
    Buzzer::alarma_sonar();
    Dispositivos_alarmas.actuar();


    latido = !latido;
    Leds::latido(latido);


    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (Menu::get_valor(LEDS_VINCULAR_RELES_FORZADOS))
        {
            back_setea_leds_por_reles_forzados();
        }
    #endif


    /*
    *   REFRESCAR LEDS
    */
    Leds::refresca_leds();



    /*
    *   ACTUADORES RELES
    */
    Reles::actuar();




    // ******** SALIR DEL MENU ATAJOS SI EXCEDO EL TIEMPO SIN TOCAR TECLA **********
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            if (Pantalla_vista_atajos_activado)
            {
                if ( Teclado_ultimo_evento_timer_ 
                    && FC::if_diff_to_millis(Teclado_ultimo_evento_timer_, (Menu::get_valor(TIEMPO_MENU_LIBERAR_SEGUNDOS)*1000)) )
                {
                    Pantalla_vista_atajos_activado = 0;
                    Buzzer::beep();
                    front_pantalla();
                }
            }
        #endif
    // ******** SALIR DEL MENU ATAJOS SI EXCEDO EL TIEMPO SIN TOCAR TECLA **********

    
    // ******** SALIR DEL MENU SI EXCEDO EL TIEMPO SIN TOCAR TECLA **********
        if (Menu_activo)
        {
            if ( Teclado_ultimo_evento_timer_ && FC::if_diff_to_millis(Teclado_ultimo_evento_timer_, (Menu::get_valor(TIEMPO_MENU_LIBERAR_SEGUNDOS)*1000)) )
            {
                Menu::salir();
            }
        }
    // ******** SALIR DEL MEN SI EXCEDO EL TIEMPO SIN TOCAR TECLA **********


    // ******** APAGA PANTALLA SI NO SE TOCA TECLA **********
        if (!Menu_activo && Pantalla_luz 
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                && !Pantalla_vista_atajos_activado
            #endif
        )
        {
            unsigned long time_test = Menu::get_valor(TIEMPO_LUZ_PANTALLA_SEGUNDOS);
            time_test *= 1000;
            //Apagar la pantalla si est encendida mas de (configuracion)
            if ( time_test > 0 && FC::if_diff_to_millis(Pantalla_luz_timer_, time_test) )
            {
                Pantalla::apagar();
            }
        }
    // ******** APAGA PANTALLA SI NO SE TOCA TECLA **********

    
    ultima_lectura_ciclo_back_process_ms_timer_ = millis();
    corriendo_procesos_back = 0;
    DogWatch_update();
}

bool back_procesos_comprueba_actividad_bombas()
{
    for(byte bucle = 0; bucle < TOTAL_SONDAS_COLECTORES; bucle++)
    {
        if (Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+bucle))
        {
            return 1;
        }
    }
    return 0;
}

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void back_setea_leds_por_reles_forzados()
    {
        byte rele_id;
        byte led_valor;
        byte bucle;
        int menu_estado_rele; 
        char menu_estado_rele_icono; 
        int dispositivo_entrada_id;
        int dispositivo_salida_id;

        for(rele_id = 0; rele_id < TOTAL_RELES; rele_id++)
        {
            menu_estado_rele = Menu::get_valor(RELE_ESTADO_1+rele_id);
            menu_estado_rele_icono = ' '; 

            switch(menu_estado_rele)
            {
                case RELE_FLAG_FORZADO_OFF:
                    led_valor = Leds::coge_estado_cuando_forzado_off();
                    menu_estado_rele_icono = ICON_DOWN; 
                    break;
                case RELE_FLAG_FORZADO_ON:
                    led_valor = Leds::coge_estado_cuando_forzado_on();
                    menu_estado_rele_icono = ICON_UP; 
                    break;
            }
            if (menu_estado_rele_icono == ' ') continue;

            for(bucle = 0; bucle < TOTAL_SONDAS_COLECTORES; bucle++)
            {
                if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_BOMBA_1+bucle) == rele_id)
                {
                    Dispositivos.set_estado_icono(DISPOSITIVO_DE_ENTRADA_COLECTOR_1+bucle, menu_estado_rele_icono);
                    _front_set_led(DISPOSITIVO_DE_ENTRADA_COLECTOR_1+bucle, led_valor);
                }
            }

            for(bucle = 0; bucle < TOTAL_SONDAS_COLECTORES; bucle++)
            {
                if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1+bucle) == rele_id)
                {
                    Dispositivos.set_estado_icono(DISPOSITIVO_DE_ENTRADA_COLECTOR_1+bucle, menu_estado_rele_icono);
                }
            }

            if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_CALENTADOR) == rele_id)
            {
                Dispositivos.set_estado_icono(DISPOSITIVO_DE_ENTRADA_DEPOSITO, menu_estado_rele_icono);
                _front_set_led(DISPOSITIVO_DE_SALIDA_CALENTADOR, led_valor);
            }

            if (Dispositivos.get_rele(DISPOSITIVO_DE_SALIDA_AGUA) == rele_id)
            {
                Dispositivos.set_estado_icono(DISPOSITIVO_DE_ENTRADA_AGUA, menu_estado_rele_icono);
                _front_set_led(DISPOSITIVO_DE_SALIDA_AGUA, led_valor);
            }
        }
    }
#endif