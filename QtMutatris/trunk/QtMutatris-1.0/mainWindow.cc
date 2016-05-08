#include "mainWindow.h"


mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), glGameWidget(this) {
	setWindowIcon(QIcon(glGameWidget[4]));
	setFixedSize(800, 600);
	setWindowTitle(QObject::tr("QtMutatris"));
	game = menuBar()->addMenu(QObject::tr("File"));
	newGame_ = new QAction(QObject::tr("New Game"), this);
	newGame_->setIcon(QIcon(glGameWidget[1]));
	pauseGame_ = new QAction(QObject::tr("Pause"), this );
	pauseGame_->setIcon(QIcon(glGameWidget[2]));
	pauseGame_->setCheckable(true);
	highScores_ = new QAction(QObject::tr("High Scores"), this );
	highScores_->setIcon(QIcon(glGameWidget[3]));
	connect(newGame_, SIGNAL(triggered()), this, SLOT(newGame()));
	connect(pauseGame_, SIGNAL(triggered()), this, SLOT(pauseGame()));
	connect(highScores_, SIGNAL(triggered()), this, SLOT(highScores()));
	game->addAction(newGame_);
	game->addAction(pauseGame_);
	game->addAction(highScores_);
	options = menuBar()->addMenu(QObject::tr("Options"));
	showOptions_ = new QAction(QObject::tr("Preferences"), this);
	connect(showOptions_, SIGNAL(triggered()), this, SLOT(showOptions()));
	options->addAction(showOptions_);
	rotAngled_ = new QAction(QObject::tr("Grid Angled"), this);
	connect(rotAngled_, SIGNAL(triggered()), this, SLOT(setAngled()));
	options->addAction(rotAngled_);
	rotFlat_ = new QAction(QObject::tr("Grid Flat"), this);
	connect(rotFlat_, SIGNAL(triggered()), this, SLOT(setFlat()));
	options->addAction(rotFlat_);
	game_active = false;
	rotFlat_->setCheckable(true);
	rotAngled_->setCheckable(true);
	setFlat();
	rotAngled_->setIcon(QIcon(glGameWidget[5]));
	rotFlat_->setIcon(QIcon(glGameWidget[4]));
	options_w_ = new optionsWindow(this);
	options_w_->hide();
	help = menuBar()->addMenu(QObject::tr("Help"));
	how_ = new QAction(QObject::tr("How to Play"), this);
	how_->setIcon(QIcon(glGameWidget[4]));
	connect(how_, SIGNAL(triggered()), this, SLOT(showHow()));
	help->addAction(how_);
	about_= new QAction(QObject::tr("About"), this);
	connect(about_, SIGNAL(triggered()), this, SLOT(showAbout()));
	help->addAction(about_);
	about_w_ = new aboutWindow(this);
	about_w_->hide();
	pauseGame_->setChecked(false);
}

void mainWindow::newGame() {
	glGameWidget.newGame(options_w_->getSpeedLevel(), options_w_->cbox->isChecked());
	game_active = true;
}

void mainWindow::pauseGame() {
	glGameWidget.togglePause();
	pauseGame_->setChecked(glGameWidget.isPaused());
}

void mainWindow::highScores() {
	glGameWidget.showScoresWindow();
}
void mainWindow::showOptions() {
	options_w_->show();
}

void mainWindow::showAbout() {

	about_w_->show();
	about_w_->startAbout();

}

void mainWindow::showHow() {

	QMessageBox::information(this, "", "How to Play:\n\nObject of the game is to clear as many blocks as possible you do this by aligning 4 blocks of the same color either horizontal, vertical, or in a square\n\nControls:\n\nUse the Left and Right arrows to move the blocks left and right, use the Up arrow or the A key to switch colors, and use the P key to pause the game.", 1, 0, 0);


}

void mainWindow::setAngled() {
	glGameWidget.setRotation(25.0f, 25.0f, 0.0f);
	rotAngled_->setChecked(true);
	rotFlat_->setChecked(false);
}
void mainWindow::setFlat() {
	glGameWidget.setRotation(-10.0f, 0.0f, 0.0f);
	rotFlat_->setChecked(true);
	rotAngled_->setChecked(false);
}

void mainWindow::keyPressEvent(QKeyEvent *key) {

	if(game_active == false || glGameWidget.isPaused()) return;

		int k = key->key();
		switch(k) {
		case Qt::Key_Left:
			glGameWidget.mutatris_object()->moveLeft();
			break;
		case Qt::Key_Right:
			glGameWidget.mutatris_object()->moveRight();
			break;
		case Qt::Key_Down:
			glGameWidget.mutatris_object()->moveDown();
			break;
		case Qt::Key_A:
		case Qt::Key_Up:
			glGameWidget.mutatris_object()->shiftColor();
			break;
		case Qt::Key_P:
			glGameWidget.togglePause();
			pauseGame_->setChecked(glGameWidget.isPaused());
			break;
		default:
			break;
		}

}

optionsWindow::optionsWindow(QWidget *parent) : QDialog(parent) {

	setFixedSize(320,150);
	setGeometry(50,100,320,150);
	setWindowTitle(QObject::tr("Game Options"));

	game_speed = new QSlider(Qt::Horizontal, this);
	game_speed->setGeometry(10, 10, 300, 25);
	game_speed->setRange(1, 20);
	game_speed->setSliderPosition(14);
	game_label_text = new QLabel(QObject::tr("Game Speed: 14"), this);
	game_label_text->setGeometry(10, 45, 300, 20);

	connect(game_speed, SIGNAL(valueChanged(int)), this, SLOT(valueChangedTo(int)));

	cbox = new QCheckBox(QObject::tr("Accumulating Speed"), this);
	cbox->setGeometry(10,70,300,25);

	ok = new QPushButton(QObject::tr("Ok"), this);
	ok->setGeometry(10,100,100,25);

	connect(ok, SIGNAL(clicked()), this, SLOT(Ok()));

}

void optionsWindow::valueChangedTo(int pos) {
	QString text;
	QTextStream stream(&text);
	stream << QObject::tr("Game Speed: ") << pos;
	game_label_text->setText(text);
}

int optionsWindow::getSpeedLevel() const {
	return game_speed->sliderPosition();
}

void optionsWindow::Ok() {
	hide();
}

aboutWindow::aboutWindow(QWidget *parent) : QDialog(parent) {
	setFixedSize(320, 240);
	setGeometry( 25, 100, 320, 240);
	setWindowTitle(QObject::tr("About QtMutatris"));
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	ok_button_ = new QPushButton(QObject::tr("Ok"), this);
	ok_button_->setGeometry(10, 210, 100, 25);
	connect(ok_button_, SIGNAL(clicked()), this, SLOT(ok()));
	pix = QPixmap(":/images/block1.png");
}

void aboutWindow::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(QBrush(QColor(0,0,0)));
	painter.setPen(QColor(255,0,0));
	painter.drawPixmap(320/2-pix.width()/2, 55, pix);
	painter.drawText(55, 29, QObject::tr("QtMutatris (C) 2009 LostSideDead"));
	painter.setPen(QColor(0,0,255));
	painter.drawText(55, 120, QObject::tr("written by Jared Bruni"));
	painter.drawText(55, 160, QObject::tr("email: jared@lostsidedead.biz"));
}

void aboutWindow::ok() {
	timer->stop();
	hide();
}

void aboutWindow::startAbout() {
	timer->start(300);

}



