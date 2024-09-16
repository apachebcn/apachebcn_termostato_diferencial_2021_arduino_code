/*
#ifdef IS_COMPILER_FOR_ARDUINO_MEGA_2560
    bool Refrigerador_actuando[TOTAL_SONDAS_COLECTORES];
#endif

#ifdef IS_COMPILER_FOR_ARDUINO_PRO_MINI
    bool Refrigerador_actuando[1];
#endif
*/

class Refrigerador
{
    public:

        static void actualizar(int);
};

