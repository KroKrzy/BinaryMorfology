#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "Textures.h"
#include "Window.h"
#include "PixelArr.h"


using namespace std;



int main(){
    TTF_Init();
    Window win = Window(10,10,"Binary Morfology");
    Textures pictures = Textures();
    pictures.setWindow(&win);
    string path = "./pictures";
    SDL_Color White = {255,255,255};
    TTF_Font* Arimo = TTF_OpenFont("Arimo-Regular.ttf",24);
    for (const auto & entry : fs::directory_iterator(path))
    {
        string name= entry.path();
        string temp=name;
        temp.erase(0,11);
        const char* path=temp.c_str();
        SDL_Surface* surface = TTF_RenderText_Solid(Arimo,path,White); 
        pictures.include(name,surface);
    }
    
    SDL_SetWindowSize(win.win,300,pictures.tex.size()*30);
    SDL_Rect rect;
    rect.x=20;
    bool close_requested=false;
    string chosenpic;
    SDL_Event event;        
    typename map<string,SDL_Texture*>::iterator it;
    while(!close_requested)
    {
        win.rendShow();
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
            {
                close_requested=true;
            }
        }
        int i=0;
        for(it=pictures.tex.begin();it!=pictures.tex.end();it++)
        {
            SDL_QueryTexture(it->second,NULL,NULL,&rect.w,&rect.h);
            rect.y=i*30;
            win.putOnRend(it->second,rect);
            i++;
        }
        int mousex,mousey;
        int buttons = SDL_GetMouseState(&mousex,&mousey);
        if (buttons & SDL_BUTTON_LEFT ){
            int got = mousey/30;
            int i=0;
            for (it=pictures.tex.begin();it!=pictures.tex.end();it++)
            {
                if(i==got)
                {
                    chosenpic=it->first;
                    close_requested=true;
                    break;
                }
                i++;
            }
        }
    }
    Textures actions=Textures();
    actions.setWindow(&win);
    actions.include("dil",TTF_RenderText_Solid(Arimo,"Dilatation",White));
    actions.include("er",TTF_RenderText_Solid(Arimo,"Erosion",White));
    actions.include("op",TTF_RenderText_Solid(Arimo,"Open",White));
    actions.include("cl",TTF_RenderText_Solid(Arimo,"Close",White));
    actions.include("co",TTF_RenderText_Solid(Arimo,"Conture",White));
    actions.include("vf",TTF_RenderText_Solid(Arimo,"VFlip",White));
    actions.include("hf",TTF_RenderText_Solid(Arimo,"HFlip",White));
    
    
    Textures struc=Textures();
    struc.setWindow(&win);
    path="./struc";
    for (const auto & entry : fs::directory_iterator(path))
    {
        string name= entry.path();
        string temp=name;
        temp.erase(0,8);
        const char* path=temp.c_str();
        SDL_Surface* surface = TTF_RenderText_Solid(Arimo,path,White); 
        struc.include(name.c_str(),surface);
    }
    
    PixelArr pic=PixelArr();
    pic.loadPicturetxt(chosenpic);
    Textures workfiles = Textures();
    workfiles.setWindow(&win);
    workfiles.include("old",pic.sur);
    workfiles.include("new",pic.sur);
    workfiles.include("bake",TTF_RenderText_Solid(Arimo,"bake",White));
    workfiles.include("save",TTF_RenderText_Solid(Arimo,"save",White));
    workfiles.include("*",TTF_RenderText_Solid(Arimo,"*",White));
    SDL_SetWindowSize(win.win,530,530);
    SDL_SetRenderDrawColor(win.rend,125,125,125,255);
    close_requested=false;
    bool bake=false;
    bool bakedone=true;
    string chosenac;
    int chosenacsym=-1;
    const char* chosenstruc;
    int chosenstrucsym=-1;
    int picW=pic.getW();
    int picH=pic.getH();
    if (picW>picH)
    {
        picH=250*(float(picH)/float(picW));
        picW=250;
    }
    else if(picW<picH)
    {
        picW=250*(float(picW)/float(picH));
        picH=250;
    }
    else
    {
        picW=250;
        picH=250;
    }
    while(!close_requested)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)close_requested=true;
        }
        if(bake&&bakedone){
            bake=false;
            bakedone=false;
            try{
                if(chosenac=="dil"){
                    workfiles.update("old",pic.sur);
                    pic.dilation(chosenstruc);
                    workfiles.update("new",pic.sur);
                }
                else if(chosenac=="er"){
                    workfiles.update("old",pic.sur);
                    pic.erosion(chosenstruc);
                    workfiles.update("new",pic.sur);
                }
                else if(chosenac=="op"){
                    workfiles.update("old",pic.sur);
                    pic.open(chosenstruc);
                    workfiles.update("new",pic.sur);
                }
                else if(chosenac=="cl"){
                    workfiles.update("old",pic.sur);
                    pic.close(chosenstruc);
                    workfiles.update("new",pic.sur);
                }
                else if(chosenac=="co"){
                    workfiles.update("old",pic.sur);
                    pic.conture(chosenstruc);
                    workfiles.update("new",pic.sur);
                }
                else if(chosenac=="vf"){
                    workfiles.update("old",pic.sur);
                    pic.vflip();
                    workfiles.update("new",pic.sur);
                }
                else if(chosenac=="hf"){
                    workfiles.update("old",pic.sur);
                    pic.hflip();
                    workfiles.update("new",pic.sur);
                }
            }
            catch(...){cout<<"No structural object chosen"<<endl;}
            bakedone=true;
        }
        rect.w=picW;
        rect.h=picH;
        rect.x=10;
        rect.y=10;
        win.putOnRend(workfiles.getTexture("old"),rect);
        rect.x=270;
        win.putOnRend(workfiles.getTexture("new"),rect);
        rect.x=10;
        rect.y=500;
        SDL_QueryTexture(workfiles.getTexture("bake"),NULL,NULL,&rect.w,&rect.h);
        win.putOnRend(workfiles.getTexture("bake"),rect);
        int i=0;
        for(it=actions.tex.begin();it!=actions.tex.end();it++)
        {
            SDL_QueryTexture(it->second,NULL,NULL,&rect.w,&rect.h);
            rect.y=270+i*30;
            win.putOnRend(it->second,rect);
            if(chosenacsym==i){
                rect.x=0;
                SDL_QueryTexture(workfiles.getTexture("*"),NULL,NULL,&rect.w,&rect.h);
                win.putOnRend(workfiles.getTexture("*"),rect);
                rect.x=10;
            }
            i++;
        }
        SDL_QueryTexture(workfiles.getTexture("save"),NULL,NULL,&rect.w,&rect.h);
        rect.x=270;
        rect.y=500;
        win.putOnRend(workfiles.getTexture("save"),rect);
        i=0;
        for(it=struc.tex.begin();it!=struc.tex.end();it++)
        {
            SDL_QueryTexture(it->second,NULL,NULL,&rect.w,&rect.h);
            rect.y=270+i*30;
            win.putOnRend(it->second,rect);
            if(chosenstrucsym==i){
                rect.x=260;
                SDL_QueryTexture(workfiles.getTexture("*"),NULL,NULL,&rect.w,&rect.h);
                win.putOnRend(workfiles.getTexture("*"),rect);
                rect.x=270;
            }
            if (i==7)break;
            i++;
        }
        int mousex,mousey;
        int buttons = SDL_GetMouseState(&mousex,&mousey);
        if (buttons & SDL_BUTTON_LEFT ){
            if(mousey<500){
                if(mousex<270){
                    int got = (mousey-270)/30;
                    int i=0;
                    for (it=actions.tex.begin();it!=actions.tex.end();it++)
                    {
                        if(i==got)
                        {
                            chosenacsym=i;
                            chosenac=it->first;
                            break;
                        }
                        i++;
                    }
                }
                else{
                    int got = (mousey-270)/30;
                    int i=0;
                    for (it=struc.tex.begin();it!=struc.tex.end();it++)
                    {
                        if(i==got)
                        {
                            chosenstrucsym=i;
                            chosenstruc=it->first.c_str();
                            break;
                        }
                        i++;
                    }
                }
            }
            else{
                if(mousex<265){
                    bake=true;
                    SDL_Delay(200);
                }
                else{
                    pic.save();
                }
            }
        }
        win.rendShow();
        win.refrRend();
    }
    
    TTF_Quit();
    return 0;
}
