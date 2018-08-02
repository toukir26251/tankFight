#include <iostream>
#include<math.h>
#include<GL/gl.h>
#include <GL/glut.h>

using namespace std;

float posy=0.0;
float posx=0.0;
float posxCam=0.0;
float posyCam=0.0;
float rot = 0.0;
float x;
float y;
int score1=0;
int score2=0;
int score3=0;

float scaleScreen = 1;

int heroLife1 = 500;

float s1=0.1,s2=0.1,s3=0.1;

float f1=0.0;
float fk=0.0;

int flagD = 0;
int flagA = 0;
int flagW = 0;
int flagS = 0;

int kidRot =0;

int winner();
void path();

static float boss = 0.0, f = 1.0, posXX=0.0;
int flag = 1;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float _angle_2 = 90;
float i = 0.0f;
int bossLife = 500;
int heroLife = 30;
float bossF =0.0;
float seaColor = 0.0;
int seaFlag = 0;

void fire()
{
    glPushMatrix();
    glBegin(GL_POLYGON);
	glVertex2f(0.04,.4);
	glVertex2f(0.08,.4);
	glVertex2f(0.08,0.46);
	glVertex2f(0.06,0.5);
	glVertex2f(0.04,0.46);
	glEnd();
	glPopMatrix();

	//glEnd();
}


void bossFire()
{
    glPushMatrix();
    glColor3f(0.7,0.0,0.0);
    glTranslatef(0.0,-1.0,0.0);
    glutSolidSphere(0.03,20,20);
    glPopMatrix();
}


void collision()
{
    if(f>=3.5)
    if(posXX*10<20 && posXX*10>-20)
    {
        bossLife --;
        winner();
        //cout<<  <<endl;
    }
    if(bossF<-0.80)
    {
        if(_angle/10<posXX+.5 && _angle/10>posXX-.5)
        {
            heroLife --;
            cout<<heroLife<<endl;
            winner();
        }
        //cout<<_angle/10 << "\t"<<posXX<<endl;
    }
}

void heroLifeBar()
{
    glPushMatrix();
    glColor3f(1-heroLife*.05,0.0,heroLife*.05);
    glTranslatef(0.0,-2.40,0.0);
    glScalef(heroLife*.05,0.3,0.30);
    glutSolidCube(0.80);
    glPopMatrix();
}

void sea()
{

    glBegin(GL_QUADS);
    glColor3f(0.0,0.20,1.0);
    glVertex2f(1.2,-2.0);
    glVertex2f(3.0,-2.0);
    glColor3f(0.0,1.0,0.90);
    glVertex2f(3.0,-.50);
    glColor3f(0.3,seaColor,1.0);
    glVertex2f(1.2,-.50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3,0.65,0.05);
    glVertex2f(1.2,-0.50);
    glColor3f(0.6,0.75,0.1);
    glVertex2f(3.0,-0.50);
    glVertex2f(3.0,-.40);
    glColor3f(0.2,0.65,0.1);
    glVertex2f(1.1,-.40);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3,0.65,0.05);
    glVertex2f(1.1,-2.0);
    glColor3f(0.6,0.75,0.1);
    glVertex2f(1.2,-2.0);
    glVertex2f(1.2,-.50);
    glColor3f(0.2,0.65,0.1);
    glVertex2f(1.1,-.40);
    glEnd();


}



