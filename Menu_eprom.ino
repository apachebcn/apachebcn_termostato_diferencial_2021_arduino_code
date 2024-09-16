#include <EEPROM.h>

void Menu_eprom::load()
{
    if (EEPROM.read(0) != 76)
    {
        return;
    }

    Menu_eprom_pos = 1;
    for(Menu_pos_id = 1; Menu_pos_id < (MENU_ELEMENTOS_TOTAL+1); Menu_pos_id++)
    {
        switch(Menu::elemento_type(Menu_pos_id))
        {
            case MENU_TYPE_GROUP:
                break;
            case MENU_TYPE_FUNCTION:
                break;
            case MENU_TYPE_SONDA_SELECTOR:
                switch(Menu_pos_id)
                {
                    case SONDA_COLECTOR_1_DIR:   
                        _load_valor_dir_sonda(Sondas_colector_dir[0]);  
                        break;
                    case SONDA_DEPOSITO_DIR:     
                        _load_valor_dir_sonda(Sondas_deposito_dir);  
                        break;
                    case SONDA_ZTERMOSTATO_DIR:    
                        _load_valor_dir_sonda(Sondas_ztermostato_dir);  
                        break;
                    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                        case LCD_7_DIR:         
                            _load_valor_dir_sonda(Sondas_lcd7_dir);    
                            break;
                        case SONDA_COLECTOR_2_DIR:   
                            _load_valor_dir_sonda(Sondas_colector_dir[1]);  
                            break;
                        case SONDA_COLECTOR_3_DIR:   
                            _load_valor_dir_sonda(Sondas_colector_dir[2]);  
                            break;
                        case SONDA_ZONA_1_DIR:
                            _load_valor_dir_sonda(Sondas_zona_dir[0]);  
                            break;
                        case SONDA_ZONA_2_DIR:
                            _load_valor_dir_sonda(Sondas_zona_dir[1]);  
                            break;
                        case SONDA_ZONA_3_DIR:
                            _load_valor_dir_sonda(Sondas_zona_dir[2]);  
                            break;
                    #endif
                    default: break;
                }
                break;
            default:
                int valor = _EEPROMReadInt();
                Menu::set_valor(Menu_pos_id, valor);
        }
    }
}

void Menu_eprom::save()
{
    Menu_eprom_pos = 1;
    for(Menu_pos_id = 1; Menu_pos_id < (MENU_ELEMENTOS_TOTAL+1); Menu_pos_id++)
    {
        switch(Menu::elemento_type(Menu_pos_id))
        {
            case MENU_TYPE_GROUP:
                break;
            case MENU_TYPE_FUNCTION:
                break;
            case MENU_TYPE_SONDA_SELECTOR:
                switch(Menu_pos_id)
                {
                    case SONDA_COLECTOR_1_DIR:   
                        _save_valor_dir_sonda(Sondas_colector_dir[0]);  
                        break;
                    case SONDA_DEPOSITO_DIR:
                        _save_valor_dir_sonda(Sondas_deposito_dir);  
                        break;
                    case SONDA_ZTERMOSTATO_DIR:    
                        _save_valor_dir_sonda(Sondas_ztermostato_dir);  
                        break;
                    #ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
                        case LCD_7_DIR:         
                            _save_valor_dir_sonda(Sondas_lcd7_dir);    
                            break;
                        case SONDA_COLECTOR_2_DIR:   
                            _save_valor_dir_sonda(Sondas_colector_dir[1]);  
                            break;
                        case SONDA_COLECTOR_3_DIR:   
                            _save_valor_dir_sonda(Sondas_colector_dir[2]);  
                            break;
                        case SONDA_ZONA_1_DIR:
                            _save_valor_dir_sonda(Sondas_zona_dir[0]);  
                            break;
                        case SONDA_ZONA_2_DIR:
                            _save_valor_dir_sonda(Sondas_zona_dir[1]);  
                            break;
                        case SONDA_ZONA_3_DIR:
                            _save_valor_dir_sonda(Sondas_zona_dir[2]);  
                            break;
                    #endif
                    default: break;
                }
                break;

            default:
                _EEPROMWriteInt(Menu::get_valor(Menu_pos_id));
        }
    }
    EEPROM.write(0, 76);
}

void Menu_eprom::_load_valor_dir_sonda(byte* addr)
{
    byte valor;
    for(byte bit = 0; bit < 8; bit++)
    {
        valor = (byte)EEPROM.read(Menu_eprom_pos++);
        addr[bit] = valor;
    }
}

void Menu_eprom::_save_valor_dir_sonda(byte* addr)
{
    byte valor;
    for(byte bit = 0; bit < 8; bit++)
    {
        valor = addr[bit];
        EEPROM.write(Menu_eprom_pos++, (byte)valor);
    }
}

//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void Menu_eprom::_EEPROMWriteInt(int p_valor)
{
    byte lowByte = ((p_valor >> 0) & 0xFF);
    byte highByte = ((p_valor >> 8) & 0xFF);
    EEPROM.write(Menu_eprom_pos, lowByte); Menu_eprom_pos++;
    EEPROM.write(Menu_eprom_pos, highByte); Menu_eprom_pos++;
}

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int Menu_eprom::_EEPROMReadInt()
{
    byte lowByte = EEPROM.read(Menu_eprom_pos); Menu_eprom_pos++;
    byte highByte = EEPROM.read(Menu_eprom_pos); Menu_eprom_pos++;
    return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void Menu_eprom::erase()
{ 
    EEPROM.write(0, 0);
}
