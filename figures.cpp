#include<fstream>
#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define ROUND(x) ((int)(x+0.5))
using namespace std;
char *text="Textin";
//GLfloat x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
double X,Y;
int a,b;
int text_length;

void setPixel(GLint x,GLint y)
{
 //glColor3f(255,255,255);
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 glEnd();
}
void Linemp(int x0,int y0,int xn,int yn)
{
 int x,y,dx,dy,pk;

 glColor3f(1,0,0);
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
void Linedda(int x0,int y0,int xn,int yn){
 int dx=xn-x0,dy=yn-y0,steps,k;
 float xIncrement,yIncrement,x=x0,y=y0;
 glColor3f (1.0, 0.0, 0.0);
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
            //glColor3f(0.0,0.5,1.0);
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
void drawRectangle(int a,int b){
glClear(GL_COLOR_BUFFER_BIT);
Linemp(X-ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y+ROUND(b/2));
Linedda(X+ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y-ROUND(b/2));
Linemp(X-ROUND(a/2),Y-ROUND(b/2),X+ROUND(a/2),Y-ROUND(b/2));
Linedda(X-ROUND(a/2),Y-ROUND(b/2),X-ROUND(a/2),Y+ROUND(b/2));
glColor3f(0.0,0.5,1.0);
scanfill(X-ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y+ROUND(b/2),X+ROUND(a/2),Y-ROUND(b/2),X-ROUND(a/2),Y-ROUND(b/2));
glFlush();
}
void drawPara(double Side_length, int height) //count = length of the string. space = space b/w the shape and the string.
{glClear(GL_COLOR_BUFFER_BIT);
    Side_length=Side_length;
    float space=height*0.7;
    glColor3f(1.0,1.0,1.0);
    Linedda(X-(Side_length/2),Y+height/2,X+(Side_length/2)+space+10,Y+height/2); //A-B
    Linedda(X+(Side_length/2)+space+10,Y+height/2,X+Side_length/2+10,Y-height/2 );//B-C
    Linedda(X-(Side_length/2)-space,Y-height/2,X+(Side_length/2)+10,Y-height/2);//C-D
    Linedda(X-(Side_length/2)-space,Y-height/2,X-Side_length/2,Y+height/2);//D-A
    scanfill(X-(Side_length/2),Y+height/2,X+(Side_length/2)+space+10,Y+height/2,X+Side_length/2+10,Y-height/2,X-(Side_length/2)-space,Y-height/2);

glFlush();
}
void drawDaimond(double d){
glClear(GL_COLOR_BUFFER_BIT);
Linemp(X-ROUND(d/2),Y,X,Y+ROUND(d/2));
Linedda(X,Y+ROUND(d/2),X+ROUND(d/2),Y);
Linemp(X,Y-ROUND(d/2),X+ROUND(d/2),Y);
Linedda(X,Y-ROUND(d/2),X-ROUND(d/2),Y);
scanfill(X-ROUND(d/2),Y,X,Y+ROUND(d/2),X+ROUND(d/2),Y,X,Y-ROUND(d/2));
glFlush();
}

void drawcircle(double r) {
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

void scanline(int ax, int by)
{
 int varx;
 for(varx=X+ax ; varx>=(X-ax) ; varx--)
 glVertex2s(varx,by+Y);
 //printf("X=%d  Y=%d",&X,&Y);
}
void colorCircle(int r)
{
 double XEnd,J;
 int i,j;
 XEnd=(r/1.414);
 for( i=0 ; i<=XEnd ; i++)
 {
 J=sqrt(r*r - i*i);
 j=(int)(J);
 scanline(i, j);
 scanline(j, i);
 scanline(j,-i);
 scanline(i,-j);
 }
 glVertex3s(X,Y,-25);
}

void drawCircle(double r)
 {
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (1.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 colorCircle(r);
 drawcircle(r);
 glEnd();
 glFlush();
 }

 void plotEllipse(float x, float y)
{
    int p1[] = {(int)X+x, (int)Y+y};
    int p2[] = {(int)X-x, (int)Y+y};
    int p3[] = {(int)X+x, (int)Y-y};
    int p4[] = {(int)X-x, (int)Y-y};
    glColor3f (1.0, 1.0, 1.0);
    glVertex2iv(p1);
    glVertex2iv(p2);
    glVertex2iv(p3);
    glVertex2iv(p4);
}

void drawellipse(float rx, float ry)
{
    float rxSq = rx * rx;
    float rySq = ry * ry;
    float x = 0, y = ry, p;
    float px = 0, py = 2 * rxSq * y;
    drawellipse(x, y);

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
        plotEllipse(x, y);
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
        plotEllipse(x, y);
    }
}

void colorEllipse(float rx,float ry){
float i;
float yco,xco;
for(i=-rx;i<=rx;i++){
    yco=(ry*(sqrt(pow(rx,2)-pow(i,2))))/rx;
    Linedda(i,-yco,i,+yco);
    Linedda(-i,-yco,-i,+yco);
}
}

 void drawEllipse(double rx,double ry)
 {
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (1.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 drawellipse(rx,ry);
colorEllipse(rx,ry);
 glEnd();
 glFlush();
 }

void RenderBitmap(float x,float y, void *font, char *string)
{
    char *c;
    glRasterPos2f(x,y);
    for(c=string;*c!='\0';c++)
    {
        glutBitmapCharacter(font,*c);
    }

}

void PgramBubble(char *text)
{
  glColor3f(1.0f,1.0f,1.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    //printf("%s",text);
    //printf("%d\n",glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr));
    text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    //printf("%d\n",glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]));
    drawPara(text_length*2.5,100);
    glColor3f(0.0f,0.0f,0.0f);
   RenderBitmap(X-text_length,Y-50/4,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}
void RectangleBubble(char *text)
{
  glColor3f(1.0f,1.0f,1.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    //printf("%s",text);
    //printf("%d\n",glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr));
    text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    //printf("%d\n",glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]));
    drawRectangle(text_length*2.5,100);
    glColor3f(0.0f,0.0f,0.0f);
   RenderBitmap(X-text_length,Y-50/4,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}
void DaimondBubble(char *text)
{
  glColor3f(1.0f,1.0f,1.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    //printf("%s",text);
    //printf("%d\n",glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr));
    text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    //printf("%d\n",glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]));
drawDaimond(text_length*2.5);
glColor3f(0.0f,0.0f,0.0f);
   RenderBitmap(X-text_length,Y-50/4,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}
void CircleBubble(char *text)
{
  glColor3f(1.0f,1.0f,1.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    //printf("%s",text);
    //printf("%d\n",glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr));
    text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    //printf("%d\n",glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]));
drawCircle(text_length*2.5);
glColor3f(0.0f,0.0f,0.0f);
   RenderBitmap(X-text_length,Y-50/4,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}
void EllipseBubble()
{
    char *text1="START";
  glColor3f(1.0f,1.0f,1.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text1);
    //printf("%s",text);
    //printf("%d\n",glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr));
    text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    //printf("%d\n",glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]));
drawEllipse(text_length*10.0,text_length*1);
glColor3f(0.0f,0.0f,0.0f);
   //RenderBitmap(X-text_length,Y-50/4,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}

void display()
{
            glClear(GL_COLOR_BUFFER_BIT);
            //a=50;
            //b=20;
            //x1=200,y1=200,x2=100,y2=300,x3=200,y3=400,x4=300,y4=300;
           // x1=100,y1=100,x2=400,y2=100,x3=400,y3=400,x4=250,y4=300;

            //drawRectangle(a,b);
            //CircleBubble(text);
            CircleBubble(text);

   glEnd();
   glFlush();
}
void myinit()
{
            glClearColor(1.0,1.0,1.0,1.0);
            glColor3f(0.0,0.0,1.0);
            glPointSize(1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc,char **argv)
{           glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
            glutInitWindowSize(500,500);
            glutInitWindowPosition(0,0);
            X=300;
            Y=300;
            glutCreateWindow("Circle");
            glutDisplayFunc(display);
            myinit();
            glutMainLoop();
            return 0;
   }
