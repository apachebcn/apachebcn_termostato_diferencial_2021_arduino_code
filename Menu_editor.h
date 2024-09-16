bool Menu_editando = 0;

class Menu_editor
{
    static void inicia_modo_edicion();
    static void tecla_atras();

    public:
    
        friend class Menu;
        friend class Menu_eventos;
        friend class Menu_eprom;

    static void finaliza_modo_edicion();
    static void tecla_arriba();
    static void tecla_abajo();
    static void print_valor_editable();
    static void tecla(byte);
    static void print_sonda();
};