#include "hardware.h"
#include "globals.h"
#include "Servo.h"

Servo tiltX(p21); //x-direction
Servo tiltY(p22); //y-direction
DigitalIn pb1(p23);              
DigitalIn pb2(p24);
DigitalIn pb3(p25);
DigitalIn pb4(p20);

 
float delay = 0.2; //delay val for switching between screens
int lifeCount = 3; //lives left
Timer timer; //time player's gameplay



int startScreen(GameInputs input) {
    
    //Setup Start Screen Graphics 
    uLCD.cls();
    uLCD.locate(2,2);
    uLCD.color(BLUE);

    uLCD.printf("Maze Game");
    uLCD.locate(4,4);

    uLCD.color(GREEN);
    uLCD.printf("Start game");
    
    uLCD.locate(4,6);
    uLCD.printf("Change");
    uLCD.locate(4,7);
    uLCD.printf("Sensitivity");

    uLCD.line(17,48,7,48,BLACK);
    uLCD.line(17,48,14,45,BLACK);
    uLCD.line(17,48,14,51,BLACK);
    uLCD.line(17,35,7,35,RED);
    uLCD.line(17,35,14,32,RED);
    uLCD.line(17,35,14,38,RED);
    
    
    bool start = false;
    bool init = false;
    int state; //menu option 
    while (!start) {
        
        if (!init) {
            wait(delay);
            init = true;
            state = 2;
        }
        if (!pb1) {
            wait(delay);
            uLCD.line(17,35,7,35,BLACK);
            uLCD.line(17,35,14,32,BLACK);
            uLCD.line(17,35,14,38,BLACK);
            uLCD.line(17,48,7,48,RED);
            uLCD.line(17,48,14,45,RED);
            uLCD.line(17,48,14,51,RED);
            state = 1;
        } else if (!pb2) {
            wait(delay);
            uLCD.line(17,48,7,48,BLACK);
            uLCD.line(17,48,14,45,BLACK);
            uLCD.line(17,48,14,51,BLACK);
            uLCD.line(17,35,7,35,RED);
            uLCD.line(17,35,14,32,RED);
            uLCD.line(17,35,14,38,RED);
            state = 2;
        } else if (!pb3) {
           wait(delay);
           start = true; 
        }
    }
    return state;
}

int changeSensitivityScreen() {
     //clear screen 
    uLCD.cls();
    double sensitivity = 1.0; //Boundary count for arrow
    uLCD.locate(3,2);
    uLCD.color(BLUE);
    uLCD.printf("Sensitivity");
    uLCD.locate(6,4);
    uLCD.color(GREEN);
    uLCD.printf("Low");
    uLCD.locate(6,7);
    uLCD.color(GREEN);
    uLCD.printf("Medium");
    uLCD.locate(6,10);
    uLCD.color(GREEN);
    uLCD.printf("High");
    
    int x1 = 17; int y1 = 35;
    int x2 = 7;  int y2 = 37;
    int delta = 23;
    
    uLCD.filled_rectangle(x1, y1, x2, y2, RED);

    bool back = false;
    bool init = false;
    while (!back) {
        // wait for user reset the position once switched between screens
        if (!init) { 
            wait(delay);
            init = true;
            sensitivity = 1.0; //Boundary count for arrow
        }
         if (!pb3) {
            back = true;
            wait(.2);
         }
        if (!pb1) {
            if (sensitivity >= 1 && sensitivity < 3) {
                uLCD.filled_rectangle(x1, y1, x2, y2, BLACK);
                uLCD.filled_rectangle(x1, y1 + delta, x2, y2 + delta, RED);
                y1 += delta;
                y2 += delta;
                sensitivity++;
                wait(delay);
            }  
    
        
        } else if (!pb2) {
            if (sensitivity > 1 && sensitivity <= 3) {

                uLCD.filled_rectangle(x1, y1, x2, y2, BLACK);
                uLCD.filled_rectangle(x1, y1 - delta, x2, 
                                    y2 - delta, RED);
                y1 -= delta;
                y2 -= delta;                
                sensitivity--;
                wait(delay);
            }
        }
    }

    return sensitivity;
}

