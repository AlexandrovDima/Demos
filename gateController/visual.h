/*
 * visual.h
 *
 *  Created on: 29.09.2024
 *      Author: Alx
 */

#ifndef VISU_H_
#define VISU_H_

#include <QDebug>
#include <QDialog>

	#include "ui_visual.h"

class Udp_sock;

class visual : public QDialog {

    Q_OBJECT

public:

	 visual(char*);

	virtual ~visual() {}
	
	::Ui::visual ui;

private:

QString fullpath;
QString ip;
QString locPort;
QString remIp;
QString remPort;
QString multiIp;
bool multiOn;
quint8 cmdset;
int buttonId;
int loopId;
int blinkId;

Udp_sock* USoc;

void initSettings();

void initSocket();

void initUi();

void setCurrentCmdToGate();

void askGateStay();

private slots:

void readData(QByteArray);

void clickOn(bool);

signals:

protected:

void timerEvent(QTimerEvent*);

}; //class

#endif
