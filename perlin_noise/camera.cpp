#include <iostream>
#include <cmath>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "perlin_noise.h"
#include "utility.h"

#define WATER_L 0.4
#define GREEN_L 0.7


#define ANGROTATE 5

void drawGrid();
void display(void);
void keyboardListener(unsigned char key, int x, int y);
void specialKeyListener(int key, int x, int y);
void init(void);

Vector pos(2, 2, 1);
Vector look(1, -1, 0);
Vector up(0, 0, 1);
Vector right(-1, -1, 0);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("my window");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	init();
	glutMainLoop();

	return 0;
}

void init(void)
{
	/*clear background color(make black)*/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/*initialize viewing values*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0, 1000);
	init_random();
}

void keyboardListener(unsigned char key, int x,int y)
{
	switch(key){
		case '1':
			look.rotate(up, -ANGROTATE);
			right = look.crossproduct(up);
			break;
		case '2':
			look.rotate(up, ANGROTATE);
			right = look.crossproduct(up);
			break;
		case '3':
			up.rotate(right, ANGROTATE);
			look = up.crossproduct(right);
			break;
		case '4':
			up.rotate(right, -ANGROTATE);
			look = up.crossproduct(right);
			break;
		case '5':
			right.rotate(look, ANGROTATE);
			up = right.crossproduct(look);
			break;
		case '6':
			right.rotate(look, -ANGROTATE);
			up = right.crossproduct(look);
			break;
		default:
			break;
	}
	
	std::cout<<"look : "<<look.mag()<<' '<<look<<std::endl;
	std::cout<<"up : "<<up.mag()<<' '<<up<<std::endl;
	std::cout<<"right : "<<right.mag()<<' '<<right<<std::endl;
	std::cout<<"pos : "<<pos.mag()<<' '<<pos<<std::endl;

	glutPostRedisplay();
}

void specialKeyListener(int key, int x, int y)
{
	switch(key){
		case GLUT_KEY_DOWN:
			pos = pos - look;
			break;
		case GLUT_KEY_UP:
			pos = pos + look;
			break;
		case GLUT_KEY_RIGHT:
			pos = pos + right;
			break;
		case GLUT_KEY_LEFT:
			pos = pos - right;
			break;
		case GLUT_KEY_PAGE_UP:
			pos = pos + up;
			break;
		case GLUT_KEY_PAGE_DOWN:
			pos = pos - up;
			break;
		default:
			break;
	}

	glutPostRedisplay();
}

void drawGrid()
{
	int i;
	glColor3f(0.6, 0.6, 0.6);	//grey
	glBegin(GL_LINES);{
		for(i=-8;i<=8;i++){

			if(i==0)
				continue;	//SKIP the MAIN axes

			//lines parallel to Y-axis
			glVertex3f(i*100, -900, 0);
			glVertex3f(i*100,  900, 0);

			//lines parallel to X-axis
			glVertex3f(-900, i*100, 0);
			glVertex3f( 900, i*100, 0);
		}
	}glEnd();
	
	double bufferx[2][5001], buffery[2][5001], bufferz[2][5001];
	for(int l=0;l<5001;l++)
	{
		bufferx[0][l] = 0;
		buffery[0][l] = 0;
		bufferz[0][l] = 0;
	}
	bufferx[1][0] = 0;
	buffery[1][0] = 0;
	bufferz[1][0] = 0;
	int sb = 1, sbc = 0;
	srand(5);
	for(double xf=0;xf<5;xf+=0.01)
	{
		int l=0;
		Vector pos(0, 0, 0);
		for(double yf=0;yf<5;yf+=0.01)
		{	
			double zf;
			pos.x = xf, pos.y = yf;
			zf = 1*perlin_noise(pos,1,BOUND);
			//std::cout<<zf<<std::endl;
			zf += 0.1*perlin_noise(pos,0.01,BOUND);
			//std::cout<<zf<<std::endl;
			zf += 0.1*perlin_noise(pos,0.1,BOUND);
			//std::cout<<zf<<std::endl;
			zf += 0.1*perlin_noise(pos,2,BOUND);
			//std::cout<<zf<<std::endl;
			//zf += perlin_noise(pos,2,BOUND);
			/*
			zf+=0.0000010*perlin_noise(vector(xf,yf,0),1.6,BOUND);
			zf+=0.0000010*perlin_noise(vector(xf,yf,0),3.2,BOUND);
			zf+=0.0000010*perlin_noise(vector(xf,yf,0),6.4,BOUND);
			zf+=0.0000010*perlin_noise(vector(xf,yf,0),12.8,BOUND);
			*/
			if(l){
				
				glBegin(GL_LINES);
				{
					glVertex3f(bufferx[sb][l-1], buffery[sb][l-1], bufferz[sb][l-1]);
					glVertex3f(xf, yf, zf);
					
					glVertex3f(xf, yf, zf);	
					glVertex3f(bufferx[sbc][l], buffery[sbc][l], bufferz[sbc][l]);
				}glEnd();
				
				/*
				double zmax = (bufferz[sb][l-1]>zf)?bufferz[sb][l-1]:zf;
				zmax = (bufferz[sb][l]>zmax)?bufferz[sb][l]:zmax;
				zmax = (bufferz[sbc][l-1]>zmax)?bufferz[sbc][l-1]:zmax;
				zmax = (bufferz[sbc][l]>zmax)?bufferz[sbc][l]:zmax;
				
				if(zmax < WATER_L){
					glColor3f(0.3, 0.3, 1.0);
				}
				else if(zmax < GREEN_L){
					glColor3f(0.1, 1.0, 0.1);
				}
				else{
					glColor3f(1.0, 1.0, 1.0);
				}
				
				
				glBegin(GL_TRIANGLES);
				{
					glVertex3f(bufferx[sb][l-1], buffery[sb][l-1], bufferz[sb][l-1]);
					glVertex3f(xf, yf, zf);	
					glVertex3f(bufferx[sbc][l], buffery[sbc][l], bufferz[sbc][l]);
				}glEnd();
				
				glBegin(GL_TRIANGLES);
				{
					glVertex3f(bufferx[sbc][l-1], buffery[sbc][l-1], bufferz[sbc][l-1]);
					glVertex3f(bufferx[sb][l-1], buffery[sb][l-1], bufferz[sb][l-1]);
					glVertex3f(bufferx[sbc][l], buffery[sbc][l], bufferz[sbc][l]);
				}glEnd();
				*/
			}
			bufferx[sb][l]=xf,buffery[sb][l]=yf,bufferz[sb][l]=zf;
			l++;
		}
		sb = (sb+1)%2;
		sbc = 1-sb;
	}
}

void display(void)
{
	Vector tmp = pos + look;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pos.x, pos.y, pos.z, tmp.x, tmp.y, tmp.z,
		up.x, up.y, up.z);
	/*glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	{
		glVertex3f(0, 100, 0);
		glVertex3f(-45, 100, 45);
		glVertex3f(45, 100, 45);
	}
	glEnd();
	*/
	drawGrid();
	glutSwapBuffers();
}

