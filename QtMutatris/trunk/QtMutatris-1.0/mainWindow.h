#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__


#include<QtGui>
#include<QtCore>
#include "gameWidget.h"

class optionsWindow;
class aboutWindow;
class scoresWindow;

class mainWindow : public QMainWindow {

	Q_OBJECT

public:
	mainWindow(QWidget *parent = 0);
	void keyPressEvent(QKeyEvent *key);
protected:
	gameWidget glGameWidget;
	QMenu *game, *options, *help;
	QAction *newGame_, *pauseGame_, *highScores_;
	QAction *showOptions_, *rotAngled_, *rotFlat_;
	QAction *about_, *how_;
public slots:
	void newGame();
	void pauseGame();
	void highScores();
	void showOptions();
	void showAbout();
	void showHow();
	void setAngled();
	void setFlat();

private:
	bool game_active;
	optionsWindow *options_w_;
	aboutWindow *about_w_;
};

class optionsWindow : public QDialog {
	Q_OBJECT
public:
	optionsWindow(QWidget *parent = 0);
	int getSpeedLevel() const;
public slots:
	void valueChangedTo(int);
	void Ok();
private:
	QSlider *game_speed;
	QLabel  *game_label_text;
	QCheckBox *cbox;
	QPushButton *ok;
	friend class mainWindow;
};

class aboutWindow : public QDialog {
	Q_OBJECT
public:
	aboutWindow(QWidget *parent = 0);
	void startAbout();
protected:
	void paintEvent(QPaintEvent *);
public slots:
	void ok();
private:
	QPushButton *ok_button_;
	QTimer *timer;
	QPixmap pix;
};



#endif

