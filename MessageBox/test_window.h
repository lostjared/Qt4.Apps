
#ifndef __QT_TEST__
#define __QT_TEST__

#include<QMainWindow>
#include<QWidget>
#include<QPushButton>
#include<QMessageBox>
#include<iostream>

class Window1 : public QMainWindow {
    
    Q_OBJECT
    
public:
    Window1(QWidget *parent = 0);
    void hello_world();
    
public slots:
    void sayHello();
private:
    QPushButton button1;
    
};


#endif
