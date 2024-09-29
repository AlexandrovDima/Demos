//#include <stdexcept>
//#include <Qt>
//#include <QtGui>
//#include <QDebug>
//#include <QtGlobal>
#include <QDebug>
#include <QApplication>
#include <QGuiApplication>

#define IPNODE "127.0.0.1"
#define PORTNODE 1144

int main(int argc, char* argv[]) {
	
	QApplication app(argc, argv);
    qApp->setApplicationName("gateCtrl");
    QApplication::setQuitOnLastWindowClosed(false);

qDebug()<< "Good comptlation and start for now";

		app.exec();

	return 0;
} //func
