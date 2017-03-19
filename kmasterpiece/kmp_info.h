#ifndef __KMP_INFO__H_
#define __KMP_INFO__H_

#include<QDialog>
#include<QWidget>
#include<QCloseEvent>
#include<QSlider>
#include<QSpinBox>
#include<QPushButton>
#include<QRadioButton>
#include<QLabel>
#include<QImage>
#include<QPainter>

class infoWindow : public QDialog {


Q_OBJECT



public:
	infoWindow(QWidget *parent = 0);
	void closeEvent(QCloseEvent *q);
	void showMessage(const char *string);
	void paintEvent(QPaintEvent *);

public slots:
	void ok();

protected:
	QLabel *text;
	QImage lg;

};










#endif

