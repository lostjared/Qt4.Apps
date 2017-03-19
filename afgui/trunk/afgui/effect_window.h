#ifndef _EFFECTWINDOW_H_
#define _EFFECTWINDOW_H_


#include<QDialog>
#include<QMainWindow>
#include<QWidget>
#include<QMenu>
#include<QAction>
#include<QImage>
#include<QListWidget>
#include<QLineEdit>
#include<QSlider>
#include<QCheckBox>
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QMenuBar>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDIalog>
#include<QFile>
#include<QPainter>

extern QString pathstr;


	class flameWindow : public QDialog {
	
		Q_OBJECT
	
	public:
		flameWindow(QWidget *parent = 0);
	
		QLineEdit *command;
		QSlider *slider;
		QCheckBox *cbox;
		QListWidget *images;
		QPushButton *add_image, *clear_list, *flame;
		
				
	public slots:
		void setValue(int val);
		void addImages();
		void clrList();
		void flameIt();
		QString changed();
		
	protected:
		void addItems(QStringList &list);
		QString change_str;
				
	};



	class effectWindow : public QMainWindow {
		
		Q_OBJECT
		
	protected:
		QMenu *file;
		QAction *new_af;
		flameWindow *fw;
		QImage bgimg;
		 
	public:
		effectWindow(QWidget *parent = 0);		
		void paintEvent(QPaintEvent *p);
		
	
	public slots:
	
		void onNewAf();
		void reloadImage();
		
	
	
	};







#endif

