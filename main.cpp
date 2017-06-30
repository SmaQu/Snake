#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <windows.h>

void idzdoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X=x;
    dwPos.Y=y;

     hCon= GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hCon, dwPos);
}


using namespace std;
int width=20, height=20, speed;
int Xsnake, Ysnake;
int Xfood,Yfood;
int snakeLength=2;
int lastXPos[10000], lastYPos[10000];
int howMany=0;
int button;
char snakeDot=219, rtc=191, rdc=217,ltc=218,ldc=192;
char food=177;
char hline=196, vline=179;
char direction='r'; //right
int main()
{
    cout<<"Podaj szybkosc(1-10): "; //1-10
    cin>>speed;
    cout<<endl;
    char area[width][height];
//e-empty, s-snake, f-food
    for(int i=0;i<height;i++)
    {
        for(int u=0;u<width;u++)
        {
            area[i][u]='e';
        }
    }
//snake
    srand(time(NULL));
    Xsnake=rand()%width;
    Ysnake=rand()%height;
    area[Xsnake][Ysnake]='s';
//food
    do
    {
         Xfood=rand()%width;
         Yfood=rand()%height;
    }while(area[Xfood][Yfood]!='e');
    area[Xfood][Yfood]='f';

    idzdoxy(0,0);
//map draw
    cout<<ltc;
    for(int i=0;i<width;i++)
    {
        cout<<hline<<hline;
    }
    cout<<rtc;
    for(int i=0;i<height;i++)
    {
        cout<<endl<<vline;
        for(int j=0;j<width;j++)
        {
            if(area[j][i]=='e')cout<<"  ";
            if(area[j][i]=='s')cout<<snakeDot<<snakeDot;
            if(area[j][i]=='f')cout<<food<<food;
        }
        cout<<vline;
    }
    cout<<endl;
    cout<<ldc;
     for(int i=0;i<width;i++)
    {
        cout<<hline<<hline;
    }
    cout<<rdc;



for(;;)
{
    howMany++;
    lastXPos[howMany]=Xsnake;
    lastYPos[howMany]=Ysnake;

    Sleep(1000/speed);
    if(kbhit())
    {
        button=getch();
        if(button==224)button+=getch();
        if(button==0)button+=getch();
        if(button==296 && (direction=='l' || direction=='r'))direction='u';
        if(button==304 && (direction=='l' || direction=='r'))direction='d';
        if(button==299 && (direction=='u' || direction=='d'))direction='l';
        if(button==301 && (direction=='u' || direction=='d'))direction='r';
    }

    if(direction=='d')Ysnake++;
    if(direction=='u')Ysnake--;
    if(direction=='l')Xsnake--;
    if(direction=='r')Xsnake++;

//wall collision
    if(Xsnake==width) Xsnake=0;
    if(Xsnake==-1) Xsnake=width-1;
    if(Ysnake==height) Ysnake=0;
    if(Ysnake==-1) Ysnake=height-1;

    if(area[Xsnake][Ysnake]=='s')
    {
        idzdoxy(0,height+3);
        cout<<endl<<"\aKoniec";
        break;
    }

    if(area[Xsnake][Ysnake]=='f')
     {
         snakeLength++;
        do
        {
            Xfood=rand()%width;
            Yfood=rand()%height;
        }while(area[Xfood][Yfood]!='e');

        area[Xfood][Yfood]='f';
        idzdoxy(Xfood*2+1,Yfood+1);
        cout<<food<<food;
     }
     else
     {
         area[lastXPos[howMany-snakeLength]][ lastYPos[howMany-snakeLength]]='e';
         idzdoxy(lastXPos[howMany-snakeLength]*2+1,lastYPos[howMany-snakeLength]+1);
         cout<<"  ";
     }
        area[Xsnake][Ysnake]='s';
        idzdoxy(Xsnake*2+1,Ysnake+1);
        cout<<snakeDot<<snakeDot;
}

return 0;
}
