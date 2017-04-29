#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <vector>
using namespace std;

class Point{
public:
	int x,y;
	Point(){}
	Point(int x, int y){
		this->x=x;
		this->y=y;
	}
};
Point center1 =Point(250,50);
Point center2 =Point(250,200);
int radius=20;
vector<Point>pts;
void draw(int x,int y,int r){
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<=360;i++){
		glVertex2f(x+r*cos(i*2*3.14/360),y+r*sin(i*2*3.14/360));
		// glVertex2f(center2.x+radius*cos(i*2*3.14/360),center2.y+radius*sin(i*2*3.14/360));
	}
	glEnd();
	
	glFlush();
}

void drawLine(int x1,int y1,int x2,int y2){
		glBegin(GL_LINES);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
		glEnd();
		glFlush();
	
}

void getPoints(int x,int y,int r){
	for(int i=240; i<=300; i++){
		pts.push_back(Point(x+r*cos(i*2*3.14/360),y+r*sin(i*2*3.14/360)));
	}
	for(int i=300; i>=240; i--){
		pts.push_back(Point(x+r*cos(i*2*3.14/360),y+r*sin(i*2*3.14/360)));
	}
}
int i=1;
void idle(){
	getPoints(center2.x,center2.y,center2.y-center1.y);
	glColor3f(1,0,0);
	i+=1;
	i%=pts.size();
	glClear(GL_COLOR_BUFFER_BIT);
	draw(center2.x,center2.y,radius);
	draw(pts[i].x,pts[i].y,radius);
	drawLine(center2.x,center2.y,pts[i].x,pts[i].y);


}
void makeDelay(int){
	idle();
	glutTimerFunc(40,makeDelay,1);
}
void display(){
}
int main(int argc, char  *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Pendulum");
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
   
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    glutTimerFunc(40,makeDelay,1);
    glutMainLoop();
	return 0;
}