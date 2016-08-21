#include "test_window.h"


Window1::Window1(QWidget *parent) : QMainWindow(parent), button1("Hello", this) {
    hello_world();
    button1.setGeometry(0,0,250,25);
    button1.show();
    connect(&button1, SIGNAL(clicked()), this, SLOT(sayHello()));
}

void Window1::hello_world() {
    std::cout << "Hello World\n";
    setWindowTitle("Hello World");
    setGeometry(0,0,640,480);
    
}

void Window1::sayHello() {
    QMessageBox msgbox;
    msgbox.setText("Hello World with connect");
    msgbox.exec();
}
