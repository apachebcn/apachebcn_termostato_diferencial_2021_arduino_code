void Dispositivos_salida::actualizar()
{
    _actualizar_estados();
    _actualizar_dependencias();
    _actualizar_dispositivos();
}

void Dispositivos_salida::_actualizar_estados()
{
    int dispositivo_id;
    bool dispositivo_activado;
    bool dispositivo_disponible;
    bool dispositivo_on_off;
    bool dispositivo_ok;

    // ACTUALIZACION DE DISPOSITIVOS DE SALIDA
    for(dispositivo_id = DISPOSITIVO_DE_SALIDA_PRIMER_ID; dispositivo_id < (TOTAL_DISPOSITIVOS_DE_SALIDA+DISPOSITIVO_DE_SALIDA_PRIMER_ID); dispositivo_id++)
    {
        dispositivo_activado = _calcula_activado(dispositivo_id);
        if (!dispositivo_activado)
        {
            Dispositivos.set_estado(dispositivo_id, ESTADO_DISPOSITIVO_DE_SALIDA_DESACTIVADO);
            continue;
        }

        dispositivo_disponible = _calcula_disponible(dispositivo_id);
        if (!dispositivo_disponible)
        {
            Dispositivos.set_estado(dispositivo_id, ESTADO_DISPOSITIVO_DE_SALIDA_NO_DISPONIBLE);
            continue;
        }

        if (dispositivo_disponible)
        {
            dispositivo_disponible = _calcula_reles_disponibles(dispositivo_id);
            if (!dispositivo_disponible)
            {
                Dispositivos.set_estado(dispositivo_id, ESTADO_DISPOSITIVO_DE_SALIDA_NO_DISPONIBLE);
                continue;
            }
        }

        Dispositivos.set_estado(dispositivo_id, ESTADO_DISPOSITIVO_DE_SALIDA_DISPONIBLE);
    }
}

void Dispositivos_salida::_actualizar_dependencias()
{
    int dispositivo_entrada_id;
    int dispositivo_salida_id;

    for(int dispositivo_id = DISPOSITIVO_DE_SALIDA_PRIMER_ID; dispositivo_id < (TOTAL_DISPOSITIVOS_DE_SALIDA+DISPOSITIVO_DE_SALIDA_PRIMER_ID); dispositivo_id++)
    {
        int dispositivo_dependiente = 0;
        if (Dispositivos.get_estado(dispositivo_id) != ESTADO_DISPOSITIVO_DE_SALIDA_DISPONIBLE) continue;
        int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_id);
        switch(dispositivo_grupo_id)
        {

            case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1:
                dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_COLECTOR_1+(dispositivo_id-dispositivo_grupo_id);
                if (!Dispositivos.disponible(dispositivo_entrada_id)) dispositivo_dependiente = dispositivo_entrada_id;
                break;

            case DISPOSITIVO_DE_SALIDA_CALENTADOR:
                dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_DEPOSITO;
                if (!Dispositivos.disponible(dispositivo_entrada_id)) dispositivo_dependiente = dispositivo_entrada_id;
                break;

            case DISPOSITIVO_DE_SALIDA_BOMBA_1:
                dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_COLECTOR_1+(dispositivo_id-dispositivo_grupo_id);
                if (!Dispositivos.disponible(dispositivo_entrada_id)) 
                {
                    dispositivo_dependiente = dispositivo_entrada_id;
                    break;
                }
                dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_DEPOSITO;
                if (!Dispositivos.disponible(dispositivo_entrada_id)) 
                {
                    dispositivo_dependiente = dispositivo_entrada_id;
                }
                break;

            case DISPOSITIVO_DE_SALIDA_BOMBA_PULSADA_1:
                dispositivo_salida_id = DISPOSITIVO_DE_SALIDA_BOMBA_1;
                if (!Dispositivos.disponible(dispositivo_salida_id)) 
                {
                    dispositivo_dependiente = dispositivo_salida_id;
                }
                break;

            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                case DISPOSITIVO_DE_SALIDA_AGUA:
                    dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_AGUA;
                    if (!Dispositivos.disponible(dispositivo_entrada_id)) dispositivo_dependiente = dispositivo_entrada_id;
                    break;
            #endif
        }
        if (dispositivo_dependiente)
        {
            Dispositivos.set_estado(dispositivo_id, dispositivo_dependiente);
        }
    }
}

void Dispositivos_salida::_actualizar_dispositivos()
{
    for(int dispositivo_id = DISPOSITIVO_DE_SALIDA_PRIMER_ID; dispositivo_id < (TOTAL_DISPOSITIVOS_DE_SALIDA+DISPOSITIVO_DE_SALIDA_PRIMER_ID); dispositivo_id++)
    {
        if (Dispositivos.inactivo(dispositivo_id)) 
        {
            Dispositivos.set_salida_valor(dispositivo_id, 0);
            continue;
        }

        if (!Dispositivos.disponible(dispositivo_id)) 
        {
            Dispositivos.set_salida_valor(dispositivo_id, 0);
            continue;
        }
        int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_id);
        switch(dispositivo_grupo_id)
        {
            case DISPOSITIVO_DE_SALIDA_BOMBA_1:
                /*
                *   PROCESA DISPOSITIVO VIRTUAL -> BOMBAS
                */
                Bombas::actualizar(dispositivo_id-dispositivo_grupo_id);
                break;
            case DISPOSITIVO_DE_SALIDA_CALENTADOR:
                /*
                *   PROCESA DISPOSITIVO VIRTUAL -> CALENTADOR
                */
                Calentador::actualizar();
                break;
            case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1:
                /*
                *   PROCESA DISPOSITIVO VIRTUAL -> REFRIGERADOR X
                */
                Refrigerador::actualizar(dispositivo_id-dispositivo_grupo_id);
                break;
        }
    }

}

