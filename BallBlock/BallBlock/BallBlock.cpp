
#include <GL/freeglut_std.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>


#define WINDOW_W 1350
#define WINDOW_H 700

static GLfloat rktx = -5.5;
static GLfloat rkty = -21.0;
static const int FPS = 60;
int blockxSize = 4;
int blockySize = 2;
int pause = 0;
int tempx, tempy;
float rktxSize = 11;
int rktySize = 2;
int score = 0;
int life = 5;
int blocks[6][19];
bool playGame=false;
bool startGame = false;

void timer(int v);
void display();

using namespace std;
static GLfloat moveXFactor = 0.2;
static GLfloat moveYFactor = 0.5;


struct _ball
{
	GLfloat radius = 0.75;
	GLfloat X = 0.0;
	GLfloat Y = 0.0;
	int directionX = 0;
	int directionY = -1;
}ball;

int level1[6][19] = {
	{1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1},
	{1,1,0,0,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1},
	{1,1,0,0,0,0,1,1,0,1,0,1,0,1,1,0,0,1,1},
	{1,1,1,1,1,0,1,1,0,0,0,1,0,1,1,0,0,1,1},
	{1,1,1,1,1,0,1,1,0,0,0,1,0,1,1,0,0,1,1},





};
void instuctions() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	string str = "Ball blocks oyununda 5 hakkiniz bulunmaktadir.(Kazanmak icin tum bloklari kirmaniz gerekmektedir.(Raket kontrolu icin yon tuslarini kullanin.(Oyuna baslamak icin yada durdurmak icin space tusunu kullanin.(Ana menuye donmek icin esc tusunu kullanýn.";
	
	int y = 10;


	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2f(-30, y);

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') {
			glRasterPos2f(-30, y -= 4);
			continue;
		}
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
void init_board() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 19; j++) {
			blocks[i][j] = level1[i][j];
		}
	}
}


void draw_board()
{

	GLfloat top = 20;
	GLfloat right = -47;







	for (int row = 0; row < 6; row++)
	{

		for (int col = 0; col < 19; col++)
		{

			
			if (blocks[row][col] == 1)
			{
				glBegin(GL_LINE_LOOP);
				glClear(GL_COLOR_BUFFER_BIT);
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glLineWidth(1.0f);
				glVertex2f(right, top);
				glVertex2f(right + blockxSize, top);
				glVertex2f(right + blockxSize, top - blockySize);
				glVertex2f(right, top - blockySize);
				glPopMatrix();
				glEnd();

				glPushMatrix();
				glColor3f(0.4,0.1,0.0);
				glRectf(right, top, right + blockxSize, top -blockySize);
				glPopMatrix();


			}


			right += blockxSize+1;
		}

		top -= blockySize+1;

	
			right = -47;
		

	}

}
void menu() {
	init_board();
	ball.X = 0;
	ball.Y = 0;
	startGame = false;
	ball.directionY = 0;
	score = 0;
	life = 5;
	srand(time(NULL));

	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glPushMatrix();
		string menuStr = "Ball Blocks Oyununa Hos geldiniz.)Oyuna baslamak icin 1 tusunu kullanin.(Oyun hakkindaki bilgilere 2 tusunu kullanarak erisebilirsiniz.";

		

		glColor3f(r, g, b);
		glRasterPos2f(-10, 20);

		for (int i = 0; i < menuStr.length(); i++) {
			if (menuStr[i] == ')') {
				glColor3f(1.0, 0.0, 0.0);
				glRasterPos2f(-40, 10);
				continue;
			}
			if (menuStr[i] == '(') {
				glColor3f(0.0, 0.0, 1.0);
				glRasterPos2f(-40, 5);
				continue;
			}

			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menuStr[i]);
		}
		glPopMatrix();
		glFlush();
		glutSwapBuffers();
	}
	

