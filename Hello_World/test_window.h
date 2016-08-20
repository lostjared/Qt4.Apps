
#ifndef __QT_TEST__
#define __QT_TEST__

#include<QtGui>
#include<iostream>

class Window1 : public QMainWindow {
    
    Q_OBJECT
    
public:
    Window1(QWidget *parent = 0);
    void hello_world();
    
};


#endif
