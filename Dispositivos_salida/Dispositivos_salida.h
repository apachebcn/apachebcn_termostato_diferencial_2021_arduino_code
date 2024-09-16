class Dispositivos_salida
{

    private:

        static bool _calcula_activado(int dispositivo_id);
        static bool _calcula_disponible(int dispositivo_id);
        static bool _calcula_reles_disponibles(int dispositivo_id);
        static void _actualizar_estados();
        static void _actualizar_dependencias();
        static void _actualizar_dispositivos();

    public:

        static void actualizar();

};