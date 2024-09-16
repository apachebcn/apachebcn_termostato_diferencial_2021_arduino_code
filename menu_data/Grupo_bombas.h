for(bucle=0; bucle < TOTAL_SONDAS_COLECTORES; bucle++)
{
    idx = Menu_grupal::get_id(G_BOMBA_1, bucle);

    if (bucle < TOTAL_SONDAS_COLECTORES-1)
    {
        idx2 = Menu_grupal::get_id(G_BOMBA_1, bucle+1);
    }
    else
    {
        idx2 = 0;
    }

    Menu::elemento_insertar(idx,    idx2,   idx+1,  MENU_TYPE_GROUP, 0);

        idx = Menu_grupal::get_id(BOMBA_1_ON_OFF, bucle);
        Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_ACTIVAR, 0);

        idx = Menu_grupal::get_id(BOMBA_1_RELE_NUM, bucle);
        Menu::elemento_insertar(idx,    idx+1,      0,      MENU_TYPE_RELE_SELECTOR, 0);

        idx = Menu_grupal::get_id(G_CONTROL_BOMBA_1, bucle);
        Menu::elemento_insertar(idx, 0, idx+1,   MENU_TYPE_GROUP, 0);

            idx = Menu_grupal::get_id(CONTROL_BOMBA_1_DIFF_TO_ON, bucle);
            Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_MINUS_255_TO_255, 10);

            idx = Menu_grupal::get_id(CONTROL_BOMBA_1_DIFF_TO_OFF, bucle);
            Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_MINUS_255_TO_255, 4);

            idx = Menu_grupal::get_id(CONTROL_BOMBA_1_RUN_SI_COLECTOR_MENOR_DE_TEMP, bucle);
            Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_MINUS_255_TO_255, 4);

            idx = Menu_grupal::get_id(CONTROL_BOMBA_1_STOP_SI_ZTERM_MAYOR_DE_TEMP, bucle);
            Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_MINUS_255_TO_255, 70);

            idx = Menu_grupal::get_id(CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_BOMBEO, bucle);
            Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_0_TO_255, 0);

            idx = Menu_grupal::get_id(CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_PAUSA, bucle);
            Menu::elemento_insertar(idx,    0,  0,      MENU_TYPE_0_TO_255, 0);
}
