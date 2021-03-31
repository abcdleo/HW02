#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

DigitalIn up(D10);
DigitalIn down(D9);
DigitalIn confirm(D8);

AnalogIn Ain(D12);
AnalogOut Aout(D7);

float ADCdata[100];

int main()
{  
    int freq_bar = 0;
    float wait = 0;
    int count = 0;
    bool wave_start = false;
    bool a=true;
    // uLCD.locate(8, 5);
    // uLCD.printf("%2d",freq_bar);
    uLCD.line(13, 100, 13 + freq_bar, 100, RED);
    uLCD.line(13 + freq_bar, 100, 113, 100, WHITE);
    uLCD.locate(0, 7);
    uLCD.printf("select frequency:\n   %f Hz\n", 3 * freq_bar + 393.7 - 250);

    while (1)
    {
        if(up || down || confirm)
        {
            wait = (1000 / (393.737 + 3 * freq_bar - 250) - 2.2) * 10;
            if (up && freq_bar < 100)
            {  
                if (wave_start)
                {
                    wave_start = false;
                    uLCD.cls();
                }
                freq_bar += 10;
            }
            else if (down && freq_bar > 0)
            {
                if (freq_bar == 100)
                    uLCD.cls();
                if (wave_start)
                {
                    wave_start = false;
                    uLCD.cls();
                }
                freq_bar -= 10;
            }
            else if (confirm)
            { 
                a = true;
                uLCD.locate(1, 2);
                uLCD.text_width(2); //4X size text
                uLCD.text_height(3);
                uLCD.color(RED);
                uLCD.printf("CONFIRM!");
                
                uLCD.text_width(1); //4X size text
                uLCD.text_height(1);
                uLCD.color(GREEN);
                uLCD.locate(0, 10);
                wave_start = true;
                uLCD.printf("wait : %2f us\n", wait);
                uLCD.printf("period = %2f ms\n", 1000 / (3 * freq_bar + 393.7 - 250));
            }
            // uLCD.locate(8, 5);
            // uLCD.printf("%2d",freq_bar);
            uLCD.line(13, 100, 13 + freq_bar, 100, RED);
            uLCD.line(13 + freq_bar, 100, 113, 100, WHITE);
            uLCD.locate(0, 7);
            uLCD.printf("select frequency:\n   %f Hz\n", 3 * freq_bar + 393.7 - 250);
        }
        else if(wave_start)
        {
            // triangle output S = 1
            // period without waiting = 2.320 ms
            //cutoff freq. = 1 / (2 * pi * (4700 + 3900) * 0.047 * 10^-6) = 393.75 Hz
            //period = 2.54 ms
            if (count == 100)
                count = 0;
            else if (count <=10)
                Aout = count/10.0f/1.1;
            else 
                Aout = (100-count)/90.0f/1.1;
            ADCdata[count++] = Ain;
            wait_us(wait);
        }

        if (count == 100 && a)
        {
            a= false;
            float freq = freq_bar + 393.7 - 50;
            printf ("%f\r\n", freq);
            for (int j = 0; j < 1; j++){
                for (int i = 0; i < 100; i++)
                {
                    printf("%f\r\n", ADCdata[i]);
                }
            }
        }
    }
}