#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <unistd.h>
using namespace std;

#define sleepTime 1000000
class Point{
public:
	int x, y;
	Point(){}
	Point(int p, int q){
		x = p;
		y = q;
	}
};

class node{
public:
	int id;
	string state="white";
	bool visited=false;
	Point pos;
	node(int i,Point p){
		id = i;
		pos = p;
	}
	void draw(){
		if(state=="white")
			glColor3f(1,1,1);
		else if(state=="grey")
			glColor3f(1,0,0);
		else if(state=="black")
			glColor3f(0,1,0);
		glBegin(GL_POINTS);
			for(int i=0; i<=360; i++){
				glVertex2f(pos.x+5*cos(2*i*3.14/360),pos.y+5*sin(2*i*3.14/360));
			}
		glEnd();
		glFlush();
	}
};

class edge{
public:
	int u,v;
	int wt;
	string state="white";
	edge(int p, int q, int w){
		u = p;
		v = q;
		wt = w;
	}
	void draw(vector<node>nodes){
		glBegin(GL_LINES);
			glVertex2f(nodes[u].pos.x,nodes[u].pos.y);
			glVertex2f(nodes[v].pos.x,nodes[v].pos.y);
		glEnd();
		glFlush();
	}

};
class Graph{
public:
	vector<node>nodes;
	vector<edge>edges;
	Graph(){
		nodes.push_back(node(0,Point(300,300)));
		nodes.push_back(node(1,Point(300,250)));
		nodes.push_back(node(2,Point(300,350)));
		nodes.push_back(node(3,Point(350,300)));
		nodes.push_back(node(4,Point(350,350)));
		nodes.push_back(node(6,Point(350,250)));
		edges.push_back(edge(0,1,3));
		edges.push_back(edge(0,2,4));
		edges.push_back(edge(0,3,5));
		edges.push_back(edge(1,5,1));
		edges.push_back(edge(3,4,2));
		edges.push_back(edge(3,5,1));
	}

	vector<int> getNeighbours(int p){
		vector<int>neighbours;
		for(int i=0; i<edges.size(); i++){
			if(edges[i].u==p)
				neighbours.push_back(edges[i].v);
			if(edges[i].v==p)
				neighbours.push_back(edges[i].u);
		}
		return neighbours; 
	}
	void dfs(int p){
		vector<int>neighbours=getNeighbours(p);
		nodes[p].visited=true;
		nodes[p].state="grey";
		nodes[p].draw();
		usleep(sleepTime);
		for(int i=0; i<neighbours.size(); i++)
		{
			if(nodes[i].visited)
				dfs(neighbours[i]);
		}
		nodes[p].state="black";
		nodes[p].draw();
		usleep(sleepTime);
	}
	void draw(){
		for(int i=0; i<nodes.size(); i++)
			nodes[i].draw();
		for(int i=0; i<edges.size(); i++)
			edges[i].draw(nodes);
	}

};
void display(){
	Graph g;
	g.draw();
	g.dfs(1);
}

int main(int argc, char *argv[])
{
	glutInit( &argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Pendulum");
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
   
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    // glutTimerFunc(40,makeDelay,1);
    glutMainLoop();
	return 0;
}