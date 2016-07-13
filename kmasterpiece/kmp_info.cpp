#include "kmp_info.h"



infoWindow::infoWindow(QWidget *parent) : QDialog(parent), lg("data/logo.png")
{
	
	
	text = new QLabel("");
	QPushButton *bt = new QPushButton("Ok");
	
	setFixedSize(480,272);

	setWindowTitle(tr("KMasterPiece"));

	connect(bt, SIGNAL(clicked()), this , SLOT(ok()));

	
	bt->setFixedSize(100,25);
	bt->setGeometry(480-120,270-35, 100, 25);
	bt->setParent(this);
	
	

}

void infoWindow::paintEvent(QPaintEvent *)
{

	QPainter p(this);

	p.drawImage(QPoint(0,0), lg);


}


void infoWindow::closeEvent(QCloseEvent *)
{

	hide();

}


void infoWindow::showMessage(const char *string)
{
	text->setText(tr(string));
	show();

}

void infoWindow::ok()
{
	hide();
}

