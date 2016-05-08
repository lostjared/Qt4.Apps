#include "gameWidget.h"
#include<iostream>
#include<algorithm>

gameWidget::gameWidget(QWidget *parent) : QGLWidget(parent), gridRotX(0), gridRotY(0), gridRotZ(0) {

	setAutoBufferSwap(false);
	setAutoFillBackground(false);
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::SampleBuffers));
	setGeometry(10,10,780,580);

	glEnable(GL_TEXTURE_2D);

	for(int i = 0; i < 6; i++) {
		QString str;
		QTextStream txt(&str);
		txt << ":/images/block" << i << ".png";
		pixmaps[i] = QPixmap(str);
	}

	gamebg = QPixmap(":/images/background.png");
	startbg = QPixmap(":/images/start.png");

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(10);

	gameTimer = new QTimer(this);
	connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
	active = false;
	paused = false;
	scores_w_ =  new scoresWindow(parent);
	scores_w_->setWindowIcon(QIcon(pixmaps[4]));
	scores_w_->hide();

}

gameWidget::~gameWidget() {



}

void gameWidget::initalizeGL() {

	qglClearColor(Qt::black);
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glShadeModel( GL_SMOOTH );
	glEnable(GL_TEXTURE_2D);


}
void gameWidget::resizeGL(int w, int h) {

	if(h == 0) h = 1;
	glViewport( 0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat) w/h , 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);

}

void gameWidget::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	gridRotX = x;
	gridRotY = y;
	gridRotZ = z;
}

void gameWidget::paintEvent(QPaintEvent *) {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if(active == true) {
		mutatris.grid.update();
		render2D();
		render3D();
	}
	else {
		render2D_start();
		render3D_start();
	}

	swapBuffers();
}

void gameWidget::render2D_start() {
	QPainter painter(this);

#ifdef DEBUG_MODE_ON
	painter.setPen(QColor(255,255,255));
	painter.drawText(QPoint(600, 25), QObject::tr("Start Screen Debug Info "));
#endif

	painter.drawPixmap(QPoint(0,0), startbg);
}


void gameWidget::render3D_start() {


}

