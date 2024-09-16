void front_procesos()
{

    int rele_id;
    int evento_id_ejecutando;

    corriendo_procesos_front = 1;
    latido = 0;

    Leds::set_lecturas(LED_ON); Leds::refresca_leds();

    /*
    *   POSICIONA RELES A 0
    *   
    */
    Reles::init();
    if (FC::is_debug(DEBUG_RELES)) 
    {
        Serial_debug::println();
        Serial_debug::print(F("-- DEBUG RELES --"));
    }

    /*
    *   POSICIONA LEDS A 0
    *   
    */
    Leds::set_bits(LED_OFF);


    
    /*
    *   SI LA ALARMA SE HA AUTOSILENCIADO
    *   Y SIGUEN ALARMAS MEMORIZADAS(NO SILENCIADAS), BEEP EN CADA LECTURA
    *   
    */
    if (Menu::get_valor(TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS))
    {
        if (Dispositivos_alarmas.existe_alarma_no_silenciada() &&  FC::if_diff_to_millis(Dispositivos_alarmas_inicio_buzzer_timer_, (1000*Menu::get_valor(TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS))) ) 
        {
            Buzzer::beep();
        }
    }



    /*
    *   LIMPIO MEMORIA DE ICONOS 
    */
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        Dispositivos.set_estado_icono(dispositivo_id, ' ');
    }



    /*
    *   ACTUALIZAR ESTADOS DE DISPOSITIVOS DE ENTRADA
    */
    Dispositivos_entrada::actualizar();



    /*
    *   ACTUALIZAR ESTADOS DE DISPOSITIVOS DE SALIDA
    */
    Dispositivos_salida::actualizar();



    /*
    *   PROCESAR EVENTOS
    */
    Dispositivos_eventos.calcular();



    /*
    *   ACTUALIZAR ALARMAS
    */
    for(int dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        switch(Dispositivos.get_estado(dispositivo_id))
        {
            case ESTADO_DISPOSITIVO_DE_ENTRADA_DESACTIVADO:
                Dispositivos_alarmas.set_estado(dispositivo_id, ALARMA_OFF);
                break;
            case ESTADO_DISPOSITIVO_DE_ENTRADA_NO_DISPONIBLE:
                Dispositivos_alarmas.set_estado(dispositivo_id, ALARMA_OFF);
                break;
            case ESTADO_DISPOSITIVO_DE_ENTRADA_ERROR:
                Dispositivos_alarmas.set_estado(dispositivo_id, ALARMA_POR_ERROR);
                break;
            case ESTADO_DISPOSITIVO_DE_ENTRADA_DISPONIBLE:
                evento_id_ejecutando = Dispositivos_eventos.ultimo_ejecutando(dispositivo_id, 1);
                if (evento_id_ejecutando > -1)
                {
                    if (Dispositivos_eventos.get_operacion(dispositivo_id))
                    { // >
                        Dispositivos_alarmas.set_estado(dispositivo_id, ALARMA_POR_EVENTO_DE_EXCESO);
                    }
                    else
                    { // <
                        Dispositivos_alarmas.set_estado(dispositivo_id, ALARMA_POR_EVENTO_DE_DECESO);
                    }
                }
                else
                {
                    Dispositivos_alarmas.set_estado(dispositivo_id, ALARMA_OFF);
                    break;
                }
                break;
        }
    }
    Dispositivos_alarmas.actuar(); //Este actuador es para que no se apague el led al final del proceso-front


    /*
    *   DEBUG ALARMAS
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        Dispositivos_alarmas.serial_print_debug();
    #endif



    /*
    *   ACTUAR LEDS Y RELES
    */
    Front_actualizar_leds_reles();



    /*
    *   MOSTRAR DEBUG RESUMEN FINAL DE DISPOSITIVOS
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        if (FC::is_debug(DEBUG_DISPOSITIVOS_IN))
        {
            Dispositivos.serial_print_debug_dispositivos_entrada();
        }

        if (FC::is_debug(DEBUG_DISPOSITIVOS_OUT))
        {
            Dispositivos.serial_print_debug_dispositivos_salida();
        }
    #endif


    corriendo_procesos_front = 0;
    ultima_lectura_ciclo_front_proceso_completo_ms_timer_ = millis();
    Leds::set_lecturas(LED_OFF); Leds::refresca_leds();


    /*
    *   PROCESAR PANTALLA
    */
    front_pantalla();
}

void front_pantalla()
{
    /*
    *   LCD7
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        imprime_lcd7();
    #endif


    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    if (Pantalla_vista_atajos_activado)
    {
        return;
    }
    #endif

    if (Menu_activo)
    {
        if (Menu_editando && Menu::elemento_type(Menu_pos) == MENU_TYPE_SONDA_SELECTOR)
        {
            Menu_editor::print_sonda();
        }
        return;
    }

    switch(Pantalla_modo_vista)
    {
        case VISTA_NORMAL:
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                if (Menu::get_valor(LEDS_VINCULAR_RELES_FORZADOS))
                {
                    back_setea_leds_por_reles_forzados();
                }
            #endif
            Pantalla::imprime_dispositivos_valores(VISTA_NORMAL);
            break;

        case VISTA_EVENTOS:
            Pantalla::print_pantalla_eventos();
            break;

        case VISTA_ALARMAS:
            Pantalla::print_pantalla_alarmas();
            break;

        case VISTA_STAT_MIN:
            Pantalla::imprime_dispositivos_valores(VISTA_STAT_MIN);
            break;

        case VISTA_STAT_MAX:
            Pantalla::imprime_dispositivos_valores(VISTA_STAT_MAX);
            break;

        case VISTA_SONDAS:
            Pantalla::visor_sondas();
            break;
    }

    Pantalla::mostrar_modo_vista();
    Pantalla::mostrar_info_msg();

    if (Pantalla_modo_vista == VISTA_NORMAL && Menu::get_valor(RELES_VISOR))
    {
        Pantalla::mostrar_visor_reles();
    }

}

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
void imprime_lcd7()
{

    if (Dispositivos.error(DISPOSITIVO_DE_ENTRADA_LCD7))
    {
        Lcd7::set_digito_error();
        return;
    }

    if (Dispositivos.inactivo(DISPOSITIVO_DE_ENTRADA_LCD7))
    {
        Lcd7::set_digito_null();
        return;
    }

    if (!Dispositivos.disponible(DISPOSITIVO_DE_ENTRADA_LCD7))
    {
        Lcd7::set_digito_desactivado();
        return;
    }

    switch(Pantalla_modo_vista)
    {
        case VISTA_STAT_MIN:
            Lcd7::set_digito(Dispositivos.get_entrada_valor_min(DISPOSITIVO_DE_ENTRADA_LCD7));
            break;
        case VISTA_STAT_MAX:
            Lcd7::set_digito(Dispositivos.get_entrada_valor_max(DISPOSITIVO_DE_ENTRADA_LCD7));
            break;
        case VISTA_NORMAL:
            Lcd7::set_digito(Dispositivos.get_entrada_valor(DISPOSITIVO_DE_ENTRADA_LCD7));
            break;
        case VISTA_EVENTOS:
        case VISTA_SONDAS:
        case VISTA_ALARMAS:
            Lcd7::set_digito_null();
            break;
    }

}
#endif

void reset_front_timer()
{
    ultima_lectura_ciclo_front_proceso_completo_ms_timer_ = 0;
}
