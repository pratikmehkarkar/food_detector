#include "mbed.h"
#include "TextLCD.h"
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);
Serial pc1(USBTX, USBRX);
TextLCD ark(D8,PA_1,PA_4,PB_0,PC_1,PC_0);
float fruitMax = 0;
float fruitMin = 0;
int choice,i;
int n = 10;
float arr[10];
volatile char fruit_name[8];
AnalogIn ain(A0);//ADC Value

void reset_lcd()
{
    //call this to reset the LCD after 5 seconds
    wait(5);
    led = 0;
    ark.cls();
}
void function_fruit_value()
{
    
    for(i = 0;i<n;i++)
    {
        wait(1);
        float adc_value = ain.read();
        float Vout = adc_value/(adc_value + 10000) * 5.0;
        float final_vout = Vout * 1000;
        arr[i] = final_vout;
    }
    fruitMax = fruitMin = arr[0];
    for(int j = 1; j<10;j++)
    {
        if(fruitMin > arr[j])
            fruitMin = arr[j];
        if(fruitMax < arr[j])
            fruitMax = arr[j];
    }
    pc.printf("\r---------\n");
    pc.printf("\rMax Value is %.2f\n",fruitMax);
    pc.printf("\rMin Value is %.2f\n",fruitMin);
    pc.printf("\rFood Added\n");
    ark.printf("Food Added");
    ark.cls();
}
void function_food_detect()
{
    float adc_value = ain.read();
    float Vout = adc_value/(adc_value + 10000) * 5.0;
    float final_vout = Vout * 1000;
    //pc.printf("\r1-Final Vout is %.2f\n",final_vout);
    
    if(final_vout> 0.26 && final_vout<0.30)
    {
        pc.printf("\rTomato\n");
        ark.locate(0,0);
        ark.printf("Tomato");
        wait(4);
        ark.cls();
    }
    else if(final_vout> 0.42 && final_vout<0.45)
    {
        pc.printf("\rCucumber\n");
        ark.locate(0,0);
        ark.printf("Cucumber");
        wait(4);
        ark.cls();
    }
    else if(final_vout> 0.46 && final_vout<0.49)
    {
        pc.printf("\rLeamon\n");
        ark.locate(0,0);
        ark.printf("Leamon");
        wait(4);
        ark.cls();
    }
    
    else if(fruitMin != 0 && fruitMax != 0)
    {
        if(final_vout > fruitMin)
        {
            pc.printf("\r%s\n",fruit_name);
            ark.locate(0,0);
            ark.printf("%s",fruit_name);
            wait(4);
            ark.cls();
        }
        else if(final_vout < fruitMax)
        {
            pc.printf("\r%s\n",fruit_name);
            ark.locate(0,0);
            ark.printf("%s",fruit_name);
            wait(4);
            ark.cls();
        }
        else if(final_vout == fruitMax)
        {
            pc.printf("\r%s\n",fruit_name);
            ark.locate(0,0);
            ark.printf("%s",fruit_name);
            wait(4);
            ark.cls();
        }
        else
        {
            ark.printf("No Food");
            wait(2);
            ark.cls();
            pc.printf("\rNo New Food Detected\n");
        }
    }
    else
    {
        pc.printf("\rNo Food Detected\n");
    }
}
void function_menu()
{
    pc.printf("\r---MAIN MENU---\n");
    pc.printf("\rPress 1 to get range of Voltage across Food\n");
    pc.printf("\rPress 2 to Detect the food\n");
    pc.printf("\rPress 3 to Exit\n");
}
int main()
{
    reset_lcd();
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
    
    int choice;
    function_menu();
    
    while(true) 
    {
        ark.cls();
        pc.printf("\rEnter the Menu Choice & Press Down Arrow Key:");
        pc.scanf("%d",&choice);
        pc.printf("%d\n",choice);
        pc.printf("\r\n");
        ark.locate(0,0);
        ark.printf("Choice:%d",choice);
        wait(2);
        ark.cls();
        
        if(choice == 1)
       {
            led = 1;
            pc.printf("\r---NEW FOOD DATA ADDING WIZARD---\n");
            pc.printf("\rEnter the short Name of Fruit or Food Item:");
            pc.scanf("%s",fruit_name);
            pc.printf("%s\n",fruit_name);
            
            ark.cls();
            ark.locate(0,0);
            ark.printf("New Food");
            ark.locate(0,1);
            ark.printf("%s",fruit_name);
            wait(3);
            ark.cls();
            
            function_fruit_value();
            ark.cls();
            led = 0;
            pc.printf("\r-------------------------------------\n\n");
            function_menu();
        }
        else if(choice == 2)
        {
            pc.printf("\r---PRE-DEFINED FOOD ITEMS DETECTION WIZARD---\n");
            function_food_detect();
            wait(2);
            pc.printf("\r-------------------------------------\n\n");
            function_menu();
        }
        else
        {
            pc.printf("\rResetting Board.....\n");
            pc.printf("\rThank you for using food detector application!\n");
            pc.printf("\r-------------------------------------------------\n");
            led = 1;
            wait(2);
            void mbed_reset();
            break;
        }
        
    }
}