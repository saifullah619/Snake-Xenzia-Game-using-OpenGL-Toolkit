//============================================================================
// Name        : snake.cpp
// Author      : Saif
// Version     :
// Copyright   : (c) Reserved
// Description : Snake...
//============================================================================

#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
#include<string>
//#include<sstream>
//#include<sys/wait.h>
#include<cstdlib>
#include<stdio.h>
#include<unistd.h>
#include<cmath>
using namespace std;
//----------------------------------------------------------------------------------------------------------------------

int w = 1366/2 , h=768/2 ;
int x[300] ;                  // snake arrat x co-ordinates
int y[300] ;                  // snake array y co-ordinates
int l=0;                      // variable for storing GLUT keys 
int tmpx=0;                   // variable for swapping X 
int tmpy=0;                   // variable for swapping Y
string scr="00";              //string for saving score
double startx=320,starty=400;  
int length=2;                 //  initial length
int bt=0 ;                    //bonus timer  
int tim=0;                    // timer for Bonus Food 
int b[5];                     // food x_axis 
int c[5];                     // food y _ axis 
int R1=-20 , R2=-30 ;         // initial co-ordinates for bonus food 
int p[5]={75000 , 75000 , 75000 , 75000 , 75000 }; // food timer array   
bool bfood=false;             // Boolean for bonus food 
bool ds=true ;                // Boolean for disappearing bonus  food
bool bar=false;
int score=0;                      
int e=0;                      // timer for exit
float bar_end=400;              // bar for power food
const int size=22;
int adx[size];                // hurdle array X axis
int ady[size];                // hurdle array Y axis
int htm=150000;               //hurdle timer
bool M=true;
int mx=1366/2 - 20;
int my= 768/2  ;
bool DL=false;
int Mx=mx;
int My=my;
int fps=300;
   
//----------------------------------------------------------------------------------------------------------------
void SetCanvasSize(int width, int height) {
                                              glMatrixMode(GL_PROJECTION);
                                              glLoadIdentity();
                                              glOrtho( 0 , width, 0 , height, -1, 1); 
                                              glMatrixMode( GL_MODELVIEW);
                                              glLoadIdentity();
}
//-----------------------------------------------------------------------------------------------------------------
void food(){
            
            for (int i=0 ; i<5 ; i++)
                  {        
                      b[i]=rand()%1280+30;
                      c[i]=rand()%600+40;
                      b[i]=b[i]/10;
                      c[i]=c[i]/10;
                      b[i]=b[i]*10;
                      c[i]=c[i]*10;
                  }         
}
//-------------------------------------------------------------------------------------------------------------------

void Bonusfood(){    
                  R1=rand()%1320+10;
                  R2=rand()%500+10;
                  bar=true;  
                }
//-----------------------------------------------------------------------------------------------------------------

void reset( ){

length=2;                 //  initial length
bt=0 ;                    //bonus timer  
tim=0;                    // timer for Bonus Food 
w=1366/2;
h=768/2;                 
R1=-20 , R2=-30 ;         // initial co-ordinates for bonus food 
for (int i=0 ; i<5 ; i++)
p[i]=75000;
x[0]=1366/2;
y[0]=768/2;
bfood=false;             // Boolean for bonus food 
ds=true ;                // Boolean for disappearing bonus  food
bar=false;
score=0;                      
e=0;
bar_end=400;               // bar for power food
htm=150000;      

}

//-----------------------------------------------------------------------------------------------------------------
void gameover(int n){
                if (M==false)       
                       { 
                        DrawRoundRect( -30, -30 , 1500 , 900 , colors[5]);             
                        n=score;
                        scr=num2str(n);
                        DrawString( 1360/2 , 768/2 , "Game Over" , colors[MISTY_ROSE]);
                        DrawString( 1360/2-30 , (768/2)-40, "Your Score is " , colors[MISTY_ROSE]);
                        DrawString( (1360/2)+130 , (768/2)-40, scr , colors[MISTY_ROSE]);
                        l=0;
                        e+=300;
                        if (e>=20000)
                              {
                                M=true;
                                
                              }
                        }
}

