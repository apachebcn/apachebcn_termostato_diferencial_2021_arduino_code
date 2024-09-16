class Menu_dispositivos_disponibles
{

    private:

        static void _imprimir_elemento(byte);
        static void _imprimir_reles_bombas();
        static void _imprimir_info_extendida_evento(byte);

    public:

        static void imprimir(int);


        /*
        *   CONTADORES SINGULARES
        */
        static bool _contar_sonda_colector_id(byte col_id);
        static bool _contar_sonda_zona_id(byte zona_id);
        static bool _contar_bomba_id(byte);
        static bool _contar_agua();
        static bool _contar_calentador();
        static bool _contar_refrigerador(byte);
        static bool _contar_evento(byte evento_id);

        /*
        *   CONTADORES GRUPALES
        */
        static byte _contar_grupo_sondas();
        static byte _contar_grupo_bombas();
        static byte _contar_grupo_eventos();
        static byte _contar_grupo_refrigeradores();
        static byte _contar_grupo_dispositivos_de_entrada();
        static byte _contar_grupo_dispositivos_de_salida();
};
