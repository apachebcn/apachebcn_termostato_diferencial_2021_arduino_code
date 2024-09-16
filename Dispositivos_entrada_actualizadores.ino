void Dispositivos_entrada::actualizar()
{
    _actualizar_estados();
    _actualizar_dependencias();
    _actualizar_dispositivos();
}

void Dispositivos_entrada::_actualizar_estados()
{
    int dispositivo_id;
    bool dispositivo_activado;
    bool dispositivo_disponible;
    bool dispositivo_on_off;
    bool dispositivo_ok;


    // ACTUALIZACION DE DISPOSITIVOS DE ENTRADA
    for(dispositivo_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_id < (DISPOSITIVO_DE_ENTRADA_PRIMER_ID+TOTAL_DISPOSITIVOS_DE_ENTRADA); dispositivo_id++)
    {
        dispositivo_activado = _calcula_activado(dispositivo_id);
        if (dispositivo_activado)
        {
            dispositivo_disponible = _calcula_sensores_disponibles(dispositivo_id);
            if (dispositivo_disponible)
            {
                Dispositivos.set_estado(dispositivo_id, ESTADO_DISPOSITIVO_DE_ENTRADA_DISPONIBLE);
            }
            else
            {
                Dispositivos.set_estado(dispositivo_id, ESTADO_DISPOSITIVO_DE_ENTRADA_NO_DISPONIBLE);
            }
        }
        else
        {
            Dispositivos.set_estado(dispositivo_id, ESTADO_DISPOSITIVO_DE_ENTRADA_DESACTIVADO);
        }
    }
}

void Dispositivos_entrada::_actualizar_dependencias()
{
}

void Dispositivos_entrada::_actualizar_dispositivos()
{
    float valor;
    for(int dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_entrada_id < (TOTAL_DISPOSITIVOS_DE_ENTRADA+DISPOSITIVO_DE_ENTRADA_PRIMER_ID); dispositivo_entrada_id++)
    {
        valor = VALOR_RESET_O_ERROR;
        if (Dispositivos.inactivo(dispositivo_entrada_id)) 
        {
            continue;
        }

        if (!Dispositivos.disponible(dispositivo_entrada_id)) 
        {
            continue;
        }
        int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_entrada_id);
        switch(dispositivo_grupo_id)
        {
            case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:
                valor = _leer_sonda_valor(Sondas_colector_dir[(dispositivo_entrada_id-dispositivo_grupo_id)]);
                break;

            case DISPOSITIVO_DE_ENTRADA_DEPOSITO:
                valor = _leer_sonda_valor(Sondas_deposito_dir);
                break;

            case DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO:
                valor = _leer_sonda_valor(Sondas_ztermostato_dir);
                break;

            #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                case DISPOSITIVO_DE_ENTRADA_ZONA_1:
                    valor = _leer_sonda_valor(Sondas_zona_dir[(dispositivo_entrada_id-dispositivo_grupo_id)]);
                    break;

                case DISPOSITIVO_DE_ENTRADA_AGUA:
                    break;

                case DISPOSITIVO_DE_ENTRADA_LCD7:
                    valor = _leer_sonda_valor(Sondas_lcd7_dir);
                break;
            #endif
        }

        if (valor == VALOR_RESET_O_ERROR)
        {
            Dispositivos.set_estado(dispositivo_entrada_id, ESTADO_DISPOSITIVO_DE_ENTRADA_ERROR);
        }
        else
        {
            Dispositivos.set_entrada_valor(dispositivo_entrada_id, valor);
            if (valor > Dispositivos.get_entrada_valor_max(dispositivo_entrada_id) || Dispositivos.get_entrada_valor_max(dispositivo_entrada_id) == VALOR_RESET_O_ERROR) 
            {
                Dispositivos.set_valor_max(dispositivo_entrada_id, valor);
            }
            if (valor < Dispositivos.get_entrada_valor_min(dispositivo_entrada_id) || Dispositivos.get_entrada_valor_min(dispositivo_entrada_id) == VALOR_RESET_O_ERROR) 
            {
                Dispositivos.set_valor_min(dispositivo_entrada_id, valor);
            }
        }
    }

    /*
    *   COMPROBAR SI ALGUNA SONDA NO HA ESTADO DISPONIBLE PARA HACER UN SCAN
    */
    Dispositivos_entrada::_prevenir_sondas();

}
