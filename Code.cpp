#include "mbed.h"
#include "C12832.h"
C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);
DigitalOut led(LED1);
DigitalIn sw_slow(p12);
DigitalIn sw_fast(p13);
int main() {
    int     second, minute, hour, state;
    char    strTime[8];
    printf("Assignment: Digital Clock with Settable Time\n");
    printf("61107959 Wathinee saeaui\n");
    state = 0;
    second = 0;
    minute = 0;
    hour = 10;
    while (1) {
        if (state++ >= 1) {
            state = 0;
            if (second++ >= 59) {
                second = 0;
                if (minute++ >= 59) {
                    minute = 0;
                    if (hour++ >= 23) {
                        hour = 0;
                    }
                }
            }
        }
        lcd.cls();
        if (state == 0)
            sprintf(strTime, "%02d:%02d:%02d\n", hour, minute, second);
        else
            sprintf(strTime, "%02d %02d %02d\n", hour, minute, second);
//        int swState = sw_slow + (sw_fast << 1);
        printf("Colon state: %d", state);
        lcd.locate(0, 0);
        lcd.printf(strTime);
        lcd.copy_to_lcd();
        led = !led;
        if (sw_slow == 1) {
            wait_ms(50);
            printf("Slow setting");
        } else if (sw_fast == 1) {
            wait_ms(1);
            printf("Fast setting");
        } else
            wait_ms(500);
    }
  }
