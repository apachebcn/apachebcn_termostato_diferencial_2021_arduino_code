void _front_set_led(int dispositivo_mixto_id, byte led_estado)
{
    if (dispositivo_mixto_id < 0) return;
    int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_mixto_id);
    switch(dispositivo_grupo_id)
    {
        case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:
        case DISPOSITIVO_DE_SALIDA_BOMBA_1:
            Leds::set_bomba(dispositivo_mixto_id-dispositivo_grupo_id, led_estado);
            return;
        case DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1:
            Leds::set_bomba_pulsada(dispositivo_mixto_id-dispositivo_grupo_id, led_estado);
            return;
    }

    switch(dispositivo_mixto_id)
    {
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_ENTRADA_AGUA:
            case DISPOSITIVO_DE_SALIDA_AGUA:
                Leds::set_agua(led_estado);
                return;
        #endif

        case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1:
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                Leds::set_refrigerador(led_estado);
            #endif
            #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
                Leds::set_calentador_refrigerador(led_estado);
            #endif
            return;

        case DISPOSITIVO_DE_ENTRADA_DEPOSITO:
        case DISPOSITIVO_DE_SALIDA_CALENTADOR:
            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                Leds::set_calentador(led_estado);
            #endif
            #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
                Leds::set_calentador_refrigerador(led_estado);
            #endif
            return;
    }
}

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    void _front_actuar_led_rele_sobre_evento(int evento_id)
    {
        if (!Menu::get_valor(LEDS_VINCULAR_RELES_EVENTOS))
        {
            return;
        }

        if (!Menu::get_valor(EVENTOS_ON_OFF))
        {
            return;
        }

        if (!Dispositivos_eventos.activado(evento_id)) return;
        int dispositivo_entrada_id = Dispositivos_eventos.get_dispositivo(evento_id);

        if (dispositivo_entrada_id < -1) return;
        if (dispositivo_entrada_id > TOTAL_DISPOSITIVOS_DE_ENTRADA) return;
        byte rele_num = Dispositivos_eventos.get_rele_num(evento_id);
        if (!rele_num) return;
        byte evento_estado = Dispositivos_eventos.estado(evento_id);

        if (!evento_estado) return;

        if (!Dispositivos_eventos.valor(evento_id)) return;

        Dispositivos.set_estado_icono(dispositivo_entrada_id, '<');
        if (Dispositivos_eventos.get_operacion(evento_id))
        {
            Dispositivos.set_estado_icono(dispositivo_entrada_id, '>');
        }

        bool rele_accion = Dispositivos_eventos.get_rele_accion(evento_id);
        if (rele_accion == 0)
        {
            _front_set_led(dispositivo_entrada_id, Leds::coge_estado_cuando_forzado_off());
            Dispositivos.set_estado_icono(dispositivo_entrada_id, ICON_PLAY);
            //Reles::set_valor(rele_num, RELE_FLAG_FORZADO_OFF, RELE_ACTIVADO_POR_EVENTO_1+evento_id);
        }
        if (rele_accion == 1)
        {
            _front_set_led(dispositivo_entrada_id, Leds::coge_estado_cuando_forzado_on());
            Dispositivos.set_estado_icono(dispositivo_entrada_id, ICON_PLAY);
            //Reles::set_valor(rele_num, RELE_FLAG_FORZADO_ON, RELE_ACTIVADO_POR_EVENTO_1+evento_id);
        }
    }

    void _front_actuar_led_rele_sobre_forzado(int rele_id)
    {
        int dispositivo_id;
        int led_estado;

        if (!Menu::get_valor(RELES_ON_OFF))
        {
            return;
        }

        int estado = Menu::get_valor(RELE_ESTADO_1+rele_id);
        switch(estado)
        {
            case RELE_FLAG_FORZADO_OFF:
                led_estado = Leds::coge_estado_cuando_forzado_off();
                //Reles::set_valor(rele_id, RELE_FLAG_FORZADO_OFF, RELE_ACTIVADO_POR_FORZADO_MANUAL);
                break;
            case RELE_FLAG_FORZADO_ON:
                led_estado = Leds::coge_estado_cuando_forzado_on();
                //Reles::set_valor(rele_id, RELE_FLAG_FORZADO_ON, RELE_ACTIVADO_POR_FORZADO_MANUAL);
                break;
            default: return;
        }

        if (!Menu::get_valor(LEDS_VINCULAR_RELES_FORZADOS))
        {
            return;
        }

        for(dispositivo_id = DISPOSITIVO_DE_SALIDA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_SALIDA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_SALIDA); dispositivo_id++)
        {
            if (Dispositivos.get_rele(dispositivo_id) == rele_id)
            {
Serial.print(dispositivo_id);
Serial.print(" - ");
Serial.print(rele_id);
Serial.println();
                _front_set_led(dispositivo_id, led_estado);
                //Dispositivos.set_estado_icono(dispositivo_id, ICON_PLAY);
            }
        }
    }
#endif
