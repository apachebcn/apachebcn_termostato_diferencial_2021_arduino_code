for(bucle=0; bucle < TOTAL_SONDAS_COLECTORES; bucle++)
{
    idx = Menu_grupal::get_id(G_REFRIGERAR_COLECTOR_1, bucle);

    if (bucle < TOTAL_SONDAS_COLECTORES-1)
    {
        idx2 = Menu_grupal::get_id(G_REFRIGERAR_COLECTOR_1, bucle+1);
    }
    else
    {
        idx2 = 0;
    }

    Menu::elemento_insertar(idx,    idx2,   idx+1,  MENU_TYPE_GROUP, 0);

    idx = Menu_grupal::get_id(REFRIGERAR_COLECTOR_1_ON_OFF, bucle);
    Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_ACTIVAR, 0);

    idx = Menu_grupal::get_id(REFRIGERAR_COLECTOR_1_RELE_NUM, bucle);
    Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_RELE_SELECTOR, 0);

    idx = Menu_grupal::get_id(REFRIGERAR_COLECTOR_1_SI_TEMP_SUPERIOR_A, bucle);
    Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_MINUS_255_TO_255, 90);

    idx = Menu_grupal::get_id(REFRIGERAR_COLECTOR_1_DIFF_OFF, bucle);
    Menu::elemento_insertar(idx,    idx+1, 0,   MENU_TYPE_0_TO_100, 0);

    idx = Menu_grupal::get_id(REFRIGERAR_COLECTOR_1_AHORRO_ON_OFF, bucle);
    Menu::elemento_insertar(idx,    0, 0,   MENU_TYPE_ACTIVAR, 0);
}

