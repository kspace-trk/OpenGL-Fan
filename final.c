#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <math.h>
#include "myShape.h"
#define KEY_ESC 27
#define WIDTH 320
#define HEIGHT 240

float dist=0.0; /*物体の移動量*/
float cam = 0.0; /*視点の移動量*/

void polarview(void);
void resetview(void);
unsigned char wireFlag = GL_TRUE;
unsigned char revolveFlag = GL_FALSE;/*回転のON/OFF切り替え*/
int xBegin, yBegin;/*ドラッグ開始時点のマウスポインタの座標*/
int mButton;/*ドラッグ時に押されているマウスボタンの判別*/
float camX, camY, twist, tranceY, tranceX, tranceTheta, cosX, idleCosX, spin, speed;
float theta = 15.0;

void display(void)
{

	int i;
	int w;
	float diffuse[] = { 1.0,1.0,1.0,1.0 };
	float specular[] = { 1.0,1.0,1.0,1.0 };
	float ambient[] = { 0.3,0.3,0.3,1.0 };
	float light[] = { 1.0,1.0,1.0,0.0 }; /* 光源の位置と種類 */
	glLightfv(GL_LIGHT0, GL_POSITION, light); /* 平行光源の設定 */
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


	/*-----ここから翼の描画-----*/
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

     /*-----ここまで翼の描画-----*/


	/*-----ここから外枠-----*/

	
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
	


	/*-----ここまで外枠-----*/
	/*-----ここから外枠円-----*/
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


	/*-----ここまで外枠円-----*/





	/*-----ここから翼の根っこの描画-----*/
	glPushMatrix();/*座標系の保存*/
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(-90.0, 1.0, -10.0, 0.0);
	glutSolidCone(0.2, 1.0, 12, 1);
	glPopMatrix();
	/*-----ここまで翼の根っこの描画-----*/


	/*-----ここからモーター-----*/
	glPushMatrix();
	glTranslatef(0.3, -0.0, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	mySolidCylinder(0.5, 1.0, 12); 
	glPopMatrix();
	/*-----ここまでモーター-----*/

	/*-----ここから脚-----*/
	glPushMatrix();
	glTranslatef(0.5, -1.6, 0.0);
	mySolidCylinder(0.2, 3.5, 12); 
	glPopMatrix();
	/*-----ここまで脚-----*/


	/*-----ここから土台-----*/
	glPushMatrix();
	glTranslatef(0.5, -3.2, 0.0);
	glScalef(3.0, 0.5, 3.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/*-----ここまで土台-----*/

	glPopMatrix();


	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST );
	

	
	
	glutSwapBuffers();
}





void idle(void)/*イベントがなければidleがつねに実行される*/
{
	dist = fmod(dist + 0.1, 32.0);
	cam = fmod(cam + 0.1, 32.0);
	spin += speed;
	idleCosX = cosX - 0.1;
	glutPostRedisplay();/*ディスプレイコールバックバック関数(display)を実行*/
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
				glutIdleFunc(idle); /*idleを繰り返し実行するように設定*/
			else
				glutIdleFunc(NULL);/*アニメーションをとめる*/
			break;
		case GLUT_RIGHT_BUTTON:
			mButton = button;
			break;
		}
		xBegin = x; /*ドラッグ開始点のx,y座標値を取得*/
		yBegin = y;
	}
}

void myMotion(int x, int y)
{
	int xDisp, yDisp;

	xDisp = x - xBegin; /*マウス移動距離の計算*/
	yDisp = y - yBegin;

	switch (mButton) {
	case GLUT_LEFT_BUTTON:/*左ボタンのドラッグで物体の姿勢を変える*/
		tranceX += (float)xDisp / 8.0;
		tranceY += (float)yDisp / 8.0;
		tranceTheta -= (float)xDisp / 10.0;
		cosX -= (float)xDisp / 30.0;
		break;
	case GLUT_RIGHT_BUTTON:/*右ボタンのドラッグでズーム*/
		camX -= (float)xDisp / 4.0;
		camY += (float)yDisp / 4.0;
		break;
	}
	xBegin = x;/*次のステップのマウスの出発点*/
	yBegin = y;
	glutPostRedisplay();/*1ステップ分のドラッグの結果を描画に反映*/
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

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); /* 拡散反射成分の強度 */
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); /* 鏡面反射成分の強度 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); /* 環境光成分の強度 */
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
	glutMouseFunc(myMouse);/*マウスクリックに対するコールバック関数の登録*/
	glutMotionFunc(myMotion);/*マウスドラッグに対するコールバック関数の登録*/
	resetview();/*ビューイング変換polarviewに初期パラメータ値を設定*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspect,0.1,500.0);/*view volume 注意*/
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
	/*イベントが無い場合にはidleを繰り返し実行する*/
	glutMainLoop();
	return(0);
}

	