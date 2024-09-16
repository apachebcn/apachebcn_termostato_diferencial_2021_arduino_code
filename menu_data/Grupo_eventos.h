Menu::elemento_insertar(EVENTOS_ON_OFF,                                     G_EVENTO_1, 0,                                 MENU_TYPE_ACTIVAR, 0);

for(bucle = 0; bucle < TOTAL_EVENTOS; bucle++)
{
    idx = Menu_grupal::get_id(G_EVENTO_1, bucle);
    if (bucle < TOTAL_EVENTOS-1)
    {
        idx2 = Menu_grupal::get_id(G_EVENTO_1, bucle+1);
    }
    else
    {
        idx2 = 0;
    }

    Menu::elemento_insertar(idx,    idx2,   idx+1,  MENU_TYPE_GROUP, 0);

    idx = Menu_grupal::get_id(EVENTO_1_ON_OFF, bucle);
    Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_ACTIVAR, 0);

    idx = Menu_grupal::get_id(EVENTO_1_DISPOSITIVO, bucle);
    Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_DISPOSITIVO, -1);

    idx = Menu_grupal::get_id(EVENTO_1_RELE_NUM, bucle);
    Menu::elemento_insertar(idx,    idx+1,      0,      MENU_TYPE_RELE_SELECTOR, 0);

    idx = Menu_grupal::get_id(EVENTO_1_RELE_ACCION, bucle);
    Menu::elemento_insertar(idx,    idx+1,      0,      MENU_TYPE_EVENTO_RELE_ACCION, 1);

    idx = Menu_grupal::get_id(EVENTO_1_ES_ALARMA, bucle);
    Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_ACTIVAR, 0);

    idx = Menu_grupal::get_id(EVENTO_1_OPERACION, bucle);
    Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_BOOL, 0);

    idx = Menu_grupal::get_id(EVENTO_1_VALOR, bucle);
    Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_MINUS_255_TO_255, 0);

    idx = Menu_grupal::get_id(EVENTO_1_DIFF_OFF, bucle);
    Menu::elemento_insertar(idx,    0,  0,      MENU_TYPE_0_TO_100, 0);
}
