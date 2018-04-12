#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
int h,k,r;
void scanline(int,int);
void drawCircle(int);
void colorCircle(int);
 void displayCircle(void)
 {
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (1.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 colorCircle(r);
 drawCircle(r);
 glEnd();
 glFlush();
 }
 void scanline(int ax, int by)
{
 int varx;
 for(varx=h+ax ; varx>=(h-ax) ; varx--)
 glVertex2s(varx,by);
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

 glVertex3s(h,k,-25);
}
void drawCircle(int r) {
 glColor3f(1.0, 0.0, 0.0);
 glPointSize(2.0);
 float x = 0, y = r;
 float p = 1 - r;
 glBegin(GL_POINTS);
 while (y>x)
 {
  x++;
  if (p < 0) {
   p += 2 * (x + 1) + 1;
  }
  else {
   y--;
   p += 2 * (x + 1) + 1 - 2 * (y - 1);
  }
  glVertex2i(x, y);
  glVertex2i(-x, y);
  glVertex2i(x, -y);
  glVertex2i(-x, -y);

  glVertex2i(y, x);
  glVertex2i(-y, x);
  glVertex2i(y, -x);
  glVertex2i(-y, -x);

 }
 glEnd();
 glFlush();
}
 void init(void)
 {
 glClearColor (0.0, 0.0, 0.0, 0.0);
 glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
 }
int main(int argc, char** argv)
{
r=10;
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize (700, 500);
 glutInitWindowPosition (100, 100);
 //printf("Enter the center of circle:\n");
 //scanf("%d %d",&h,&k);
 h=0;
 k=0;
 //printf("Enter the radius:\n");
 //scanf("%d",&r);

 glutCreateWindow ("Circle : Scanline Filling Method ");
 init ();
 glutDisplayFunc(displayCircle);
 glutMainLoop();
 return 0;
}
