#include "kmp_highscore.h"
#include<QFile>
#include<iostream>
#include<vector>
#include<sstream>


Scorer::Scorer()
{
	score = 0;

}

void Scorer::init(const Scorer &c)
{
	std::stringstream s;
	s << c.score;
	scr = s.str();
	score = c.score;
	name = c.name;

}

Scorer::Scorer(const Scorer &c)
{

	init(c);

}

Scorer& Scorer::operator=(const Scorer &c)
{

	init(c);
	return *this;

}

highScores::highScores(QWidget *parent) : QDialog(parent), edit(this), bt_one("Enter", this), lst(this), scr_label(this)
{

	setFixedSize(350,240);
	setWindowTitle("Game Highscores");
	readFromFile();
	edit.setGeometry(170,10,100,25);
	bt_one.setGeometry(275,10,50,25);
	connect(&bt_one, SIGNAL(clicked()), this, SLOT(add()));

	lst.setGeometry(10,10,140,200);
	scr_label.setGeometry(170, 150, 160, 50);
	scr_label.setText("Current Game Highscores");

	edit.hide();
	bt_one.hide();
	new_score = 0;
	loadlist();


}

void highScores::loadlist()
{

	lst.clear();
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		QString text;
		QTextStream stream (&text);

		stream << "(" << (i+1) << ") " <<  vec.at(i).name.c_str() << " : " << vec.at(i).score;

		lst.addItem( text );

	}


}


void highScores::add()
{

	QString text,tname,tscore;
	QTextStream stream(&text);

	tname = edit.toPlainText();

	if(tname.size() <= 0)
	{
		// error message
		return;

	}

	stream << new_score;
	int pos = vec.size()-1;
	vec.at(pos).name = tname.toStdString();
	vec.at(pos).score = new_score;
	vec.at(pos).scr = text.toStdString();

	savelist();
	edit.hide();
	bt_one.hide();
	loadlist();
	scr_label.setText("Current High Scores");
	
}

void highScores::readFromFile()
{

	QFile data(".kmp");
	data.open(QIODevice::ReadWrite | QIODevice::Text);

	if(data.error())
	{
		promptCreate();
		return;
	}


	QTextStream stream(&data);

	for(int i = 0; i < 10 || !data.atEnd(); i++)
	{

		QString line = stream.readLine();
		if(line == "") break;
		struct Scorer r;
		QStringList lst = line.split(":");
		r.name = lst.at(0).toStdString();
		r.score = lst.at(1).toInt();
		r.scr = lst.at(1).toStdString();
		vec.push_back( r );

	}

	data.close();



}

bool operator<(const Scorer &c, const Scorer &c2)
{
	if(c.score > c2.score) return true;
	return false;

}


void highScores::closeEvent(QCloseEvent *)
{
	savelist();
	
}

void highScores::savelist()
{
	QFile fptr(".kmp");
	fptr.open(QIODevice::WriteOnly);
	QTextStream stream(&fptr);

	sort();
	
	for(unsigned int i = 0; i < vec.size(); i++)
	{

		stream << vec.at(i).name.c_str() << ":" << vec.at(i).score << "\n";

	}

	fptr.close();
}

void highScores::sort()
{
	std::sort(vec.begin(), vec.end());
}


void highScores::promptCreate()
{

	QFile data(".kmp");
	data.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream stream(&data);

	for(int i = 0; i  < 10; i++) stream << "Anonymous:" << "0\n";


	data.close();
}

void highScores::paintEvent(QPaintEvent *)
{

/*

	QImage temp_image(size(), QImage::Format_ARGB32_Premultiplied);
	QPainter paint(&temp_image);

	unsigned int i, y_down = 25;

	paint.setPen(QColor(255, 0, 0) );


	for(i = 0; i < vec.size(); i++)
	{

		paint.setPen(QColor(255, 0, 0) );
		paint.drawText(QPoint(25, y_down), vec.at(i).name.c_str());
		paint.setPen(QColor(0, 255, 0) );
		paint.drawText(QPoint(100, y_down), vec.at(i).scr.c_str());
		y_down += 20;

	}

	QPainter ptr(this);
	ptr.drawImage(QPoint(0,0), temp_image); */
	
}

void highScores::gameOver(const int score)
{
	int len = vec.size();
	if(len > 0)
	{

		int temp_pos = len-1;
		int temp_score = vec.at(temp_pos).score;

		if(score > temp_score)
		{
			new_score = score;
			bt_one.show();
			edit.show();
			show();
			scr_label.setText("New High Score");
			
		}

	}

}


