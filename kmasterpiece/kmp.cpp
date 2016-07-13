#include<QApplication>
#include"kmp_window.h"
#include<iostream>
#include<string>
#include<unistd.h>

int main(int argc, char **argv)
{

	if(argv[0][0] != '.') {

		std::string fpath;
		fpath = argv[0];
		std::string temp = fpath.substr(0, fpath.rfind("/"));
		chdir(temp.c_str());
	}

	if(argc == 3)
	{
		if((strcmp(argv[1], "--path") == 0) && (argv[2][0] != '-'))
		{
			std::cout << "Changed directory to: " << argv[2] << "\n";
			chdir(argv[2]);
		}
	}


	QApplication app(argc, argv);
	mpWindow *win = new mpWindow;
	win->show();
	return app.exec();
}




