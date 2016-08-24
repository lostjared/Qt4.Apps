#include "calc_window.h"
#include<iostream>
#include<iomanip>
#include<unordered_map>
#include<sstream>
#include<cmath>
#include<string>
#include"lexer.h"

std::unordered_map<std::string, double> variables;
std::unordered_map<std::string, lex::Func> functions;
std::ostringstream stream;

double val_sqrt(double d) { return sqrtf(d); }
double val_abs(double d) { return abs(static_cast<int>(d)); }
double val_print(double d) {
    stream << "value of variable: " << d << "\n";
    return d;
}
double val_cosf(double d) { return cosf(d); }
double val_sinf(double d) { return sinf(d); }
double val_log(double d) { return logf(d); }
double val_tan(double d) { return tanf(d); }
double val_rand(double d) { return std::rand()%static_cast<int>(d); }
double val_exit(double /*d*/) {
    throw lex::Exit_Exception();
    return 0;
}

void add_func(std::initializer_list<lex::Func> lst) {
    for(auto &i : lst) {
        functions[i.name] = i;
    }
}

/* end temporary */

void grabInput(const std::string &text) {
    
    if(text.length() == 0) {
        stream << "Please enter expressions each followed by a semi-colon.\n";
    	return;
    }
    
    if(text.find(";")  == std::string::npos) {
        stream << "Error missing semi-colon\n";
        return;
    }
    std::istringstream stream_in(text);
    lex::Parser pscan(stream_in, variables, functions);
    if(pscan.eval()) {
        for (auto &s : variables) {
            stream << std::setw(10) << s.first << " " << std::setw(10) << s.second << "\n";
        }
    }
}

void initFunctions() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    add_func({
        {"sqrt",val_sqrt}, {"abs",val_abs},
        {"print",val_print}, {"cos",val_cosf},
        {"sin",val_sinf}, {"tan",val_tan},
        {"log",val_log}, {"exit",val_exit},
        {"rand",val_rand}
    });
}

CalculatorWindow::CalculatorWindow(QWidget *parent) : QMainWindow(parent) {
    initFunctions();
    setGeometry(0,0,640,460);
    setWindowTitle(QObject::tr("Expression Calculator"));
    setFixedSize(640, 460);
    edit_box = new QTextEdit(this);
    edit_box->setGeometry(5, 5, 630, 420);
    proc = new QPushButton(QObject::tr("Parse"), this);
    proc->setGeometry(550, 430, 85, 20);
    connect(proc, SIGNAL(clicked()),this,SLOT(parse_expression()));
}

void CalculatorWindow::parse_expression() {
    const QString &text = edit_box->toPlainText();
    std::string temp_text = text.toUtf8().constData();
    try {
    	grabInput(temp_text);
    }
    catch(std::exception &e) {
        stream << e.what() << "\n";
    }
    catch(lex::Scanner_EOF) {
        stream << "end of file.\n";
    }
    catch(lex::Exit_Exception) {}
    
    QMessageBox msgbox;
    msgbox.setText(QObject::tr(stream.str().c_str()));
    msgbox.exec();
    stream.str("");
}
