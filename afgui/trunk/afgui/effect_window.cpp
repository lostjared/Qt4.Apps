#include"effect_window.h"
#include<sstream>


QString pathstr;


effectWindow::effectWindow(QWidget *parent) : QMainWindow(parent)
{
		
	setWindowTitle(tr("AlphaFlame Editor"));	
	file = menuBar()->addMenu(tr("&File"));
	new_af = new QAction(tr("New Alphaflame"), this);
	new_af->setShortcut(tr("Ctrl+A"));
	new_af->setStatusTip(tr(" New alpha flame filter "));
	new_af->setIcon(QIcon(pathstr+"img/icon.png"));
	connect( new_af, SIGNAL(triggered()), this, SLOT(onNewAf()) );
	file->addAction(new_af);
	
	fw = 0;
	
	bgimg.load(pathstr+"img/splash.png");
	
	setFixedSize(bgimg.width(), bgimg.height());
	this->setWindowIcon(QIcon(pathstr+"img/icon.png"));
	
}


void effectWindow::onNewAf() {
	
	if(fw == 0) {
		fw = new flameWindow();
		connect(fw, SIGNAL(accepted()), this, SLOT(reloadImage()));	
	}
	fw->show();	
}

void effectWindow::paintEvent(QPaintEvent *) {
	
	QPainter paint(this);
	paint.drawImage( QPoint(0,0), bgimg);
	
}
void effectWindow::reloadImage() {
	
	
	QString str = fw->changed();
	bgimg.load(str);
	setFixedSize(bgimg.width(), bgimg.height());
	repaint();
	
	QString txt;
	QTextStream ss(&txt);
	ss << " AlphaFlame Editor: " << str;
	setWindowTitle(txt);
	
}

flameWindow::flameWindow(QWidget *parent) : QDialog(parent) 
{
	
	setGeometry( 50, 50, 475, 240 );
	setWindowTitle(" AlphaFlame Effect Settings ");
	
	command = new QLineEdit("aftool list.txt 10 output.png");
	slider = new QSlider(Qt::Horizontal);
	slider->setRange(1, 500);
	QLabel *lbl = new QLabel ("Command: ");
	QHBoxLayout *v = new QHBoxLayout;
	command->setFixedSize(140, 23);	
	
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	
	v->addWidget(lbl);
	v->addWidget(command);
	v->addWidget(slider);
	
	QVBoxLayout *vbox = new QVBoxLayout;
	QHBoxLayout *vv = new QHBoxLayout;
	
	QLabel *lbl2 = new QLabel(" Morph: ");
	vv->addWidget(lbl2);
	
	cbox = new QCheckBox("first");
	vv->addWidget(cbox);
	
	add_image = new QPushButton("Add Images");
	clear_list = new QPushButton("Clear List");
	
	vv->addWidget(add_image);
	vv->addWidget(clear_list);
	
	clear_list->setEnabled(false);
	
	cbox->setChecked( true );

	connect(add_image, SIGNAL(clicked()), this, SLOT(addImages()));
	connect(clear_list, SIGNAL(clicked()), this, (SLOT(clrList())));
	
	images = new QListWidget();
	
	QHBoxLayout *vvv = new QHBoxLayout;
	
	vvv->addWidget(images);
	
	QHBoxLayout *v4 = new QHBoxLayout;
	
	flame = new QPushButton(" AlphaFlame It ");
	flame->setEnabled(false);
	
	connect(flame, SIGNAL(clicked()), this, SLOT(flameIt()));
		
	QLabel *l = new QLabel(" Press Button when Ready: ");
	
	v4->addWidget(l);
	v4->addWidget(flame);
		
	vbox->addItem(v);
	vbox->addItem(vv);
	vbox->addItem(vvv);
	vbox->addItem(v4);
	
	setLayout(vbox);
	slider->setSliderPosition(10);
	command->setReadOnly(true);
	
	setWindowIcon(QIcon(pathstr+"img/icon.png"));
	
		
}

void flameWindow::setValue(int val) {

	char data[1024];
	sprintf(data, "aftool list.txt %d output.png %s", val, (cbox->checkState() == Qt::Checked) ? "-m" : "-a");;
	command->setText(data);
	command->setSelection(0,0);
}

void flameWindow::addImages() {
	
	
	 QStringList files = QFileDialog::getOpenFileNames(this,"Select one or more files to open", "","Images (*.png)");
	 addItems(files);
}

void flameWindow::clrList() {
	
	images->clear();
	clear_list->setEnabled(false);
	flame->setEnabled(false);
}

void flameWindow::addItems(QStringList &list) {
	
	int i = 0;
	for(i = 0; i < list.size(); i++) 
		images->addItem(list[i]);
	

	if(images->count() > 0) clear_list->setEnabled(true);
	if(images->count() >= 4) flame->setEnabled(true);
	
}

void flameWindow::flameIt() {
	
	 QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),"output.png",tr("Images (*.png)"));
	
	 if(filename != "") {
		 std::string str = filename.toStdString();
		 std::ostringstream ss;
		 
		 QString cmode = "";
		 
		 if(cbox->checkState() == Qt::Checked) cmode = "-m"; 
		 else cmode = "-a";
		 		 
		 ss << "\"" << pathstr.toStdString()  << "aftool\" list.txt " << slider->value() << " \"" << str << "\" " << cmode.toStdString() << "\n";
		 QFile fptr ("list.txt");
		 if(!fptr.open( QIODevice::WriteOnly | QIODevice::Text ))
			 return;
		 
		 QTextStream txtstr(&fptr);
		 for(int i = 0; i < 4; i++) {
			QListWidgetItem *wid = images->item(i);
			txtstr << wid->text() << "\n";
		 }
		 fptr.close();
		 if( system(ss.str().c_str()) == 0 ) {
			 QString strz = "Ran Command: ";
			 strz += ss.str().c_str();
			 QMessageBox::information(this, "Command Ran", strz);
			 change_str = filename;
			 accept();
		 } else QMessageBox::information(this, "Error", "a error has occoured");
	 }
	
}

QString flameWindow::changed() { return change_str; }