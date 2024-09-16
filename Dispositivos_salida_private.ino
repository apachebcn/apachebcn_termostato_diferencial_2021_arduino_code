bool Dispositivos_salida::_calcula_activado(int dispositivo_id)
{
    //ACTIVADORES PROPIOS
    int dispositivo_grupo_id = Dispositivos.pertenece_a_grupo_de(dispositivo_id);
    switch(dispositivo_grupo_id)
    {
        case DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1:
            if (!Menu::get_valor(REFRIGERAR_COLECTOR_1_ON_OFF, dispositivo_id-dispositivo_grupo_id)) 
            {
                return FALSE;
            }
            break;

        case DISPOSITIVO_DE_SALIDA_CALENTADOR:
            if (!Menu::get_valor(CALENTADOR_DEPOSITO_ON_OFF)) 
            {
                return FALSE;
            }
            break;

        case DISPOSITIVO_DE_SALIDA_BOMBA_1:
            if (!Menu::get_valor(BOMBA_1_ON_OFF, dispositivo_id-dispositivo_grupo_id)) 
            {
                return FALSE;
            }
            break;

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            case DISPOSITIVO_DE_SALIDA_AGUA:
                if (!Menu::get_valor(AGUA_ON_OFF)) 
                {
                    return FALSE;
                }
                break;
        #endif
   }
    return TRUE;
}

bool Dispositivos_salida::_calcula_disponible(int dispositivo_id)
{
    return TRUE;
}

bool Dispositivos_salida::_calcula_reles_disponibles(int dispositivo_id)
{
    int rele_num = Dispositivos.get_rele(dispositivo_id);
    return (rele_num > -1);
}
