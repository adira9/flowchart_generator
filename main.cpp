#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int value = 0; // used in timer function
int tx, ty; // translation vector
int n = 4; // no. of vertices
//int points_list[4][2] = {{-50, 0}, {0, 100}, {50, 0}, {0, -100}};
int points_list[4][2]; // list of vertices (x, y)
int x[4], y[4]; // used for scaling
int refreshtime = 100; //milliseconds
int xc, yc; // actual center
int dist1; //passed from sony (diagonal or length)
int dist2; //width (0 for rhombus)
int len, wid; // len = dist1 / 2; wid = dist2 / 2;
int xctemp, yctemp; // temporary center
int sx = 10, sy = 10; //scaling matrix

void init(void)
{
 glClearColor(0.0,0.0,0.0,1.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(-250.0,250.0,-250.0,250.0);
}

void findNewCoordinate(int s[][2], int p[][1])
{
    int temp[2][1] = { 0 };

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 1; j++)
            for (int k = 0; k < 2; k++)
                temp[i][j] += (s[i][k] * p[k][j]);

    p[0][0] = temp[0][0];
    p[1][0] = temp[1][0];
}

// Scaling the Polygon
void scale(int x[], int y[], int sx, int sy)
{
    int i;
    glBegin(GL_LINE_LOOP);
    for(i=0;i<n;i++){
        glColor3f(0,0,1);
        glVertex3f(x[i], y[i], 0.0);
        printf("doing.....\n");
    }
    glEnd();
    printf("scale entered\n");
    // Initializing the Scaling Matrix.
    int s[2][2] = { sx, 0, 0, sy };
    int p[2][1];

    // Scaling the triangle
    for (int i = 0; i < n; i++)
    {
        p[0][0] = x[i];
        p[1][0] = y[i];

        findNewCoordinate(s, p);

        x[i] = p[0][0];
        y[i] = p[1][0];
    }

    glBegin(GL_LINE_LOOP);
    for(i=0;i<n;i++){
        glColor3f(1,0,0);
        glVertex3f(x[i], y[i], 0.0);
        printf("done\n");
    }
    glEnd();
}

void timer(int value)
{
   //printf("itr: %d\n", iterations);
   glutPostRedisplay();
   if (xctemp <= xc && yctemp <= yc) {
      glutTimerFunc(refreshtime, timer, value);
      if(xctemp == xc && yctemp == yc){
        printf("%d %d\n", xc, yc);
        int i;
        for(i=0;i<n;i++){
            x[i] = points_list[i][0];
            y[i] = points_list[i][1];
        }
        for(i=0;i<n;i++){
            printf("%d %d\n", x[i], y[i]);
        }
        //scale(x, y, sx,sy);
      }
      xctemp = xctemp;
      yctemp = yctemp + ty;
   }
   else{
    return;
   }
}

void plot(GLint x,GLint y)
{
 glBegin(GL_POINTS);
 glVertex2i(x,y);
 glEnd();
}

void translate(int x,int y,int tx,int ty)
{
    //printf("%d %d", x+tx, y+ty);
    glColor3f (0.0, 1.0, 0.0);
    plot(x+tx,y+ty);
    glColor3f (255.0, 255.0, 255.0);
}

int round1(double number)
{
 return (number>=0) ? (int)(number+0.5):(int)(number-0.5);
}

void dda(int x0,int y0,int x1,int y1)
{
 int dy=y1-y0;
 int dx=x1-x0;
 int steps,i;
 float xinc,yinc,x=x0,y=y0;
 if(abs(dx)>abs(dy))
 {
  steps=abs(dx);
 }
 else
 {
  steps=abs(dy);
 }
 xinc=(float)dx/(float)steps;
 yinc=(float)dy/(float)steps;
 //plot(round1(x),round1(y));
 translate(round1(x),round1(y),tx,ty);
 for(i=0;i<steps;i++)
 {
  x+=xinc;
  y+=yinc;
  //plot(round1(x),round1(y));
  translate(round1(x),round1(y),tx,ty);
 }
 glutSwapBuffers();
}

void draw()
{
 glClear(GL_COLOR_BUFFER_BIT);
 int i;
 for(i=0;i<n-1;i++)
    dda(points_list[i][0], points_list[i][1], points_list[i+1][0], points_list[i+1][1]);
 dda(points_list[i][0], points_list[i][1], points_list[0][0], points_list[0][1]);
 // after translation
 for(i=0;i<n;i++){
    points_list[i][0] = points_list[i][0] + tx;
    points_list[i][1] = points_list[i][1] + ty;
 }

 glFlush();
}
int main(int argc,char **argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowPosition(50,50);
 glutInitWindowSize(500,500);
 tx = 0;
 ty = 5;
 xc = 0;
 yc = 0;
 dist1 = 80;
 dist2 = 60;
 len = dist1 / 2;
 wid = dist2 / 2;
 xctemp = xc;
 yctemp = -250 + len;

 //rhombus
 /*
 points_list[0][0] = xctemp;
 points_list[0][1] = yctemp - len;
 points_list[1][0] = xctemp - len;
 points_list[1][1] = yctemp;
 points_list[2][0] = xctemp;
 points_list[2][1] = yctemp + len;
 points_list[3][0] = xctemp + len;
 points_list[3][1] = yctemp;
*/
 // rectangle

 points_list[0][0] = xctemp - len;
 points_list[0][1] = yctemp - wid;
 points_list[1][0] = xctemp - len;
 points_list[1][1] = yctemp + wid;
 points_list[2][0] = xctemp + len;
 points_list[2][1] = yctemp + wid;
 points_list[3][0] = xctemp + len;
 points_list[3][1] = yctemp - wid;


 glutCreateWindow("polygon translation..");
 init();
 glutTimerFunc(100, timer, value);
 glutDisplayFunc(draw);
 glutMainLoop();
 return 0;
}
