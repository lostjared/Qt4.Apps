/*
 * 
 * leffect
 * 
 * 
 */
#include"effect_window.h"
#include<QApplication>


int main(int argc, char *argv[]) {

#ifndef _WIN32
	if(argv[0][0] == '/') {
		std::string path = argv[0];
		std::string path_ex = path.substr(0, path.rfind("/"));
		path_ex+="/";
		pathstr=path_ex.c_str();
	}
#else
	pathstr = "";
#endif
	QApplication app(argc, argv);
	effectWindow *window = new effectWindow();
	window->show();
	return app.exec();
}