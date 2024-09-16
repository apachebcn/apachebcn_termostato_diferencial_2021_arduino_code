#ifndef Eprom_h
#define Eprom_h
#endif

int Menu_eprom_pos;
int Menu_pos_id;

class Menu_eprom
{
    private:

            static void _load_valor_dir_sonda(byte*);
            static void _save_valor_dir_sonda(byte*);
            static void _EEPROMWriteInt(int);

    public:

        friend class Menu;
        friend class Menu_editor;
        friend class Menu_eventos;

        static void load();
        static void save();
        static unsigned int _EEPROMReadInt();
        static void erase();

};































































