#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

int x1=50,yp=-50,x2=-50,y2=-100;

void display(){
	int dx = x2-x1;
	int dy = y2-yp;
	int x=x1;
	int y=yp;
	int steps;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	float xinc=dx/steps;
	float yinc = dy/steps;
	glBegin(GL_POINTS);
	for(int i=0; i<steps; i++){

		x=x+xinc;
		y+=yinc;
		glVertex2f(x,y);
	}
	glEnd();
	glFlush();
}

void bresenham(){
	int dx = x2-x1;
	int dy = y2-yp;
	int x=x1;
	int y=yp;

	int inc=1;
	int sinc = 1;
	if(abs(dx)>abs(dy))
	{
		if (dx<0)
			sinc=-1;

			if(dy<0){
				inc=-1;
				dy=-dy;
			}
			int p=2*dy-dx;
			while(x!=x2){
				x+=sinc;
				if(p<0)
					p+=2*dy;
				else{
					y+=inc;
					p+=2*(dy-dx);
				}
				glBegin(GL_POINTS);
				glVertex2f(x,y);
				glEnd();
			}
	}
	else
	{
		if(dy<0)
			sinc=-1;
		if(dx<0){
			inc=-1;
			dx=-dx;
		}
		int p=2*dx-dy;
		while(y!=y2){
			y+=sinc;
			if(p<0)
				p+=2*dx;
			else{
				x+=inc;
				p+=2*(dx-dy);
			}
			glBegin(GL_POINTS);
			glVertex2f(x,y);
			glEnd();
			
		}

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
	glutDisplayFunc(bresenham);
	glutMainLoop();
	return 0;
}