/*! 
\file
\brief visual.h
\date 29.09.2024
\author Alx
 */

/*!
\brief Основной класс предоставляющий визуальную форму Класс наследник QDialog, предоставляющий основную форму, содедержащий сокет для отправки/получения данных.
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

QString fullpath; ///< Хранит абсолютный путь местоположения исполняемого файла, используется для организации работы QSetings в классе
QString ip;	 ///< IP адрес для приема данных, восстановленный из конфигурационого файла
QString locPort; ///< Порт для приема данных, восстановленный из конфигурационого файла
QString remIp;///< IP адрес получателя данных, восстановленный из конфигурационого файла
QString remPort; ///< Порт получателя данных, восстановленный из конфигурационого файла
QString multiIp; ///< IP адрес multicast для приема данных, восстановленный из конфигурационого файла
bool multiOn; ///< Признак использования multicast адреса для приема данных, восстановленный из конфигурационого файла \warning значение true не проверялось
quint8 cmdset; ///< Хранение текущей команды которая отправлена или будет отправлена к воротам
int buttonId; ///< Идентификатор таймера для задержки после нажатия кнопки
int loopId; ///< Идентификатор таймера для обеспечения задержки после которой можно опрашивать ворота
int blinkId; ///< Идентификатор таймера для обеспечения моргания надписи

Udp_sock* USoc; ///< Указатель на объект сокета используемый для отправки данных/получения данных от ворот

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
