void Front_actualizar_leds_reles()
{
    bool disponible;
    int dispositivo_entrada_id;
    int dispositivo_salida_id;
    int rele_id;
    bool valor;


    /*
    *
    *   PROCESA ICONO, LEDS, RELES - BOMBAS
    *
    */
    for(byte col_id = 0; col_id < TOTAL_SONDAS_COLECTORES; col_id++)
    {
        dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_COLECTOR_1+col_id;
        if (Dispositivos.error(dispositivo_entrada_id))
        {
            continue;            
        }

        disponible = Dispositivos.disponible(dispositivo_entrada_id);
        if (!disponible) continue;

        dispositivo_salida_id = DISPOSITIVO_DE_SALIDA_BOMBA_1+col_id;
        disponible = Dispositivos.disponible(dispositivo_salida_id);
        if (!disponible) continue;

        rele_id = Dispositivos.get_rele(dispositivo_salida_id);
        valor = Dispositivos.get_salida_valor(dispositivo_salida_id);
        if (valor)
        {
            Dispositivos.set_estado_icono(dispositivo_entrada_id, ICON_PLAY);
            _front_set_led(dispositivo_salida_id, LED_ON);
            Reles::set_valor(rele_id, RELE_FLAG_AUTO_ON, RELE_ACTIVADO_POR_BOMBA_1+col_id);
        }
    }
    

    /*
    *
    *   PROCESA ICONOS, LEDS, RELES - CALENTADOR
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_DEPOSITO;
        if (!Dispositivos.error(dispositivo_entrada_id))
        {
            dispositivo_salida_id = DISPOSITIVO_DE_SALIDA_CALENTADOR;
            if (Dispositivos.disponible(dispositivo_entrada_id) && Dispositivos.disponible(dispositivo_salida_id))
            {
                byte rele_id = Dispositivos.get_rele(dispositivo_salida_id);
                valor = Dispositivos.get_salida_valor(dispositivo_salida_id);
                if (valor)
                {
                    Dispositivos.set_estado_icono(dispositivo_entrada_id, ICON_PLAY);
                    _front_set_led(dispositivo_salida_id, LED_ON);
                    Reles::set_valor(rele_id, RELE_FLAG_AUTO_ON, RELE_ACTIVADO_POR_CALENTADOR_DEPOSITO);
                }
            }
        }
    #endif


    /*
    *
    *   PROCESA ICONO, LEDS, RELES - REFRIGERADORES
    *
    */
    bool led_unificado_valor = 0;
    for(byte col_id = 0; col_id < TOTAL_SONDAS_COLECTORES; col_id++)
    {
        dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_COLECTOR_1+col_id;
        if (Dispositivos.error(dispositivo_entrada_id))
        {
            continue;            
        }

        disponible = Dispositivos.disponible(dispositivo_entrada_id);
        if (!disponible) continue;

        dispositivo_salida_id = DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1+col_id;
        disponible = Dispositivos.disponible(dispositivo_salida_id);
        if (!disponible) continue;

        rele_id = Dispositivos.get_rele(dispositivo_salida_id);
        valor = Dispositivos.get_salida_valor(dispositivo_salida_id);
        if (valor)
        {
            Dispositivos.set_estado_icono(dispositivo_entrada_id, ICON_PLAY);
            led_unificado_valor = 1;
            Reles::set_valor(rele_id, RELE_FLAG_AUTO_ON, RELE_ACTIVADO_POR_REFRIGERAR_COLECTOR_COLECTOR_1+col_id);
        }
    }
    _front_set_led(dispositivo_salida_id, led_unificado_valor);


    /*
    *
    *   PROCESA ICONOS, LEDS, RELES - AGUA
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_AGUA;
        if (!Dispositivos.error(dispositivo_entrada_id))
        {
            dispositivo_salida_id = DISPOSITIVO_DE_SALIDA_AGUA;
            if (Dispositivos.disponible(dispositivo_entrada_id) && Dispositivos.disponible(dispositivo_salida_id))
            {
                byte rele_id = Dispositivos.get_rele(dispositivo_salida_id);
                valor = Dispositivos.get_salida_valor(dispositivo_salida_id);
                if (valor)
                {
                    Dispositivos.set_estado_icono(dispositivo_entrada_id, ICON_PLAY);
                    _front_set_led(dispositivo_salida_id, LED_ON);
                    Reles::set_valor(rele_id, RELE_FLAG_AUTO_ON, RELE_ACTIVADO_POR_AGUA);
                }
            }
        }
    #endif


    /*
    *
    *   PROCESA ICONOS, LEDS, RELES - EVENTOS
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        for(int evento_id = 0; evento_id < TOTAL_EVENTOS; evento_id++)
        {
            _front_actuar_led_rele_sobre_evento(evento_id);
        }
    #endif

    /*
    *
    *   PROCESA ICONOS, LEDS, RELES - RELES FORZADOS
    *
    */
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        for(int rele_id = 0; rele_id < TOTAL_RELES; rele_id++)
        {

            _front_actuar_led_rele_sobre_forzado(rele_id);
        }
    #endif
    
}
