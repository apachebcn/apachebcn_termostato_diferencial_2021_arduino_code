Menu::elemento_insertar(CALENTADOR_DEPOSITO_ON_OFF,                         CALENTADOR_DEPOSITO_RELE_NUM, 0,            MENU_TYPE_ACTIVAR, 0);
Menu::elemento_insertar(CALENTADOR_DEPOSITO_RELE_NUM,                       CALENTADOR_DEPOSITO_SI_TEMP_INFERIOR_A, 0,  MENU_TYPE_RELE_SELECTOR, 0);
Menu::elemento_insertar(CALENTADOR_DEPOSITO_SI_TEMP_INFERIOR_A,             CALENTADOR_DEPOSITO_DIFF_OFF, 0,            MENU_TYPE_MINUS_255_TO_255, 30);
Menu::elemento_insertar(CALENTADOR_DEPOSITO_DIFF_OFF,                       CALENTADOR_DEPOSITO_AHORRO_ON_OFF, 0,       MENU_TYPE_0_TO_100, 0);
Menu::elemento_insertar(CALENTADOR_DEPOSITO_AHORRO_ON_OFF,                  0, 0,                                       MENU_TYPE_ACTIVAR, 1);


