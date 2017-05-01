#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

int xc=50,yc=50,r=50;
void bresenham(){
	int x=0;
	int y=r;
	int d=3-2*r;
	while(x<y){
		glBegin(GL_POINTS);
			glVertex2f(x+xc,y+yc);
			glVertex2f(-x+xc,y+yc);
			glVertex2f(x+xc,-y+yc);
			glVertex2f(-x+xc,-y+yc);
			glVertex2f(y+xc,x+yc);
			glVertex2f(-y+xc,x+yc);
			glVertex2f(y+xc,-x+yc);
			glVertex2f(-y+xc,-x+yc);
		glEnd();
		x++;
		if(d<0)
			d = d+4*x+6;
		else{
			y-=1;
			d = d+4*(x-y)+10;
		}
	}
	glFlush();

}

void midpoint(){
	int p = 1-r;
	int x=0;
	int y=r;
	while(x++<=y){
		if(p<0)
			p+=2*x+1;
		else{
			y-=1;
			p+=2*(x-y)+3;
		}
		glBegin(GL_POINTS);
			glVertex2f(x+xc,y+yc);
			glVertex2f(-x+xc,y+yc);
			glVertex2f(x+xc,-y+yc);
			glVertex2f(-x+xc,-y+yc);
			glVertex2f(y+xc,x+yc);
			glVertex2f(-y+xc,x+yc);
			glVertex2f(y+xc,-x+yc);
			glVertex2f(-y+xc,-x+yc);
		glEnd();

	}
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Line");
	gluOrtho2D(-250,250,-250,250);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glutDisplayFunc(midpoint);
	glutMainLoop();
	return 0;
}