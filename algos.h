#include<fstream>
#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

#define ROUND(x) ((int)(x+0.5))

using namespace std;


float round_value(float v)
{
  return floor(v + 0.5);
}

void LineDDL(double X0,double Y0, double X1, double Y1) // P0-P1 line.
{
  double dx=(X1-X0);
  double dy=(Y1-Y0);
  double steps;
  float xInc,yInc,x=X0,y=Y0;
  /* Find out whether to increment x or y */
  steps=(fabs(dx)>fabs(dy))?(fabs(dx)):(fabs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;

  glPointSize(0.75);
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_POINTS);
  glVertex2d(x,y);
  int k;
  /* For every step, find an intermediate vertex */
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    glVertex2d(round_value(x), round_value(y));
  }
  glEnd();
  glFlush();
}

void DrawArrow(float x1, float y1, float x2, float y2) //Draws an arrow from x1,y1 to x2,y2.
{
glColor3f(0.0,0.0,0.0);

float dx = x2 - x1;
float dy = y2 - y1;
//Vector length.
float length = sqrt(dx*dx + dy*dy);
//Vector components.
float vdx = dx / length;
float vdy = dy / length;
//Perpendicular vector.
float px = -vdy;
float py = vdx;

//Points forming the arrow head with length 4 and height 3 from the main line.

float leftx = x2 - 4*vdx + 3*px;
float lefty = y2 - 4*vdy + 3*py;
float rightx = x2 - 4*vdx - 3*px;
float righty = y2 - 4*vdy - 3*py;

//Line tip.
LineDDL(x2,y2,leftx,lefty);
LineDDL(x2,y2,rightx,righty);
//The main line.
LineDDL(x1,y1,x2,y2);
glFlush();
}

void setPixel(GLint x,GLint y)
{
 glBegin(GL_POINTS);
 glColor3f(0.0,0.0,0.0);
 glVertex2f(x,y);
 glEnd();
}
void Linemp(int x0,int y0,int xn,int yn)
{
 int x,y,dx,dy,pk;
 setPixel(x0,y0);
 dx=xn-x0;
 dy=yn-y0;
 pk=2*dy-dx;
 x=x0;
 y=y0;
while(x<xn)
 {
  if(pk<0)
  {
   pk=pk+2*dy;
  }
  else
  {
   pk=pk+2*dy-2*dx;
   ++y;
  }
  ++x;
  setPixel(x,y);
 }

}


void Linedda(int x0,int y0,int xn,int yn)
{
 int dx=xn-x0,dy=yn-y0,steps,k;
 float xIncrement,yIncrement,x=x0,y=y0;
 if(abs(dx)>abs(dy))
 steps=abs(dx);
 else steps=abs(dy);
 xIncrement=dx/(float)steps;
 yIncrement=dy/(float)steps;
 setPixel(ROUND(x),ROUND(y));
for(k=0;k<steps;k++)
 {
 x+=xIncrement;
 y+=yIncrement;
 setPixel(ROUND(x),ROUND(y));

 }
 }


//__________________________________________Start Bubble Starts___________________________
void scanline(int ax, int by, double X, double Y)
{
 int varx;
 glColor3f(0.9,1.0,0.93);
 for(varx=X+ax ; varx>=(X-ax) ; varx--)
 glVertex2s(varx,by+Y);
}

void colorCircle(int r, double X, double Y)
{
 double XEnd,J;
 int i,j;
 XEnd=(r/1.414);
 for( i=0 ; i<=XEnd ; i++)
 {
 J=sqrt(r*r - i*i);
 j=(int)(J);
 scanline(i, j, X, Y);
 scanline(j, i,X,Y);
 scanline(j,-i, X, Y);
 scanline(i,-j,X, Y);
 }
 glVertex3s(X,Y,-25);
}


void drawcircle(double r, double X, double Y) {
 glColor3f(0.0, 0.0, 0.0);
 glPointSize(2.0);
 double x = 0, y = r;
 double p = 1 - r;
 glBegin(GL_POINTS);
 while (y>x) {
  x++;
  if (p < 0) {
   p += 2 * (x + 1) + 1;}
  else {
   y--;
   p += 2 * (x + 1) + 1 - 2 * (y - 1);}
  glVertex2i(x+X, y+Y);
  glVertex2i(-x+X, y+Y);
  glVertex2i(x+X, -y+Y);
  glVertex2i(-x+X, -y+Y);

  glVertex2i(y+X, x+Y);
  glVertex2i(-y+X, x+Y);
  glVertex2i(y+X, -x+Y);
  glVertex2i(-y+X, -x+Y);}
 glEnd();
 glFlush();}

