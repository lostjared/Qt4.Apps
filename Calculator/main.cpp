#include"calc_window.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    CalculatorWindow calc;
    calc.show();
    app.exec();
    return 0;
}