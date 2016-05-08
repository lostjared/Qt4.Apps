#include "mainWindow.h"
#include<ctime>
#include<cstdlib>
#include<string>
#include<unistd.h>


int main(int argc, char **argv) {
	QApplication app(argc, argv);
	if(!QGLFormat::hasOpenGL()) {
		QMessageBox::warning(0,QObject::tr("Error OpenGL Required"), QObject::tr("OpenGL not found on your System"), 1, 0, 0);
		return EXIT_FAILURE;
	}
	srand(static_cast<unsigned int>(time(0)));
#ifdef __APPLE__
	std::string temp=argv[0];
	temp=temp.substr(0, temp.rfind("/"));
	chdir(temp.c_str());
#endif
	mainWindow *appWindow = new mainWindow();
	appWindow->show();
	return app.exec();
}



