#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

    bool Agua::_activado()
    {
        return (bool)Menu::get_valor(AGUA_ON_OFF);
    }

    void Agua::actualiza_pin()
    {
        if (_activado())
        {
            pinMode(PIN_WATER_LEVEL_READ, INPUT); 
            pinMode(PIN_WATER_LEVEL_WRITE, OUTPUT); 
        }
        else
        {
            pinMode(PIN_WATER_LEVEL_READ, 0); 
            pinMode(PIN_WATER_LEVEL_WRITE, 0); 
        }
    }

    bool Agua::activado()
    {
        return _activado();
    }

    bool Agua::ok()
    {
        if (Menu::get_valor(AGUA_ALTURA_PUNTOS) < 2) 
        {
            //agua_set_error(AGUA_ERROR_NIVEL_MENOR_DE_PUNTO_2);
            return FALSE;
        }

        unsigned int altura_config_punto_maximo = (Menu::get_valor(AGUA_ALTURA_PUNTOS));
        unsigned int agua_total = Menu::get_valor(AGUA_CAPACIDAD_TOTAL);
        unsigned int agua_techo = Menu::get_valor(AGUA_TECHO_VIRTUAL);
        unsigned int agua_suelo = Menu::get_valor(AGUA_SUELO_VIRTUAL);

        if (agua_techo > agua_total)
        {
            //agua_set_error(AGUA_ERROR_TECHO_MAYOR_TOTAL);
            return FALSE;
        }
        else if (agua_suelo >= agua_total)
        {
            //agua_set_error(AGUA_ERROR_SUELO_MAYOR_TOTAL);
            return FALSE;
        }
        else if (agua_suelo >= agua_techo)
        {
            //agua_set_error(AGUA_ERROR_SUELO_MAYOR_TECHO);
            return FALSE;
        }
        return TRUE;
    }
#endif
