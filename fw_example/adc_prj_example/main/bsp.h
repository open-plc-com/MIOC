#ifndef BSP_DEF
#define BSP_DEF
/* ======================================================================== */
/* Board Support Package File                                               */
/* ======================================================================== */

/*
                            Var
                            type
                            ----
    bool                    1
    int8                    2
    unsigned int8           3
    int16                   4
    unsigned int16          5
    int32                   6
    unsigned int32          7
    int64                   8
    unsigned int64          9       GPIO
    float                   10      type
    double                  11      ----
    GPIO_Mode_AIN           5       1       ( uint16_t )
    GPIO_Mode_IN_FLOATING   1       2       ( bool     )
    GPIO_Mode_IPD           1       3       ( bool     )
    GPIO_Mode_IPU           1       4       ( bool     )
    GPIO_Mode_Out_OD        1       5       ( bool     )
    GPIO_Mode_Out_PP        1       6       ( bool     )
    DS18B20                 11      7       ( double   )
    iButton                 9       8       ( int64_t  )
*/

#define SN_FW 1299532780
#define UART1_SPEED 9600
#define LCD_1602    // Use LCD 1602
#define PCF8574     // I2C chip of LCD_1602
#define VAR_NN 2

struct Var_Struct
{
    unsigned int  *name_ptr;
    uint16_t       var_type;      // Variable type:
    uint16_t       gpio_type;     // GPIO type
    GPIO_TypeDef  *gpio;          // GPIO Port
    uint16_t       gpio_pin;      // GPIO Pin
    uint16_t       sync;          // Sync (R/W)
    uint16_t       err_1w;        // 1-Wire continuous error count
    uint16_t       ibutton_time;  // The rest of the time for remember the value iButton
} Var[VAR_NN];

uint16_t  adc1;
double    ds;

void init_bsp( void )
{
    int i;

    for( i = 0; i < VAR_NN; i++ )
    {
        Var[i].name_ptr     = 0;
        Var[i].var_type     = 0;
        Var[i].gpio_type    = 0;
        Var[i].gpio         = 0;
        Var[i].gpio_pin     = 0;
        Var[i].sync         = 0;
        Var[i].err_1w       = 0;
        Var[i].ibutton_time = 0;
    }

    Var[0].name_ptr=(unsigned int*)&adc1; Var[0].var_type=5; Var[0].gpio_type=1; Var[0].gpio=GPIOA; Var[0].gpio_pin=GPIO_Pin_0;
    Var[1].name_ptr=(unsigned int*)&ds; Var[1].var_type=11; Var[1].gpio_type=7; Var[1].gpio=GPIOA; Var[1].gpio_pin=GPIO_Pin_1;
}

#endif // BSP_DEF
/* ======================================================================== */