void hero()
{
    glPushMatrix();
    glColor3f(0.0,0.0,0.8);
    glScalef(0.60,0.50,4.50);
    //glRotatef(_angle,0.0,1.0,0.0);
    glTranslatef(-1.15,-.80,0.0);
    glutSolidTorus(.2,.2,70,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.60,0.50,4.50);
    //glRotatef(_angle,0.0,1.0,0.0);
    glTranslatef(1.15,-.80,0.0);
    glutSolidTorus(.2,.2,70,70);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glutSolidSphere(.3,15,15);

    glColor3f(1.0,0.0,0.0);
    glScalef(1.0,.5,1.2);
    glutSolidCube(0.60);

    glColor3f(0.6,0.0,0.0);
    //glScalef(1.3,1.0,1.0);
    glTranslatef(0.0,-0.50,0.0);
    glScalef(1.2,0.80,1.10);
    glutSolidCube(0.80);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.0,0.0,0.9);
    //glRotatef(_angle,0.0,1.0,0.0);
    glTranslatef(0.0,0.20,0.50);
    glScalef(0.70,1.0,7.0);
    glutSolidCube(.10);
    glPopMatrix();

    glPushMatrix();
    //glRotatef(40,1.0,0.0,0.0);
    glRotatef(-posXX*7,0.0,0.0,1.0);
    glTranslatef(0.0,f,0.0);
    fire();
    collision();
    glPopMatrix();

    heroLifeBar();

}

void lifeBar()
{
    glPushMatrix();
    glColor3f(1-bossLife*.002,bossLife*.002,0.0);
    glTranslatef(0.0,0.40,0.0);
    glScalef(bossLife*.002,0.1,0.10);
    glutSolidCube(1.0);
    glPopMatrix();
}

void bossBody()
{

    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glScalef(0.60,0.50,4.50);
    //glRotatef(_angle,0.0,1.0,0.0);
    glTranslatef(-1.15,-.80,-0.05);
    glutSolidTorus(.2,.2,70,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.60,0.50,4.50);
    //glRotatef(_angle,0.0,1.0,0.0);
    glTranslatef(1.15,-.80,-0.05);
    glutSolidTorus(.2,.2,70,70);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glutSolidSphere(.3,15,15);

    glColor3f(0.3,0.3,0.3);
    glScalef(1.0,.5,1.2);
    glutSolidCube(0.60);

    glColor3f(0.2,0.2,0.2);
    //glScalef(1.3,1.0,1.0);
    glTranslatef(0.0,-0.50,0.0);
    glScalef(1.2,0.80,1.10);
    glutSolidCube(0.80);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.18,0.18,0.18);
    glRotatef(_angle,0.0,1.0,0.0);
    glTranslatef(0.0,0.20,0.50);
    glScalef(0.70,1.0,7.0);
    glutSolidCube(.10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(_angle*2,0.0,1.0,0.0);
    glRotatef(-40,1.0,0.0,0.0);
    glTranslatef(0.0,bossF,0.3);
    bossFire();
    glPopMatrix();

    lifeBar();


    //glEnd();
    //glEnd();
}

void reshape(int w, int h)
{
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);

glLoadIdentity();
gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glClearColor(0.020, 0.80, 0.0, 0.0);
glTranslatef(0.0, 0.0, -5.0);
}

void gameOver()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    //init();

    //glScalef(1.0,1.0,1.0);

    glPushMatrix();
    glScalef(3.0,3.00,1.0);
    glTranslatef(-0.50,-0.50,0.0);
    path();
    glPopMatrix();

	glFlush();
	//glutSwapBuffers();
}

