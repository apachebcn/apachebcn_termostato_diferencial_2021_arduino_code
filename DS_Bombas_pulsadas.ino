/*
void Bombas::_procesa_bomba_pulsada(int bomba_id)
{
    int dispositivo_id = (DISPOSITIVO_DE_SALIDA_BOMBA_1_PULSADA+bomba_id);
    if (!Dispositivos.disponible(dispositivo_id))
    {
        return;
    }

    unsigned long config_time_ms;
    switch(!Bombas_vars[bomba_id].actuando_pulso)
    {
        case FALSE:
            config_time_ms = 1000 * Menu::get_valor(CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_BOMBEO, bomba_id);
            break;
        case TRUE:
            config_time_ms = 1000 * Menu::get_valor(CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_PAUSA, bomba_id);
            break;
    }

    if ( FC::if_diff_to_millis(BombasPulsadasElementos[bomba_id].timer_, config_time_ms) )
    {
        BombasPulsadasElementos[bomba_id].actuando = !BombasPulsadasElementos[bomba_id].actuando;
        BombasPulsadasElementos[bomba_id].timer_ = millis();
    }
}

*/
