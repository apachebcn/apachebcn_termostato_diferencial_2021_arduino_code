for(bucle=0; bucle < TOTAL_SONDAS_ZONAS; bucle++)
{
    idx = Menu_grupal::get_id(G_SONDA_ZONA_1, bucle);
    if (bucle < TOTAL_SONDAS_ZONAS-1)
    {
        idx2 = Menu_grupal::get_id(G_SONDA_ZONA_1, bucle+1);
    }
    else
    {
        idx2 = 0;
    }
    Menu::elemento_insertar(idx,    idx2,   idx+1,  MENU_TYPE_GROUP, 0);
    
    idx = Menu_grupal::get_id(SONDA_ZONA_1_ON_OFF, bucle);
    Menu::elemento_insertar(idx,    idx+1,  0,      MENU_TYPE_ACTIVAR, 0);

    idx = Menu_grupal::get_id(SONDA_ZONA_1_DIR, bucle);
    Menu::elemento_insertar(idx,    0,      0,      MENU_TYPE_SONDA_SELECTOR, 0);
}

