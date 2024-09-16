void Dispositivos_entrada::_prevenir_sondas()
{
    bool sondas_error = 0;
    for(int dispositivo_entrada_id = DISPOSITIVO_DE_ENTRADA_PRIMER_ID; dispositivo_entrada_id < (TOTAL_DISPOSITIVOS_DE_ENTRADA+DISPOSITIVO_DE_ENTRADA_PRIMER_ID); dispositivo_entrada_id++)
    {
        if (Dispositivos.es_tipo_sonda(dispositivo_entrada_id))
        {
            if (Dispositivos.error(dispositivo_entrada_id))
            {
                sondas_error = 1;
            }
        }
    }
    if (sondas_error)
    {
        Sondas::scan();
    }
}

bool Dispositivos_entrada::_calcula_activado(int dispositivo_id)
{
    //DISPOSITIVOS QUE DEPENDEN DEL ACTIVADOR SONDAS_ON_OFF
    if (Dispositivos.es_tipo_sonda(dispositivo_id))
    {
        if (!Menu::get_valor(SONDAS_ON_OFF)) 
        {
            return FALSE;
        }
    }
    
    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
        int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_id);
        //ACTIVADORES PROPIOS
        switch(dispositivo_grupo_id)
        {
            case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:
                if (!Menu::get_valor(SONDA_COLECTOR_1_ON_OFF, dispositivo_id-dispositivo_grupo_id)) 
                {
                    return FALSE;
                }
                break;

            case DISPOSITIVO_DE_ENTRADA_ZONA_1:
                if (!Menu::get_valor(SONDA_ZONA_1_ON_OFF, dispositivo_id-dispositivo_grupo_id)) 
                {
                    return FALSE;
                }
                break;

            case DISPOSITIVO_DE_ENTRADA_AGUA:
                if (!Menu::get_valor(AGUA_ON_OFF)) 
                {
                    return FALSE;
                }
                break;

            case DISPOSITIVO_DE_ENTRADA_LCD7:
                if (!Menu::get_valor(LCD_7_ON_OFF)) 
                {
                    return FALSE;
                }
                break;
       }
    #endif

    return TRUE;
}

bool Dispositivos_entrada::_calcula_sensores_disponibles(int dispositivo_id)
{
    // DISPOSITIVOS QUE DEPENDEN DE SONDAS PROPIAS
    bool colector_ok;
    int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_id);
    switch(dispositivo_grupo_id)
    {
        case DISPOSITIVO_DE_ENTRADA_DEPOSITO:
            if (!Sondas::test_dir(Sondas_deposito_dir)) 
            {
                return FALSE;
            }
            break;

        case DISPOSITIVO_DE_ENTRADA_ZTERMOSTATO:
            if (!Sondas::test_dir(Sondas_ztermostato_dir))
            {
                return FALSE;
            }
            break;

        case DISPOSITIVO_DE_ENTRADA_COLECTOR_1:
            if (!Sondas::test_dir(Sondas_colector_dir[(dispositivo_id-dispositivo_grupo_id)]))
            {
                return FALSE;
            }
            break;

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_ENTRADA_ZONA_1:
                if (!Sondas::test_dir(Sondas_zona_dir[(dispositivo_id-dispositivo_grupo_id)]))
                {
                    return FALSE;
                }
                break;

            case DISPOSITIVO_DE_ENTRADA_AGUA:
                if (Dispositivos.get_entrada_valor(dispositivo_id) < Menu::get_valor(AGUA_SUELO_VIRTUAL))
                {
                    return FALSE;
                }
                if (Dispositivos.get_entrada_valor(dispositivo_id) > Menu::get_valor(AGUA_TECHO_VIRTUAL)) 
                {
                    return FALSE;
                }
                return TRUE;
                break;

            case DISPOSITIVO_DE_ENTRADA_LCD7:
                if (!Sondas::test_dir(Sondas_lcd7_dir))
                {
                    return FALSE;
                }
        #endif
    }
    return TRUE;
}

float Dispositivos_entrada::_leer_sonda_valor(byte* sonda_addr)
{
    float valor;
    if (Sondas::buscar_addr_dir(sonda_addr) < 0) 
    {
        return VALOR_RESET_O_ERROR;
    }
    valor = Sondas::lee_la_sonda_dir(sonda_addr, 0);
    if (valor == VALOR_RESET_O_ERROR) return VALOR_RESET_O_ERROR;
    return valor;
}

