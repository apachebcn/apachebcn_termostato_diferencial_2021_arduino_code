#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

    void Reles::actualiza_pin()
    {
        if (disponible())
        {
            _activar();
        }
        else
        {
            _desactivar();
        }
    }

    void Reles::_activar()
    {
        byte pin_num;
        for(byte shift_num = 0; shift_num < TOTAL_RELES; shift_num++)
        {
            pin_num = reles_get_pin_num(shift_num);
            pinMode(pin_num, OUTPUT);
            digitalWrite(pin_num, REAL_REAL_SIGNAL_OFF);
        }
        set_valores(RELE_FLAG_AUTO_OFF);
        actuar();
    }

    void Reles::_desactivar()
    {
        byte pin_num;
        for(byte shift_num = 0; shift_num < TOTAL_RELES; shift_num++)
        {
            pin_num = reles_get_pin_num(shift_num);
            digitalWrite(pin_num, REAL_REAL_SIGNAL_OFF);
            pinMode(pin_num, 0);
        }
    }

    void Reles::actuar()
    {
        if (!disponible())
        {
            return;
        }
        byte pin_num;
        for(byte rele_id = 0; rele_id < (TOTAL_RELES); rele_id++)
        {
            pin_num = reles_get_pin_num(rele_id);
            switch(Reles_estado[rele_id])
            {
                case RELE_FLAG_AUTO_ON:
                case RELE_FLAG_FORZADO_ON:
                    digitalWrite(pin_num, REAL_REAL_SIGNAL_ON); 
                    break;
                default:
                case RELE_FLAG_AUTO_OFF:
                case RELE_FLAG_FORZADO_OFF:
                    digitalWrite(pin_num, REAL_REAL_SIGNAL_OFF); 
            }
        }
    }

    void Reles::_actuar_testing(byte rele_id, bool rele_estado)
    {
        byte pin_num = reles_get_pin_num(rele_id);
        if (rele_estado == 1)
        {
            digitalWrite(pin_num, REAL_REAL_SIGNAL_ON); 
        }
        if (rele_estado == 0)
        {
            digitalWrite(pin_num, REAL_REAL_SIGNAL_OFF); 
        }
    }

#endif
