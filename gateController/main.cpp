//#include <stdexcept>
//#include <Qt>
//#include <QtGui>
//#include <QDebug>
//#include <QtGlobal>
#include <QDebug>
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>

#include "visual.h"

int main(int argc, char* argv[]) {
	
	QApplication app(argc, argv);
    qApp->setApplicationName("gateCtrl");
    QApplication::setQuitOnLastWindowClosed(true);

qDebug()<< "Good comptlation and start for now";

		visual vi(argv[0]);
		
		app.exec();

	return 0;
} //func
