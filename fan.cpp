#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
using namespace std;

#define pi 3.14

class Point{
public:
	int x,y;
	Point(int a,int b){
		x=a;
		y=b;
	}
};

Point toRadial(int rad, float angle){
	angle= angle*pi/180;
	return Point(rad*cos(angle),rad*sin(angle));
}
class Fan{
public:
	std::vector<Point> body;
	int speed=1;
	Fan(){
		body.push_back(Point(0,0));
        body.push_back(toRadial(50, 0));
        body.push_back(toRadial(50, 30));
        body.push_back(Point(0,0));
        body.push_back(toRadial(50, 120));
        body.push_back(toRadial(50, 150));
        body.push_back(Point(0,0));
        body.push_back(toRadial(50, 240));
        body.push_back(toRadial(50, 270));
        body.push_back(Point(0,0));
	
	}
	void draw(){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,0,0);
		glRotatef(speed,0,0,1);

		glBegin(GL_LINE_LOOP);
		for(int i=0; i<body.size(); i++)
			glVertex2f(body[i].x,body[i].y);
		glEnd();
		glFlush();
	}
};
Fan f;
void keyboard(unsigned char c,int x,int y){
	if(c>='0' && c<='9')
		f.speed =c-'0';	
}
void display(int){
	f.draw();
	glutTimerFunc(40,display,1);
}

int main(int argc, char  *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Rotating fan");
	gluOrtho2D(-250,250,-250,250);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	   glutKeyboardFunc(keyboard);
	glutTimerFunc(40,display,1);
	glutMainLoop();
	return 0;
}