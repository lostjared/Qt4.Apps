#ifndef __KMP__HIGHSCORES__H_
#define __KMP__HIGHSCORES__H_

#include<QtGui>
#include<QStringList>
#include<vector>

struct Scorer {

	std::string name, scr;
	int     score;

	Scorer(const Scorer &c);
	Scorer();

	void init(const Scorer &c);

	Scorer& operator=(const Scorer &c);

};

class highScores : public QDialog {

Q_OBJECT

public:

	highScores(QWidget *parent = 0);
	void readFromFile();
	void promptCreate();
	void paintEvent(QPaintEvent *e);
	void closeEvent(QCloseEvent *c);
	void gameOver(const int score);

public slots:
	void add();
	
protected:
	
	std::vector<struct Scorer> vec;
	void sort();
	void loadlist();
	void savelist();
	QTextEdit edit;
	QPushButton bt_one;
	QListWidget lst;
	QLabel scr_label;
	int new_score;


};





#endif


