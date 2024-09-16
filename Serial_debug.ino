#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    void Serial_debug::inicia_pin() {}
    void Serial_debug:: forzar_on() {}
    void Serial_debug:: write(char) {}
    void Serial_debug:: println() {}
    void Serial_debug:: print(float) {}
    void Serial_debug:: println(float) {}
    void Serial_debug:: print(int) {}
    void Serial_debug:: println(int) {}
    void Serial_debug:: print(char) {}
    void Serial_debug:: println(char) {}
    void Serial_debug:: print(char*) {}
    void Serial_debug:: println(char*) {}
    void Serial_debug:: print(const __FlashStringHelper*) {}
    void Serial_debug:: println(const __FlashStringHelper*) {}
    void Serial_debug:: print(byte&, int) {}
    void Serial_debug:: println(byte&, int) {}
    void Serial_debug:: serial_saludo() {}
#endif


#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

    void Serial_debug::forzar_on()
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        Serial.begin(1000000);
        Serial_debug_estado_baudio = 1000000;
        Serial.println(F("Serial forzado a 1Mbauds"));
    }

    unsigned long Serial_debug::get_valor_baudio(int menu_valor)
    {
        switch(menu_valor)
        {
            case 0: return 2400;
            case 1: return 4800;
            case 2: return 9600;
            case 3: return 14400;
            case 4: return 19200;
            case 5: return 28800;
            case 6: return 38400;
            case 7: return 57600;
            case 8: return 76800;
            case 9: return 115200;
            case 10: return 250000;
            case 11: return 500000;
            case 12: return 1000000;
            case 13: return 2000000;
            default: return 500000;
        }
    }

    void Serial_debug::inicia_pin()
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif

        if (!Menu::get_valor(SERIAL_DEBUG_ON_OFF))
        {
            Serial_debug_estado_baudio = 0;
            return;
        }

        unsigned long baud;

        #ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
            baud = 57600;
        #endif

        baud = get_valor_baudio(Menu::get_valor(SERIAL_DEBUG_BAUD));
        Serial.begin(baud);
        Serial_debug_estado_baudio = baud;
        serial_saludo();
    }

    void Serial_debug::write(char valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.print(valor);
        }
    }

    void Serial_debug::println()
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.println();
        }
    }

    void Serial_debug::print(float valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.print(valor);
        }
    }

    void Serial_debug::println(float valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.println(valor);
        }
    }

    void Serial_debug::print(int valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.print(valor);
        }
    }

    void Serial_debug::println(int valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.println(valor);
        }
    }

    void Serial_debug::print(char valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.print(valor);
        }
    }

    void Serial_debug::println(char valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.println(valor);
        }
    }

    void Serial_debug::print(char* valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.print(valor);
        }
    }

    void Serial_debug::println(char* valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.println(valor);
        }
    }

    void Serial_debug::print(const __FlashStringHelper* valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.print(valor);
        }
    }

    void Serial_debug::println(const __FlashStringHelper* valor)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.println(valor);
        }
    }

    void Serial_debug::print(byte& valor, int mode)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.print(valor, mode);
        }
    }

    void Serial_debug::println(byte& valor, int mode)
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        if (Serial_debug_estado_baudio)
        {
            Serial.println(valor, mode);
        }
    }

    void Serial_debug::serial_saludo()
    {
        #ifndef ABLE_SERIAL_DEBUG
            return;
        #endif
        Serial_debug::println(F("-INIT-"));
        Serial_debug::println(F("-misolarcasero.com-"));
        Serial_debug::println(F("apachebcn@gmail.com"));
        Serial_debug::println(F("PEDRO REINA ROJAS"));
        Serial_debug::println();

        Serial_debug::print(F("TERMOSTATO DIFERENCIAL"));
        Serial_debug::write(' ');
        Serial_debug::print(VERSION);
        Serial_debug::print(F(" parche "));
        Serial_debug::println(PARCHE);
        Serial_debug::println();
    }

#endif
