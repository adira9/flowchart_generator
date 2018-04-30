#include "flowchart.h"

double X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
int mouse_flag = 1;
int count=0;
struct bubble bubbleArray[20];
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
void bubbleRender(struct bubble current,int x,int y)
{
    switch(current.id)
    {
        case 1: IOBubble(current.text,x,500-y);
                break;
        case 2: ProcessBubble(current.text,x,500-y);
                break;
        case 3: DecisionBubble(current.text,x,500-y);
                break;
        case 4: startBubble(current.text,x,500-y);
                break;
        case 5: YNBubble(current.text,x,500-y);
                break;
        default: break;
    }

}

void onClick(int bin,int state, int x, int y)
{
    if(bin==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        bubbleRender(bubbleArray[count],x,y);
        count++;
    }
    if(bin == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && mouse_flag <= 2) {
        if(mouse_flag == 1){
            X1 = x;
            Y1 = 500 - y;
            mouse_flag++;
        }
        else if(mouse_flag == 2){
            X2 = x;
            Y2 = 500 - y;
            mouse_flag--;
            DrawArrow(X1, Y1, X2, Y2);
            X1 = 0;
            Y1 = 0;
            X2 = 0;
            Y2 = 0;
        }

}
}

void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}
int main(int argc,char **argv)
{
    int nBubbles=0;
    printf("Enter the number of bubbles: ");
    scanf("%d",&nBubbles);
    for(int i=0;i<nBubbles;i++)
    {
        printf("Enter bubble type (1.IO , 2.Process , 3.Decision , 4.Start, 5.Y/N): ");
        scanf("%d",&bubbleArray[i].id);
        printf("Enter bubble content: ");
        gets(bubbleArray[i].text);
        gets(bubbleArray[i].text);
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Flowchart Creator");
    glutDisplayFunc(display);
    glutMouseFunc(onClick);
    myinit();
    glutMainLoop();
    return 0;
}
