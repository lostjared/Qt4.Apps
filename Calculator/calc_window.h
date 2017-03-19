#ifndef __CALC_WINDOW_H__
#define __CALC_WINDOW_H__

#include<QApplication>
#include<QMainWindow>
#include<QTextEdit>
#include<QPushButton>
#include<QWidget>
#include<QMessageBox>

class CalculatorWindow : public QMainWindow {
    Q_OBJECT
public:
    CalculatorWindow(QWidget *parent = 0);
    
public slots:
    void parse_expression();
    
private:
    
    QTextEdit *edit_box;
    QPushButton *proc;
    
};







#endif