void gameWidget::render3D() {

	glLoadIdentity();


	glShadeModel(GL_SMOOTH);

	gluLookAt(0.0f, 0.0f , 90.0f , 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glTranslatef(-42.0f,32.0f, 0.0f);

	int i,z;



	glRotatef(gridRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(gridRotY, 0.0f, 1.0f, 0.0f);
	glRotatef(gridRotZ, 0.0f, 0.0f, 1.0f);


	for(i = 0; i < mutatris.GRID_W; i++) {
		for(z = 0; z < mutatris.GRID_H; z++) {

			if(mutatris.grid.data[i][z] != 0)
				renderCube(mutatris.grid.data[i][z]-1);

			for(int q = 0; q < 4; q++) {
				if(mutatris.current.blocks[q].x+mutatris.current.x == i && mutatris.current.blocks[q].y+mutatris.current.y == z) {
					renderCube((mutatris.current.blocks[q].index_color)-1);
				}
			}

			glTranslatef(0.0f, -3.0f, 0.0f);

		}
		glTranslatef(2.5f, 3.0f*mutatris.GRID_H, 0.0f);
	}


	glFlush();

}

void gameWidget::renderCube(int cube) {

	glEnable(GL_TEXTURE_2D);
	bindTexture(pixmaps[cube], GL_TEXTURE_2D, GL_RGBA);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

	glEnd();

}

void gameWidget::render2D() {

	QPainter painter(this);


	painter.drawPixmap(QPoint(0,0), gamebg);

#ifdef DEBUG_MODE_ON
	painter.setPen(QColor(255, 0, 0));
	painter.drawText(QPoint(10, 25), QObject::tr("Debug Mode - Info here"));
#endif

	QString str;
	QTextStream stream(&str);

	if(!isPaused())
	stream << QObject::tr("Score: ") << mutatris.grid.score << QObject::tr(" Blocks: ") << mutatris.grid.blocks_cleared;
	else
	stream << QObject::tr("Game Paused");

	painter.setPen(QColor(255,255,255));
	painter.drawText(QPoint(600,25), str);

	painter.setBrush(QBrush(QColor(0,0,0)));
	painter.drawRect(QRect(600,30, 160, 250));

	int offset_x = 620, offset_y = 120;


	for(unsigned int i = 0; i < 4; i++) {
		mp::blockType *block = &mutatris.next.blocks[i];
		int x_pos = block->x, y_pos=block->y;
		x_pos *= pixmaps[0].width();
		y_pos *= pixmaps[0].height();
		switch(mutatris.next.block_type)  {
		case mp::gameBlock::BLOCK_HORIZ:
			offset_x   = 660;
			break;
		case mp::gameBlock::BLOCK_VERT:
			offset_x =  620;
			break;
		case mp::gameBlock::BLOCK_SQUARE:
			offset_x = 640;
			break;
		}
		painter.drawPixmap(x_pos+offset_x, y_pos+offset_y, pixmaps[block->index_color]);
	}

	painter.setPen(QColor(255,255,255));
	painter.drawText(630, 80, QObject::tr("Next Block"));


}


void gameWidget::newGame(int level, bool inci) {
	mutatris.newGame();
	gameTimer->start(speed[level]);
	active = true;
	paused = false;
	game_level = true;
	incr = inci;
}

void gameWidget::togglePause() {
	if(active == false) return;
	paused = !paused;
}


void gameWidget::updateGame() {

	if(paused == true) return;

	if(mutatris.is_gameOver()==false)
		mutatris.update_moveDown();
	else {
		active = false;
		gameTimer->stop();
		scores_w_->enterScore(mutatris.grid.score);
	}

	if(incr == true && mutatris.increase == true) {
		mutatris.increase = false;

		if(game_level < 19) {
			++game_level;
			gameTimer->stop();
			gameTimer->start(speed[game_level]);
			printf("Increased game speed\n");
		}

	}
}

void gameWidget::showScoresWindow() {
	scores_w_->showScores();
}

scoresWindow::scoresWindow(QWidget *parent) : QDialog(parent) {

	setFixedSize(230, 320);
	setGeometry(25, 100, 230, 320);
	input_ = new QLineEdit("", this);
	input_->setGeometry(10, 10, 110, 25);
	enter_ = new QPushButton(QObject::tr("Enter Score"), this);
	enter_->setGeometry(120, 10, 100, 25);
	connect(enter_, SIGNAL(clicked()), this, SLOT(enter()));
	setWindowTitle(QObject::tr(" High Scores "));
	loadScores();

}

bool operator<(const scoresWindow::highScore &lhs, const scoresWindow::highScore &rhs) {
	if(lhs.score > rhs.score) return true;
	return false;
}

void scoresWindow::enter() {

	QString initials = input_->text();
	std::string  str = initials.toStdString();
	if(str.length() > 23) str = str.substr(0, 22);
	scores[9] = highScore(str.c_str(), cur_score);
	std::sort(scores.begin(), scores.end());
	showScores();
	update();
	saveScores();
}

void scoresWindow::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setPen(QColor(255, 0, 0));
	int coord_y = 75;

	for(unsigned int i = 0; i <  10; i++) {

		QString txt;
		QTextStream stream(&txt);
		stream << "Player: " <<  scores[i].name << ":  " <<  scores[i].score;
		painter.drawText(25, coord_y+(25*i), txt);
	}

}

void scoresWindow::showScores() {
	show();
	cur_score = 0;
	input_->setText("");
	setWindowTitle(QObject::tr(" High Scores "));
	input_->setEnabled(false);
	enter_->setEnabled(false);
}

void scoresWindow::enterScore(int score) {
	if(scores[9].score < score) {
		input_->setEnabled(true);
		enter_->setEnabled(true);
		show();
		setWindowTitle(QObject::tr("Enter Initials"));
		cur_score = score;
	}
}


void scoresWindow::loadScores() {

	std::fstream fobj;
	fobj.open("scores.dat", std::ios::binary | std::ios::in);
	if(!fobj.is_open()) {
		for(unsigned int i = 0; i < 10; i++)
			scores.push_back(highScore("anonymous", 0));
		saveScores();
		return;
	}
	for(unsigned int i = 0; i < 10 && !fobj.eof(); i++) {
		highScore scr;
		fobj.read((char*)&scr, sizeof(scr));
		scores.push_back(scr);
	}
	fobj.close();
}

void scoresWindow::saveScores() {
	std::fstream fobj;
	fobj.open("scores.dat", std::ios::binary | std::ios::out);
	for(unsigned int i = 0; i < 10; i++) {
		fobj.write((char*)&scores.at(i), sizeof(scores.at(i)));
	}
	fobj.close();
}


