#ifndef __CALC_WINDOW_H__
#define __CALC_WINDOW_H__

#include<QtGui>
#include<QtCore>

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
