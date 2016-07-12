#ifndef __QT_GAMEWINDOW_H_
#define __QT_GAMEWINDOW_H_

// cool
#define DEBUG_MODE_ON


#include<QtCore>
#include<QtGui>
#include<QtOpenGL>
#ifdef __APPLE__
#include<OpenGL/glu.h>
#else
#include<GL/glu.h>
#endif
#include"mpmut.h"
#include<vector>
#include<fstream>
#include<string>
#include<iostream>

static const int speed[] = { 0, 1400, 1300, 1200, 1100, 1000, 900, 850, 800, 750, 700, 650, 600, 500, 400, 300, 200, 150, 125, 100, 75, 0 };

class scoresWindow : public QDialog  {

	Q_OBJECT
public:
	scoresWindow(QWidget *parent = 0);
	void showScores();
	void enterScore(int score);

	struct highScore {
		char name[25];
		int score;
		highScore() { }
		highScore(const char *name, int score) {
			strncpy(this->name, name,24);
			if(strlen(name) < 24) this->name[strlen(name)] = 0;
			else this->name[24] = 0;
			this->score = score;
		}
	};

protected:
	void paintEvent(QPaintEvent *);
public slots:
	void enter();
private:
	QLineEdit *input_;
	QPushButton *enter_;
	int cur_score;
	std::vector<highScore> scores;

	void loadScores();
	void saveScores();
};

class gameWidget : public QGLWidget {

	Q_OBJECT
public:
	gameWidget(QWidget *parent = 0);
	~gameWidget();

	void newGame(int level, bool inci);
	void togglePause();
	mp::mxMut *mutatris_object() { return &mutatris; }
	void setRotation(GLfloat x, GLfloat y, GLfloat z);
	bool isPaused() const { return paused; }
	QPixmap &operator[](unsigned int i) {  return pixmaps[i]; }
	void showScoresWindow();

protected:
	void initalizeGL();
	void resizeGL(int width, int height);
	void paintEvent(QPaintEvent *);
private:
	scoresWindow *scores_w_;
	mp::mxMut mutatris;
	QPixmap pixmaps[6], gamebg, startbg;
	QTimer *timer, *gameTimer;
	GLfloat gridRotX, gridRotY, gridRotZ;
	bool active;
	bool paused;
	int game_level;
	bool incr;

	void render3D();
	void render2D();
	void render2D_start();
	void render3D_start();

	void renderStartScreen();
	void renderCube(int cube);

public slots:
	void updateGame();

};


#endif
