#include "kmp_window.h"
#include<QTextStream>



void mpWindow::loadPixmaps()
{
	QString data_name;

	QTextStream stream(&data_name);


	for(unsigned int i = 0; i < 9; i++)
	{
		data_name = "";
		stream << "data/block" << i+1 << ".png";
		QPixmap pix(data_name);
		gpix << pix;
	}

	 

}

mpWindow::mpWindow() : intro("data/intro.png")
{

	game_started = false;
	loadPixmaps();

	setFixedSize(640,480);
	setWindowTitle("KMasterPiece");

	file_menu = menuBar()->addMenu(tr("&File"));
	file_new = new QAction(tr("&New Single Player"), this);
	file_new->setShortcut(tr("Ctrl+N"));
	file_new->setStatusTip(tr("Start a new Game"));
	file_new->setIcon(QIcon(gpix.at(0)));
	connect(file_new, SIGNAL(triggered()), this, SLOT(newGame()));
	file_menu->addAction(file_new);

	options_menu = menuBar()->addMenu(tr("&Options"));
	edit_options = new QAction(tr("Edit Options"), this);
	edit_options->setShortcut(tr("Ctrl+O"));
	edit_options->setStatusTip(tr("Edit Game Options"));
	edit_options->setIcon(QIcon(gpix.at(1)));
	connect(edit_options, SIGNAL(triggered()), this, SLOT(showOptions()));

	options_menu->addAction(edit_options);

	score_option = new QAction(tr("Highscores"), this);
	score_option->setShortcut(tr("Ctrl+H"));
	score_option->setStatusTip(tr("View / Edit Highscores"));
	score_option->setIcon(QIcon(gpix.at(4)));

	connect(score_option, SIGNAL(triggered()), this, SLOT(showScores()));

	options_menu->addAction(score_option);


	help_menu = menuBar()->addMenu(tr("&Help"));
	help_about = new QAction(tr("&About"), this);
	help_about->setShortcut(tr("Ctrl+A"));
	help_about->setStatusTip(tr("About dialog"));
	help_about->setIcon(QIcon(gpix.at(2)));
	connect(help_about, SIGNAL(triggered()), this, SLOT(showAbout()));


	help_menu->addAction(help_about);



	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(gameIdle()));
	
	update_timer = new QTimer(this);
	connect(update_timer, SIGNAL(timeout()), this, SLOT(gameUpdate()));


	this->setWindowIcon(QIcon(gpix.at(6)));




}


void mpWindow::newGame()
{
	game.newGame();
	int op_speed = op_dlg.getSpeed();

	timer->stop();
	update_timer->stop();
	timer->start(op_speed);
 	update_timer->start(100);
	game_started = true;

}

void mpWindow::gameIdle()
{
	if(game_started == true) 
	{
		game.moveDown();
		if(game.isOver() == true)
		{
			game_started = false;
			scores.gameOver(game.getScore());

		}

	}

}

void mpWindow::gameUpdate()
{
	if(game_started == true)
		game.update();
	repaint();
	
	

}

void mpWindow::paintEvent(QPaintEvent *)
{
	QImage temp_image(size(), QImage::Format_ARGB32_Premultiplied);
	QPainter paint(&temp_image);


	if(game_started == true) 
	{
		paint.fillRect(QRect(0,0,640,480), QColor(0,0,0));
		drawTiles(paint);
	}
	else
	{

		paint.drawPixmap(QPoint(0,0), intro);

	}


	QPainter flip_paint(this);
	flip_paint.drawImage(0,0, temp_image);

}

void mpWindow::drawTiles(QPainter &p)
{

	QString data_string;
	QTextStream stream(&data_string);
	stream << "Score: " << game.getScore();	
	p.setPen(QColor(255,255,255));
	p.drawText(500,50, data_string);
	data_string = "";
	stream << "Lines: " << game.getLines();
	p.setPen(QColor(255,0,0));
	p.drawText(500,80, data_string);



	int offset_x , offset_y;
	const mpBlock *b = game.getBlock();
	offset_x = 40;
	offset_y = 25;

	int i,z;

	for(i = 0; i < TILE_W; i++)
	{

		for(z = 0; z < TILE_H; z++)
		{


				if(game(i,z) != 0)
				{
					int x_pos = offset_x + ( i*32 );
					int y_pos = offset_y + ( z*16 );

					p.drawPixmap(QPoint(x_pos, y_pos), gpix.at(game(i,z)));

				}


		}

	}

	for(i = 0; i < TILE_W; i++)
	{
		for(z = 0; z < TILE_H; z++)
		{
			if(b->x == i && b->y == z)
			{
				int x_pos = offset_x + ( i*32 );
				int y_pos = offset_y + ( z*16 );
				p.drawPixmap(QPoint(x_pos, y_pos),  gpix.at(b->block_a[0]));
				x_pos = offset_x + ((i)*32);
				y_pos = offset_y + ((z+1)*16);
				p.drawPixmap(QPoint(x_pos, y_pos), gpix.at(b->block_a[1]));
				x_pos = offset_x + ((i)*32);
				y_pos = offset_y + ((z+2)*16);
				p.drawPixmap(QPoint(x_pos,y_pos), gpix.at(b->block_a[2]));
				break;
			} 


		}
	
	}

	




}

void mpWindow::keyPressEvent(QKeyEvent *e)
{

	int key_down = e->key();

	switch(key_down)
	{
	case Qt::Key_Left:
	game.moveLeft();
	break;
	case Qt::Key_Right:
	game.moveRight();
	break;
	case Qt::Key_Up:
	break;
	case Qt::Key_Down:
	game.moveDown();
	break;
	case Qt::Key_A:
	case Qt::Key_S:
	game.shiftBlock();
	break;
	}

}

void mpWindow::showOptions()
{

	op_dlg.show();

}

void mpWindow::showAbout()
{
	about_window.showMessage("");
}

void mpWindow::showScores()
{

	scores.show();

}