int winner()
{
	//strcpy(quote[0], "Game Over");

	//strcpy(quote[1], "Winner Is ");
	//	strcpy_s(quote[2], );
	//strcpy(quote[2], "Player ");
	//strcpy(quote[3], &a);
	//numberOfQuotes = 5;

	if(heroLife<=0 || bossLife <=0 || heroLife1<=0)
    {
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(1360, 750);
        glutCreateWindow("Game Over");
        //glClearColor(0.0, 0.80, 0.0, 0.0);
        //glLineWidth(3);

        glutDisplayFunc(gameOver);
        glutReshapeFunc(reshape);
        //glutTimerFunc(25, update1, 0);
        //glutIdleFunc(timeTick);
        glutMainLoop();

        return 0;
    }
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);

    //glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(posXX, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0,-3.0);

	glPushMatrix();
	glRotatef(-40,1.0,0.0,0.0);
	glBegin(GL_QUADS);
	glColor3f(0.5,0.45,0.35);
	glVertex2f(-4.0,1.50);
	glVertex2f(4.0,1.50);
	glVertex2f(5.0,4.0);
	glVertex2f(-5.0,4.0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-40,1.0,0.0,0.0);
	glTranslatef(-1.0,0.0,0.0);
	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0.4);
	glVertex2f(-2.0,0.58);
	glVertex2f(-0.55,0.58);
	glVertex2f(-0.55,1.5);
	glVertex2f(-2.0,1.5);

	glColor3f(0.5,0.45,0.4);
	glVertex3f(-0.55,0.58,0.0);
	glVertex3f(-0.55,0.53,-.05);
	glVertex3f(-0.55,1.5,-.05);
	glVertex3f(-0.55,1.5,0.0);

	glColor3f(0.5,0.45,0.4);
	glVertex3f(-2.0,0.52,-0.05);
	glVertex3f(-0.55,0.52,-0.05);
	glVertex3f(-0.55,0.58,0.0);
	glVertex3f(-2.0,0.58,0.0);

	glEnd();


	glPopMatrix();


	glPushMatrix();
	glScalef(.8,.8,.8);
	glTranslatef(0.0,1.0,0.0);
	glRotatef(40,1.0,0.0,0.0);
	bossBody();
	//glTranslatef(posXX,0.0,0.0);
	//hero();
	glPopMatrix();

	glPushMatrix();

	glScalef(.3,.3,.3);
	glTranslatef(posXX,0.0,0.0);
	glTranslatef(0.0,-2.50,0.0);
	glRotatef(180,0.0,1.0,0.0);
	glRotatef(-40,1.0,0.0,0.0);
	hero();
    //fire();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,-2.0);
	glRotatef(-40,1.0,0.0,0.0);

	glBegin(GL_QUADS);
	glColor3f(0.1,0.50,0.0);
	glVertex2f(-3.50,-2.20);
	glVertex2f(3.50,-2.20);
	glColor3f(0.8,0.75,0.0);
	glVertex2f(7.50,4.30);
	glVertex2f(-7.50,4.30);

	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.20,0.3,0.0);
	glScalef(1.2,.7,.8);
	glRotatef(10,1.0,1.0,0.0);

	glPushMatrix();
	glScalef(1.0,.4,.2);
	glTranslatef(-1.80,0.80,0.0);
	glColor3f(0.6,0.60,0.50);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.80,0.8,.2);
	glTranslatef(-2.67,0.90,0.0);
	glColor3f(0.6,0.60,0.50);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.50,0.8,.2);
	glTranslatef(-2.84d,0.85,0.0);
	glColor3f(0.6,0.60,0.50);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.50,0.5,.2);
	glTranslatef(-1.31,1.90,0.0);
	glColor3f(0.6,0.60,0.50);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();

	glPushMatrix();

	glScalef(0.25,.25,.25);
	glTranslatef(4.65,4.24,-0.05);
	glRotatef(-90,0.0,1.0,0.0);
	//glRotatef(-15,0.0,0.0,1.0);

	glColor3f(0.55,0.5,0.40);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1.0,-0.47);
	glVertex2f(0.95,-2.0);
	glVertex2f(-1.0,1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45,1.0,0.0,0.0);
	glScalef(.85,.5,.5);
	glTranslatef(2.85,2.25,0.0);
	glBegin(GL_QUADS);
	glColor3f(0.6,0.60,0.40);
	glVertex2f(-1.0,-0.10);
	glVertex2f(1.05,-0.10);
	glVertex2f(1.05,0.10);
	glVertex2f(-1.0,0.10);
	glEnd();
	glPopMatrix();

	glTranslatef(1.80,0.90,0.0);
    glRotatef(10,1.0,0.0,0.0);

	glPushMatrix();
	glScalef(2.50,0.20,0.20);
	//glTranslatef(1.0,1.0,0.0);
	glColor3f(0.55,.50,0.40);
	glutSolidCube(.5);

	glPopMatrix();

	glPushMatrix();
	glScalef(2.50,0.20,0.20);
	glTranslatef(0.0,-1.0,1.0);
	glColor3f(0.55,0.50,0.40);
	glutSolidCube(.5);

	glPopMatrix();

	glPushMatrix();
	glScalef(2.50,0.20,0.20);
	glTranslatef(0.0,-0.50,0.50);
	glColor3f(0.6,0.60,0.40);
	glutSolidCube(.5);

	glPopMatrix();

	glPushMatrix();
	glScalef(2.50,0.20,0.20);
	glTranslatef(0.0,0.50,-0.50);
	glColor3f(0.60,0.60,0.40);
	glutSolidCube(.5);

	glPopMatrix();
	glPushMatrix();
	glScalef(2.50,0.20,0.20);
	glTranslatef(0.0,1.0,-1.0);
	glColor3f(0.55,0.50,0.40);
	glutSolidCube(.5);

	glPopMatrix();
	glPushMatrix();
	glScalef(2.50,0.20,0.20);
	glTranslatef(0.0,1.50,-1.50);
	glColor3f(0.60,0.60,0.40);
	glutSolidCube(.5);

	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotatef(-40,1.0,0.0,0.0);
	sea();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,0.0);
	glRotatef(-40,1.0,0.0,0.0);
	glRotatef(180,0.0,1.0,0.0);
	sea();
	glPopMatrix();

	//glPopMatrix();

	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
