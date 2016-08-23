
#ifndef __QT_TEST__
#define __QT_TEST__

#include<QtGui>
#include<iostream>

class MyQPushButton : public QPushButton {
public:
    MyQPushButton(QString str, QWidget *parent) : QPushButton(str, parent), name(str) {}
    
    ~MyQPushButton() {
        std::cout << name.toUtf8().constData() << " released..\n";
    }
private:
    QString name;
};

class Window1 : public QMainWindow {
    Q_OBJECT
public:
    Window1(QWidget *parent = 0);
    ~Window1();
    void setPos();
    
public slots:
    void sayHello();
private:
    MyQPushButton *button1;
};


#endif