void drawCircle(double r,double X, double Y)
 {
 glColor3f (1.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 colorCircle(r,X,Y);
 drawcircle(r,X,Y);
 glEnd();
 glFlush();
 }

 //_______________________________________Start Bubble Ends - YN Bubble Starts_____________________________

 void setPixelEll(GLint x,GLint y)
{
 glBegin(GL_POINTS);
 glColor3f(0.87,1.0,1.0);
 glVertex2f(x,y);
 glEnd();
}

 void Ellipsedda(int x0,int y0,int xn,int yn)
{
 int dx=xn-x0,dy=yn-y0,steps,k;
 float xIncrement,yIncrement,x=x0,y=y0;
 glColor3f (0.87, 1.0, 1.0);
 if(abs(dx)>abs(dy))
 steps=abs(dx);
 else steps=abs(dy);
 xIncrement=dx/(float)steps;
 yIncrement=dy/(float)steps;
 setPixelEll(ROUND(x),ROUND(y));
for(k=0;k<steps;k++)
 {
 x+=xIncrement;
 y+=yIncrement;
 setPixelEll(ROUND(x),ROUND(y));

 }
 }

 void drawEllipse(float x, float y, double X, double Y)
{
    int p1[] = {(int)X+x, (int)Y+y};
    int p2[] = {(int)X-x, (int)Y+y};
    int p3[] = {(int)X+x, (int)Y-y};
    int p4[] = {(int)X-x, (int)Y-y};
    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2iv(p1);
    glVertex2iv(p2);
    glVertex2iv(p3);
    glVertex2iv(p4);
    glEnd();
}

void ellipseMidpoint(float rx, float ry, double X, double Y)
{
    float rxSq = rx * rx;
    float rySq = ry * ry;
    float x = 0, y = ry, p;
    float px = 0, py = 2 * rxSq * y;
    drawEllipse(x, y, X, Y);

    p = rySq - (rxSq * ry) + (0.25 * rxSq);
    while (px < py)
    {
        x++;
        px = px + 2 * rySq;
        if (p < 0)
            p = p + rySq + px;
        else
        {
            y--;
            py = py - 2 * rxSq;
            p = p + rySq + px - py;
        }
        drawEllipse(x, y, X, Y);
    }

    p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
    while (y > 0)
    {
        y--;
        py = py - 2 * rxSq;
        if (p > 0)
            p = p + rxSq - py;
        else
        {
            x++;
            px = px + 2 * rySq;
            p = p + rxSq - py + px;
        }
        drawEllipse(x, y, X, Y);
    }
}
void colorEllipse(float rx,float ry, double X, double Y){
float i;
float yco,xco;
float x=X,y=Y;

for(i=-rx;i<=rx;i++){
    yco=(ry*(sqrt(pow(rx,2)-pow(i,2))))/rx;
    Ellipsedda(i+x,-yco+y,i+x,yco+y);
    Ellipsedda(-i+x,-yco+y,-i+x,yco+y);
}
for(i=-ry;i<=ry;i++){
    xco=(rx*(sqrt(pow(ry,2)-pow(i,2))))/ry;
    Ellipsedda(-xco+x,i+y,xco+x,i+y);
    Ellipsedda(-xco+x,-i+y,xco+x,-i+y);
}
}

//________________________YN Bubble Ends - Decision Bubble starts__________________________

void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le1,int *re1,int *le2,int *re2)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)
            {
              temp=x1;
              x1=x2;
              x2=temp;

              temp=y1;
              y1=y2;
              y2=temp;
            }

            if((y2-y1)!=0)
                mx=(x2-x1)/(y2-y1);
            else
                mx=x2-x1;

            x=x1;

            for(i=y1;i<y2;i++)
            {
                if(le2[i]<2 && re2[i]<2){
                if(x<le1[i])
                {
                    le1[i]=x;
                    le2[i]++;
                    if(le2[i]==2){
                        le2[i]=500;
                        re2[i]=0;}
                }
                if(x>re1[i])
                {
                    re1[i]=x;
                    re2[i]++;
                    if(re2[i]==2){
                        le2[i]=500;
                        re2[i]=0;}
                }}
                else
                {
                    if(x<le2[i])
                    {
                    le2[i]=x;
                    }
                    if(x>re2[i])
                    {
                    re2[i]=x;
                    }

                }
                x+=mx;
            }
}
void drawpixel(int x,int y)
{
            glColor3f(1.0,1.0,0.8);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
            int le1[500],re1[500],le2[500],re2[500];
            int i,y;
            for(i=0;i<500;i++)
            {
                        le1[i]=500;
                        re1[i]=0;
                        le2[i]=0;
                        re2[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le1,re1,le2,re2);
            edgedetect(x2,y2,x3,y3,le1,re1,le2,re2);
            edgedetect(x3,y3,x4,y4,le1,re1,le2,re2);
            edgedetect(x4,y4,x1,y1,le1,re1,le2,re2);


            for(y=0;y<500;y++)
            {
                if(le1[y]<=re1[y])
                    for(i=le1[y]+1;i<re1[y];i++)
                        drawpixel(i,y);
                if(le2[y]>2 && re2[y]>2)
                    for(i=le2[y]+1;i<re2[y];i++)
                        drawpixel(i,y);
            }
}


void drawDiamond(double d, double X, double Y)
{
Linedda(X-ROUND(d/2),Y,X,Y+ROUND(d/2));
Linedda(X,Y+ROUND(d/2),X+ROUND(d/2),Y);
Linedda(X,Y-ROUND(d/2),X+ROUND(d/2),Y);
Linedda(X,Y-ROUND(d/2),X-ROUND(d/2),Y);
scanfill(X-ROUND(d/2),Y,X,Y+ROUND(d/2),X+ROUND(d/2),Y,X,Y-ROUND(d/2));
glFlush();
}

//__________________________Decision Bubble Ends - IO Bubble Starts_________________________

void drawpixelIO(int x,int y)
{
            glColor3f(1.0,0.90,1.0);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}

void scanfillIO(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
            int le1[500],re1[500],le2[500],re2[500];
            int i,y;
            for(i=0;i<500;i++)
            {
                        le1[i]=500;
                        re1[i]=0;
                        le2[i]=0;
                        re2[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le1,re1,le2,re2);
            edgedetect(x2,y2,x3,y3,le1,re1,le2,re2);
            edgedetect(x3,y3,x4,y4,le1,re1,le2,re2);
            edgedetect(x4,y4,x1,y1,le1,re1,le2,re2);


            for(y=0;y<500;y++)
            {
                if(le1[y]<=re1[y])
                    for(i=le1[y]+1;i<re1[y];i++)
                        drawpixelIO(i,y);
                if(le2[y]>2 && re2[y]>2)
                    for(i=le2[y]+1;i<re2[y];i++)
                        drawpixelIO(i,y);
            }
}


void drawPara(double Side_length, int height,double X,double Y)
{
    float space=height*0.7;
    glColor3f(0.0,0.0,0.0);
    scanfillIO(X-(Side_length/2),Y+height/2,X+(Side_length/2)+space+10,Y+height/2,X+Side_length/2+10,Y-height/2,X-(Side_length/2)-space,Y-height/2);
    Linedda(X-(Side_length/2),Y+height/2,X+(Side_length/2)+space+10,Y+height/2);
    Linedda(X+(Side_length/2)+space+10,Y+height/2,X+Side_length/2+10,Y-height/2 );
    Linedda(X-(Side_length/2)-space,Y-height/2,X+(Side_length/2)+10,Y-height/2);
    Linedda(X-(Side_length/2)-space,Y-height/2,X-Side_length/2,Y+height/2);
    glFlush();
}

//__________________________IO Bubble Ends - Process Bubble Starts___________________________

void drawpixelP(int x,int y)
{
            glColor3f(0.90,0.97,0.77);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}

void scanfillP(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
            int le1[500],re1[500],le2[500],re2[500];
            int i,y;
            for(i=0;i<500;i++)
            {
                        le1[i]=500;
                        re1[i]=0;
                        le2[i]=0;
                        re2[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le1,re1,le2,re2);
            edgedetect(x2,y2,x3,y3,le1,re1,le2,re2);
            edgedetect(x3,y3,x4,y4,le1,re1,le2,re2);
            edgedetect(x4,y4,x1,y1,le1,re1,le2,re2);


            for(y=0;y<500;y++)
            {
                if(le1[y]<=re1[y])
                    for(i=le1[y]+1;i<re1[y];i++)
                        drawpixelP(i,y);
                if(le2[y]>2 && re2[y]>2)
                    for(i=le2[y]+1;i<re2[y];i++)
                        drawpixelP(i,y);
            }
}

void drawRectangle(int a,int b,double X, double Y)
{
    scanfillP(X-ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y-ROUND(b/2),X-ROUND(a/2),Y-ROUND(b/2));
    Linedda(X-ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y+ROUND(b/2));
    Linedda(X+ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y-ROUND(b/2));
    Linedda(X-ROUND(a/2),Y-ROUND(b/2),X+ROUND(a/2),Y-ROUND(b/2));
    Linedda(X-ROUND(a/2),Y-ROUND(b/2),X-ROUND(a/2),Y+ROUND(b/2));
    glFlush();
}

//_____________________________________Process Bubble Ends_________________________