switch (key) {


        case 'd':

        if(posXX<2.5)
        posXX+=.1;
        glutPostRedisplay();
        break;

        case 'a':

        if(posXX>-2.5)
        posXX-=.1;
        glutPostRedisplay();
        break;

        default:
        break;

}
}

void update(int value) {
	if(flag==0)
    {
        _angle += 0.20f;
        if (_angle > 20) {
            flag =1;
        }
    }
    if(flag==1)
    {
        _angle -= 0.20f;
        if (_angle < -20) {
            flag =0;
        }
    }

	f += 0.06f;
	if (f > 4) {
		f -= 4;
	}
	bossF -= 0.04f;
	if (bossF < -1.0) {
		bossF += 1.6;
	}
	if(seaFlag==0)
    {
       seaColor+=.005;
        if(seaColor>.5)
        {
            seaFlag=1;
        }
    }
    if(seaFlag==1)
    {
       seaColor-=.005;
        if(seaColor<0.0)
        {
            seaFlag=0;
        }
    }


	glutPostRedisplay();

	glutTimerFunc(25, update, 0);
}


int finalStage()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1366, 700);

	glutCreateWindow("Tank Fight");
	initRendering();


	glutDisplayFunc(drawScene);

	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}

void rota()
{
    //glTranslatef(-posx,-posy,0.0);
    glScalef(.6,1.0,1.0);
    glRotatef(rot,0.0,0.0,1.0);
    //glTranslatef(,0.0,0.0);
}

