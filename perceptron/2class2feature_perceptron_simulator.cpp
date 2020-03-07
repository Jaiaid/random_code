#include <iostream>
#include <fstream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "perceptron.h"


void display(void);
void keyboardListener(unsigned char key, int x, int y);
void specialKeyListener(int key, int x, int y);
void init(void);

double camX = 50;
std::vector<std::vector<double> > trainData;
// perceptron object with two input features
perceptron neuron(2);
std::vector<double> weights;

int main(int argc, char **argv)
{
	// check to see if train data provided
	if(argc!=2){
		std::cout << "2class2feature_perceptron_simulator.out <train data file>" << std::endl;
		return 0;
	}

	// open and read train data
	double x, y, result;
	std::ifstream fin(argv[1]);
	if(!fin) {
		std::cout << argv[1] << " data file not found" << std::endl;
		return 0;
	}

	fin >> x >> y >> result;
	while(!fin.eof())
	{
		trainData.push_back(std::vector<double>(3, -1));
		trainData[trainData.size() - 1][0] = x;
		trainData[trainData.size() - 1][1] = y;
		trainData[trainData.size() - 1][2] = result;

		fin >> x >> y >> result;
	}
	fin.close();
	
	// report initial weight
	weights = neuron.getWeights();
	std::cout << "weights : " << weights[0] << ' ' << weights[1] << ' ' << weights[2] << std::endl;

	// init display
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("2feature perceptron simulator");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardListener);

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
	gluPerspective(90, 1, 1, 1000);

	glPointSize(3.0);
}

void keyboardListener(unsigned char key, int x,int y)
{
	switch(key)
	{
		case 'f':
			// train with one sample
			neuron.trainOnce(trainData);
			weights = neuron.getWeights();
			std::cout << "Faulty Classification : " << neuron.getFaultCount() << std::endl << 
			"weights : " << weights[0] << ' ' << weights[1] << ' ' << weights[2] << std::endl;
			break;
		case 'w':
			camX -= 2;
			break;
		case 's':
			camX += 2;
			break;
		case 'q':
			exit(0);
	}
	// readraw the scene
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, camX, 0, 0, camX - 1, 0, 1, 0);

	//draw main axes
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);{
		glVertex3f(1000, 0, -100);
		glVertex3f(-1000,  0, -100);

		glVertex3f(0, 1000, -100);
		glVertex3f(0, -1000, -100);
	}glEnd();

	glBegin(GL_POINTS);
	{
		for(int i = 0;i < trainData.size();i++)
		{
			if(trainData[i][2] < 0) glColor3f(1.0, 0.0, 0.0);
			else glColor3f(0.0, 0.0, 1.0);
			glVertex3f(trainData[i][0], trainData[i][1], -100);
		}
	}
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	{
		if(weights[0] == 0) {
			glVertex3f(-1000.0, -weights[2]/weights[1], -100);
			glVertex3f(1000.0, -weights[2]/weights[1], -100);
		}
		else {
			glVertex3f((-weights[2] - 1000*weights[1])/weights[0], 1000.0, -100);
			glVertex3f((-weights[2] + 1000*weights[1])/weights[0], -1000.0, -100);
		}
	}
	glEnd();

	glutSwapBuffers();
}
