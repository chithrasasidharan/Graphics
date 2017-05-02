#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <set>
#include <unistd.h>
#include <iterator>
using namespace std;
#define sleepTime 1000000
class Point{
public:
	int x,y;
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
	node(int i, Point p){
		id = i;
		pos = p;
	}
	void draw(){
		if(state=="white")
			glColor3f(1,1,1);
		if(state=="grey")
			glColor3f(1,0,0);
		if(state=="black")
			glColor3f(0,1,0);
		glBegin(GL_POINTS);
			for(int i=0; i<=360; i++)
				glVertex2f(pos.x+5*cos(2*i*3.14/360),pos.y+5*sin(2*3.14*i/360));
		glEnd();
		glFlush();
	}
};

class edge{
public:
	int wt,u,v;
	string state ="white";
	edge(int p,int q,int w){
		wt=w;
		u=p;
		v=q;
	}
	void draw(vector<node>nodes){
		if(state=="white")
			glColor3f(1,1,1);
		if(state=="grey")
			glColor3f(1,0,0);
		if(state=="black")
			glColor3f(0,1,0);
		glBegin(GL_LINES);
			glVertex2f(nodes[u].pos.x,nodes[u].pos.y);
			glVertex2f(nodes[v].pos.x,nodes[v].pos.y);
		glEnd();
		glFlush();
	}
	bool has(int p){
		return u==p || v==p;
	}
};

class Graph{
public:
	vector<node>nodes;
	vector<edge>edges;
	// vector<int>neighbours;
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
	int findEdge(int u,int v){
		for(int i=0; i<edges.size(); i++)
			if(edges[i].has(u) && edges[i].has(v))
				return i;
		return -1;
	}
	set<set<int>> S;
	vector<edge>sortList;
	vector<int>A;

	set<set<int>>::iterator findRep(int p){
		for(auto it= S.begin(); it!=S.end(); it++){
			// int rep = *(it->begin());
			for(auto i=	it->begin(); i!=it->end(); i++)
			{
				if(*i==p)
					return it;
			}
		}
	}
	void Kruskal(){
		for(int i=0; i<nodes.size(); i++){
			set<int>s;
			s.insert(i);
			S.insert(s);
		}
		vector<edge>temp = edges;
		for(int i=0; i<edges.size(); i++){
			int min=0;
			for(int j=0; j<temp.size(); j++){
				if(temp[j].wt<temp[min].wt)
					min=j;
			}
		sortList.push_back(temp[min]);
		temp.erase(temp.begin()+min);
		}
		for(int i=0; i<sortList.size(); i++){
			set<set<int>>::iterator one = findRep(sortList[i].u);
			set<set<int>>::iterator two = findRep(sortList[i].v);
			if(one!=two){
				set<int>s;
				for(auto it=one->begin();it!=one->end();it++){
					s.insert(*it);
				}
				for(auto it=two->begin();it!=two->end();it++){
					s.insert(*it);
				}
				S.insert(s);
				S.erase(one);
				S.erase(two);
				int p = sortList[i].u;
				int q = sortList[i].v;
				A.push_back(findEdge(p,q));
				edges[findEdge(p,q)].state="grey";
					draw();
					usleep(sleepTime);


			}
			for(int i=0; i<A.size(); i++)
				edges[A[i]].state="grey";
			draw();
		}

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
	g.Kruskal();
}

int main(int argc, char *argv[])
{
	glutInit( &argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Kruskal MST");
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
   
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    // glutTimerFunc(40,makeDelay,1);
    glutMainLoop();
	return 0;
}