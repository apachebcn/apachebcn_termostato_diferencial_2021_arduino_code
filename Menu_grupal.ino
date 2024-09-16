int Menu_grupal::get_id(int menu_id, int nivel_id)
{
        int diff;
        int ini, end;
        int step_var = 0;
        if (nivel_id < 1)
        {
            return menu_id;
        }
        
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            diff = G_BOMBA_2 - G_BOMBA_1;
            ini = G_BOMBA_1;
            end = CONTROL_BOMBA_1_TIEMPO_PULSADO_CICLO_PAUSA;
            end += (diff*(TOTAL_SONDAS_COLECTORES-1));
            if (menu_id >= ini && menu_id <= end) return _select_id_multi_menu(menu_id, diff, ini, end, nivel_id);
        #endif

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            diff = G_SONDA_COLECTOR_2 - G_SONDA_COLECTOR_1;
            ini = G_SONDA_COLECTOR_1;
            end = SONDA_COLECTOR_3_DIR;
            end += (diff*(TOTAL_SONDAS_COLECTORES-1));
            if (menu_id >= ini && menu_id <= end) return _select_id_multi_menu(menu_id, diff, ini, end, nivel_id);
        #endif

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            diff = G_SONDA_ZONA_2 - G_SONDA_ZONA_1;
            ini = G_SONDA_ZONA_1;
            end = SONDA_ZONA_1_DIR;
            end += (diff*(TOTAL_SONDAS_ZONAS-1));
            if (menu_id >= ini && menu_id <= end) return _select_id_multi_menu(menu_id, diff, ini, end, nivel_id);
        #endif

        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            diff = G_REFRIGERAR_COLECTOR_2 - G_REFRIGERAR_COLECTOR_1;
            ini = G_REFRIGERAR_COLECTOR_1;
            end = REFRIGERAR_COLECTOR_1_RELE_NUM;
            end += (diff*(TOTAL_SONDAS_COLECTORES-1));
            if (menu_id >= ini && menu_id <= end) return _select_id_multi_menu(menu_id, diff, ini, end, nivel_id);
        #endif

        diff = G_EVENTO_2 - G_EVENTO_1;
        ini = G_EVENTO_1;
        end = EVENTO_1_RELE_NUM;
        end += (diff*(TOTAL_EVENTOS-1));
        if (menu_id >= ini && menu_id <= end) return _select_id_multi_menu(menu_id, diff, ini, end, nivel_id);

        diff = RELE_ESTADO_2 - RELE_ESTADO_1;
        ini = RELE_ESTADO_1;
        end = RELE_ESTADO_1;
        end += (diff*(TOTAL_RELES-1));
        if (menu_id >= ini && menu_id <= end) return _select_id_multi_menu(menu_id, diff, ini, end, nivel_id);

        return menu_id;
}

int Menu_grupal::_select_id_multi_menu(int menu_id, int diff, int ini, int end, int nivel_id)
{
    if (diff < 0)
    {
        //MT#10
        Menu::print_err(menu_id, 10, F("diff"), diff);
        return 0;
    }

    if (diff > MENU_ELEMENTOS_TOTAL)
    {
        //MT#11
        Menu::print_err(menu_id, 11, F("diff"), diff);
        return 0;
    }

    if (ini < 0)
    {
        //MT#12
        Menu::print_err(menu_id, 12, F("ini"), ini);
        return 0;
    }

    if (ini > MENU_ELEMENTOS_TOTAL)
    {
        //MT#13
        Menu::print_err(menu_id, 13, F("ini"), ini);
        return 0;
    }

    if (end < 0)
    {
        //MT#14
        Menu::print_err(menu_id, 14, F("end"), end);
        return 0;
    }

    if (end > MENU_ELEMENTOS_TOTAL)
    {
        //MT#15
        Menu::print_err(menu_id, 15, F("end"), end);
        return 0;
    }

    if (nivel_id < 0)
    {
        //MT#16
        Menu::print_err(menu_id, 16, F("idx"), nivel_id);
        return 0;
    }

    if (nivel_id > MENU_ELEMENTOS_TOTAL)
    {
        //MT#17
        Menu::print_err(menu_id, 17, F("idx"), nivel_id);
        return 0;
    }

    int multilevel_menu_id = menu_id + (nivel_id * diff);
    if (multilevel_menu_id > MENU_ELEMENTOS_TOTAL)
    {
        //MT#18
        Menu::print_err(menu_id, 18, F("idx"), nivel_id);
        return 0;
    }

    if (multilevel_menu_id < 0)
    {
        //MT#19
        Menu::print_err(menu_id, 19, F("idx"), nivel_id);
        return 0;
    }
    return multilevel_menu_id;
}
