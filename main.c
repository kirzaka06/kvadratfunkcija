#include <stdio.h>
#include "window.h"
#include <stdint.h>
#include <string.h>

#define DELAY 1000/12
#define SQR(x) (x*x)

int R=1, numit=100, chng=0;
float a=1, b=1, c=1;
char* a_str="1",* b_str="1",* c_str="1",* i_str="100", v2i='a', *inp="\0";
char* LUT[52]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

float sqrfunc(float x,float a, float b, float c){
    float result = a*(SQR(x)) + b*x + c;
    return result;
}
void input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT)
            R=0;
        if(e.type==SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_ESCAPE:
                    R=0;
                break;
                case SDLK_a:
                    v2i='a';
                break;
                case SDLK_b:
                    v2i='b';
                break;
                case SDLK_c:
                    v2i='c';
                break;
                case SDLK_i:
                    v2i='i';
                break;
                case SDLK_F1:
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Help", "use keys A, B, C, I to select variable. Press F2 to change corresponding variable.(EX: a->f2->100;a now = 100)(Max for I=100)", NULL);
                break;
                case SDLK_F2:
                    if(!chng){
                        chng=1;
                        inp=malloc(256);
                        memset(inp, 0,256);
                        SDL_StartTextInput();
                    }
                    else{
                        chng=0;
                        SDL_StopTextInput();
                        int contains=0;
                        for(int i=0;i<52;++i){
                            if(strstr(inp, LUT[i])){
                                contains=1;
                                break;
                            }
                        }
                        if(strlen(inp) <=0)
                            contains=1;
                        if(!contains){
                            switch(v2i){
                                case 'a':
                                    a_str=malloc(sizeof(inp));
                                    memset(a_str,0,sizeof(inp));
                                    strcpy(a_str,inp);
                                    a=atof(a_str);
                                break;
                                case 'b':
                                    b_str=malloc(sizeof(inp));
                                    memset(b_str,0,sizeof(inp));
                                    strcpy(b_str,inp);
                                    b=atof(b_str);
                                break;
                                case 'c':
                                    c_str=malloc(sizeof(inp));
                                    memset(c_str,0,sizeof(inp));
                                    strcpy(c_str,inp);
                                    c=atof(c_str);
                                break;
                                case 'i':
                                    i_str=malloc(sizeof(inp));
                                    memset(i_str,0,sizeof(inp));
                                    strcpy(i_str,inp);
                                    numit=atoi(i_str);
                                    if(numit>100)
                                        numit=100;
                                break;
                            }
                        }
                    }
                break;
            }
        }
        if(chng==1 && e.type==SDL_KEYDOWN){
            if(e.key.keysym.sym==SDLK_BACKSPACE && inp[0] != '\0')
                inp[strlen(inp)-1]='\0';
        }else if(chng==1 && e.type==SDL_TEXTINPUT)
            strcat(inp, e.text.text);
        
    }
}
int main(){
    Window_t* win=CreateWindow("PARABOLA_tavā_mātē", 800, 600);
    uint32_t start=SDL_GetTicks(),time, last=0;

    SDL_Color BLACK={0,0,0};
    SDL_Color RED={255,0,0};
    SDL_Color GREEN={0,255,0};
    SDL_Color BLUE={0,0,255};

    TTF_Init();
    TTF_Font* font=TTF_OpenFont("font.ttf", 22);
    while(R){
        last=start;
        start=SDL_GetTicks();

        input();
        ClearWindow(win);
        for(int i=-numit-1;i<numit;++i)
            DisplayRect(win, 400+(i-1.5), 300-(sqrfunc(i,a, b, c))-1.5, 3, 3,RED);
        /*fuckery down below*/
        char* toinp_full=malloc(sizeof("var selected(F2 to start input): ")+4);
        sprintf(toinp_full,"var selected(i change): %c", v2i);
        DisplayText(win,font,toinp_full,4,0, BLACK); 
        free(toinp_full);
        DisplayLine(win, 0,300,800,300,BLACK);
        DisplayText(win, font, "x", 776, 276,BLACK);
        DisplayLine(win, 400,0,400,800,BLACK);
        DisplayText(win, font, "y", 404, 0,BLACK);
        DisplayText(win,font,"points: ",4,482,BLACK);
        DisplayText(win,font,i_str,106,482,BLACK);
        DisplayText(win,font,"a: ",4,510,BLACK);
        DisplayText(win,font,a_str,28,510,BLACK);
        DisplayText(win,font,"b: ",4,538,BLACK);
        DisplayText(win,font,b_str,28,538,BLACK);
        DisplayText(win,font,"c: ",4,566,BLACK);
        DisplayText(win,font,c_str,28,566,BLACK);
        if(strlen(inp)>0)
            DisplayText(win,font,inp,0,28,BLACK);
        PresentWindow(win);

        time=SDL_GetTicks()-start;
        if(DELAY>time)
            SDL_Delay(DELAY-time);
    }
    return 0;
}
