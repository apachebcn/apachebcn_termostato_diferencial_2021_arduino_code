Menu::elemento_insertar(RELES_ON_OFF,                                       RELES_VISOR,    0,                                      MENU_TYPE_ACTIVAR, 1);
Menu::elemento_insertar(RELES_VISOR,                                        G_RELES_ESTADOS, 0,                                     MENU_TYPE_ACTIVAR, 0);

#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
	Menu::elemento_insertar(G_RELES_ESTADOS,                                    0, RELE_ESTADO_1,                                       MENU_TYPE_GROUP, 0);
	for(bucle=0; bucle < TOTAL_RELES; bucle++)
	{
	    Menu::elemento_insertar(RELE_ESTADO_1+bucle,                            RELE_ESTADO_2+bucle, 0,                                 MENU_TYPE_RELE_ESTADO, 0);
	}
#endif
