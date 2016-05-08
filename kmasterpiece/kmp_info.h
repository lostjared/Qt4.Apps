#ifndef __KMP_INFO__H_
#define __KMP_INFO__H_
#include<QtGui>



class infoWindow : public QDialog {


Q_OBJECT



public:
	infoWindow(QWidget *parent = 0);
	void closeEvent(QCloseEvent *q);
	void showMessage(char *string);
	void paintEvent(QPaintEvent *);

public slots:
	void ok();

protected:
	QLabel *text;
	QImage lg;

};










#endif

