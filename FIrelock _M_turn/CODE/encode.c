#include "FIRELOCK.h"




void encode(void)
{
            lf=-encoder4_speed_spi(ABS_ENCODER_SPI_PC4_PIN);
            lb=-encoder3_speed_spi(ABS_ENCODER_SPI_PC3_PIN);
            rf=encoder1_speed_spi(ABS_ENCODER_SPI_PC1_PIN);
            rb=encoder2_speed_spi(ABS_ENCODER_SPI_PC2_PIN);


}

void encode_calculation(void)
{
    RB = (int16)((rb)*50*1.0/WHEEL_PULSE*WHEEL_C/7);    //cm/s
    RF = (int16)((rf)*50*1.0/WHEEL_PULSE*WHEEL_C/7);    //cm/s
    LF = (int16)((lf)*50*1.0/WHEEL_PULSE*WHEEL_C/7);    //cm/s
    LB = (int16)((lb)*50*1.0/WHEEL_PULSE*WHEEL_C/7);    //cm/s

}

