bool Sondas::_activado()
{
    return (bool)Menu::get_valor(SONDAS_ON_OFF);
}

void Sondas::_print_resolution(byte resolution_num)
{
    Serial_debug::print(F("Resolucion actual: ")); 
    Serial_debug::print(resolution_num); Serial_debug::write(' '); 
    Serial_debug::print(F("bits")); Serial_debug::write(';'); Serial_debug::write(' '); 
}

void Sondas::_print_chip(const __FlashStringHelper* chip_name)
{
    Serial_debug::print(F("Chip")); Serial_debug::write(' '); 
    Serial_debug::print(chip_name); Serial_debug::write(';'); Serial_debug::write(' '); 
}

int Sondas::_lee_temp(byte* dir, bool usa_debug)
{

    if (!_activado()) 
    {
        return 0;
    }

    byte type_s;
    byte data[12];

    if (OneWire::crc8(dir, 7) != dir[7]) 
    {
        if (usa_debug && FC::is_debug(DEBUG_SONDAS)) Serial_debug::print(F("No se puede calcular la temperatura (CRC Error)"));
        return VALOR_RESET_O_ERROR;
    }

    switch(dir[0]) 
    {
        case 0x10:
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_chip(F("DS18S20 or old DS1820"));
            type_s = 1;
            break;
        case 0x28:
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_chip(F("DS18B20"));
            type_s = 0;
            break;
        case 0x22:
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_chip(F("DS1822"));
            type_s = 0;
            break;
        default:
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) Serial_debug::print(F("ERROR: Device is not a DS18x20 or not address"));
            return VALOR_RESET_O_ERROR;
    } 

    dallas_sondas_wires.reset();
    dallas_sondas_wires.select(dir);
    dallas_sondas_wires.write(0x44, 1);
    byte present = dallas_sondas_wires.reset();
    dallas_sondas_wires.select(dir);    
    dallas_sondas_wires.write(0xBE);         // Read Scratchpad

    for ( byte i = 0; i < 9; i++) 
    {
        // we need 9 bytes
        data[i] = dallas_sondas_wires.read();
        //Serial.print(data[i], HEX); Serial.print(" ");
    }
    //Serial.print(" CRC=");
    //Serial.print( OneWire::crc8( data, 8), HEX);
    //Serial.println();

    if (data[0] == 255) 
    {
        #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) Serial_debug::print(F("ERROR data-0"));
        #endif
        return VALOR_RESET_O_ERROR;
    }

    // Convert the data to actual temperature
    // because the estado is a 16 bit signed integer, it should
    // be stored to an "int16_t" type, which is always 16 bits
    // even when compiled on a 32 bit processor.
    int16_t raw = (data[1] << 8) | data[0];

    if (type_s) 
    {
        raw = raw << 3; // 9 bit resolution default
        if (data[7] == 0x10) 
        {
            // "count remain" gives full 12 bit resolution
            raw = (raw & 0xFFF0) + 12 - data[6];
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_resolution(12);
        }
        else
        {
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_resolution(9);
        }
    } 
    if (!type_s) 
    {
        byte cfg = (data[4] & 0x60);
        // at lower res, the low bits are undefined, so let's zero them
        if (cfg == 0x00) 
        {
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_resolution(9);
            raw = raw & ~7;  // 9 bit resolution, 93.75 ms
        }
        else if (cfg == 0x20) 
        {
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_resolution(10);
            raw = raw & ~3; // 10 bit res, 187.5 ms
        }
        else if (cfg == 0x40) 
        {
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_resolution(11);
            raw = raw & ~1; // 11 bit res, 375 ms
        }
        else
        {
            if (usa_debug && FC::is_debug(DEBUG_SONDAS)) _print_resolution(12);
            //// default is 12 bit resolution, 750 ms conversion time
        }
    }

    if (raw == 1360) 
    {
        if (usa_debug && FC::is_debug(DEBUG_SONDAS)) Serial_debug::print(F("ERROR 1360"));
        return VALOR_RESET_O_ERROR;
    }

    if (usa_debug && FC::is_debug(DEBUG_SONDAS))
    {
        Serial_debug::print(F("Temp"));
        Serial_debug::write(':');
        Serial_debug::print(Sondas::convert_temp(raw));
    }

    return raw;
}

void Sondas::_WriteScratchPad(byte* dir)
{
    byte reg_cmd;
    switch(SONDAS_RESOLUCION)
    {
        case 9: reg_cmd = 0x1F; break;
        case 10: reg_cmd = 0x3F; break;
        case 11: reg_cmd = 0x5F; break;
        case 12: reg_cmd = 0x7F; break;
        default: reg_cmd = 0x7F; break;
    }

    dallas_sondas_wires.reset();
    dallas_sondas_wires.select(dir);
    dallas_sondas_wires.write(0x4E);     // Write scratchpad command
    dallas_sondas_wires.write(0);        // TL data
    dallas_sondas_wires.write(0);        // TH data
    dallas_sondas_wires.write(reg_cmd);  // Configuration Register (resolution) 7F=12bits 5F=11bits 3F=10bits 1F=9bits
    dallas_sondas_wires.reset();         // This "reset" sequence is mandatory
    dallas_sondas_wires.select(dir);    // it allows the DS18B20 to understand the copy scratchpad to EEPROM command
    dallas_sondas_wires.write(0x48);     // Copy Scratchpad command
}

