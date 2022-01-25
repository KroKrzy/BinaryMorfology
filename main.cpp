#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "Textures.h"
#include "Window.h"
#include "PixelArr.h"
#include <experimental/filesystem>


using namespace std;


/**
 * Main function of the program
 * 
 * Calls methods of the other classes
 * 
 * Manages user interface
 */
int main(){
    TTF_Init();
    open:
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
    if(chosenpic.substr(chosenpic.length()-4)==".txt"){
    pic.loadPicturetxt(chosenpic);
    }
    else{
        pic.loadPictureGrp(chosenpic);
        pic.savetxt("./temp/1.txt");
        pic.loadPicturetxt("./temp/1.txt");
    }
    Textures workfiles = Textures();
    workfiles.setWindow(&win);
    workfiles.include("old",pic.sur);
    workfiles.include("new",pic.sur);
    workfiles.include("bake",TTF_RenderText_Solid(Arimo,"Bake",White));
    workfiles.include("save",TTF_RenderText_Solid(Arimo,"Save",White));
    workfiles.include("*",TTF_RenderText_Solid(Arimo,"*",White));
    workfiles.include("undo",TTF_RenderText_Solid(Arimo,"Undo",White));
    workfiles.include("redo",TTF_RenderText_Solid(Arimo,"Redo",White));
    workfiles.include("open",TTF_RenderText_Solid(Arimo,"Open",White));
    workfiles.include("comm",TTF_RenderText_Solid(Arimo," ",White));
    SDL_SetWindowSize(win.win,530,600);
    SDL_SetRenderDrawColor(win.rend,125,125,125,255);
    close_requested=false;
    bool bake=false;
    bool bakedone=true;
    bool action=true;
    bool open=false;
    string logac="";
    string chosenac;
    int chosenacsym=-1;
    const char* chosenstruc;
    int chosenstrucsym=-1;
    int picW=pic.getW();
    int picH=pic.getH();
    ofstream outfile;
    int iterator = 0;
    int maxredo = 0;
    outfile.open("./output/log.txt");
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
        SDL_SetRenderDrawColor(win.rend,0,0,0,255);
        rect.x=10;
        rect.y=560;
        rect.w=510;
        rect.h=30;
        SDL_RenderFillRect(win.rend,&rect);
        SDL_SetRenderDrawColor(win.rend,125,125,125,255);
        if(bake&&bakedone&&!open){
            bake=false;
            bakedone=false;
            try{
                if(chosenac=="dil"){
                    pic.dilation(chosenstruc);
                    workfiles.update("new",pic.sur);
                    logac="dilation "+string(chosenstruc);
                }
                else if(chosenac=="er"){
                    pic.erosion(chosenstruc);
                    workfiles.update("new",pic.sur);
                    logac="erosion "+string(chosenstruc);
                }
                else if(chosenac=="op"){
                    pic.open(chosenstruc);
                    workfiles.update("new",pic.sur);
                    logac="opening "+string(chosenstruc);
                }
                else if(chosenac=="cl"){
                    pic.close(chosenstruc);
                    workfiles.update("new",pic.sur);
                    logac="closing "+string(chosenstruc);
                }
                else if(chosenac=="co"){
                    pic.conture(chosenstruc);
                    workfiles.update("new",pic.sur);
                    logac="conture "+string(chosenstruc);
                }
                else if(chosenac=="vf"){
                    pic.vflip();
                    workfiles.update("new",pic.sur);
                    logac="vertical flip";
                }
                else if(chosenac=="hf"){
                    pic.hflip();
                    workfiles.update("new",pic.sur);
                    logac="horizontal flip";
                }
                action =true;
            }
            catch(...){
                workfiles.update("comm",TTF_RenderText_Solid(Arimo,"No structural object chosen",White));
            }
            bakedone=true;
        }
        if (open){
            workfiles.update("comm",TTF_RenderText_Solid(Arimo,"YES     Are you sure?     NO",White));
            SDL_QueryTexture(workfiles.getTexture("comm"),NULL,NULL,&rect.w,&rect.h);
            rect.x=(530-rect.w)/2;
            rect.y = 560;
            win.putOnRend(workfiles.getTexture("comm"),rect);
        }
        else{
            rect.x=15;
            rect.y=560;
            SDL_QueryTexture(workfiles.getTexture("comm"),NULL,NULL,&rect.w,&rect.h);
            win.putOnRend(workfiles.getTexture("comm"),rect);
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
        rect.x=450;
        rect.y=500;
        win.putOnRend(workfiles.getTexture("save"),rect);
        SDL_QueryTexture(workfiles.getTexture("undo"),NULL,NULL,&rect.w,&rect.h);
        rect.x=10;
        rect.y=530;
        win.putOnRend(workfiles.getTexture("undo"),rect);
        SDL_QueryTexture(workfiles.getTexture("redo"),NULL,NULL,&rect.w,&rect.h);
        rect.x=235;
        win.putOnRend(workfiles.getTexture("redo"),rect);
        SDL_QueryTexture(workfiles.getTexture("open"),NULL,NULL,&rect.w,&rect.h);
        rect.x=450;
        win.putOnRend(workfiles.getTexture("open"),rect);
        i=0;
        rect.x=270;
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
            else if(mousey<530){
                if(mousex<265){
                    bake=true;
                    
                    SDL_Delay(200);
                }
                else{
                    pic.save();
                    workfiles.update("comm",TTF_RenderText_Solid(Arimo,"State saved",White));
                }
            }
            else if(mousey<560){
                if (mousex<177){
                    if(iterator>0){
                        pic.loadPicturetxt("./temp/"+to_string(--iterator)+".txt");
                        workfiles.update("new",pic.sur);
                        SDL_Delay(200);
                        logac = "undo";
                        outfile<<logac<<endl;
                    }
                    else{workfiles.update("comm",TTF_RenderText_Solid(Arimo,"Nothing to undo",White));}
                }
                else if(mousex<354){
                    if(iterator<maxredo)
                    {
                        pic.loadPicturetxt("./temp/"+to_string(++iterator)+".txt");
                        workfiles.update("new",pic.sur);
                        SDL_Delay(200);
                        logac = "redo";
                        outfile<<logac<<endl;
                    }
                    else{workfiles.update("comm",TTF_RenderText_Solid(Arimo,"Nothing to redo",White));}
                }
                else{
                    open=true;
                }
            }
            else{
                if(open){
                    if(mousex<265){
                        win.deletewin();
                        outfile.close();
                        goto open;
                        
                    }
                    else{
                        open=false;
                        workfiles.update("comm",TTF_RenderText_Solid(Arimo," ",White));
                    }
                }
            }
        }
        if(action)
        {
            outfile<<logac<<endl;
            action =false;
            pic.savetxt(("./temp/"+to_string(iterator)+".txt").c_str());
            workfiles.update("comm",TTF_RenderText_Solid(Arimo," ",White));
            maxredo = iterator;
            iterator++;
        }
        win.rendShow();
        win.refrRend();
    }
    path="./temp";
    for (const auto & entry : fs::directory_iterator(path))
    {
        std::experimental::filesystem::remove_all(entry.path());
    }
    outfile.close();
    TTF_Quit();
    return 0;
}
