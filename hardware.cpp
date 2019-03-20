// This header has all the (extern) declarations of the globals.
// "extern" means "this is instantiated somewhere, but here's what the name
// means.
#include "globals.h"
#include "hardware.h"

// We need to actually instantiate all of the globals (i.e. declare them once
// without the extern keyword). That's what this file does!

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p28,p27,p29); // serial tx, serial rx, reset pin;        

Serial pc(USBTX,USBRX);                 // USB Console (tx, rx)
MMA8452 acc(p9, p10, 100000);        // Accelerometer (sda, sdc, rate)
DigitalIn button1(p23);                 // Pushbuttons (pin)
DigitalIn button2(p24);
DigitalIn button3(p25);
DigitalIn button4(p20);
AnalogOut DACout(p18);                  // Speaker (pin)
PwmOut speaker(p26);


// Some hardware also needs to have functions called before it will set up
// properly. Do that here.
int hardware_init()
{
    // Crank up the speed
    uLCD.baudrate(3000000);
    //pc.baud(115200);
        
    //Initialize pushbuttons
    button1.mode(PullUp); 
    button2.mode(PullUp);
    button3.mode(PullUp);
    button4.mode(PullUp);
    
    return ERROR_NONE;
}

GameInputs read_inputs() 
{
    GameInputs in;
    
    //Accelorameter inputs
    double *xAccel = &in.ay;
    double *yAccel = &in.ax;
    acc.readXGravity(xAccel);
    acc.readYGravity(yAccel);
    in.ay = *xAccel;
    in.ax = *yAccel;
    in.b1 = button1;
    in.b2 = button2;
    in.b3 = button3;
    in.b4 = button4;
    
    if (!in.b1 || !in.b2 || !in.b3 || !in.b4 )
        wait(.2);
    
    return in;
}