void path()
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2f(.15,.3);
    glVertex2f(.20,.3);
    glVertex2f(.20,.6);
    glVertex2f(.15,.6);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(.10,.6);
    glVertex2f(.25,.6);
    glVertex2f(.25,.7);
    glVertex2f(.10,.7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(.32,.3);
    glVertex2f(.37,.3);
    glVertex2f(.37,.7);
    glVertex2f(.32,.7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(.42,.3);
    glVertex2f(.47,.3);
    glVertex2f(.47,.7);
    glVertex2f(.42,.7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(.37,.6);
    glVertex2f(.42,.6);
    glVertex2f(.42,.7);
    glVertex2f(.37,.7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(.53,.3);
    glVertex2f(.68,.3);
    glVertex2f(.68,.7);
    glVertex2f(.53,.7);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(.75,.3);
    glVertex2f(.90,.3);
    glVertex2f(.90,.7);
    glVertex2f(.75,.7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2,0.8,0.0);
    glVertex2f(.62,.5);
    glVertex2f(.63,.5);
    glVertex2f(.63,.7);
    glVertex2f(.62,.7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2,0.8,0.0);
    glVertex2f(.58,.3);
    glVertex2f(.59,.3);
    glVertex2f(.59,.5);
    glVertex2f(.58,.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2,0.8,0.0);
    glVertex2f(.80,.6);
    glVertex2f(.81,.6);
    glVertex2f(.85,.7);
    glVertex2f(.84,.7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2,0.8,0.0);
    glVertex2f(.80,.4);
    glVertex2f(.81,.4);
    glVertex2f(.85,.3);
    glVertex2f(.84,.3);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2,0.8,0.0);
    glVertex2f(.85,.5);
    glVertex2f(.90,.39);
    glVertex2f(.90,.61);
    glEnd();
}

void heroLifeBar1()
{
    glPushMatrix();
    glColor3f(1-heroLife1*.002,0.0,heroLife1*.002);
    glTranslatef(0.0,-.25,0.0);
    //glTranslatef(0.0,-2.40,0.0);
    glScalef(heroLife1*.02,0.5,0.5);
    glutSolidCube(0.05);
    glPopMatrix();
}

void collission()
{
    if(posx>.80 && posy>.45 && rot == 0)
       {
            score3++;
            cout<<score3<<endl;

       }
    if(posx>.65 && posy>.75 && rot ==-90)
    {
        score3++;
            cout<<score3<<endl;
    }
    if(posx<.16 && posy>.70 && rot == 90)
       {
            score1++;
            cout<<score1<<endl;
       }
    if(posx>.35 && posx<.45 && posy>.1 && rot == 0)
    {
        score2++;
        cout<<score2<<endl;
        kidRot =180;
        //heroLife1--;
    }
    if(posx>=.38 && posx<=.42 && posy>=.54 && rot ==180)
    {
        score2++;
        cout<<score2<<endl;
        kidRot =0;
    }
    if(posx<=-.02 && posx>=-.04 && posy>=.14 && rot == 0)
    {
        score1++;
        cout<<score1<<endl;
    }
    if(posx<=-.02 && posx>=-.04 && posy>=.10 && s1 !=0)
    {
        heroLife1--;
        cout<<heroLife1<<endl;
            winner();
    }
    if(posx>.35 && posx<.45 && posy>.1 && rot == 0 && s2!=0)
    {
        heroLife1--;
    }
    if(posx>=.38 && posx<=.42 && posy>=.54 && s2!=0)
    {
        heroLife1--;
        cout<<heroLife1<<endl;
            winner();
    }
    if(posx>.5 && posy>.75 && rot ==-90 && s3!=0)
    {
        heroLife1--;
        cout<<heroLife1<<endl;
            winner();
    }
    if(score1>300)
    {
        s1=0;
    }
    if(score2>300)
    {
        s2=0;
    }
    if(score3>300)
    {
        s3=0;
    }
}

void fire1()
{
    glPushMatrix();
    glBegin(GL_POLYGON);
	glVertex2f(-0.02,.3);
	glVertex2f(0.02,.3);
	glVertex2f(0.02,0.36);
	glVertex2f(0.00,0.4);
	glVertex2f(-0.02,0.36);
	glEnd();
	glPopMatrix();

	//glEnd();
}



void hero1()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.4, .8);
    glVertex3f(-.1, .2, 0);
    glVertex3f(-.20,.2, 0);
    glVertex3f(-.20,-.20, 0);
    glVertex3f(-.1,-.20, 0);

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);

    glVertex3f(.1,.1, 0);
    glVertex3f(-.1,.1, 0);
    glVertex3f(-.1,-.1, 0);
    glVertex3f(.1,-.1, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,0,1);
    for(int i=0;i<100;i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/100;
        float r=.05;
        float x=r*cos(A);
        float y=r*sin(A);
        glVertex3f(x,y,0.0);
    }
glEnd();

     glBegin(GL_QUADS);

glColor3f(0.0, 0.4, .8);
    glVertex3f(.2,.2, 0);
    glVertex3f(.1,.2, 0);
    glVertex3f(.1,-.20, 0);
    glVertex3f(.2,-.20, 0);


