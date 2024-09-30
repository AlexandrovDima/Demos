/*
 * visual.cpp
 *
 *  Created on: 29.09.2024
 *      Author: Alx
 *
*/

#include <QDebug>
#include <QSettings>

	#include "visual.h"
	#include "udpV2.h"

#define BUTTONTIMEOUT 750
#define COMMANDLOOP 30000 ///~30sec
#define BLIKTIMER 500 

visual::visual(char* fullpath) {
#ifdef MARKERS
qDebug() << "visual::visual(QWidget *parent, char* fullpath) : QDialog(parent) { --- works";
#endif
buttonId = 0;
loopId = 0;
blinkId = 0;
this->fullpath = QString(fullpath);
ui.setupUi(this);
initSettings();
initSocket();
initUi();
show();
#ifdef MARKERS
qDebug() << " *********************** constr over *************************** fullpath " << fullpath;
#endif
} ///constr

void visual::initSettings() {
#ifdef MARKERS
qDebug() << "visual::initSettings() { --- works";
#endif

ip = "127.0.0.1";
locPort = "2244";
remIp = "127.0.0.1";
remPort = "4422";
multiIp = "224.0.0.1";
multiOn = false;

#ifdef WIN
fullpath.remove(".exe");
#endif
QSettings* setts = new QSettings(QString(fullpath) + ".conf", QSettings::IniFormat);
setts->beginGroup("ip_settings");

	if (setts->value("ip").toString().isEmpty()) {
        qCritical() << "Block ip is Empty";
        setts->setValue("ip", QVariant(ip));
	} else {
        ip = setts->value("ip").toString();
	}
	
	if (setts->value("locPort").toString().isEmpty()) {
        qCritical() << "Block locPort is Empty";
        setts->setValue("locPort", QVariant(locPort));
	} else {
        locPort = setts->value("locPort").toString();
	}
	
	if (setts->value("remoteIp").toString().isEmpty()) {
        qCritical() << "Block remoteIp is Empty";
        setts->setValue("remoteIp", QVariant(remIp));
	} else {
        remIp = setts->value("remoteIp").toString();
	}
	
	if (setts->value("remotePort").toString().isEmpty()) {
        qCritical() << "Block remotePort is Empty";
        setts->setValue("remotePort", QVariant(remPort));
	} else {
        remPort = setts->value("remotePort").toString();
	}
	
	if (setts->value("multicastIP").toString().isEmpty()) {
        qCritical() << "Block multicastIP is Empty";
        setts->setValue("multicastIP", QVariant(multiIp));
	} else {
        multiIp = setts->value("multicastIP").toString();
	}
	
	if (setts->value("useMulticast").toString().isEmpty()) {
        qCritical() << "Block useMulticast is Empty";
        setts->setValue("useMulticast", QVariant(multiOn));
	} else {
        multiOn = setts->value("useMulticast").toBool();
	}
setts->endGroup();
setts->~QSettings();
} ///func

void visual::initSocket() {
#ifdef MARKERS
qDebug() << "void visual::initSocket() { --- works";
#endif
USoc = new Udp_sock(ip, locPort, remPort, remIp);
QObject::connect(USoc, SIGNAL(dataIncome(QByteArray, QString, quint16)), this, SLOT(readData(QByteArray)));
if (USoc->bindresult) {
ui.l_soc_stay->setText("Порт открыт");
} else {
ui.l_soc_stay->setText("Ошибка открытия порта");
}
} ///func

void visual::initUi() {
#ifdef MARKERS
qDebug() << "void visual::initUi() { --- works";
#endif
if (ui.pb_do_work->isChecked()) {
cmdset = 0xcc;
} else {
cmdset = 0xdd;
}
QObject::connect(ui.pb_do_work, SIGNAL(toggled(bool)), this, SLOT(clickOn(bool)));
} ///func

void visual::clickOn(bool toggled) {
#ifdef MARKERS
qDebug() << "void visual::clickOn(bool toggled) { --- toggled -- " << toggled;
#endif
if (loopId) {
killTimer(loopId);
loopId = 0;
}
if (toggled) {
cmdset = 0xcc;
ui.l_iam_getresult->setText("команда: открыть ворота");
ui.pb_do_work->setText("Закрыть ворота");
} else {
cmdset = 0xdd;
ui.l_iam_getresult->setText("команда: закрыть ворота");
ui.pb_do_work->setText("Открыть ворота");
}
ui.l_iam_tryset->setText("ожидание подтверждения...");
if (!blinkId) blinkId = startTimer(BLIKTIMER);
if (buttonId) killTimer(buttonId);
buttonId = startTimer(BUTTONTIMEOUT);
} ///func

void visual::timerEvent(QTimerEvent* event) {
#ifdef MARKERS
qDebug() << "void visual::timerEvent(QTimerEvent* event) { --- works";
#endif
if (buttonId == event->timerId()) {
killTimer(buttonId);
buttonId = 0;
setCurrentCmdToGate();
if (!loopId) loopId = startTimer(COMMANDLOOP);
return;
}
if (loopId == event->timerId()) {
askGateStay();
return;
}
if (blinkId == event->timerId()) {
if (ui.l_iam_tryset->text().isEmpty()) {
ui.l_iam_tryset->setText("ожидание подтверждения...");
} else {
ui.l_iam_tryset->setText(QString());
}
return;
}
} ///func

void visual::askGateStay() {
#ifdef MARKERS
qDebug() << "void visual::askGateStay() {";
#endif
if (loopId) killTimer(loopId);
QByteArray arr;
arr.append((char)(0xff));
arr.append((char)(0xfb));
arr.append((char)(0));
arr.append((char)(0xff));
if (USoc) USoc->sending(arr);
loopId = startTimer(COMMANDLOOP/10);
}///func

void visual::setCurrentCmdToGate() {
#ifdef MARKERS
qDebug() << "void visual::setCurrentCmdToGate() { cmdset -- " << QString::number(cmdset, 16);
#endif
QByteArray arr;
arr.append((char)(0xff));
arr.append((char)(0xfa));
arr.append((char)(cmdset));
arr.append((char)(0xff));
if (USoc) USoc->sending(arr);
} ///func

void visual::readData(QByteArray dt) {
#ifdef MARKERS
qDebug() << "void visual::readData(QByteArray dt) { --- dt.size() -- " << dt.size();
#endif
if (dt.size() != 4 || (quint8)dt.at(0) != 0xff || (quint8)dt.at(1) != 0xff || (quint8)dt.at(3) != 0xff) return;
	if (loopId) {
		killTimer(loopId);
		loopId = 0;
	}
quint8 stayNow = (quint8)dt.at(2);
if (stayNow != cmdset) {
	setCurrentCmdToGate();
	if (!loopId) loopId = startTimer(COMMANDLOOP);
} else {
	if (blinkId) {
		killTimer(blinkId);
		blinkId = 0;
		ui.l_iam_tryset->setText("подтверждено!");
	}
}
} ///func
