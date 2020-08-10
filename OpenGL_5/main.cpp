#include <gl/glut.h>

//各種コールバック関数

//三角形の描画
void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.5f, 0.f);
	glVertex3f(-0.5f,-0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glEnd();
}

//xyz軸の描画
void drawXYZ()
{
	glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);//x軸：赤
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(200.f, 0.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);//y軸：緑
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 200.f, 0.f);

		glColor3f(0.f, 0.f, 1.f);//z軸：青
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 200.f);
	glEnd();

	glColor3f(1.f, 1.f, 1.f);//色のリセット
}


//ディスプレイ
void display()
{
	static int angle = 0;

	//バッファの初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//デプスバッファ有効化
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
		glTranslatef(1.f, 0.f, 0.f);
		glRotatef(float(angle), 0.f, 1.f, 0.f);
		glColor3f(1.f, 1.f, 0.f);//黄色
		drawTriangle();
	glPopMatrix();

	glPushMatrix();
		glRotatef(float(angle), 0.f, 1.f, 0.f);
		glTranslatef(1.f, 0.f, 0.f);
		glColor3f(0.7f, 0.7f, 0.7f);//灰色
		drawTriangle();
	glPopMatrix();

	drawXYZ();//xyz軸の描画

	glutSwapBuffers();

	//デプスバッファ無効化
	glDisable(GL_DEPTH_TEST);

	if (++angle >= 360) {
		angle = 0; //回転角度のリセット
	}


	glFlush();
}

//ウィンドウサイズを変更した際
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);//ビューポートの設定

	glMatrixMode(GL_PROJECTION);//射影行列の設定
	glLoadIdentity();
	gluPerspective(30, (double)w / h, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW); //モデルビュー行列の設定
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//再描画する用の関数
//void idle()
//{
//	glutPostRedisplay();//再描画命令
//}

void timer(int t)
{
	glutPostRedisplay();//再描画命令
	glutTimerFunc(17, timer, t);//少なくとも17ms後
}
//メイン関数

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); //GLUTの初期化

	//Windowの作成
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //ディスプレイモード
	glClearDepth(1.f);
	glutCreateWindow("Timer Animation");


	//コールバック関数登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(idle);
	glutTimerFunc(0, timer, 17);

	//カラーバッファの初期化
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop(); //メインループへ

	return 0;
}