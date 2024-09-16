void Refrigerador::actualizar(int col_id)
{
    //Funcion ahorro, si cualquiera de las 3 bombas están actuando, anular la funcion calentar
    if (Menu::get_valor(REFRIGERAR_COLECTOR_1_AHORRO_ON_OFF+col_id))
    {
        if (Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+col_id))
        {
            Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1+col_id, 0);
            return;
        }
    }

    float dispositivo_valor = Dispositivos.get_entrada_valor(DISPOSITIVO_DE_ENTRADA_COLECTOR_1+col_id);
    int menu_valor = Menu::get_valor(REFRIGERAR_COLECTOR_1_SI_TEMP_SUPERIOR_A, col_id);
    int menu_diff_valor = Menu::get_valor(REFRIGERAR_COLECTOR_1_DIFF_OFF, col_id);
    switch(Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1 + col_id))
    {
        case 0:
            if (dispositivo_valor > menu_valor)
            {
                Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1 + col_id, 1);
            }
            break;
        case 1:
            if (dispositivo_valor <= (menu_valor-menu_diff_valor))
            {
                Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_REFRIGERADOR_1 + col_id, 0);
            }
            break;
    }
}