#ifndef __KMP__H__
#define __KMP__H__

#include<QMainWindow>
#include<QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QKeyEvent>
#include<QTimer>
#include<QPixmap>
#include<QMenu>
#include<QAction>
#include<QLabel>
#include<QList>
#include<QMenuBar>
#include "mp.h"
#include "kmp_op.h"
#include "kmp_info.h"
#include "kmp_highscore.h"



class mpWindow : public QMainWindow {

Q_OBJECT

public:
	mpWindow();
	void paintEvent(QPaintEvent *p);
	void drawTiles(QPainter &p);
	void keyPressEvent(QKeyEvent *e);
public slots:
	void newGame();
	void gameIdle();
	void gameUpdate();
	void showOptions();
	void showAbout();
	void showScores();


protected:

	QList<QPixmap> gpix;

	QMenu *file_menu, *options_menu, *help_menu;
	QAction *file_new, *edit_options, *score_option, *help_about;
	QTimer *timer;
	QTimer *update_timer;
	mpGame game;
	QPixmap intro;
	OptionsDialog op_dlg;
	infoWindow   about_window;
	highScores   scores;
	bool game_started;

	void loadPixmaps();






};



#endif
