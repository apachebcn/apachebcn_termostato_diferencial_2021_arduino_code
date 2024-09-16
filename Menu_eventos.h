class Menu_eventos
{

    public:
    
        friend class Menu;
        friend class Menu_editor;
        friend class Menu_eprom;

        static void tecla(byte);
        static void al_editar_valor();
        static void al_modificar_valor();
        static void al_validar_valor();
        static void validar_sonda();
};