glBegin(GL_QUADS);

    glColor3f(0, 0, 1);
    glVertex3f(.02,.3, 0);
    glVertex3f(-.02,.3, 0);
    glVertex3f(-.02,.0, 0);
    glVertex3f(.02,.0, 0);

    glEnd();

    glPushMatrix();
    glTranslatef(0.0,f1,0.0);
    fire1();
    collission();
    glPopMatrix();
    cout<<posx<<","<<posy<<endl;
    heroLifeBar1();
}

void kid()
{
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.3, .3);
    glVertex3f(-.1, .2, 0);
    glVertex3f(-.20,.2, 0);
    glVertex3f(-.20,-.20, 0);
    glVertex3f(-.1,-.20, 0);

    glBegin(GL_QUADS);
    glColor3f(.2, 0.2, 0.2);

    glVertex3f(.1,.1, 0);
    glVertex3f(-.1,.1, 0);
    glVertex3f(-.1,-.1, 0);
    glVertex3f(.1,-.1, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3,0.3,.3);
    for(int i=0;i<100;i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/100;
        float r=.05;
        float x=r*cos(A);
        float y=r*sin(A);
        glVertex3f(x,y,0.0);
    }
glEnd();

     glBegin(GL_QUADS);

glColor3f(0.3, 0.3, .3);
    glVertex3f(.2,.2, 0);
    glVertex3f(.1,.2, 0);
    glVertex3f(.1,-.20, 0);
    glVertex3f(.2,-.20, 0);


glBegin(GL_QUADS);

glColor3f(0.3, 0.3, .3);
    glVertex3f(.02,.3, 0);
    glVertex3f(-.02,.3, 0);
    glVertex3f(-.02,.0, 0);
    glVertex3f(.02,.0, 0);



glEnd();

    glPushMatrix();
    glTranslatef(0.0,fk,0.0);
    fire1();
    glPopMatrix();

    //kidLifeBar();

}

void init(void)
{
/* select clearing (background) color */
glClearColor(0.020, 0.80, 0.0, 0.0);
/* initialize viewing values */
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
gluOrtho2D(0.0,1,0.0,1);
}

void display()
{
/* clear all pixels */
glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
init();
glTranslatef(-posxCam*1.3,-posyCam*1.4,0.0);
glScalef(2.0*scaleScreen,2.0*scaleScreen,2.0*scaleScreen);

//glColor3f(0.0, 1.0, 0.0);//(R,G,B)

//Draw a triangle using line.
glPushMatrix();
glTranslatef(posx,posy,0.0);
//glRotatef(rot,0,1,1);

//glPushMatrix();
glTranslatef(.1,.1,0);
glScalef(.2,.2,0.0);
rota();
hero1();

glPopMatrix();

glPushMatrix();
path();
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,.5,0);
glScalef(s2,.2,0.0);
glRotatef(kidRot,0.0,0.0,1.0);
kid();
glPopMatrix();

glPushMatrix();
glTranslatef(0.95,0.90,0);
glScalef(s3,.2,0.0);
glRotatef(90,0.0,0.0,1.0);
kid();
glPopMatrix();

glPushMatrix();
glTranslatef(0.07,0.85,0);
glScalef(s1,.2,0.0);
glRotatef(180,0.0,0.0,1.0);
kid();
glPopMatrix();
if(scaleScreen<=.5)
    finalStage();


glFlush();

//cout <<f<<","<<fk<<","<<posx<<","<<posy<<endl;
}


