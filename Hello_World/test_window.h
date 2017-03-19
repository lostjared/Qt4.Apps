
#ifndef __QT_TEST__
#define __QT_TEST__

#include<QMainWindow>
#include<QWidget>
#include<QLabel>
#include<QApplication>

class Window1 : public QMainWindow {
    
    Q_OBJECT
    
public:
    Window1(QWidget *parent = 0);
    void hello_world();
    
};


#endif