//-----------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------
void food_chk()
      {

                   for (int i=0 ; i<5 ; i++)      
                   if ( abs(x[0]-b[i])<=6 && abs(y[0]-c[i])<=6)
                    {       
                       length++;
                       score+=5;
                                 
                       
                       bfood=false;
                      for (int j=0 ; j<5 ; j++)
                      {
                       
                       int r2=rand()%500+40  ;
                       r2=r2/10;
                       r2=r2*10;
                       int r1=rand()%1300+40 ;
                       r1=r1/10;
                       r1=r1*10;
                       
                        b[i]=b[i]/10;
                        b[i]=b[i]*10;
                       
                        c[i]=c[i]/10;
                        c[i]=c[i]*10;

                      if (i!=j && b[i]!=r1 && c[i]!=r2 && b[i]-c[i]!=r1-r2 &&  b[i]+c[i]!=r1+r2 )
                      {
                      b[i]=r1;
                      c[i]=r2;
                      }
                      else
                          continue;
                      }
                   }
}
//----------------------------------------------------------------------------------------------------------------------
void B_food_chk()
                  {
                 
                   if ( abs(x[0]-R1)<=12 && abs(y[0]-R2)<=12 )
                    {       
                       length++;
                       bfood=true;
                       score+=20;
                       bt=0;
                       R1=-31;
                       R2=-41;
                       tim=0;
                       ds=true;
                       bar=false;
                       
                    }
                  }
//-----------------------------------------------------------------------------------------------------------------------
void hurdle( ){
 
             adx[0]=rand()%1000+100;
             ady[0]=rand()%450+100;
             int RN=rand()%2+1;
             switch (RN)
             {
             case 1 :
             
                   for (int i=1 ; i<size/2 ; i++)
                     {
                      adx[i]=adx[i-1]+10;
                      ady[i]=ady[i-1];
                     }
                   
                   for (int i=size/2 ; i<size ; i++)
                     {
                      adx[i]=adx[i-1];
                      ady[i]=ady[i-1]+10;
                     }
             break;
             
             case 2 :
            
                    for (int i=1 ; i<8 ; i++)
                   {
                     adx[i]=adx[i-1]+10;
                     ady[i]=ady[i-1];
                   }
                   
                   int k=2,H=10;
                   
                   for (int i=8 ; i<17 ; i++)
                   {
                     adx[i]=adx[i-k];
                     ady[i]=ady[i-k]-H;
                     k+=2;
                     H+=10;
             
                   }
                   
                    for (int j=15 ; j<22  ; j++) 
                      {
                       adx[j]=adx[j-1]+10;
                       ady[j]=ady[j-1];
                      }
              
              }
             

            }
//-------------------------------------------------------------------------------------------------------------
void exit_check (){

                     // Boundary chek
                     
                      if ( x[0]<=1 || x[0]>=1360 )
                      {
                        gameover(score);
                      }  
                      else if ( y[0]<=1 || y[0]>=640 )
                              gameover(score); 
                       
                     //snake collision            
                         
                         for (int i=3 ; i<=length ; i++ )
                         {
                            if (x[0]==x[i] && y[0]==y[i])
                              {  
                                    gameover(score);
                              }
                         }
                        
                      //hurdle check 

                      for (int i=0 ; i<size ; i++ )
                        {
                            if (abs(adx[i]-x[0])<=5 && abs(ady[i]-y[0])<=5)
                                gameover(score);
                        }    
                            
}

