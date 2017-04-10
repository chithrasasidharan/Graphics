#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
using namespace std;
int x1=120,x2=320,y2=50,r=40;
int tx1=0,tx2=0,ty=200;
int spokeNo1=360;
int spokeNo2=360;

class Point{
public:
	int x,y;
	Point(){}
	Point(int p,int q){
		x=p;
		y=q;
	}
};

vector <Point> pts;
vector <Point> pt;

void getPoints(){
	 pts.push_back(Point(80,50));
    pts.push_back(Point(70,50));
    pts.push_back(Point(70,50));
	pts.push_back(Point(70,100));
	pts.push_back(Point(70,100));
	pts.push_back(Point(120,100));
	pts.push_back(Point(120,100));
	pts.push_back(Point(120,150));
	pts.push_back(Point(120,150));
	pts.push_back(Point(320,150));
	pts.push_back(Point(320,150));
	pts.push_back(Point(320,100));
	pts.push_back(Point(320,100));
	pts.push_back(Point(370,100));
	pts.push_back(Point(370,100));
	pts.push_back(Point(370,50));
	pts.push_back(Point(370,50));
	pts.push_back(Point(360,50));
	pts.push_back(Point(160,50));
	pts.push_back(Point(280,50));
}

void display(){
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		for(int i=0; i<=360; i++){
			glVertex2f(x1+r*cos(i*2*3.14/360)+tx1,y2+r*sin(i*2*3.14/360));
			if(i==spokeNo1)
				glVertex2f(x1+tx1,y2);
		}
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		for(int i=0; i<=360; i++){
			glVertex2f(x2+r*cos(i*2*3.14/360)+tx1,y2+r*sin(i*2*3.14/360));
			if(i==spokeNo1)
				glVertex2f(x2+tx1,y2);
		}
	glEnd();
	glBegin(GL_LINE_LOOP);
	// glBegin(GL_POINTS);
		for(int i=0; i<=360; i++){
			glVertex2f(x1+r*cos(i*2*3.14/360)+tx2,y2+r*sin(i*2*3.14/360)+ty);
			if(i==spokeNo2)
				glVertex2f(x1+tx2,y2+ty);
		}
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0; i<=360; i++){
			glVertex2f(x2+r*cos(i*2*3.14/360)+tx2,y2+r*sin(i*2*3.14/360)+ty);
			if(i==spokeNo2)
				glVertex2f(x2+tx2,y2+ty);
		}
			
	glEnd();
	glBegin(GL_LINES);
		for(int i=0; i<pts.size()-2; i++)
			glVertex2f(pts[i].x+tx2,pts[i].y+ty);
		for(int i=0; i<pts.size()-2; i++)
			glVertex2f(pts[i].x+tx1,pts[i].y);
	glEnd();
	glBegin(GL_LINES);
		for(int i=pts.size()-2; i<pts.size(); i++)
			glVertex2f(pts[i].x+tx2,pts[i].y+ty);
		for(int i=pts.size()-2; i<pts.size(); i++)
			glVertex2f(pts[i].x+tx1,pts[i].y);
	glEnd();
	
	glFlush();
}

void stepFunc(int kx1,int kx2){
	spokeNo1-=kx1;
    spokeNo1%=360;
    spokeNo2-=kx2;
    spokeNo2%=360;
	tx1+=kx1;
	tx2+=kx2;
}

void idle(){
	glClear(GL_COLOR_BUFFER_BIT);
	stepFunc(1,2);
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
	glutCreateWindow("Pendulum");
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    getPoints();
    glutDisplayFunc(display);
    glutTimerFunc(40,makeDelay,1);
    glutMainLoop();
	return 0;
}

