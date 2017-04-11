#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
using namespace std;
#define center 0
// Point class with x and y
class Point{
    public:
        int x,y;
        Point(){
            x=0;
            y=0;
        }
        Point(int a,int b){
            x=a;
            y=b;
        }
};

// Path for the cycle to follow
vector<Point> path;
// Cycle always points to path[now] both angle and movement
int now=1;

// Find the new point after rotating about origin and then transalating trans
Point getPoint(Point a,float rotAngle,Point origin,Point trans){
    rotAngle = rotAngle*2*3.14/360;
    Point p=a;
    // t
    p.x-=origin.x;
    p.y-=origin.y;
    // r
    Point q=p;
    q.x=p.x*cos(rotAngle)+p.y*sin(rotAngle);
    q.y=-p.x*sin(rotAngle)+p.y*cos(rotAngle);
    p=q;
    // t'
    p.x+=origin.x;
    p.y+=origin.y;
    // main t
    p.x+=trans.x;
    p.y+=trans.y;
    return p;
}

// For x, y, r and its draw function
class Circle:public Point{
    public:
        int r;
        int spokeNo;
        Circle(){}
        Circle(int a, int b, int c):Point(a,b){
            spokeNo=360;
            r=c;
        }
        // to decrement spokeno
        void step(){
            spokeNo-=1;
            spokeNo%=360;
        }
        void draw(float rotAngle, Point origin, Point trans){
            glBegin(GL_LINE_LOOP);
                for(int i=0; i<=360; i++){
                    Point p(x+r*cos(2*3.14/360*i),y+r*sin(2*3.14/360*i));
                    Point q = getPoint(p, rotAngle, origin, trans);
                    glVertex2f(q.x, q.y);
                    if(i==spokeNo)
                    {
                        // Draw a spoke to the center
                        Point r = getPoint(Point(x,y), rotAngle, origin, trans);
                        glVertex2f(r.x, r.y);

                    }
                }
            glEnd();
        }
};
// Has two wheels and a vectory of points called body..
// translate, its current position
// rotate, its current orientation
class Cycle{
    public:
        Circle *a,*b;
        Point translate;
        float rotAngle;
        vector <Point>body;

        // make the cycle
        Cycle(){
            rotAngle=0;
            a = new Circle(120,50,40);
            b = new Circle(320,50,40);
            body.push_back(Point(120,50));
            body.push_back(Point(150,100));
            body.push_back(Point(320,50));
            body.push_back(Point(320,150));
            body.push_back(Point(280,160));
            body.push_back(Point(320,150));
            body.push_back(Point(340,170));

        }
        // Place the cycle at point p by adjusting translate such that body+translate=p
        void place(Point p){
            // place the body[center] there
            translate.x = p.x - body[center].x;
            translate.y = p.y - body[center].y;
        }
        // Get the first point in body after translate
        Point getFirst(){
            return Point(body[center].x+translate.x, body[center].y+translate.y);
        }
        // move one step in direction of path[now] if already there, increment now
        void step(){
            a->step();
            b->step();
            Point p = getFirst();
            // Already there
            if(p.x==path[now].x && p.y==path[now].y)
                if(now<path.size()-1)
                    now++;
            // Set angle
            rotAngle = -atan2(path[now].y - p.y, path[now].x - p.x) * 180 / 3.14;

            // Move the cycle one move, x and y
            if(p.x<path[now].x)
                translate.x++;
            else if(p.x>path[now].x)
                translate.x--;
            
            if(p.y<path[now].y)
                translate.y++;
            else if(p.y>path[now].y)
                translate.y--;
            
        }
        // Draw the translated rotated cycle
        void draw(){
            a->draw(rotAngle, body[center], translate);
            b->draw(rotAngle, body[center], translate);
            glBegin(GL_LINE_STRIP);
                for(int i=0; i<body.size(); i++){
                    Point p(body[i].x,body[i].y);
                    Point q = getPoint(p, rotAngle, body[center], translate);
                    glVertex2f(q.x, q.y);
                }
            glEnd();
        }
};
// Create the cycle
Cycle a;
// Display func 
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    a.draw();
    a.step();
    glFlush();
}

// so that its called in 50 ms interval instead of very fast
void timer(int){
    display();
    glutTimerFunc(50, timer, 1);
}
int main(int argc, char **argv){
    path.push_back(Point(50,50));
    path.push_back(Point(100,50));
    path.push_back(Point(200,150));
    path.push_back(Point(300,50));
    path.push_back(Point(400,50));
    a.place(path[0]);
    glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Pendulum");
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glutDisplayFunc(display);
    glutTimerFunc(50, timer, 1);
    glutMainLoop();
}