#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <math.h>
#include "myShape.h"
#define KEY_ESC 27
#define WIDTH 320
#define HEIGHT 240

float dist=0.0; /*���̂̈ړ���*/
float cam = 0.0; /*���_�̈ړ���*/

void polarview(void);
void resetview(void);
unsigned char wireFlag = GL_TRUE;
unsigned char revolveFlag = GL_FALSE;/*��]��ON/OFF�؂�ւ�*/
int xBegin, yBegin;/*�h���b�O�J�n���_�̃}�E�X�|�C���^�̍��W*/
int mButton;/*�h���b�O���ɉ�����Ă���}�E�X�{�^���̔���*/
float camX, camY, twist, tranceY, tranceX, tranceTheta, cosX, idleCosX, spin, speed;
float theta = 15.0;

void display(void)
{

	int i;
	int w;
	float diffuse[] = { 1.0,1.0,1.0,1.0 };
	float specular[] = { 1.0,1.0,1.0,1.0 };
	float ambient[] = { 0.3,0.3,0.3,1.0 };
	float light[] = { 1.0,1.0,1.0,0.0 }; /* �����̈ʒu�Ǝ�� */
	glLightfv(GL_LIGHT0, GL_POSITION, light); /* ���s�����̐ݒ� */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	glPushMatrix();
	gluLookAt(camX, 10.0 + camY, 10.0 + camX, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(tranceTheta, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 2.0, 0.0);


	glEnable(GL_DEPTH_TEST );
	glEnable(GL_LIGHTING);


	/*-----�������痃�̕`��-----*/
	glPushMatrix();
	glRotatef(spin, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	for (i = 0; i < 5; i++) {
		glRotatef(72.0, 1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(1.5, -0.7, 0.0);
		glScalef(0.1, 1.5, 0.5);
		glutSolidCube(1.0);
		glPopMatrix();
	}
	glPopMatrix();

     /*-----�����܂ŗ��̕`��-----*/


	/*-----��������O�g-----*/

	
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(1.5, 0, 0);
	for (i = 0; i < 6; i++) {
		glRotatef(30.0, 1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2d(-1, 0);
		glVertex2d(-0.7, -1);
		glVertex2d(-0.2, -2);
		glVertex2d(0.2, -2);
		glVertex2d(0.7, -1);
		glVertex2d(1, 0);
		glVertex2d(0.7, 1);
		glVertex2d(0.2, 2);
		glVertex2d(-0.2, 2);
		glVertex2d(-0.7, 1);
		glEnd();
	}
	glPopMatrix();
	


	/*-----�����܂ŊO�g-----*/
	/*-----��������O�g�~-----*/
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(1.7, 0.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2d(-2, 0);
		glVertex2d(-1.7, -1);
		glVertex2d(-1, -1.7);
		glVertex2d(-0, -2.0);
		glVertex2d(1, -1.7);
		glVertex2d(1.7, -1);
		glVertex2d(2, 0);
		glVertex2d(1.7, 1);
		glVertex2d(1, 1.7);
		glVertex2d(0, 2.0);
		glVertex2d(-1, 1.7);
		glVertex2d(-1.7, 1);
		glEnd();

	glPopMatrix();


	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(1.3, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(-2, 0);
	glVertex2d(-1.7, -1);
	glVertex2d(-1, -1.7);
	glVertex2d(-0, -2.0);
	glVertex2d(1, -1.7);
	glVertex2d(1.7, -1);
	glVertex2d(2, 0);
	glVertex2d(1.7, 1);
	glVertex2d(1, 1.7);
	glVertex2d(0, 2.0);
	glVertex2d(-1, 1.7);
	glVertex2d(-1.7, 1);
	glEnd();

	glPopMatrix();


	/*-----�����܂ŊO�g�~-----*/





	/*-----�������痃�̍������̕`��-----*/
	glPushMatrix();/*���W�n�̕ۑ�*/
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(-90.0, 1.0, -10.0, 0.0);
	glutSolidCone(0.2, 1.0, 12, 1);
	glPopMatrix();
	/*-----�����܂ŗ��̍������̕`��-----*/


	/*-----�������烂�[�^�[-----*/
	glPushMatrix();
	glTranslatef(0.3, -0.0, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	mySolidCylinder(0.5, 1.0, 12); 
	glPopMatrix();
	/*-----�����܂Ń��[�^�[-----*/

	/*-----��������r-----*/
	glPushMatrix();
	glTranslatef(0.5, -1.6, 0.0);
	mySolidCylinder(0.2, 3.5, 12); 
	glPopMatrix();
	/*-----�����܂ŋr-----*/


	/*-----��������y��-----*/
	glPushMatrix();
	glTranslatef(0.5, -3.2, 0.0);
	glScalef(3.0, 0.5, 3.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/*-----�����܂œy��-----*/

	glPopMatrix();


	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST );
	

	
	
	glutSwapBuffers();
}





void idle(void)/*�C�x���g���Ȃ����idle���˂Ɏ��s�����*/
{
	dist = fmod(dist + 0.1, 32.0);
	cam = fmod(cam + 0.1, 32.0);
	spin += speed;
	idleCosX = cosX - 0.1;
	glutPostRedisplay();/*�f�B�X�v���C�R�[���o�b�N�o�b�N�֐�(display)�����s*/
}

void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			mButton = button;
			break;
		case GLUT_MIDDLE_BUTTON:
			revolveFlag = !revolveFlag;
			if (revolveFlag == GL_TRUE)
				glutIdleFunc(idle); /*idle���J��Ԃ����s����悤�ɐݒ�*/
			else
				glutIdleFunc(NULL);/*�A�j���[�V�������Ƃ߂�*/
			break;
		case GLUT_RIGHT_BUTTON:
			mButton = button;
			break;
		}
		xBegin = x; /*�h���b�O�J�n�_��x,y���W�l���擾*/
		yBegin = y;
	}
}

void myMotion(int x, int y)
{
	int xDisp, yDisp;

	xDisp = x - xBegin; /*�}�E�X�ړ������̌v�Z*/
	yDisp = y - yBegin;

	switch (mButton) {
	case GLUT_LEFT_BUTTON:/*���{�^���̃h���b�O�ŕ��̂̎p����ς���*/
		tranceX += (float)xDisp / 8.0;
		tranceY += (float)yDisp / 8.0;
		tranceTheta -= (float)xDisp / 10.0;
		cosX -= (float)xDisp / 30.0;
		break;
	case GLUT_RIGHT_BUTTON:/*�E�{�^���̃h���b�O�ŃY�[��*/
		camX -= (float)xDisp / 4.0;
		camY += (float)yDisp / 4.0;
		break;
	}
	xBegin = x;/*���̃X�e�b�v�̃}�E�X�̏o���_*/
	yBegin = y;
	glutPostRedisplay();/*1�X�e�b�v���̃h���b�O�̌��ʂ�`��ɔ��f*/
}






void myKbd(unsigned char key,int x,int y)
{
	switch (key) {
	case '1':
		speed = 3;
		break;
	case '2':
		speed = 4;
		break;
	case '3':
		speed = 6;
		break;
	case '4':
		speed = 8;
		break;
	case KEY_ESC:
		exit(0);
	}
}

void initLighting(void)
{
	float diffuse[] = { 1.0,1.0,1.0,1.0 };
	float specular[] = { 0.5,0.5,1.0,1.0 };
	float ambient[] = { 0.5,0.5,0.5,1.0 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); /* �g�U���ː����̋��x */
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); /* ���ʔ��ː����̋��x */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); /* ���������̋��x */
	glEnable(GL_LIGHT0);
}

void myInit(char *progname)
{
	int width=640,height=480;
	float aspect =(float)width/(float)height;
	
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(progname);
	glClearColor(0.0,0.0,0.0,1.0);
	glutKeyboardFunc(myKbd);
	glutMouseFunc(myMouse);/*�}�E�X�N���b�N�ɑ΂���R�[���o�b�N�֐��̓o�^*/
	glutMotionFunc(myMotion);/*�}�E�X�h���b�O�ɑ΂���R�[���o�b�N�֐��̓o�^*/
	resetview();/*�r���[�C���O�ϊ�polarview�ɏ����p�����[�^�l��ݒ�*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspect,0.1,500.0);/*view volume ����*/
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	initLighting();
}

void resetview(void)
{
	camX = 0.0;
	camY = 0.0;
	twist = 0.0;
	tranceX = 0.0;
	tranceTheta = 0.0;
}



int main (int argc, char** argv)
{
	glutInit(&argc,argv);
	myInit(argv[0]);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	/*�C�x���g�������ꍇ�ɂ�idle���J��Ԃ����s����*/
	glutMainLoop();
	return(0);
}

	