void endGame(){
	srand(time(NULL));

	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	string str;
	if(score==770)
	str = "Tebrikler Oyunu Kazandiniz,menuye donmek icin Esc tusunu kullanin.";
	else {
	str = " Uzgunum oyunu kaybettiniz,menuye donmek icin Esc tusunu kullanin.";
	}
	glColor3f(r, g, b);
	glRasterPos2f(-20, 0);
	for (int i = 0; i < str.length(); i++) {
		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0 / aspect, 50.0 / aspect, -1.0, 1.0);
}

void draw_circle(float x, float y, float radius) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	srand(time(NULL));
	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;
	glColor3f(r, g, b);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	static const int circle_points = 100;
	static const float angle = 2.0f * 3.1416f / circle_points;

	// this code (mostly) copied from question:
	glBegin(GL_POLYGON);
	double angle1 = 0.0;
	glVertex2d(radius * cos(0.0), radius * sin(0.0));
	int i;
	for (i = 0; i < circle_points; i++)
	{
		glVertex2d(radius * cos(angle1), radius * sin(angle1));
		angle1 += angle;
	}
	glEnd();
	glPopMatrix();
}


void draw_rkt(int rktx, int rkty) {
	srand(time(NULL));
	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;


	glPushMatrix();
	glColor3f(g, b,r);
	glRectf(rktx, rkty, rktx + rktxSize, rkty - rktySize);

	glPopMatrix();

}


void draw_score() {

	string scoreStr = "Score: " + to_string(score);


	glPushMatrix();

	
	glColor3f(0.0, 1.0, 0.0); 
	glRasterPos2f(-45, 24); 

	for (int i = 0; i < scoreStr.length(); i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreStr[i]); 
	}
	
	glPopMatrix();
}
void draw_life() {
	string lifeStr = "Life: " + to_string(life);


	glPushMatrix();

	
	glColor3f(1.0, 0.0, 0.0); 
	glRasterPos2f(40, 24);

	for (int i = 0; i < lifeStr.length(); i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, lifeStr[i]);
	}
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, life);
	glPopMatrix();
}






void display()

{

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		srand(time(NULL));
		float r = (float)rand() / (float)RAND_MAX;
		float g = (float)rand() / (float)RAND_MAX;
		float b = (float)rand() / (float)RAND_MAX;


		glColor3f(b, r, g);
		glLineWidth(1.0f);

		glBegin(GL_LINE_LOOP);
		glVertex2f(-49.5, 23);
		glVertex2f(49.5, 23);
		glVertex2f(49.5, -24);
		glVertex2f(-49.5, -24);
		glEnd();


		draw_score();
		
		draw_life();
		
		draw_board();
		draw_rkt(rktx, rkty);
		draw_circle(ball.X, ball.Y, ball.radius);
		
		glFlush();
		glutSwapBuffers();
	}


