#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <vector>
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
vector<Point> v;

Point translate(Point p, int tx, int ty){
	return Point(p.x+tx,p.y+ty);
}

Point scale(Point p,int sx,int sy){
	return Point(p.x*sx,p.y*sy);
}

Point rotate(Point p, float angle){
	return Point((p.x*cos(angle*3.14/180)+p.y*sin(angle*3.14/180)),(p.x*-sin(angle*3.14/180)+p.y*cos(angle*3.14/180)));

}

void keyboard(unsigned char c, int m, int n){
	glClear(GL_COLOR_BUFFER_BIT);
	Point p;
	if(c=='t'){
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<v.size(); i++){
			p= translate(v[i],50,50);
			glVertex2f(p.x,p.y);
		}
		glEnd();
	}
	if(c=='s'){
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<v.size(); i++){
			p= scale(v[i],2,2);
			glVertex2f(p.x,p.y);
		}
		glEnd();
	}
	if(c=='r'){
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<v.size(); i++){
			p= rotate(v[i],90);
			glVertex2f(p.x,p.y);
		}
		glEnd();
	}
	glFlush();
}

void display(){
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<v.size(); i++)
		glVertex2f(v[i].x,v[i].y);
	glEnd();
	glFlush();

}

int main(int argc, char *argv[])
{
	v.push_back(Point(50,50));
	v.push_back(Point(100,100));
	v.push_back(Point(150,50));
	glutInit(&argc,argv);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Transformation");
	gluOrtho2D(-500,500,-500,500);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}