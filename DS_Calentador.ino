void Calentador::actualizar()
{
    //Funcion ahorro, si cualquiera de las 3 bombas están actuando, anular la funcion calentar
    if (Menu::get_valor(CALENTADOR_DEPOSITO_AHORRO_ON_OFF))
    {
        for(int colector_num = 0; colector_num < TOTAL_SONDAS_COLECTORES; colector_num++)
        {
            if (Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_BOMBA_1+colector_num))
            {
                Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_CALENTADOR, 0);
                return;
            }
        }
    }

    float dispositivo_valor = Dispositivos.get_entrada_valor(DISPOSITIVO_DE_ENTRADA_DEPOSITO);
    int menu_valor = Menu::get_valor(CALENTADOR_DEPOSITO_SI_TEMP_INFERIOR_A);
    int menu_diff_valor = Menu::get_valor(CALENTADOR_DEPOSITO_DIFF_OFF);

    switch(Dispositivos.get_salida_valor(DISPOSITIVO_DE_SALIDA_CALENTADOR))
    {
        case 0:
            if (dispositivo_valor < menu_valor)
            {
                Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_CALENTADOR, 1);
                Serial.print("CALENTADOR ON");
            }
            break;
        case 1:
            if (dispositivo_valor >= (menu_valor+menu_diff_valor))
            {
                Dispositivos.set_salida_valor(DISPOSITIVO_DE_SALIDA_CALENTADOR, 0);
                Serial.print("CALENTADOR OFF");
            }
    }
}
