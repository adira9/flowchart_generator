#include "algos.h"

void RenderBitmap(float x,float y, void *font, char *string)
{
    char *c;
    glRasterPos2f(x,y);
    for(c=string;*c!='\0';c++)
    {
        glutBitmapCharacter(font,*c);
    }
    glFlush();

}

struct bubble
{
    char text[30];
    int id;
};

void startBubble(char *text, double Centre_x,double Centre_y)
{
    glColor3f(0.0f,0.0f,0.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    int text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    drawCircle(text_length/1.5,Centre_x,Centre_y);
    glColor3f(0.0f,0.0f,0.0f);
    RenderBitmap(Centre_x-text_length/2,Centre_y-25/8,GLUT_BITMAP_TIMES_ROMAN_10,buf);
}

void YNBubble(char *text, double Centre_x, double Centre_y)
{
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    int text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    colorEllipse(text_length,text_length*1.5,Centre_x, Centre_y);
    ellipseMidpoint(text_length,text_length*1.5,Centre_x, Centre_y);
    glColor3f(0.0f,0.0f,0.0f);
    RenderBitmap(Centre_x-text_length/2,Centre_y-25/4,GLUT_BITMAP_TIMES_ROMAN_10,buf);
}

void DecisionBubble(char *text, double Centre_x, double Centre_y)
{
  glColor3f(1.0f,1.0f,1.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    int text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    drawDiamond(text_length*1.414, Centre_x,Centre_y);
    glColor3f(0.0f,0.0f,0.0f);
    RenderBitmap(Centre_x-text_length/2,Centre_y-25/4,GLUT_BITMAP_TIMES_ROMAN_10,buf);
}

void IOBubble(char *text, double Centre_x, double Centre_y)
{
    glColor3f(0.0f,0.0f,0.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    int text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    drawPara(text_length*1.5,25,Centre_x,Centre_y);
    glColor3f(0.0f,0.0f,0.0f);
    RenderBitmap(Centre_x-text_length/2,Centre_y-25/4,GLUT_BITMAP_TIMES_ROMAN_10,buf);
    glFlush();
}

void ProcessBubble(char *text, double Centre_x, double Centre_y)
{
    glColor3f(1.0f,1.0f,1.0f);
    char buf[100]={0};
    const unsigned char *ptr=(unsigned char*)&buf[0];
    sprintf(buf,text);
    int text_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,ptr);
    drawRectangle(text_length*2,25,Centre_x,Centre_y);
    glColor3f(0.0f,0.0f,0.0f);
    RenderBitmap(Centre_x-text_length/2,Centre_y-25/4,GLUT_BITMAP_TIMES_ROMAN_10,buf);
}

