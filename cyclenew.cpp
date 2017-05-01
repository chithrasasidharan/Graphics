#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;


class Point{
public:
	int x,y;
	Point(){}
	Point(int p, int q){
		x=p;
		y=q;
	}
};

class Circle: public Point{
public:
	int r;
	Point translate;
	int spokeNo=360;
	Circle(){		
	}
	Circle(int p,int q,int s){
		Point(p,q);
		r=s;
	}
	void draw(int p,int q,int s){
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<=360; i++){
			glVertex2f(p+s*cos(2*3.14*i/360)+translate.x,q+s*sin(2*3.14*i/360)+translate.y);
			if((spokeNo-i)%30==0)
				glVertex2f(p+translate.x,q);
		}
		glEnd();
		glFlush();
	}

};
std::vector<Point> path;

class Cycle{
public:
	Circle *a, *b;
	Point trans;
	int s;
	Cycle(){
		a=new Circle(120,50,40);
		b=new Circle(320,50,40);
		body.push_back(Point(120,50));
        body.push_back(Point(150,100));
        body.push_back(Point(320,50));
        body.push_back(Point(320,150));
        body.push_back(Point(280,160));
        body.push_back(Point(320,150));
        body.push_back(Point(340,170));
	}
	vector<Point>body;
	void draw(){
		a->translate=trans;
		b->translate=trans;
		a->spokeNo=s;
		b->spokeNo=s;
		a->draw(120,50,40);
		b->draw(320,50,40);
		glBegin(GL_LINE_STRIP);
		for(int i=0; i<body.size();i++)
			glVertex2f(body[i].x+trans.x,body[i].y+trans.y);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for(int i=0; i<path.size();i++)
			glVertex2f(path[i].x,path[i].y);
		glEnd();
		glFlush();
	}
};

Cycle c;
void step(){
	int k=rand()%10;
	// int m=rand()%10;+trans.x;
	c.s-=k;
	c.s%=360;
	c.trans.x+=k;
}
void keyboard(unsigned char c, int x, int y){
	if(c=='0')
		glRotatef(1,0,0,1);
	if(c=='1')
		glRotatef(1,0,0,-1);
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	c.draw();
	step();
	// glFlush();
}
void makeDelay(int){
	display();
	glutTimerFunc(40,makeDelay,1);
}
int main(int argc, char  *argv[])
{
	path.push_back(Point(50,50-100));
    path.push_back(Point(300,50-100));
    path.push_back(Point(600,150-100));
    path.push_back(Point(800,50-100));
    path.push_back(Point(1000,50-100));
	glutInit(&argc,argv);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cycle");
	gluOrtho2D(0,1000,-500,500);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutTimerFunc(40,makeDelay,1);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}