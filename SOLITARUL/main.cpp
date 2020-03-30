#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include<fstream>
using namespace std;
void meniu_general();
void setari();
void meniu();
struct buton{
    int x1=0;
    int x2=0;
    int y1=0;
    int y2=0;
};
struct undo{
    int M[12][12];};
undo v[100];
int cB=14, cT=2, w=0;
bool sound=true, vs_c=false, cust=false;
int sun1=1500, sun2=30;
char p1[15], p2[15];
buton butoane_setari(int x, int y, int k);
void patratel(int x,int y)
{
    x*=40;
    y*=40;
    setcolor(COLOR(220,220,220));
    rectangle(x,y,x+40,y+40);
    setfillstyle(SOLID_FILL,cT);
    floodfill(x+20,y+20,COLOR(220,220,220));
}
void pion(int x,int y)
{
    x*=40,y*=40;
    x+=20,y+=20;
    setcolor(COLOR(200,200,200));
    circle(x,y,11);
    setfillstyle(SOLID_FILL,cB);
    floodfill(x,y,COLOR(200,200,200));
}
buton desen_buton(int x,int y, int k)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+250,y+50);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    if(k==1)
        outtextxy(x+20,y+10,"SINGLE PLAYER");
    else
        if(k==2)
        outtextxy(x+35,y+10,"MULTIPLAYER");
    else
        if(k==5)
        outtextxy(x+35,y+10,"Player vs PC");
    B.x1=x;
    B.y1=y;
    B.x2=x+250;
    B.y2=y+50;
    return B;
}
buton buton_mape(int x, int y)
{
    buton B;
    B.x1=x;
    B.y1=y;
    B.x2=x+280;
    B.y2=y+280;
    return B;
}
bool button_apasat(buton B)
{
    int x = mousex(), y = mousey();

    if((x >= B.x1 && x <= B.x2 ) && (y >= B.y1 && y<=B.y2))
        return true;

    return false;
}
void mapa(int poz, int A[12][12])
{
    clearmouseclick(WM_LBUTTONDOWN);
    for(int i=1;i<=12;i++)
        for(int j=1;j<=12;j++)
            if(A[i][j]==1)
            {
                patratel(i+poz,j);
                pion(i+poz,j);
            }
            else
                if(A[i][j]==0)
                    patratel(i+poz,j);

}
void patrat_activat(int x, int y, int color)
{
        x*=40;
        y*=40;
        setcolor(BLUE);
        rectangle(x,y,x+40,y+40);
        setfillstyle(SOLID_FILL,color);
        floodfill(x+20,y+20,BLUE);
}
bool verif_coordonate_m1(int x, int y, int k, int A[12][12])
{
    if(k==1)
    {
        if(A[x][y]==1)
            return true;

     return false;
    }
    if(k==0)
    {
        if(A[x][y]==0)
            return true;

     return false;
    }
}
void patrate_adiacente(int x, int y, int A[12][12], int calc)
{
    if(A[x-2][y]==0 and A[x-1][y]==1 and verif_coordonate_m1(x-2,y,0,A))
        patrat_activat(x-2,y,15);
    if(A[x][y-2]==0 and A[x][y-1]==1 and verif_coordonate_m1(x,y-2,0,A))
        patrat_activat(x,y-2,15);
    if(A[x+2][y]==0 and A[x+1][y]==1 and verif_coordonate_m1(x+2,y,0,A))
        patrat_activat(x+2,y,15);
    if(A[x][y+2]==0 and A[x][y+1]==1 and verif_coordonate_m1(x,y+2,0,A))
        patrat_activat(x,y+2,15);
    if(calc!=1)
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(sound)
                Beep(sun1,sun2);
            int moux=mousex();
            int mouy=mousey();
            moux/=40;
            mouy/=40;
            if(A[moux][mouy]==-1||A[moux][mouy]==1)
                break;
            if(A[(x+moux)/2][(y+mouy)/2]!=1)
                break;
            if((moux==x-2 and mouy==y) or (moux==x and mouy==y-2) or (moux==x+2 and mouy==y) or (moux==x and mouy==y+2))
            {
            clearmouseclick(WM_LBUTTONDOWN);
            patratel(x,y);
            w++;
            for(int i=0; i<=12; i++)
                for(int j=1; j<=12; j++)
                    v[w].M[i][j]=A[i][j];
            A[x][y]=0;
            patratel((x+moux)/2,(y+mouy)/2);
            A[(x+moux)/2][(y+mouy)/2]=0;
            pion(moux,mouy);
            A[moux][mouy]=1;
            mapa(0,A);
            }
            break;
        }
    }
}
buton buton_back(int x, int y)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+39,y+29);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 1);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    outtextxy(x+1,y+7,"BACK");
    B.x1=x;
    B.y1=y;
    B.x2=x+39;
    B.y2=y+29;
    return B;
}
buton buton_custom(int x, int y)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+300,y+75);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    outtextxy(x+35,y+10,"CUSTOM");
    B.x1=x;
    B.y1=y;
    B.x2=x+250;
    B.y2=y+50;
    return B;
}
int numar_pioni(int A[12][12]);
void top_scriere(int x, char num[20]);
bool GameOver(int A[12][12])
{
    for(int i=1; i<=11; i++)
        for(int j=1; j<=11; j++)
        {
            if(A[i][j]==1)
            {
                if(i>2)
                    if(A[i-1][j]==1&&A[i-2][j]==0)
                        return false;
                if(i<9)
                    if(A[i+1][j]==1&&A[i+2][j]==0)
                        return false;
                if(j>2)
                    if(A[i][j-1]==1&&A[i][j-2]==0)
                        return false;
                if(j<9)
                    if(A[i][j+1]==1&&A[i][j+2]==0)
                        return false;
            }
        }
        return true;
}
int numar_pioni(int A[12][12])
{
    int k=0;
    for(int i=1; i<=11; i++)
        for(int j=1;j<=11;j++)
            if(A[i][j]==1)
                k++;
    return k;
}
void matrice_2P(int A[12][12], int B[12][12])
{
    for(int i=0;i<=12;i++)
        for(int j=0;j<=12;j++)
            B[i][j]=A[i][j];
}
buton buton_undo(int x, int y)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+150,y+50);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    outtextxy(x+35,y+10,"UNDO");
    B.x1=x;
    B.y1=y;
    B.x2=x+150;
    B.y2=y+50;
    return B;
}
void meniu_mape(int k);
void click_mapa(int A[12][12], int k, int pu1)
{
    int contor, nr_pioni, pioni_mancati, B[12][12];
    char s[3];
    int aux;
    w=0;
    if(cust==true)
        aux=50;
    else
        aux=0;
    buton backb = buton_back(1,1);
    buton undoB = buton_undo(375+aux,280);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    if(k==2)
        matrice_2P(A,B);
     if(k==3)
    {
        setcolor(BLACK);
        outtextxy(420+aux,150,"Score");
        if(vs_c==true)
             outtextxy(380+aux,165,"Computer");
        else
        if(p1[0]==NULL)
            outtextxy(380+aux,165,"Player1");
        else
            outtextxy(380+aux,165,p1);
        s[0]=pu1/10+'0';
        s[1]=pu1%10+'0';
        s[2]=NULL;
        outtextxy(440+aux,180,s);
    }
    nr_pioni=numar_pioni(A);
    while(1)
    {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                    if(sound)
                        Beep(sun1,sun2);
                    mapa(0,A);
                    if(button_apasat(undoB)&& w>0)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        for(int i=0; i<=12; i++)
                            for(int j=0; j<=12; j++)
                                A[i][j]=v[w].M[i][j];
                        w--;
                        mapa(0,A);
                    }
                    int moux=mousex();
                    int mouy=mousey();
                    if((moux >= 1 && moux <= 40 ) and (mouy >= 1 && mouy<= 30))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        closegraph();
                        initwindow(500,500, "HAVI", 50,50);
                        meniu();
                    }
                    clearmouseclick(WM_LBUTTONDOWN);
                    moux/=40;
                    mouy/=40;
                    if(verif_coordonate_m1(moux,mouy,1,A))
                    {
                        patrat_activat(moux,mouy,10);
                        patrate_adiacente(moux,mouy,A,0);
                    }
            }
            contor=numar_pioni(A);
            if(contor!=0)
            {
                setcolor(BLACK);
                outtextxy(380+aux,50,"There");
                outtextxy(380+aux,65,"are");
                s[0]=contor/10+'0';
                s[1]=contor%10+'0';
                s[2]=NULL;
                outtextxy(440,82,s);
                outtextxy(410+aux,100,"more");

                if(k==2)
                {
                    setcolor(BLACK);
                    outtextxy(420+aux,150,"Score");
                    if(p1[0]==NULL)
                            outtextxy(380+aux,165,"Player1");
                        else
                            outtextxy(380+aux,165,p1);
                    pioni_mancati=nr_pioni-contor;
                    s[0]=pioni_mancati/10+'0';
                    s[1]=pioni_mancati%10+'0';
                    s[2]=NULL;
                    outtextxy(440+aux,180,s);
                }

                if(k==3)
                {
                    setcolor(BLACK);
                    outtextxy(420+aux,210,"Score");
                    if(vs_c==true)
                    {
                         if(p1[0]==NULL)
                            outtextxy(380+aux,225,"Player1");
                        else
                            outtextxy(380+aux,225,p1);
                    }
                    else
                    if(p2[0]==NULL)
                            outtextxy(380+aux,225,"Player2");
                        else
                            outtextxy(380+aux,225,p2);
                    pioni_mancati=nr_pioni-contor;
                    s[0]=pioni_mancati/10+'0';
                    s[1]=pioni_mancati%10+'0';
                    s[2]=NULL;
                    outtextxy(440+aux,240,s);
                }
            }
            if(GameOver(A))
            {
                for(int i=1; i<=11; i++)
                    for(int j=1; j<=11; j++)
                        A[i][j]=-1;

                if(k==1)
                {
                    setcolor(WHITE);
                    rectangle(54,130,304,200);
                    setbkcolor(COLOR(255,0,0));
                    setcolor(BLACK);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR, 3);
                    setfillstyle(SOLID_FILL,COLOR(255,0,0));
                    floodfill(55,131,WHITE);
                    outtextxy(74,155,"GAME OVER");

                    setcolor(WHITE);
                    rectangle(93,210,262,260);
                    setbkcolor(COLOR(0,0,255));
                    setcolor(BLACK);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
                    setfillstyle(SOLID_FILL,COLOR(0,0,255));
                    floodfill(95,221,WHITE);
                    outtextxy(130,220,"BACK TO");
                    outtextxy(118,240,"MAIN MENU");
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            if(button_apasat(backb))
                            {
                                clearmouseclick(WM_LBUTTONDOWN);
                                closegraph();
                                initwindow(500,500, "HAVI", 50,50);
                                meniu();
                            }
                            else
                            {
                                int x,y;
                                x=mousex();
                                y=mousey();
                                clearmouseclick(WM_LBUTTONDOWN);
                                if(x>93&&x<262&&y>210&&y<260)
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    closegraph();
                                    initwindow(500,650, "HAVI", 50,50);
                                    meniu_general();
                                }
                            }
                        }
                    }
                }
                else
                if(k==2)
                {
                    setcolor(WHITE);
                    rectangle(54,130,304,200);
                    setbkcolor(COLOR(255,0,0));
                    setcolor(BLACK);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR, 3);
                    setfillstyle(SOLID_FILL,COLOR(255,0,0));
                    floodfill(55,131,WHITE);
                    outtextxy(74,155,"GAME OVER");

                    setcolor(WHITE);
                    rectangle(93,210,262,260);
                    setbkcolor(COLOR(0,0,255));
                    setcolor(BLACK);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
                    setfillstyle(SOLID_FILL,COLOR(0,0,255));
                    floodfill(95,221,WHITE);
                    outtextxy(130,220,"It follows");
                    if(p2[0]==NULL)
                            outtextxy(118,240,"Player2");
                        else
                            outtextxy(118,240,p2);
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            if(button_apasat(backb))
                            {
                                clearmouseclick(WM_LBUTTONDOWN);
                                closegraph();
                                initwindow(500,500, "HAVI", 50,50);
                                meniu();
                            }
                            else
                            {
                                int x,y;
                                x=mousex();
                                y=mousey();
                                clearmouseclick(WM_LBUTTONDOWN);
                                if((x >= 1 && x <= 40 ) and (y >= 1 && y<= 30))
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    closegraph();
                                    initwindow(500,500, "HAVI", 50,50);
                                    meniu();
                                }
                                if(x>93&&x<262&&y>210&&y<260)
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    closegraph();
                                    initwindow(700,450, "2", 50,50);
                                    mapa(0,B);
                                    click_mapa(B,3,pioni_mancati);
                                }
                            }
                        }
                    }
                }
                if(k==3)
                {
                    setcolor(WHITE);
                    rectangle(54,130,304,200);
                    setbkcolor(COLOR(255,0,0));
                    setcolor(BLACK);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR, 3);
                    setfillstyle(SOLID_FILL,COLOR(255,0,0));
                    floodfill(55,131,WHITE);
                    if(pu1!=pioni_mancati)
                        outtextxy(77,145,"have won");
                    if(pu1>pioni_mancati)
                    {
                        if(vs_c==true)
                            outtextxy(74,165,"Computer");
                        else
                        if(p1[0]==NULL)
                            outtextxy(74,165,"Player1");
                        else
                            outtextxy(74,165,p1);
                    }
                    else
                    if(pu1<pioni_mancati)
                    {
                        if(vs_c==true)
                        {
                            if(p1[0]==NULL)
                            outtextxy(74,165,"Player1");
                        else
                            outtextxy(74,165,p1);
                        }
                        else
                        if(p2[0]==NULL)
                            outtextxy(74,165,"Player2");
                        else
                            outtextxy(74,165,p2);
                    }
                    else
                    if(pu1==pioni_mancati)
                        outtextxy(77,155,"Draw");

                    setcolor(WHITE);
                    rectangle(93,210,262,260);
                    setbkcolor(COLOR(0,0,255));
                    setcolor(BLACK);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
                    setfillstyle(SOLID_FILL,COLOR(0,0,255));
                    floodfill(95,221,WHITE);
                    outtextxy(130,220,"BACK TO");
                    outtextxy(118,240,"MAIN MENU");
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            if(button_apasat(backb))
                            {
                                clearmouseclick(WM_LBUTTONDOWN);
                                closegraph();
                                initwindow(500,500, "HAVI", 50,50);
                                meniu();
                            }
                            else
                            {
                                int x,y;
                                x=mousex();
                                y=mousey();
                                clearmouseclick(WM_LBUTTONDOWN);
                                if(x>93&&x<262&&y>210&&y<260)
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    closegraph();
                                    initwindow(500,650, "HAVI", 50,50);
                                    meniu_general();
                                }
                            }
                        }
                    }
                }
            }
    }
}
void vs_calc_medium(int A[12][12])
{
    int i, j, x, y, k, scor, B[12][12];
    char s[3];
    matrice_2P(A,B);
    int vecx[]={0,2,0,-2};
    int vecy[]={2,0,-2,0};
    bool OK;
    buton backb=buton_back(1,1);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    scor=0;
    int aux;
    if(cust==true)
        aux=50;
    else
        aux=0;
    while(!GameOver(A))
    for(i=1;i<=12;i++)
    {
        for(j=1;j<=12;j++)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            if(button_apasat(backb))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,500, "HAVI", 50,50);
                meniu();
            }
            if(A[i][j]==0)
            {
                mapa(0,A);
                setcolor(BLACK);
                outtextxy(420+aux,150,"Score");
                outtextxy(380+aux,165,"Computer");
                for(k=0;k<=3;k++)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    if(button_apasat(backb))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        closegraph();
                        initwindow(500,500, "HAVI", 50,50);
                        meniu();
                    }
                    OK=true;
                    mapa(0,A);
                    x=i+vecx[k];
                    y=j+vecy[k];
                    if(A[x][y]==1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        if(button_apasat(backb))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            closegraph();
                            initwindow(500,500, "HAVI", 50,50);
                            meniu();
                        }
                        if(verif_coordonate_m1(x,y,1,A))
                        {
                            patrat_activat(x,y,10);
                            patrate_adiacente(x,y,A,1);
                        }
                        delay(100);

                        if(A[(i+x)/2][(j+y)/2]!=1)
                            OK=false;

                        if(OK==true)
                        {
                            patratel(x,y);
                            A[x][y]=0;
                            patratel((i+x)/2,(j+y)/2);
                            A[(i+x)/2][(j+y)/2]=0;
                            pion(i,j);
                            A[i][j]=1;
                            mapa(0,A);
                            scor++;
                            k=5;
                        }
                    }
                    s[0]=scor/10+'0';
                    s[1]=scor%10+'0';
                    s[2]=NULL;
                    setcolor(BLACK);
                    outtextxy(440+aux,180,s);
                }
            }
            if(ismouseclick(WM_LBUTTONDOWN))
            if(button_apasat(backb))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,500, "HAVI", 50,50);
                meniu();
            }
        }
    }

    setcolor(WHITE);
    rectangle(54,130,304,200);
    setbkcolor(COLOR(255,0,0));
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 3);
    setfillstyle(SOLID_FILL,COLOR(255,0,0));
    floodfill(55,131,WHITE);
    outtextxy(74,155,"GAME OVER");

    setcolor(WHITE);
    rectangle(93,210,262,260);
    setbkcolor(COLOR(0,0,255));
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,COLOR(0,0,255));
    floodfill(95,221,WHITE);
    outtextxy(130,220,"It follows");
    if(p1[0]==NULL)
        outtextxy(118,240,"Player1");
    else
        outtextxy(118,240,p1);
    while(1)
    {
       if(ismouseclick(WM_LBUTTONDOWN))
       {
           if(sound)
                Beep(sun1,sun2);
          int x,y;
          x=mousex();
          y=mousey();
          clearmouseclick(WM_LBUTTONDOWN);
          if((x >= 1 && x <= 40 ) and (y >= 1 && y<= 30))
          {
             clearmouseclick(WM_LBUTTONDOWN);
             closegraph();
             meniu_mape(k);
          }
          if(x>93&&x<262&&y>210&&y<260)
          {
             clearmouseclick(WM_LBUTTONDOWN);
             closegraph();
             initwindow(700,450, "2", 50,50);
             mapa(0,B);
             click_mapa(B,3,scor);
          }
       }
   }
}
void vs_calc_easy(int A[12][12])
{
    int i, j, x, y, k, scor, B[12][12];
    char s[3];
    matrice_2P(A,B);
    int vecx[]={0,2,0,-2};
    int vecy[]={2,0,-2,0};
    bool OK;
    int aux;
    if(cust==true)
        aux=50;
    else
        aux=0;
    buton backb=buton_back(1,1);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    scor=0;
    while(!GameOver(A))
    for(i=1;i<=12;i++)
    {
        for(j=1;j<=12;j++)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            if(button_apasat(backb))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,500, "HAVI", 50,50);
                meniu();
            }
            if(A[i][j]==1)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                if(button_apasat(backb))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    initwindow(500,500, "HAVI", 50,50);
                    meniu();
                }
                mapa(0,A);
                setcolor(BLACK);
                outtextxy(420+aux,150,"Score");
                outtextxy(380+aux,165,"Computer");
                for(k=0;k<=3;k++)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    if(button_apasat(backb))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        closegraph();
                        initwindow(500,500, "HAVI", 50,50);
                        meniu();
                    }
                    OK=true;
                    if(verif_coordonate_m1(i,j,1,A))
                    {
                        patrat_activat(i,j,10);
                        patrate_adiacente(i,j,A,1);
                    }
                    delay(30);
                    x=i+vecx[k];
                    y=j+vecy[k];

                    if(A[x][y]==-1)
                        OK=false;

                    if(A[x][y]==1)
                        OK=false;

                    if(A[(i+x)/2][(j+y)/2]!=1)
                        OK=false;

                    if(OK==true)
                    {
                        patratel(i,j);
                        A[i][j]=0;
                        patratel((i+x)/2,(j+y)/2);
                        A[(i+x)/2][(j+y)/2]=0;
                        pion(x,y);
                        A[x][y]=1;
                        mapa(0,A);
                        scor++;
                        k=5;
                    }
                    s[0]=scor/10+'0';
                    s[1]=scor%10+'0';
                    s[2]=NULL;
                    outtextxy(440+aux,180,s);
                }
            }
            if(ismouseclick(WM_LBUTTONDOWN))
            if(button_apasat(backb))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,500, "HAVI", 50,50);
                meniu();
            }
        }
    }

    setcolor(WHITE);
    rectangle(54,130,304,200);
    setbkcolor(COLOR(255,0,0));
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 3);
    setfillstyle(SOLID_FILL,COLOR(255,0,0));
    floodfill(55,131,WHITE);
    outtextxy(74,155,"GAME OVER");

    setcolor(WHITE);
    rectangle(93,210,262,260);
    setbkcolor(COLOR(0,0,255));
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,COLOR(0,0,255));
    floodfill(95,221,WHITE);
    outtextxy(130,220,"It follows");
    if(p1[0]==NULL)
        outtextxy(118,240,"Player1");
    else
        outtextxy(118,240,p1);
    while(1)
    {
       if(ismouseclick(WM_LBUTTONDOWN))
       {
           if(sound)
                Beep(sun1,sun2);
          int x,y;
          x=mousex();
          y=mousey();
          clearmouseclick(WM_LBUTTONDOWN);
          if((x >= 1 && x <= 40 ) and (y >= 1 && y<= 30))
          {
             clearmouseclick(WM_LBUTTONDOWN);
             closegraph();
             meniu_mape(k);
          }
          if(x>93&&x<262&&y>210&&y<260)
          {
             clearmouseclick(WM_LBUTTONDOWN);
             closegraph();
             initwindow(700,450, "2", 50,50);
             mapa(0,B);
             click_mapa(B,3,scor);
          }
       }
   }
}
buton butoane_vs_calc(int x, int y, int k)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+200,y+50);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    if(k==1)
        outtextxy(x+40,y+10,"Easy");
    else
        outtextxy(x+25,y+10,"Medium");
    B.x1=x;
    B.y1=y;
    B.x2=x+200;
    B.y2=y+50;
    return B;
}
void vs_calc()
{
    buton easy, medium, backB;
    easy= butoane_vs_calc(50,50,1);
    medium= butoane_vs_calc(50,150,2);
    backB= butoane_setari(50,250,5);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            Beep(sun1,sun2);
            if(button_apasat(easy))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                meniu_mape(5);
            }
            else
            if(button_apasat(medium))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                meniu_mape(6);
            }
            else
            if(button_apasat(backB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,500,"Menu",50,50);
                meniu();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }

}
void creare_mapa(int A[12][12], int k);
void joc_custom(int A[12][12], int k)
{
    buton backb;
    backb=buton_back(1,1);
    setcolor(WHITE);
    rectangle(420,200,585,240);
    setbkcolor(COLOR(0,255,0));
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,COLOR(0,255,0));
    floodfill(421,201,WHITE);
    outtextxy(425,205,"It can't be");
    outtextxy(463,220,"played");
    setcolor(WHITE);
    rectangle(460,260,545,290);
    setbkcolor(COLOR(0,255,0));
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,COLOR(0,255,0));
    floodfill(461,261,WHITE);
    outtextxy(465,265,"RETRY");
    buton retry;
    retry.x1=460;
    retry.x2=545;
    retry.y1=260;
    retry.y2=290;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(button_apasat(retry))
            {
                if(sound)
                    Beep(sun1,sun2);
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(700,450, "MAPA_CUSTOM", 50,50);
                creare_mapa(A,k);
                mapa(0,A);
                 while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            int x=mousex();
                            int y=mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            x=x/40;
                            y=y/40;
                            if(A[x][y]==1)
                                {
                                    A[x][y]=0;
                                    mapa(0,A);
                                    if(GameOver(A))
                                        joc_custom(A,k);
                                    else
                                        break;
                                }
                        }
                    }
                click_mapa(A,k,0);
            }
            if(button_apasat(backb))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                meniu_mape(k);
            }
        }
    }
}
void creare_mapa(int A[12][12], int k)
{
    buton gata, backb;
    for(int i=40;i<=400;i+=40)
        for(int j=40;j<=400;j+=40)
    {
        line(i,j,i,400);
        line(i,j,400,j);
    }
    backb=buton_back(1,1);
    for(int i=0;i<=12;i++)
        for(int j=0;j<=12;j++)
            A[i][j]=-1;
    setcolor(WHITE);
    rectangle(500,320,600,360);
    setbkcolor(COLOR(0,255,0));
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,COLOR(0,255,0));
    floodfill(501,321,WHITE);
    outtextxy(510,330,"START");
    buton start;
    start.x1=500;
    start.x2=600;
    start.y1=320;
    start.y2=360;
    while(1)
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        if(sound)
            Beep(sun1,sun2);
        if(button_apasat(backb))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            closegraph();
            meniu_mape(k);
        }
        if(button_apasat(start))
        {
            clearmouseclick(WM_LBUTTONDOWN);

                closegraph();
                initwindow(700,450, "MAPA_CUSTOM", 50,50);
                break;

        }
        int moux=mousex();
        int mouy=mousey();
        clearmouseclick(WM_LBUTTONDOWN);
        moux/=40;
        mouy/=40;
        if(moux!=0 and mouy!=0 and moux<=9 and mouy<=9)
        if(A[moux][mouy]==-1)
        {
            patratel(moux,mouy);
            A[moux][mouy]=1;
        }
    }
}
void meniu_mape(int k)
{
    buton m1,m2,ms,backb,custom;
    int A[12][12], i, j;
    closegraph();
    initwindow(1400,600, "HAVI2", 50,50);
    for(i=0; i<=12; i++)
        for(j=0;j<=12;j++)
            A[i][j]=-1;
    for(i=0; i<=12; i++)
        for(j=0;j<=12;j++)
            if(i==0||j==0||(i<3&&j<3)||(i>5&&j<3)||(i<3&&j>5)||(i>5&&j>5)||i>=8||j>=8)
                A[i][j]=-1;
            else
                A[i][j]=0;
    mapa(0,A);
    A[2][2]=0; A[6][2]=0;A[6][6]=0; A[2][6]=0;
    mapa(13,A);
    A[1][1]=0; A[1][2]=0; A[2][1]=0; A[1][6]=0; A[1][7]=0; A[2][7]=0; A[6][1]=0;A[7][1]=0; A[7][2]=0; A[6][7]=0; A[7][6]=0; A[7][7]=0;
    mapa(26,A);
    m1=buton_mape(40,40);
    m2=buton_mape(520,40);
    ms=buton_mape(1040,40);
    backb=buton_back(1,1);
    custom=buton_custom(570,475);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
            {
                cust=false;
                if(sound)
                    Beep(sun1,sun2);
                if(button_apasat(m1))
                {
                    for(i=0; i<=12; i++)
                        for(j=0;j<=12;j++)
                            if(i==0||j==0||(i<3&&j<3)||(i>5&&j<3)||(i<3&&j>5)||(i>5&&j>5)||i>=8||j>=8)
                                A[i][j]=-1;
                            else
                                A[i][j]=1;
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    initwindow(550,350, "MAPA1", 50,50);
                    mapa(0,A);
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            int x=mousex();
                            int y=mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            x=x/40;
                            y=y/40;
                            if(A[x][y]==1)
                                {
                                    A[x][y]=0;
                                    break;
                                }
                        }
                    }
                    mapa(0,A);
                    if(k==5)
                        vs_calc_easy(A);
                    else
                    if(k==6)
                        vs_calc_medium(A);
                    else
                    click_mapa(A,k,0);
                }
                if(button_apasat(m2))
                {
                    for(i=1; i<=12; i++)
                        for(j=1;j<=12;j++)
                            if((i<3&&j==1)||(i==1&&j==2)||(i>5&&j==1)||(i==7&&j==2)||(i<3&&j==7)||(i==1&&j==6)||(i>5&&j==7)||(i==7&&j==6)||i>=8||j>=8)
                                A[i][j]=-1;
                            else
                                A[i][j]=1;
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    initwindow(550,350, "MAPA2", 50,50);
                    mapa(0,A);
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            int x=mousex();
                            int y=mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            x=x/40;
                            y=y/40;
                            if(A[x][y]==1)
                                {
                                    A[x][y]=0;
                                    break;
                                }
                        }
                    }
                    mapa(0,A);
                    if(k==5)
                        vs_calc_easy(A);
                    else
                    if(k==6)
                        vs_calc_medium(A);
                    else
                    click_mapa(A,k,0);
                }
                if(button_apasat(ms))
                {
                    for(i=1;i<=12;i++)
                        for(j=1;j<=12; j++)
                            if(i>=8||j>=8)
                            A[i][j]=-1;
                        else
                            A[i][j]=1;
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    initwindow(550,350, "MAPA_SAH", 50,50);
                    mapa(0,A);
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            int x=mousex();
                            int y=mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            x=x/40;
                            y=y/40;
                            if(A[x][y]==1)
                                {
                                    A[x][y]=0;
                                    break;
                                }
                        }
                    }
                    mapa(0,A);
                    if(k==5)
                        vs_calc_easy(A);
                    else
                    if(k==6)
                        vs_calc_medium(A);
                    else
                        click_mapa(A,k,0);
                }
                if(button_apasat(backb))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    initwindow(500,500, "HAVI", 50,50);
                    meniu();
                }
                if(button_apasat(custom))
                {
                    cust=true;
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    initwindow(700,450, "MAPA_CUSTOM", 50,50);
                    creare_mapa(A,k);
                    mapa(0,A);
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            if(sound)
                                Beep(sun1,sun2);
                            int x=mousex();
                            int y=mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            x=x/40;
                            y=y/40;
                            if(A[x][y]==1)
                                {
                                    A[x][y]=0;
                                    mapa(0,A);
                                    if(GameOver(A))
                                        joc_custom(A,k);
                                    else
                                        break;
                                }
                        }
                    }
                    mapa(0,A);
                    if(k==5)
                        vs_calc_easy(A);
                    else
                    if(k==6)
                        vs_calc_medium(A);
                    else
                    click_mapa(A,k,0);
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
    }
}
buton butoane_nume(int x, int y, char c[])
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+40,y+40);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    outtextxy(x+2,y+2,c);
    B.x1=x;
    B.y1=y;
    B.x2=x+40;
    B.y2=y+40;
    return B;
}
buton butoane_editare_text(int x, int y, int k)
{
    buton B;
    setcolor(WHITE);
    if(k==1)
        rectangle(x,y,x+120,y+40);
    else
        rectangle(x,y,x+165,y+40);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    if(k==1)
        outtextxy(x+2,y+2,"Delete");
    else
        outtextxy(x+2,y+2,"Backspace");
    B.x1=x;
    B.y1=y;
    if(k==1)
        B.x2=x+120;
    else
        B.x2=x+165;
    B.y2=y+40;
    return B;
}
void nume_jucatori_meniu();
void nume_jucatori(char sir[])
{
    buton q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m,backB,backspace,deleteB;
    int nr=0;
    q=butoane_nume(100,100,"q");
    w=butoane_nume(145,100,"w");
    e=butoane_nume(190,100,"e");
    r=butoane_nume(235,100,"r");
    t=butoane_nume(280,100,"t");
    y=butoane_nume(325,100,"y");
    u=butoane_nume(370,100,"u");
    i=butoane_nume(415,100,"i");
    o=butoane_nume(460,100,"o");
    p=butoane_nume(505,100,"p");
    a=butoane_nume(110,145,"a");
    s=butoane_nume(155,145,"s");
    d=butoane_nume(200,145,"d");
    f=butoane_nume(245,145,"f");
    g=butoane_nume(290,145,"g");
    h=butoane_nume(335,145,"h");
    j=butoane_nume(380,145,"j");
    k=butoane_nume(425,145,"k");
    l=butoane_nume(470,145,"l");
    z=butoane_nume(120,190,"z");
    x=butoane_nume(165,190,"x");
    c=butoane_nume(210,190,"c");
    v=butoane_nume(255,190,"v");
    b=butoane_nume(300,190,"b");
    n=butoane_nume(345,190,"n");
    m=butoane_nume(390,190,"m");
    backB=butoane_setari(300,300,5);
    backspace=butoane_editare_text(435,190,2);
    deleteB=butoane_editare_text(515,145,1);
    sir[0]=NULL;

    setcolor(WHITE);
    rectangle(100,50,500,90);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(101,51,WHITE);

    int val;
    while(1)
    {
        outtextxy(135,60,sir);
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(sound)
                Beep(sun1,sun2);
            if(nr==0)
                val='A'-'a';
            else
                val=0;
            if(nr<=16)
            {
            if(button_apasat(q))
            {
                sir[nr]='q'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(w))
            {
                sir[nr]='w'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(e))
            {
                sir[nr]='e'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(r))
            {
                sir[nr]='r'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(t))
            {
                sir[nr]='t'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(y))
            {
                sir[nr]='y'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(u))
            {
                sir[nr]='u'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(i))
            {
                sir[nr]='i'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(o))
            {
                sir[nr]='o'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(p))
            {
                sir[nr]='p'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(a))
            {
                sir[nr]='a'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(s))
            {
                sir[nr]='s'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(d))
            {
                sir[nr]='d'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(f))
            {
                sir[nr]='f'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(g))
            {
                sir[nr]='g'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(h))
            {
                sir[nr]='h'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(j))
            {
                sir[nr]='j'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(k))
            {
                sir[nr]='k'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(l))
            {
                sir[nr]='l'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(z))
            {
                sir[nr]='z'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(x))
            {
                sir[nr]='x'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(c))
            {
                sir[nr]='c'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(v))
            {
                sir[nr]='v'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(b))
            {
                sir[nr]='b'+val;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(n))
            {
                sir[nr]='n'+val;;
                nr++;
                sir[nr]=NULL;
            }
            else
            if(button_apasat(m))
            {
                sir[nr]='m'+val;
                nr++;
                sir[nr]=NULL;
            }
            }
            if(button_apasat(backspace))
            {
                nr--;
                sir[nr]=NULL;
                setcolor(WHITE);
                rectangle(100,50,500,90);
                setbkcolor(LIGHTGRAY);
                setcolor(BLACK);
                settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
                setfillstyle(SOLID_FILL,LIGHTGRAY);
                floodfill(101,51,WHITE);
            }
            else
            if(button_apasat(deleteB))
            {
                sir[0]=NULL;
                nr=0;
                setcolor(WHITE);
                rectangle(100,50,500,90);
                setbkcolor(LIGHTGRAY);
                setcolor(BLACK);
                settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
                setfillstyle(SOLID_FILL,LIGHTGRAY);
                floodfill(101,51,WHITE);
            }
            else
            if(button_apasat(backB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(400,400,"Player_names",50,50);
                nume_jucatori_meniu();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
buton butoane_jucatori(int x, int y, int k)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+200,y+40);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    if(k==1)
    {
        if(p1[0]==NULL)
            outtextxy(x+35,y+10,"Player1");
        else
            outtextxy(x+35,y+10,p1);
    }
    else
    {
        if(p2[0]==NULL)
            outtextxy(x+35,y+10,"Player2");
        else
            outtextxy(x+35,y+10,p2);
    }
    B.x1=x;
    B.y1=y;
    B.x2=x+200;
    B.y2=y+40;
    return B;
}
void nume_jucatori_meniu()
{
    buton play1,play2, backB;
    play1=butoane_jucatori(100,100,1);
    play2=butoane_jucatori(100,200,2);
    backB=butoane_setari(100,300,5);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(sound)
                Beep(sun1,sun2);
            if(button_apasat(play1))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(650,400,"Player_names1",50,50);
                nume_jucatori(p1);
            }
            else
            if(button_apasat(play2))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(650,400,"Player_names2",50,50);
                nume_jucatori(p2);
            }
            else
            if(button_apasat(backB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,650,"Settings",50,50);
                setari();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
buton butoane_sunet(int x, int y, int k)
{
    buton B;
    char c[2];
    c[0]=k+'0';
    c[1]=NULL;
    setcolor(WHITE);
    if(k>5)
        rectangle(x,y,x+60,y+40);
    else
        rectangle(x,y,x+40,y+40);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    if(k<=5)
        outtextxy(x+2,y+2,c);
    else
        if(k==6)
            outtextxy(x+2,y+2,"ON");
    else
        outtextxy(x+2,y+2,"OFF");
    B.x1=x;
    B.y1=y;
    if(k>5)
        B.x2=x+60;
    else
        B.x2=x+40;
    B.y2=y+40;
    return B;
}
void sunetist()
{
    buton on, off, sound1, sound2, sound3, sound4, sound5, backB;
    on=butoane_sunet(50,50,6);
    off=butoane_sunet(140,50,7);
    sound1=butoane_sunet(25,150,1);
    sound2=butoane_sunet(75,150,2);
    sound3=butoane_sunet(125,150,3);
    sound4=butoane_sunet(175,150,4);
    sound5=butoane_sunet(225,150,5);
    backB=butoane_setari(50,230,5);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(button_apasat(on))
            {
                sound=true;
                Beep(sun1,sun2);
            }
            else
            if(button_apasat(off))
            {
                sound=false;
            }
            else
            if(button_apasat(sound1))
            {
                sun1=1000;
                Beep(sun1,sun2);
            }
            else
            if(button_apasat(sound2))
            {
                sun1=1200;
                Beep(sun1,sun2);
            }
            else
            if(button_apasat(sound3))
            {
                sun1=1500;
                Beep(sun1,sun2);
            }
            else
            if(button_apasat(sound4))
            {
                sun1=1750;
                Beep(sun1,sun2);
            }
            else
            if(button_apasat(sound5))
            {
                sun1=2000;
                Beep(sun1,sun2);
            }
            else
            if(button_apasat(backB))
            {
                Beep(sun1,sun2);
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,650,"Settings",50,50);
                setari();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
buton butoane_culori(int x, int y, int k)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+40,y+40);
    if(k==0)
        setbkcolor(COLOR(181, 122, 0));
    else
    if(k==1)
        setbkcolor(1);
    else
    if(k==2)
        setbkcolor(2);
    else
    if(k==3)
        setbkcolor(3);
    else
    if(k==4)
        setbkcolor(4);
    else
    if(k==5)
        setbkcolor(5);
    else
    if(k==6)
        setbkcolor(6);
    else
    if(k==7)
        setbkcolor(7);
    else
    if(k==8)
        setbkcolor(8);
    else
    if(k==9)
        setbkcolor(9);
    else
    if(k==10)
        setbkcolor(10);
    else
    if(k==11)
        setbkcolor(11);
    else
    if(k==12)
        setbkcolor(12);
    else
    if(k==13)
        setbkcolor(13);
    else
    if(k==14)
        setbkcolor(14);
    else
    if(k==15)
        setbkcolor(COLOR(85, 31, 48));

    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);

    if(k==0)
        setfillstyle(SOLID_FILL,COLOR(181, 122, 0));
    else
    if(k==1)
        setfillstyle(SOLID_FILL,1);
    else
    if(k==2)
        setfillstyle(SOLID_FILL,2);
    else
    if(k==3)
        setfillstyle(SOLID_FILL,3);
    else
    if(k==4)
        setfillstyle(SOLID_FILL,4);
    else
    if(k==5)
        setfillstyle(SOLID_FILL,5);
    else
    if(k==6)
        setfillstyle(SOLID_FILL,6);
    else
    if(k==7)
        setfillstyle(SOLID_FILL,7);
    else
    if(k==8)
        setfillstyle(SOLID_FILL,8);
    else
    if(k==9)
        setfillstyle(SOLID_FILL,9);
    else
    if(k==10)
        setfillstyle(SOLID_FILL,10);
    else
    if(k==11)
        setfillstyle(SOLID_FILL,11);
    else
    if(k==12)
        setfillstyle(SOLID_FILL,12);
    else
    if(k==13)
        setfillstyle(SOLID_FILL,13);
    else
    if(k==14)
        setfillstyle(SOLID_FILL,14);
    else
    if(k==15)
        setfillstyle(SOLID_FILL,COLOR(85, 31, 48));

    floodfill(x+1,y+1,WHITE);
    B.x1=x;
    B.y1=y;
    B.x2=x+40;
    B.y2=y+40;
    return B;
}
void culoare_pioni()
{
    buton c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15, backB;
    c0=butoane_culori(50,50,0);
    c1=butoane_culori(50,100,1);
    c2=butoane_culori(50,150,2);
    c3=butoane_culori(50,200,3);
    c4=butoane_culori(100,50,4);
    c5=butoane_culori(100,100,5);
    c6=butoane_culori(100,150,6);
    c7=butoane_culori(100,200,7);
    c8=butoane_culori(150,50,8);
    c9=butoane_culori(150,100,9);
    c10=butoane_culori(150,150,10);
    c11=butoane_culori(150,200,11);
    c12=butoane_culori(200,50,12);
    c13=butoane_culori(200,100,13);
    c14=butoane_culori(200,150,14);
    c15=butoane_culori(200,200,15);
    backB=butoane_setari(300,140,5);
    cB=1;
    while(1)
    {
        setcolor(WHITE);
        rectangle(350,50,390,90);
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(351,51,WHITE);
        setcolor(COLOR(200,200,200));
        circle(370,70,11);
        setfillstyle(SOLID_FILL,cB);
        floodfill(370,70,COLOR(200,200,200));
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(sound)
                Beep(sun1,sun2);
            if(button_apasat(c0))
                cB=COLOR(181, 122, 0);
            else
            if(button_apasat(c1))
                cB=1;
            else
            if(button_apasat(c2))
                cB=2;
            else
            if(button_apasat(c3))
                cB=3;
            else
            if(button_apasat(c4))
                cB=4;
            else
            if(button_apasat(c5))
                cB=5;
            else
            if(button_apasat(c6))
                cB=6;
            else
            if(button_apasat(c7))
                cB=7;
            else
            if(button_apasat(c8))
                cB=8;
            else
            if(button_apasat(c9))
                cB=9;
            else
            if(button_apasat(c10))
                cB=10;
            else
            if(button_apasat(c11))
                cB=11;
            else
            if(button_apasat(c12))
                cB=12;
            else
            if(button_apasat(c13))
                cB=13;
            else
            if(button_apasat(c14))
                cB=14;
            else
            if(button_apasat(c15))
                cB=COLOR(85, 31, 48);
            else
            if(button_apasat(backB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,650,"Settings",50,50);
                setari();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
void culoare_tabla()
{
    buton c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15, backB;
    c0=butoane_culori(50,50,0);
    c1=butoane_culori(50,100,1);
    c2=butoane_culori(50,150,2);
    c3=butoane_culori(50,200,3);
    c4=butoane_culori(100,50,4);
    c5=butoane_culori(100,100,5);
    c6=butoane_culori(100,150,6);
    c7=butoane_culori(100,200,7);
    c8=butoane_culori(150,50,8);
    c9=butoane_culori(150,100,9);
    c10=butoane_culori(150,150,10);
    c11=butoane_culori(150,200,11);
    c12=butoane_culori(200,50,12);
    c13=butoane_culori(200,100,13);
    c14=butoane_culori(200,150,14);
    c15=butoane_culori(200,200,15);
    backB=butoane_setari(300,140,5);
    cT=1;
    while(1)
    {
        setcolor(COLOR(200,200,200));
        rectangle(350,50,390,90);
        setfillstyle(SOLID_FILL,cT);
        floodfill(351,51,COLOR(200,200,200));
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(sound)
                Beep(sun1,sun2);
            if(button_apasat(c0))
                cT=COLOR(181, 122, 0);
            else
            if(button_apasat(c1))
                cT=1;
            else
            if(button_apasat(c2))
                cT=2;
            else
            if(button_apasat(c3))
                cT=3;
            else
            if(button_apasat(c4))
                cT=4;
            else
            if(button_apasat(c5))
                cT=5;
            else
            if(button_apasat(c6))
                cT=6;
            else
            if(button_apasat(c7))
                cT=7;
            else
            if(button_apasat(c8))
                cT=8;
            else
            if(button_apasat(c9))
                cT=9;
            else
            if(button_apasat(c10))
                cT=10;
            else
            if(button_apasat(c11))
                cT=11;
            else
            if(button_apasat(c12))
                cT=12;
            else
            if(button_apasat(c13))
                cT=13;
            else
            if(button_apasat(c14))
                cT=14;
            else
            if(button_apasat(c15))
                cT=15;
            else
            if(button_apasat(backB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,650,"Settings",50,50);
                setari();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }

}
buton butoane_setari(int x, int y, int k)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+200,y+50);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    if(k==1)
        outtextxy(x+40,y+10,"Sound");
    else
        if(k==2)
        {
            outtextxy(x+25,y+10,"Color");
            outtextxy(x+55,y+32,"pawn");
        }
    else
        if(k==3)
        {
            outtextxy(x+25,y+10,"Color");
            outtextxy(x+55,y+32,"table");
        }
    else
        if(k==4)
        outtextxy(x+35,y+10,"Players");
    else
        if(k==5)
        outtextxy(x+35,y+10,"BACK");
    B.x1=x;
    B.y1=y;
    B.x2=x+200;
    B.y2=y+50;
    return B;
}
void setari()
{
    buton sunet, culoareP, culoareT, playeri, backB;
    sunet = butoane_setari(100,100,1);
    culoareP = butoane_setari(100,200,2);
    culoareT = butoane_setari(100,300,3);
    playeri = butoane_setari(100,400,4);
    backB = butoane_setari(100,500,5);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(sound)
                Beep(sun1,sun2);
            if(button_apasat(sunet))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(290,350,"Sound",50,50);
                sunetist();
            }
            else
            if(button_apasat(culoareP))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(550,350,"Pawn_color",50,50);
                culoare_pioni();
            }
            else
            if(button_apasat(culoareT))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(550,350,"Table_color",50,50);
                culoare_tabla();
            }
            else
            if(button_apasat(playeri))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(400,400,"Player_names",50,50);
                nume_jucatori_meniu();
            }
            else
            if(button_apasat(backB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,650, "HAVI", 50,50);
                meniu_general();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
void meniu()
{
    buton oneP, twoP, calcP, backB;
    oneP = desen_buton(100,100,1);
    twoP = desen_buton(100,200,2);
    calcP = desen_buton(100,300,5);
    backB = butoane_setari(125,400,5);
    while(1)
    {
    if(ismouseclick(WM_LBUTTONDOWN))
        {
            vs_c=false;
            if(sound)
                Beep(sun1,sun2);
            if(button_apasat(oneP))
                meniu_mape(1);
            else
            if(button_apasat(twoP))
                meniu_mape(2);
            else
            if(button_apasat(calcP))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                vs_c=true;
                initwindow(300,400, "Vs_calc", 50,50);
                vs_calc();
            }
            else
            if(button_apasat(backB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,650, "HAVI", 50,50);
                meniu_general();
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

    }
}
buton butoane_meniu(int x, int y, int k)
{
    buton B;
    setcolor(WHITE);
    rectangle(x,y,x+250,y+50);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x+1,y+1,WHITE);
    if(k==1)
        outtextxy(x+40,y+10,"Start");
    else
        if(k==2)
        outtextxy(x+20,y+10,"Instructions");
    else
        if(k==3)
        outtextxy(x+35,y+10,"Settings");
    else
        if(k==4)
        outtextxy(x+35,y+10,"EXIT");
    B.x1=x;
    B.y1=y;
    B.x2=x+250;
    B.y2=y+50;
    return B;
}
void instructiuni(int k)
{
    initwindow(750,950, "Instructions", 50,50);
    if(k==0)
        readimagefile("0.jpg",0,0,750,950);
    if(k==1)
        readimagefile("1.jpg",0,0,750,950);
    if(k==2)
        readimagefile("2.jpg",0,0,750,950);
    if(k==3)
        readimagefile("3.jpg",0,0,750,950);
    if(k==4)
        readimagefile("4.jpg",0,0,750,950);
    if(k==5)
        readimagefile("5.jpg",0,0,750,950);
    buton_back(0,0);
    buton backB, next, previous;
    backB.x1=0;
    backB.x2=39;
    backB.y1=0;
    backB.y2=29;
    next.x1=675;
    next.x2=750;
    next.y1=475;
    next.y2=500;
    previous.x1=0;
    previous.x2=75;
    previous.y1=475;
    previous.y2=500;
    setcolor(WHITE);
    rectangle(0,475,75,500);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(1,476,WHITE);
    outtextxy(17,482,"<-");
    setcolor(WHITE);
    rectangle(675,475,750,500);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(676,476,WHITE);
    outtextxy(692,482,"->");
    while(1)
    {
         if(ismouseclick(WM_LBUTTONDOWN))
            {
                if(button_apasat(previous))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    if(sound)
                        Beep(sun1,sun2);
                    if(k==0)
                    {
                        closegraph();
                        initwindow(500,650, "HAVI", 50,50);
                        meniu_general();
                    }
                    else
                        instructiuni(k-1);
                }
                if(button_apasat(next))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    if(sound)
                        Beep(sun1,sun2);
                    if(k==5)
                    {
                        closegraph();
                        initwindow(500,650, "HAVI", 50,50);
                        meniu_general();
                    }
                    else
                        instructiuni(k+1);
                }
                if(button_apasat(backB))
                {
                    if(sound)
                        Beep(sun1,sun2);
                    clearmouseclick(WM_LBUTTONDOWN);
                    closegraph();
                    initwindow(500,650, "HAVI", 50,50);
                    meniu_general();
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
    }
    getch();
}
void meniu_general()
{
    buton start, instr, setB, top, exitB;
    start = butoane_meniu(100,100,1);
    instr = butoane_meniu(100,200,2);
    setB = butoane_meniu(100,300,3);
    exitB = butoane_meniu(100,500,4);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(sound)
                Beep(sun1,sun2);
            if(button_apasat(start))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,500,"Menu",50,50);
                meniu();
            }
            else
            if(button_apasat(instr))
            {
                instructiuni(0);
            }
            else
            if(button_apasat(setB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                initwindow(500,650,"Settings",50,50);
                setari();
            }
            else
            if(button_apasat(exitB))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                exit(0);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
int main()
{
    initwindow(500,650, "HAVI", 50,50);
    meniu_general();
    getch();
    return 0;
}
