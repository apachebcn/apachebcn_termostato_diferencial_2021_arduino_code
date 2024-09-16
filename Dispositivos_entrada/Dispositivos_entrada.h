
class Dispositivos_entrada
{

    private:

        static bool _calcula_activado(int dispositivo_id);
        static bool _calcula_sensores_disponibles(int dispositivo_id);
        static float _leer_sonda_valor(byte* sonda_addr);
        static void _prevenir_sondas();
        static void _actualizar_estados();
        static void _actualizar_dependencias();
        static void _actualizar_dispositivos();


    public:

        static void actualizar();

};