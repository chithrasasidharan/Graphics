#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
using namespace std;
int x=250;
int y=50,y2=320;
int r=40;
int seg=360;
class Point{
public:
	int x,y;
	Point(){}
	Point(int p,int q){
		x=p;
		y=q;
	}
};

vector<Point>pts;


void drawCircle(int x, int y, int r){
	glBegin(GL_POINTS);
		for(int i=0; i<=seg; i++)
			glVertex2f(x+r*cos(i*2*3.14/360),y+r*sin(i*2*3.14/360));
	glEnd();
	glFlush();


}
void drawLine(int x1,int x2,int y,int y2){
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex2f(x1,y);
		glVertex2f(x2,y2);
	glEnd();
	glFlush();
}
void getPoints(int x,int y,int r){
	// glClear(GL_COLOR_BUFFER_BIT);
	for(int i=240; i<=300; i++){
		pts.push_back(Point(x+r*cos(i*2*3.14/360),y+r*sin(i*2*3.14/360)));
	}
	for(int i=300; i>=240; i--){
		pts.push_back(Point(x+r*cos(i*2*3.14/360),y+r*sin(i*2*3.14/360)));
	}
}
int i=0;
void idle(){
	getPoints(x,y2,y2-y);
	
	glColor3f(1,0,0);
	// for(int i=0; i<pts.size();i++){
	i+=1;
	i%=pts.size();
	glClear(GL_COLOR_BUFFER_BIT);
	drawCircle(x,y2,r);
		drawCircle(pts[i].x,pts[i].y,r);
		drawLine(x,pts[i].x,y2,pts[i].y);
	// }

}

void makeDelay(int){
	idle();
	glutTimerFunc(40,makeDelay,1);
}

void display(){
	// idle();
	
}
int main(int argc, char **argv){
	
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