void keyboard1(unsigned char key, int x, int y)
{
switch (key) {
case 'w': /* s key rotates at shoulder */
//shoulder = (shoulder + 5) % 360;
if(posx>0.21 && posx<.27 && posy>.13 && posy<.63)
        flagW = 1;
else if(posx>0.03 && posx<.13 && posy>.13 && posy<.63)
        flagW = 1;
else if(posx>=0.0 && posx<.17 && posy>=.46 && posy<.62)
        flagW = 1;
else if(posx>0.26 && posx<.32 && posy>.45 && posy<.63)
        flagW = 1;
else if(posx>0.31 && posx<.38 && posy>.13 && posy<.63)
        flagW = 1;
else if(posx>0.43 && posx<.62 && posy>.13 && posy<.63)
        flagW = 1;
else if(posx>0.63 && posx<.80 && posy>.13 && posy<.63)
        flagW = 1;
else if(posy>.82)
        flagW = 1;
else
    flagW = 0;
if(flagW==0)
{
    posy +=0.02f;
    posyCam+=0.02;
}
rot=0;
glutPostRedisplay();
break;
case 's':
//shoulder = (shoulder - 5) % 360;
if(posx>0.21 && posx<.27 && posy>.14 && posy<.67)
        flagS = 1;
else if(posx>0.03 && posx<.13 && posy>.14 && posy<.67)
        flagS= 1;
else if(posx>=0.0 && posx<.17 && posy>.47 && posy<.67)
        flagS = 1;
else if(posx>0.26 && posx<.32 && posy>.47 && posy<.64)
        flagS = 1;
else if(posx>0.31 && posx<.38 && posy>.14 && posy<.67)
        flagS = 1;
else if(posx>0.43 && posx<.62 && posy>.14 && posy<.67)
        flagS = 1;
else if(posx>0.63 && posx<.80 && posy>.14 && posy<.67)
        flagS = 1;
else if(posy<- .04)
    flagS= 1;
else
    flagS = 0;
if(flagS==0)
{
    posy -=0.02f;
    posyCam-=0.02;
}
rot=180;
glutPostRedisplay();
break;


case 'd':
//shoulder = (shoulder - 5) % 360;
if(posx>0.17 && posx<.3 && posy>.17 && posy<.63)
        flagD = 1;
else if(posx>0.01 && posx<.08 && posy>.17 && posy<.63)
        flagD = 1;
else if(posx>-0.05 && posx<.19 && posy>.45 && posy<.63)
        flagD = 1;
else if(posx>0.3 && posx<.4 && posy>.17 && posy<.63)
        flagD = 1;
else if(posx>0.4 && posx<.6 && posy>.17 && posy<.63)
        flagD = 1;
else if(posx>0.6 && posx<.8 && posy>.17 && posy<.63)
        flagD = 1;
else if (posx>.86)
    flagD=1;
else
    flagD = 0;

if(flagD == 0)
    {
        posx+=.02;
        posxCam+=.02;
    }

rot=-90;
glutPostRedisplay();
break;

case 'a':
//shoulder = (shoulder - 5) % 360;
if(posx>0.2 && posx<.3 && posy>.17 && posy<.63)
        flagA = 1;
else if(posx>0.03 && posx<.15 && posy>.17 && posy<.63)
        flagA = 1;
else if(posx>=0.0 && posx<.19 && posy>=.46 && posy<.63)
        flagA = 1;
else if(posx>0.3 && posx<.4 && posy>.17 && posy<.63)
        flagA = 1;
else if(posx>0.4 && posx<.6 && posy>.17 && posy<.63)
        flagA = 1;
else if(posx>0.6 && posx<.84 && posy>.17 && posy<.63)
        flagA = 1;
else if(posx <-.04 )
        flagA = 1;
else
    flagA = 0;

if(flagA == 0)
{
    posx -=0.02f;
    posxCam -= .02;
}
cout<<posx<<","<<posy<<endl;
rot=90;
glutPostRedisplay();
break;

//case 'r':
   // rot
  }
}

void update1(int value) {

    f1 += 0.06f;
	if (f1 > 1) {
		f1 -= 1;
	}

	fk += 0.06f;
	if (fk > 2.5) {
		fk -= 2.5;
	}
	if(s1 == 0 && s2==0 && s3 == 0)
    {
            posxCam=0;
            posyCam=0;
            if(scaleScreen>=.5)
            {
                scaleScreen-=.005;
            }
    }

	glutPostRedisplay();


	glutTimerFunc(25, update1, 0);
}


int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(1366, 700);
//glutFullScreen();
glutInitWindowPosition(0, 0);
glutCreateWindow("Tank Fight");
glutDisplayFunc(display);
glutKeyboardFunc(keyboard1);
glutTimerFunc(25, update1, 0);
glutMainLoop();
return 0;
}