//-------------------------------------------------------------------------------------------------------------
void Display(){
   
                  glClearColor(0, 0.0,0.0, 0 );
                  glClear(GL_COLOR_BUFFER_BIT);   
      if (M==false && DL==false)                 
                  {                        
                        htm+=300;
                        if (htm>=150000)
                        {
                              hurdle( );
                              htm=0;
                        }
                       
                        
                      
                        for (int j=0 ; j<size ; j++ )
                                           DrawSquare( adx[j] , ady[j]   , 10 , colors[5]);
                        
                        int yellow=rand()%17+7;

                        for (int i=0 ; i<5 ; i++)
                                           DrawSquare( b[i] , c[i]   , 10 , colors[yellow]);
                              
                           
                     DrawRoundRect( x[0],  y[0] , 10 , 10 , colors[5] ,5 );

                     int rang=LIGHT_GRAY;
                     if (bfood==true)
                     rang=rand()%100+3;
                     else
                     {
                        bfood=false;
                      }
                     
                     int randcolor=rand()%100+3;
                     int rag=rand()%8+83;
                     
                      if (bar==true)
                        {
                         DrawLine( 20 , 700 , bar_end , 700 , 20 ,  colors[randcolor]);
                         bar_end-=1.5;
                        }    
                            
                     DrawCircle( R1 , R2 , 10 , colors[randcolor]);  
                     for (int i=1 ; i<=length ; i++ )
                     {
                       DrawSquare( x[i]  , y[i] , 10 ,colors[rang]);  
                     }
                      rang=100;
                      DrawString( 570 , 700 , " ~~~  SnAkE  ~~~ ", colors[MISTY_ROSE]);
                      DrawString( 1080, 700 , "Score :- ", colors[MISTY_ROSE]);

                      string scr=num2str(score);
                      DrawString( 1170 , 700 , scr , colors[MISTY_ROSE]);
                      
                      //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
                      
                      
                      for (int j=0 ; j<150 ; j++)
                      {
                        if (j%2==0)
                       {
                        
                        DrawSquare( 2  , 2+j*10 , 10 ,colors[rag]); 
                        DrawSquare(  1358 , 2+j*10  , 10 ,colors[rag]);  
                        DrawSquare( 2+j*10  , 2 , 10 ,colors[rag]);
                        DrawSquare(  2+j*10 , 650 , 10 ,colors[rag]);
                              
                       }  
                      else
                      {  
                         DrawSquare( 2  , 2+j*10 , 10 ,colors[100]);
                         DrawSquare( 1358  , 2+j*10 , 10 ,colors[100]); 
                         DrawSquare( 2+j*10  , 2 , 10 ,colors[100]);
                         DrawSquare( 2+j*10  , 650 , 10 ,colors[100]);      
                         
                      }
                     }
                    
                    exit_check();
                  }
              
              if (M==true || DL==true)
                     {        
                       
                       if (M==true){
                       DrawRoundRect( mx,  my-10 , 170 , 35 , colors[46] ,5 );
                       DrawString( mx , 768/2   , " New Game", colors[MISTY_ROSE]);
                       DrawString( mx , 768/2 - 40 , " Resume ", colors[MISTY_ROSE]);
                       DrawString( mx , 768/2 - 80 , " Difficulty Level ", colors[MISTY_ROSE]);
                       DrawString( mx , 768/2 - 120 , " High Score", colors[MISTY_ROSE]);
                       DrawString( mx , 768/2  - 160 , " Exit", colors[MISTY_ROSE]); 
                       }
                       if (DL==true){
                       DrawRoundRect( Mx,  My-10   , 170 , 35   , colors[46] ,5 );
                       DrawString( Mx , 768/2      , " Level  1 ", colors[MISTY_ROSE]);
                       DrawString( Mx , 768/2 - 40 , " Level  2 ", colors[MISTY_ROSE]);
                       DrawString( Mx , 768/2 - 80 , " Level  3 ", colors[MISTY_ROSE]);
                       
                       }
    
                     }  
                 
                  glutSwapBuffers(); 
}

//-------------------------------------------------------------------------------------------------------------------
 
void NonPrintableKeys(int key, int x_axis, int y_axis)    {
                                                if (M==false)
                                                {
                                                    if (key == GLUT_KEY_LEFT    && l!=GLUT_KEY_RIGHT)     {
		                                                l=key;			
                                                    } else if (key == GLUT_KEY_RIGHT  && l!=GLUT_KEY_LEFT){
		                                                l=key;
                                                    } else if (key == GLUT_KEY_UP && l!=GLUT_KEY_DOWN)    {
                                                            l=key;    
                                                    }else if (key == GLUT_KEY_DOWN && l!=GLUT_KEY_UP )    {
		                                                l=key;
                                                    }
                                              } 
                                              if (M==true && DL==false )
                                                   {
                                                        if (key == GLUT_KEY_UP && my<(768/2))    {
                                                            my+=40;}
                                                            else if (key == GLUT_KEY_DOWN && my>=(768/2)-120){
		                                                my-=40;}
                                                   }
                                                   
                                              else
                                                   {
                                                            
                                                            
                                                        if (key == GLUT_KEY_UP && My<(768/2) ){
                                                            My+=40;}
                                                          else if (key == GLUT_KEY_DOWN  && My>(768/2)-80 ){
		                                                My-=40;}   
                                                   
                                                   
                                                   }
                                                   
                                          
                                                     glutPostRedisplay();
}

