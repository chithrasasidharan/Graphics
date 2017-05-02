#include <iostream>
#include <vector>
#include <GL/glut.h>
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

class Window{
public:
	vector<Point>w;
	Window(){
		w.push_back(Point(0,0));
		w.push_back(Point(200,0));
		w.push_back(Point(200,200));
		w.push_back(Point(0,200));

	}
	int inside(Point p,int edge){
		switch(edge){
			case 1: return p.y>0;
			case 2: return p.x<200;
			case 3: return p.y<200;
			case 4: return p.x>0;
		}
	}

	Point findIntersection(Point p, Point q, int edge){
		Point r;
		switch(edge){
			//r.y-p.y/q.y-p.y=r.x-p.x/q.x-p.x
			case 1:
					r.y=0;
					r.x=(r.y-p.y)*(q.x-p.x)/(q.y-p.y)+p.x;
					return r;
			case 2:
					r.x=200;
					r.y=(r.x-p.x)*(q.y-p.y)/(q.x-p.x)+p.y;
					return r;
			case 3:
					r.y=200;
					r.x=(r.y-p.y)*(q.x-p.x)/(q.y-p.y)+p.x;
					return r;
			case 4:
					r.x=0;
					r.y=(r.x-p.x)*(q.y-p.y)/(q.x-p.x)+p.y;
					return r;


		}
	}
	void draw(){
		glBegin(GL_LINE_LOOP);
			for(int i=0; i<w.size(); i++)
				glVertex2f(w[i].x,w[i].y);
		glEnd();
		glFlush();
	}
}w;

class Polygon{
public:
	vector<Point>poly;
	Polygon(){
		poly.push_back(Point(100,50));
		poly.push_back(Point(250,100));
		// poly.push_back(Point(100,100));
		poly.push_back(Point(300,300));
		poly.push_back(Point(100,250));
		// poly.push_back(100,50);
		// poly.push_back(100,50);
	}
	void draw(){
		glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
			for(int i=0; i<poly.size(); i++)
				glVertex2f(poly[i].x,poly[i].y);
		glEnd();
		glFlush();
	}
	vector<Point> clip(Window w){
		vector<Point>out = poly;
		for(int j=0; j<w.w.size(); j++){
			vector<Point>in=out;
			out.clear();
			Point s=in[in.size()-1];
			for(int i=0; i<in.size();i++){
				Point p=in[i];
				if(w.inside(p,j)){
					if(!w.inside(s,j))
						out.push_back(w.findIntersection(s,p,j));
					out.push_back(p);

				}
				else{
					if(w.inside(s,j))
						out.push_back(w.findIntersection(s,p,j));
				}
				s=p;
			}
			return out;
		}
	}
}p;
void display(){
	w.draw();
	p.draw();
}
void keyboard(unsigned char c,int x, int y){
	glClear(GL_COLOR_BUFFER_BIT);
	if(c=='c')
	{
		glColor3f(1,0,0);
		w.draw();
		p.poly=p.clip(w);
		glColor3f(0,1,0);
		p.draw();
	}
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
   
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    // glutTimerFunc(40,makeDelay,1);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
	return 0;
}