#include <stdio.h>
#include "window.h"
#include <stdint.h>
#include <string.h>
#define DELAY 1000/24
#define SQR(x) (x*x)

int R=1;
int numit=100;
float a=1, b=1, c=1;
char* a_str="1", b_str="1", c_str="1";
int a_inp=0, b_inp=0, c_inp=0;

float sqrfunc(float x,float a, float b, float c){
    float result = ((a*(SQR(x))) + (x*b) + c);
    return result;
}
void input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT)
            R=0;
        if(e.type==SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_a:
                    a_inp=1;
                    c_inp=0;
                    b_inp=0;
                break;
                case SDLK_b:
                    b_inp=1;
                    a_inp=0;
                    c_inp=0;
                break;
                case SDLK_c:
                    c_inp=1;
                    b_inp=0;
                    a_inp=0;
                break;
            }
        }
        if(e.type==SDL_TEXTINPUT && a_inp){
        
        }
    }
}
int main(){
    Window_t* win=CreateWindow("PARABOLA_tavā_mātē", 800, 600);
    /*framelimit*/
    uint32_t start=SDL_GetTicks(),time, last=0;
    /*colors*/
    SDL_Color BLACK={0,0,0};
    SDL_Color RED={255,0,0};
    SDL_Color GREEN={0,255,0};
    SDL_Color BLUE={0,0,255};
    /*font*/
    TTF_Init();
    TTF_Font* font=TTF_OpenFont("font.ttf", 24);
    while(R){
        /*fpsdelay start*/
        last=start;
        start=SDL_GetTicks();

        input();
        /*render*/
        ClearWindow(win);
        //void DisplayText(Window_t* win, TTF_Font* font, const char* text, float x, float y, SDL_Color col){
        DisplayLine(win, 0,300,800,300,BLACK);
        DisplayText(win, font, "x", 776, 276,BLACK);
        DisplayLine(win, 400,0,400,800,BLACK);
        DisplayText(win, font, "y", 404, 0,BLACK);
        for(int i=-numit+1;i<numit;++i)
            DisplayRect(win, 400+i-2, 250+(sqrfunc(i,a, b, c))-2, 4, 4,RED);
        DisplayText(win,font,"a: ",4,510,BLACK);
        DisplayText(win,font,"b: ",4,538,BLACK);
        DisplayText(win,font,"c: ",4,566,BLACK);
        PresentWindow(win);
        /*framelimit end*/
        time=SDL_GetTicks()-start;
        if(DELAY>time)
            SDL_Delay(DELAY-time);
    }
    return 0;
}
