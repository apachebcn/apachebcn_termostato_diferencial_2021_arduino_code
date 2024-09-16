#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI

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
        pinMode(PIN_ANALOG_RELES_74HC595_CLOCK, OUTPUT);
        pinMode(PIN_ANALOG_RELES_74HC595_LATCH, OUTPUT);
        pinMode(PIN_ANALOG_RELES_74HC595_DATA, OUTPUT);
        set_valores(RELE_FLAG_AUTO_OFF);
        actuar();
    }

    void Reles::_desactivar()
    {
        pinMode(PIN_ANALOG_RELES_74HC595_CLOCK, 0);
        pinMode(PIN_ANALOG_RELES_74HC595_LATCH, 0);
        pinMode(PIN_ANALOG_RELES_74HC595_DATA, 0);
    }

    byte Reles::GetBitArrayAsByte(byte* mask_shift_bits)
    {
        byte valor = 0;
        byte bit;
        byte chip_bit;

        for (bit = 1; bit < 9; bit++)
        {
            switch(bit)
            {
                case 1: chip_bit = 7; break;
                case 2: chip_bit = 6; break;
                case 3: chip_bit = 5; break;
                case 4: chip_bit = 4; break;
                case 5: chip_bit = 3; break;
                case 6: chip_bit = 2; break;
                case 7: chip_bit = 1; break;
                case 8: chip_bit = 0; break;
            }

            valor <<= 1;
            bool real_value = REAL_REAL_SIGNAL_OFF;
            switch(mask_shift_bits[chip_bit])
            {
              case RELE_FLAG_AUTO_ON:
              case RELE_FLAG_FORZADO_ON:
                  real_value = REAL_REAL_SIGNAL_ON;
            }
            valor |= real_value;
        }
        return valor;
    }

    void Reles::actuar()
    {
        if (!disponible())
        {
            return;
        }

        byte bits_shift_reles = GetBitArrayAsByte(Reles_estado);
        digitalWrite(PIN_ANALOG_RELES_74HC595_LATCH, 0);
        shiftOut(PIN_ANALOG_RELES_74HC595_DATA, PIN_ANALOG_RELES_74HC595_CLOCK, MSBFIRST, bits_shift_reles);
        digitalWrite(PIN_ANALOG_RELES_74HC595_LATCH, 1);    
    }

    void Reles::_actuar_testing(byte rele_id, bool rele_estado)
    {
        Reles_estado[rele_id] = rele_estado;
        byte bits_shift_reles = GetBitArrayAsByte(Reles_estado);
        digitalWrite(PIN_ANALOG_RELES_74HC595_LATCH, 0);
        shiftOut(PIN_ANALOG_RELES_74HC595_DATA, PIN_ANALOG_RELES_74HC595_CLOCK, MSBFIRST, bits_shift_reles);
        digitalWrite(PIN_ANALOG_RELES_74HC595_LATCH, 1);    
    }

#endif

