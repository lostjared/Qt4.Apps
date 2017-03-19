#include<iostream>
#include"test_window.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
   
    Window1 *win1 = new Window1();
    win1->show();
    Window1 win2; // destructor will be called automatically when we leave scope
    win2.setPos();
    win2.show();
    app.exec();
    
    delete win1; // delete all child objects that this is the parent for
    // will be deleted when win1 is deleted
    
    
    return 0;
}

