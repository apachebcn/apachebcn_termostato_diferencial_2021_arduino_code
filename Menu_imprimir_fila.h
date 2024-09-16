class Menu_imprimir_fila
{

    private:

        static void _imprime_derecha_int_con_prefijo(int, char, byte);
        static void _imprime_derecha_int_con_sufijo(int, char, byte);
        static void _imprime_derecha_int_con_sufijo(int, const __FlashStringHelper*, byte);
        static void _imprime_derecha_prefijo_y_dir(int, char, byte);
        static void _imprime_derecha(int, byte);
        static void _imprime_derecha(char*, byte);
        static void _imprime_derecha(char, byte);
        static void _imprime_derecha(const __FlashStringHelper*, byte);

    public:

        static void etiqueta(int);
        static void post_etiqueta(int);

        static void valor(int, int, byte);

        static void imprimir(int, byte);
        static byte print_sufijo(int, byte);
        static void configuracion_reles();

};
