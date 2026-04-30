#include <reg51.h>
sbit START = P1^0;
sbit RESET = P1^1;
sbit LAP   = P1^2;
unsigned int ms = 0;
unsigned int sec = 0;
unsigned int lap_sec = 0;
bit running = 0;
vod timer0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x66;
    if(running)
    {
        ms++;
        if(ms >= 1000)
        {
            ms = 0;
            sec++;
        }
    }
}
void Timer0_Init()
{
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA  = 1;
    TR0 = 1;
}
void main()
{
    Timer0_Init();
    while(1)
    {
        if(START == 0)
        {
            running = !running;
            while(START == 0);
        }
        if(RESET == 0)
        {
            ms = 0;
            sec = 0;
            while(RESET == 0);
        }

        if(LAP == 0)
        {
            lap_sec = sec;
            while(LAP == 0);
        }
    }
}