void MazeControl(GameInputs inputs, double sensitivity) {
    uLCD.cls();
    uLCD.locate(4,4);
    uLCD.printf("Game Started");
    bool life = true;
    wait(2.0);
    uLCD.cls();
    while (life) {
        uLCD.locate(4,4);
        uLCD.printf("Lives left = ", lifeCount); 
        double *xAccel = &inputs.ay;
        double *yAccel = &inputs.ax;
        acc.readXGravity(xAccel);
        acc.readYGravity(yAccel);
        inputs.ay = *xAccel;
        inputs.ax = *yAccel;

        double x; 
        double y;
        
        (x >= 1.0) ? x = 1.0 :    ((inputs.ax + 1.0) / 2.0) * sensitivity;
        (y >= 1.0) ? y = 1.0 :    ((inputs.ay + 1.0) / 2.0) * sensitivity;     
             
        pc.printf("ax = %.2f, ay = %.2f\n\r", x, y);
        
        tiltX = x;
        tiltY = y;
        
        if (!pb4) {
            life = false;
            wait(delay);
        }

    }
} 

void show(GameInputs inputs) {
    
    uLCD.cls();
    uLCD.locate(0,0);
    uLCD.printf("sfghdgh");
    double *xAccel = &inputs.ay;
    double *yAccel = &inputs.ax;
    acc.readXGravity(xAccel);
    acc.readYGravity(yAccel);
    inputs.ay = *xAccel;
    inputs.ax = *yAccel;
    uLCD.printf("ax = %.2f, ay = %.2f", inputs.ax, inputs.ay);
    pc.printf("ax = %.2f, ay = %.2f", inputs.ax, inputs.ay);

}

void calibrate(GameInputs inputs) {
    //Setup Calibration Graphics
    uLCD.cls();
    uLCD.locate(2,2);
    uLCD.printf("Starting");
    uLCD.locate(2,4);
    uLCD.printf("Calibration");
    uLCD.locate(2,6);
    uLCD.printf("Process");
    
    //Setup Parameters
    wait(delay);
    int slightDelay = .2; 
    uLCD.cls();
    bool calibrate = false;
    
    double calibVal = 0.2;
    
    
    while(!calibrate) {
        
        double *xAccel = &inputs.ax;
        double *yAccel = &inputs.ay;
        acc.readXGravity(xAccel);
        acc.readYGravity(yAccel);
        inputs.ax = *xAccel;
        inputs.ay = *yAccel;
        
        
        pc.printf("ax = %.2f, ay = %.2f\n\r", inputs.ax, inputs.ay);
        pc.printf("calibVal = %d \n\r", calibVal);
        if (inputs.ax > calibVal) {
            uLCD.cls();
            uLCD.locate(2,2);
            uLCD.printf("Move Right");
            wait(slightDelay );
        } else if (inputs.ax < -calibVal) {
            uLCD.cls();
            uLCD.locate(2,2);
            uLCD.printf("Move Left");
            wait(slightDelay );
        } else if (inputs.ay > calibVal) {
            uLCD.cls();
            uLCD.locate(2,2);
            uLCD.printf("Move Up");
            wait(slightDelay );
        } else if (inputs.ay < -calibVal) {
            uLCD.cls();
            uLCD.locate(2,2);
            uLCD.printf("Move Down");
            wait(slightDelay );
        } else {
            calibrate = true;//break out of the loop
            uLCD.locate(2,2);
            uLCD.printf("Calibrated");
            wait(delay);
            uLCD.cls();
            uLCD.locate(2,2);
            uLCD.printf("Begin");
            wait(delay);
        }
    }
}

int main() {
    GameInputs game;
    
    pb1.mode(PullUp); 
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    bool start = false;
    int menuOption;
    double sensitivity;
 
     while (!start) {
        menuOption = startScreen(game);
        if (menuOption == 2) {
             start = true;
             uLCD.cls();
             uLCD.locate(2,2);
             uLCD.printf("StartScreen");
             wait(delay);
         } else if (menuOption == 1) {
            wait(delay);
            sensitivity = changeSensitivityScreen();
            
        }
    }
    uLCD.cls();
    uLCD.printf("ouuta dat loop");
    calibrate(game);
    MazeControl(game, sensitivity);
}