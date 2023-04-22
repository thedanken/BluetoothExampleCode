#include "mbed.h"
#include "string.h"

#define UART_RX PD_2
#define UART_TX PC_12
BufferedSerial pc(UART_TX, UART_RX, 9600);

const int MAXBUFFSIZE = 32;
#define UART5_TX PC_12
#define UART5_RX PD_2

BufferedSerial blue(UART5_TX, UART5_RX, 9600);
 
DigitalOut LedGreen(LED1);
DigitalOut LedBlue(LED2);
char buf[MAXBUFFSIZE] = {' '};

void clearbuffer(void);

int main() 
{
  blue.set_format(
    8,
    BufferedSerial::None,
    1
  );
  pc.set_format(
    8,
    BufferedSerial::None,
     1
  );
  blue.set_blocking(false);
  printf("Bluetooth Start\r\n");

  string s;
    // echo back characters and toggle the LED
    while (1) 
    {
      char buf[MAXBUFFSIZE] = {0};  
        if (blue.readable()) 
        {
          blue.read(buf, sizeof(buf));
          printf(buf);
          if(buf[0] == 'h')
          {
            LedGreen = !LedGreen;
          }
          else
          {
            LedBlue = !LedBlue;
          }
        }
        if (pc.readable()) 
        {
          pc.read(buf, sizeof(buf));
          blue.write(buf, sizeof(buf));
          
        }
        blue.write("testing\n", sizeof("testing\n")-1);
        osDelay(1000);
    }
}
void clearbuffer()
{
  for(int i = 0; i< MAXBUFFSIZE; i++)
  {
    buf[i] = (char)0;
  }
}