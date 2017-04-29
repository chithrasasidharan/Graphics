#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
using namespace std;

class Point{
public:
	int x,y;
	Point(){}
	Point(int p, int q){
		x = p;
		y = q;
	}
};
vector<Point>pts;
class Circle : public Point{
public:
	int rad;
	int spokeNo=360;
	Point translate;
	Circle(int p,int q, int r){
		Point(p,q);
		rad=r;
	}
	void draw(int p,int q,int r){
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<=360; i++){

			glVertex2f(p+rad*cos(i*2*3.14/360)+translate.x,q+rad*sin(i*2*3.14/360));
			if(i==spokeNo)
				glVertex2f(p+translate.x,y);
		}
		glEnd();
		glFlush();
	}
};
class Car
{
public:
		Circle *a, *b;
		int s;
		Point trans;
	Car(){
		a=new Circle(120,50,40);
		b=new Circle(320,50,40);
		pts.push_back(Point(80,50));
	    pts.push_back(Point(70,50));
		pts.push_back(Point(70,100));
		pts.push_back(Point(120,100));
		pts.push_back(Point(120,150));
		pts.push_back(Point(320,150));
		pts.push_back(Point(320,100));
		pts.push_back(Point(370,100));
		pts.push_back(Point(370,50));
		pts.push_back(Point(360,50));
		// pts.push_back(Point(280,50));
	}
	void drawCar(vector<Point>pts){
		a->draw(120,50,40);
		b->draw(320,50,40);
		a->spokeNo=s;
		b->spokeNo=s;
		a->translate = trans;
		b->translate=trans;
		glBegin(GL_LINE_STRIP);
		for(int i=0; i<pts.size();i++)
			glVertex2f(pts[i].x+trans.x,pts[i].y+trans.y);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(160+trans.x,50);
			glVertex2f(280+trans.x,50);
		glEnd();
		glFlush();
	}

	// ~Car();
	
};

	Car c;

void step(int k){
	c.trans.x+=k;
	c.s-=k;
	c.s%=360;
}
int i=1;
void display(){
	// Car c;

	c.drawCar(pts);
	// glFlush();
}
void idle(){
	glClear(GL_COLOR_BUFFER_BIT);
	step(2);
	display();
	
}

void makeDelay(int){
	idle();
	glutTimerFunc(40,makeDelay,1);
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Car race");
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutTimerFunc(40,makeDelay,1);
	glutMainLoop();
	return 0;
}