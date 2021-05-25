#include "mbed.h"
#include "TextLCD.h"
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);
TextLCD ark(D8,PA_1,PA_4,PB_0,PC_1,PC_0);

int main()
{
    ark.locate(0,0);
    ark.printf("Hello Pratik");
    ark.locate(0,1);
    ark.printf("**Welcome**");
    wait(5);
    ark.cls();
    
    ark.locate(0,0);
    ark.printf("Smart Food");
    ark.locate(0,1);
    ark.printf("Detection");
    wait(5);
    ark.cls();
    while(true) 
    {
        while(pc.readable())
        {
            char c = pc.getc();
            ark.printf("%c",c);
            led =1;
        }
    }
}