void update_board() {
	GLfloat top = 20;
	GLfloat right = -47;
	bool collided = false;

	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 19; col++)
		{
			if (blocks[row][col] == 1)
			{
				if ((ball.Y + ball.radius <= top && ball.Y + ball.radius >= top - blockySize) || (ball.Y - ball.radius <= top && ball.Y - ball.radius >= top - blockySize)) {
					if (ball.X - ball.radius == right + blockxSize - 1 || ball.X - ball.radius + 1 == right || ball.X + ball.radius - 1 == right || ball.X + ball.radius - 1 == right + blockxSize) {
						blocks[row][col] = 0;
						score += 10;
						ball.directionX = -ball.directionX;
						collided = true;
						break;
					}
					else {
						if (ball.directionX >= 0) {
							if (ball.X - ball.radius <= right + blockxSize && ball.X - ball.radius >= right)
							{
								blocks[row][col] = 0;
								ball.directionY = ball.directionY * (-1);						
								score += 10;
								collided = true;
								break;
							}
							else if (ball.X + ball.radius >= right && ball.X + ball.radius <= right + blockxSize) {
								blocks[row][col] = 0;
								ball.directionY = ball.directionY * (-1);							
								score += 10;
								collided = true;
								break;
							}
						}
						if (ball.directionX <= -1) {
							if (ball.X - ball.radius >= right && ball.X - ball.radius <= right + blockxSize) {
								blocks[row][col] = 0;
								ball.directionY = ball.directionY * (-1);
								score += 10;
								collided = true;
								break;
							}
							else if (ball.X + ball.radius >= right && ball.X + ball.radius <= right + blockxSize)
							{
								blocks[row][col] = 0;
								ball.directionY = ball.directionY * (-1);
								score += 10;
								collided = true;
								break;
							}
						}
					}
				}
				if (score == 770 && playGame) {
					playGame = false;
					glutDisplayFunc(endGame);
				}
				if (life == 0 && playGame) {
					playGame = false;
					glutDisplayFunc(endGame);
				}
			}
			right += blockxSize + 1;
		}
		if (collided) {
			break;
		}
		top -= blockySize + 1;
		if (row % 2 == 0 || row % 2 == 1)
		{
			right = -47;
		}
	}
}
void timer(int v)
{
	glutPostRedisplay();
	if (ball.Y-ball.radius <= -24)
	{
		startGame = false;
		life--;
		ball.X = 0;
		ball.Y = 0;
		ball.directionX = 0;
		ball.directionY = 0;
		rktx = -5.5;
	}


	else
	{
		if ((ball.Y <= rkty+rktySize)&&ball.Y>rkty+1) {
			if ((rktx <= ball.X+ball.radius) && (ball.X < (rktx + 4)))
			{
				ball.directionX = -1;
				ball.directionY = -ball.directionY ;
			}
			if ((rktx+4 <= ball.X) && (ball.X < (rktx + 8)))
			{
				ball.directionX = 0;
				ball.directionY = -ball.directionY ;
			}
			if ((rktx + 8 <= ball.X) && (ball.X < (rktx + 12)))
			{
				ball.directionX = 1;
				ball.directionY = -ball.directionY ;
			}

		}

	}

	update_board();


	//printf("ball Y: %f \n", ball.Y);
	if (ball.Y >22)
	{
		ball.directionY = -ball.directionY ;
	}
	if (ball.X < -49 || ball.X >49)
	{
		ball.directionX = -ball.directionX ;
	}
	ball.X = ball.X + (moveXFactor * ball.directionX);
	ball.Y = ball.Y + (moveYFactor * ball.directionY);
	
	glutTimerFunc(900 / FPS, timer, v);


}



void kbSpecial(int key, int x, int y)
{

	switch (key)
	{
	
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;
	case GLUT_KEY_LEFT:

		rktx = rktx - 1;
		draw_rkt(rktx, rkty);

		break;
	case GLUT_KEY_RIGHT:

		rktx = rktx + 1;
		draw_rkt(rktx, rkty);

		break;
	}
}

void keyboardFunc(unsigned char key, int x, int y)
{
	
	if (key == '1' ) {
		playGame = true;
		glutDisplayFunc(display);
	}
	if (key == 27) {
		
		glutDisplayFunc(menu);
	}
	if (key == 32) {
		
		

		if (ball.directionY == 0&&!startGame) {
			
			startGame = true;
			ball.directionY = -1;
			pause = 1;
			
		}
		else if(pause==1){
			tempx = ball.directionX;
			tempy = ball.directionY;
			ball.directionY = 0;
			ball.directionX = 0;
			pause = 2;
		}
		else if (pause == 2) {
			ball.directionX = tempx;
			ball.directionY = tempy;
			pause = 1;        
		}
		
	}
	if (key == '2') {
		glutDisplayFunc(instuctions);
	}
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("Ball Blocks");
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(menu);
	


	glutSpecialFunc(kbSpecial);
	glutKeyboardFunc(keyboardFunc);
	glutMainLoop();
}

