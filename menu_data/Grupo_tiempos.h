Menu::elemento_insertar(TIEMPO_LECTURAS_SEGUNDOS,                           TIEMPO_LUZ_PANTALLA_SEGUNDOS, 0,                        MENU_TYPE_1_TO_30, 5);
Menu::elemento_insertar(TIEMPO_LUZ_PANTALLA_SEGUNDOS,                       TIEMPO_MENU_LIBERAR_SEGUNDOS, 0,                        MENU_TYPE_0_TO_255, 5);
Menu::elemento_insertar(TIEMPO_MENU_LIBERAR_SEGUNDOS,                       TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS, 0,                 MENU_TYPE_2_TO_255, 30);
Menu::elemento_insertar(TIEMPO_AUTOSILENCIA_ALARMA_SEGUNDOS,                0, 0,                                                   MENU_TYPE_2_TO_255, 180);

