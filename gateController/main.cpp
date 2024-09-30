#include <QDebug>
#include <QApplication>
#include <QGuiApplication>

#include "visual.h"

int main(int argc, char* argv[]) {
	
	QApplication app(argc, argv);
    qApp->setApplicationName("gateCtrl");
    QApplication::setQuitOnLastWindowClosed(true);

		visual vi(argv[0]);
		
		app.exec();

	return 0;
} //func
