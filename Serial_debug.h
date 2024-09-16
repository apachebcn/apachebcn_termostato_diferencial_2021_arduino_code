#define head_serial_start F("|MSC_0_")
#define head_serial_end F("|MSC_1_")


unsigned long Serial_debug_estado_baudio;

class Serial_debug
{
    public:

        static unsigned long get_valor_baudio(int);
        static void inicia_pin();
        static void forzar_on();

        static void write(char);
        static void println();
        static void print(float);
        static void println(float);
        static void print(int);
        static void println(int);
        static void print(char);
        static void println(char);
        static void print(char*);
        static void println(char*);
        static void print(const __FlashStringHelper*);
        static void println(const __FlashStringHelper*);
        static void print(byte&, int);
        static void println(byte&, int);
        static void serial_saludo();

};



