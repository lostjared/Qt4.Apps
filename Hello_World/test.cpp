#include<QtGui>
#include<iostream>
#include"test_window.h"



int main(int argc, char **argv) {
    
    QApplication app(argc, argv);
    Window1 win1;
    win1.show();
    app.exec();
    
    return 0;
}