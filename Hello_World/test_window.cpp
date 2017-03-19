#include<iostream>
#include "test_window.h"


Window1::Window1(QWidget *parent) : QMainWindow(parent) {
    hello_world();
}

void Window1::hello_world() {
    std::cout << "Hello World\n";
    setWindowTitle("Hello World");
    setGeometry(0,0,640,480);
    
}

