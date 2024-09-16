#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560

    void Lcd7::actualiza_pin()
    {
        pinMode(PIN_DIGITAL_LCD7SEG_74HC595_CLOCK, OUTPUT);
        pinMode(PIN_DIGITAL_LCD7SEG_74HC595_LATCH, OUTPUT);
        pinMode(PIN_DIGITAL_LCD7SEG_74HC595_DATA, OUTPUT);
        pinMode(PIN_DIGITAL_LCD7SEG_BRILLO, OUTPUT);
        if (!Menu::get_valor(LCD_7_ON_OFF))
        {
            Lcd7::set_digito_null();
        }
    }

    void Lcd7::demo()
    {
        analogWrite(PIN_DIGITAL_LCD7SEG_BRILLO, 50);
        int delay_demo = 50;
        set_digito(000); FC::delayMilisegundos(delay_demo);
        set_digito(1.11); FC::delayMilisegundos(delay_demo);
        set_digito(22.2); FC::delayMilisegundos(delay_demo);
        set_digito(3.33); FC::delayMilisegundos(delay_demo);
        set_digito(44.4); FC::delayMilisegundos(delay_demo);
        set_digito(6.66); FC::delayMilisegundos(delay_demo);
        set_digito(77.7); FC::delayMilisegundos(delay_demo);
        set_digito(8.88); FC::delayMilisegundos(delay_demo);
        set_digito(99.9); FC::delayMilisegundos(delay_demo);
        set_digito(000); 
    }

    void Lcd7::test()
    {
        analogWrite(PIN_DIGITAL_LCD7SEG_BRILLO, 50);
        int delay_demo = 400;
        set_digito(000); FC::delayMilisegundos(delay_demo);
        set_digito(1.11); FC::delayMilisegundos(delay_demo);
        set_digito(22.2); FC::delayMilisegundos(delay_demo);
        set_digito(3.33); FC::delayMilisegundos(delay_demo);
        set_digito(44.4); FC::delayMilisegundos(delay_demo);
        set_digito(6.66); FC::delayMilisegundos(delay_demo);
        set_digito(77.7); FC::delayMilisegundos(delay_demo);
        set_digito(8.88); FC::delayMilisegundos(delay_demo);
        set_digito(99.9); FC::delayMilisegundos(delay_demo);
    }

    byte Lcd7::brillo_get_value(byte percent)
    {
        byte n = map(percent, 0, 10, 
                    255, //tension minima
                    20); //tension maxima
        return n;
    }

    void Lcd7::refresca_pantallas()
    {
        byte num_digito = 0;
        byte Digitos[3];
        bool tiene_punto = 0;
        int brillo = brillo_get_value(Menu::get_valor(LCD_7_BRILLO));
        analogWrite(PIN_DIGITAL_LCD7SEG_BRILLO, brillo);

        for(byte columna = 0; columna < 3; columna++)
        {
            if (Lcd7_digito[(num_digito+1)] == '.') tiene_punto = 1; 
            if (Lcd7_digito[num_digito] == '.') 
            {
                num_digito++; 
                columna--;
                continue;
            }

            byte vcc_digito = get_lcd_char(Lcd7_digito[num_digito]);

            if (tiene_punto) // && columna < 3) 
            {
                vcc_digito += LCD7_SEGMENTO_PUNTO;
                tiene_punto = 0; 
            }
            Digitos[columna] = vcc_digito;
            num_digito++; 
        }

        digitalWrite(PIN_DIGITAL_LCD7SEG_74HC595_LATCH, 0);
        shiftOut(PIN_DIGITAL_LCD7SEG_74HC595_DATA, PIN_DIGITAL_LCD7SEG_74HC595_CLOCK, MSBFIRST, Digitos[2]);
        shiftOut(PIN_DIGITAL_LCD7SEG_74HC595_DATA, PIN_DIGITAL_LCD7SEG_74HC595_CLOCK, MSBFIRST, Digitos[1]);
        shiftOut(PIN_DIGITAL_LCD7SEG_74HC595_DATA, PIN_DIGITAL_LCD7SEG_74HC595_CLOCK, MSBFIRST, Digitos[0]);
        digitalWrite(PIN_DIGITAL_LCD7SEG_74HC595_LATCH, 1);  
    }

    void Lcd7::set_digito_null()
    {
        for(byte bucle = 0; bucle < 3; bucle++) 
        {
            Lcd7_digito[bucle] = 'X';
        }
        refresca_pantallas();
    }

    void Lcd7::set_digito_desactivado()
    {
        for(byte bucle = 0; bucle < 3; bucle++) 
        {
            Lcd7_digito[bucle] = '-';
        }
        refresca_pantallas();
    }

    void Lcd7::set_digito_error()
    {
        for(byte bucle = 0; bucle < 3; bucle++) 
        {
            Lcd7_digito[bucle] = 'E';
        }
        refresca_pantallas();
    }

    void Lcd7::set_digito(float new_digito)
    {
        byte char_len = 3;
        byte bucle;
        if (new_digito > 199)
        {
            for(bucle = 0; bucle < char_len; bucle++)
            {
                Lcd7_digito[bucle] = 'H';
            }
            Lcd7_digito[bucle] = 0;
            return;
        }

        if (new_digito < -99)
        {
            for(bucle = 0; bucle < char_len; bucle++)
            {
                Lcd7_digito[bucle] = 'L';
            }
            Lcd7_digito[bucle] = 0;
            return;
        }

        char charray[10];
        dtostrf(new_digito, 3, 2, charray);

        for(bucle = 0; bucle < char_len; bucle++)
        {
            Lcd7_digito[bucle] = charray[bucle];
            if (charray[bucle] == '.') char_len++;
        }

        Lcd7_digito[bucle] = 0;
        refresca_pantallas();
    } 

    byte Lcd7::get_lcd_char(char digito)
    {
        switch(digito)
        {
            case 'A': 
                return LCD7_DIGITO_A;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': 
                return pantalla_bits_vcc_array_nums[digito-48];
            case '-':
                return LCD7_DIGITO_MENOS;
            case '.': 
                return 0;
            case 'X':
                return LCD7_DIGITO_NULL;
            case 'L':
                return LCD7_DIGITO_DECESO;
            case 'H':
                return LCD7_DIGITO_EXCESO;
            case 'E':
                return LCD7_DIGITO_ERROR;        
        }
        return LCD7_DIGITO_NULL;
    }
#endif
