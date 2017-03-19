
#ifndef __KMPOP_H__
#define __KMPOP_H__

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
#include<QHBoxLayout>
#include<QVBoxLayout>

class OptionsDialog : public QDialog
{

Q_OBJECT

public:
	OptionsDialog(QWidget *parent = 0);
	void closeEvent(QCloseEvent *close);

	int getSpeed() const;
	void setSpeed(const int speed);
	int getMode() const;

protected:
	QSlider *slider_options;
	QSpinBox *spin_box;
	QPushButton *button_apply, *button_cancel;
	QRadioButton *rb_new, *rb_orig;
	int game_speed;
	int mode;

public slots:
	void ok();
	void cancel();

};


#endif