//-------------------------------------------------------------------------------------------------------------------- 

void PrintableKeys(unsigned char key, int x, int y) {
                                                    if (key == KEY_ESC) {
                                                            M=!M;
                                                            DL=false;
                                                    }
                                                    if (M==true){   
                                                       
                                                    if (key==13 && my==768/2)
                                                                  {
                                                                     M=false;
                                                                     w=1366/2;
                                                                     h=768/2 ;
                                                                     
                                                                     reset( );                        
                                                                  }
                                                                  
                                                    else if (key==13 && my== 768/2 - 40)
                                                                  {     M=false ;} 
                                                    else if ((key==13 && my== 768/2 - 160))
                                                            {    exit(1);         }
                                                     else if (key==13 && my == 768/2 - 80)
                                                      {   
                                                       M=false;
                                                       DL=true;
                                                                                  
                                                      }
                                                    }
                                                if (DL==true)
                                                {
                                                  if (key==13 && My==768/2)
                                                  {
                                                      fps=300;                
                                                  }
                                                  else if (key==13 && My==768/2 - 40 )
                                                  fps=250;
                                                  else if  (key==13 && My==768/2 - 80)
                                                  {
                                                  fps=190;
                                                  }
                                                  
                                                }
                                                    
                                                    glutPostRedisplay();
}

//---------------------------------------------------------------------------------------------------------------------

void Timer(int m ) {
      if (M==false && DL==false)
          {
                        x[0]=w;
                        y[0]=h;
                     
                   for (int i=1 ; i<=length ; i++)
                               {
                                   tmpx=x[i];
                                   x[i]=x[i-1];
                                   x[i-1]=tmpx;
                              
                                   tmpy=y[i]   ;
                                   y[i]=y[i-1] ;
                                   y[i-1]=tmpy ;        
                               }
                               
                  if       (l==GLUT_KEY_UP )
                  {h+=10;}
                  else if  (l==GLUT_KEY_DOWN)
                  {h-=10;}
                  else if  (l==GLUT_KEY_LEFT )
                  {w-=10;}
                  else if  (l==GLUT_KEY_RIGHT)
                  {w+=10;} 
                             
                  x[0]=w;
                  y[0]=h;
                             
                    food_chk();
                    B_food_chk();
// timer 
                  for (int i=0 ; i<5 ; i++)
                   {
                         p[i]+=300;
                         
                         if (ds==true)
                       {   
                        bt+=300; 
                        bar=false;
                        bar_end=400;
                       }
                         if (ds==false)
                          tim+=300;
                          
                          if (bt>=(1450000))
                         {
                          bt=0;
                          ds=false;
                          Bonusfood( );
                         }
                         if (p[i]>=75000)
                         {
                              p[i]=0;
                              food( );
                         }
                          if (tim>=(750000/2))
                          {
                          tim=0;
                          ds=true ;
                          R1=-43;
                          R2=-78;
                          }
                        
                   } 
                  
         }
                  glutPostRedisplay();
                  glutTimerFunc(fps / FPS, Timer, 0);
}


// =======================================================================================================================
// =======================================================================================================================
// =======================================================================================================================


int main(int argc, char*argv[]) {
     x[0]=w;
     y[0]=h;
     x[1]=w;
     y[1]=h-10;
     x[2]=w;
     y[2]=h-20;
     
    int width = 1366, height = 768; // I have set my window size to be 800 x 600
    InitRandomizer();               //  seed the random number generator...
    glutInit(&argc, argv);          //   initialize the graphics library...
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(0, 0); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("Pf Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...
// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
   
    glutTimerFunc(5.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */
