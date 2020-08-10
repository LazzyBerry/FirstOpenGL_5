#include <gl/glut.h>

//�e��R�[���o�b�N�֐�

//�O�p�`�̕`��
void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.5f, 0.f);
	glVertex3f(-0.5f,-0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glEnd();
}

//xyz���̕`��
void drawXYZ()
{
	glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);//x���F��
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(200.f, 0.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);//y���F��
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 200.f, 0.f);

		glColor3f(0.f, 0.f, 1.f);//z���F��
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 200.f);
	glEnd();

	glColor3f(1.f, 1.f, 1.f);//�F�̃��Z�b�g
}


//�f�B�X�v���C
void display()
{
	static int angle = 0;

	//�o�b�t�@�̏�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�f�v�X�o�b�t�@�L����
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
		glTranslatef(1.f, 0.f, 0.f);
		glRotatef(float(angle), 0.f, 1.f, 0.f);
		glColor3f(1.f, 1.f, 0.f);//���F
		drawTriangle();
	glPopMatrix();

	glPushMatrix();
		glRotatef(float(angle), 0.f, 1.f, 0.f);
		glTranslatef(1.f, 0.f, 0.f);
		glColor3f(0.7f, 0.7f, 0.7f);//�D�F
		drawTriangle();
	glPopMatrix();

	drawXYZ();//xyz���̕`��

	glutSwapBuffers();

	//�f�v�X�o�b�t�@������
	glDisable(GL_DEPTH_TEST);

	if (++angle >= 360) {
		angle = 0; //��]�p�x�̃��Z�b�g
	}


	glFlush();
}

//�E�B���h�E�T�C�Y��ύX������
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);//�r���[�|�[�g�̐ݒ�

	glMatrixMode(GL_PROJECTION);//�ˉe�s��̐ݒ�
	glLoadIdentity();
	gluPerspective(30, (double)w / h, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW); //���f���r���[�s��̐ݒ�
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//�ĕ`�悷��p�̊֐�
//void idle()
//{
//	glutPostRedisplay();//�ĕ`�施��
//}

void timer(int t)
{
	glutPostRedisplay();//�ĕ`�施��
	glutTimerFunc(17, timer, t);//���Ȃ��Ƃ�17ms��
}
//���C���֐�

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); //GLUT�̏�����

	//Window�̍쐬
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //�f�B�X�v���C���[�h
	glClearDepth(1.f);
	glutCreateWindow("Timer Animation");


	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(idle);
	glutTimerFunc(0, timer, 17);

	//�J���[�o�b�t�@�̏�����
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop(); //���C�����[�v��

	return 0;
}