#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#define ROUND(x)((int)(x+0.5))
GLfloat x1,y1,x2,y2,x3,y3,x4,y4;
void setPixel(GLint x,GLint y)
{
 //glColor3f(255,255,255);
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 glEnd();
}
void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;
            x=x1;
            for(i=y1;i<y2;i++)
            {
                        if(x<le[i])
                                    le[i]=x;
                        if(x>re[i])
                                    re[i]=x;
                        x+=mx;
            }
}
void drawpixel(int x,int y)
{
            glColor3f(1.0,0.0,0.0);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}
void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
            int le[500],re[500];
            int i,y;
            for(i=0;i<500;i++)
            {
                        le[i]=500;
                        re[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le,re);
            edgedetect(x2,y2,x3,y3,le,re);
            edgedetect(x3,y3,x4,y4,le,re);
            edgedetect(x4,y4,x1,y1,le,re);
for(y=0;y<500;y++)
{
           if(le[y]<=re[y])
                        for(i=le[y]+1;i<re[y];i++)
                                        drawpixel(i,y);
}
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

void display()
{
            glClear(GL_COLOR_BUFFER_BIT);
            //x1=100,y1=100,x2=200,y2=200,x3=100,y3=400,x4=0,y4=200;
Linemp(x1,y1,x2,y2);
Linedda(x2,y2,x3,y3);
Linemp(x3,y3,x4,y4);
Linedda(x4,y4,x1,y1);
    glEnd();
   scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
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
{          glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
            glutInitWindowSize(500,500);
            glutInitWindowPosition(0,0);
            glutCreateWindow("scanfill");
            //printf("Enter 4 vertices;");
            //scanf("%f %f %f %f %f %f %f %f",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
            x1=0;
            y1=0;
            x2=100;
            y2=0;
            x3=100;
            y3=100;
            x4=0;
            y4=100;
            glutDisplayFunc(display);
            myinit();
            glutMainLoop();
            return 0;
   }
