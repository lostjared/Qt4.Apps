#include "kmp_op.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent)
{
	game_speed = 600;
	setFixedSize(320,150);
	setWindowTitle(tr("Options Menu"));

	spin_box = new QSpinBox;
	slider_options = new QSlider(Qt::Horizontal);
	slider_options->setRange(1, 1500);
	spin_box->setRange(1, 1500);
	QHBoxLayout *layout = new QHBoxLayout;
	QLabel *label = new QLabel(tr("Game Speed"));
	layout->addWidget(label);
	layout->addWidget(spin_box);
	layout->addWidget(slider_options);
	
	QVBoxLayout *layout2 = new QVBoxLayout;
	
	layout2->addLayout(layout);

	rb_new = new QRadioButton(tr("New Style"), this);
	rb_orig = new QRadioButton(tr("Original Style"), this);

	QHBoxLayout *radio_layout = new QHBoxLayout;
	radio_layout->addWidget(rb_new);
	radio_layout->addWidget(rb_orig);

	layout2->addLayout(radio_layout);
	
	button_apply = new QPushButton(tr("Apply"));
	button_cancel = new QPushButton(tr("Cancel"));
	
	QHBoxLayout *layout3 = new QHBoxLayout;

	layout3->addWidget(button_apply);
	layout3->addWidget(button_cancel);

	layout2->addLayout(layout3);
	
	setLayout(layout2);

	connect(slider_options, SIGNAL(valueChanged(int)), spin_box, SLOT(setValue(int)));
	connect(spin_box, SIGNAL(valueChanged(int)), slider_options, SLOT(setValue(int)));
	connect(button_apply, SIGNAL(clicked()), this, SLOT(ok()));
	connect(button_cancel, SIGNAL(clicked()), this, SLOT(cancel()));

	slider_options->setValue(game_speed);
	spin_box->setValue(game_speed);

	mode = 0;
	rb_orig->setChecked(true);

	//rb_new->setDown(false);

}


void OptionsDialog::closeEvent(QCloseEvent *)
{
	hide();
}

void OptionsDialog::ok()
{

	if(rb_new->isChecked())
	mode = 1;
	else mode = 0;

	game_speed = slider_options->value();
	hide();

}

void OptionsDialog::cancel()
{
	if(slider_options->value() != game_speed)
	setSpeed(game_speed);
	hide();

}

const int OptionsDialog::getSpeed() const
{
	return game_speed;
}

const int OptionsDialog::getMode() const
{
	return mode;
}


void OptionsDialog::setSpeed(const int value)
{

	slider_options->setValue(value);
	spin_box->setValue(value);
	game_speed = value;

}

