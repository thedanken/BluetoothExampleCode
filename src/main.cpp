#include "mbed.h"
 
Serial pc(USBTX, USBRX);
 
#if   defined(TARGET_LPC1768)
Serial blue(p9, p10);          		// TX, RX
//Serial blue(p13, p14);         	// TX, RX
#elif defined(TARGET_LPC4330_M4)
Serial blue(P6_4, P6_5);         	// UART0_TX, UART0_RX
//Serial blue(P2_3, P2_4);         	// UART3_TX, UART3_RX
#endif
 
DigitalOut myled(LED1);
DigitalOut myled4(LED4);
 
int main() 
{
    blue.baud(115200);
    pc.baud(115200);
    pc.printf("Bluetooth Start\r\n");
    
    // echo back characters and toggle the LED
    while (1) 
    {
        if (blue.readable()) 
        {
            pc.putc(blue.getc());
            myled = !myled;
        }
        if (pc.readable()) 
        {
            blue.putc(pc.getc());
            myled4 = !myled4;
        }
    }
}