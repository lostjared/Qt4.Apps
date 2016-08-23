#include "test_window.h"


Window1::Window1(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Memory Check");
    setGeometry(0,0,640,480);
    button1 = new MyQPushButton("Hello", this);
    button1->setGeometry(0,0,640,480);
    button1->show();
    connect(button1, SIGNAL(clicked()), this, SLOT(sayHello()));
}

Window1::~Window1() {
    std::cout << "Destructor called for Window1 Object\n";
}

void Window1::setPos() {
    setGeometry(680, 0, 640, 480);
}

void Window1::sayHello() {
    QMessageBox msgbox;
    msgbox.setText("Hello World with connect");
    msgbox.exec();
}
