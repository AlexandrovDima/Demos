/*! 
\file
\brief udpV2.h
\date 25.09.2018
\author alx
 */

/*!
\brief Основной класс реализующий UDP сокет с возможностью приема данных из multicast шруппы. 

Класс наследник QDialog, предоставляющий основную форму, содедержащий сокет для отправки/получения данных
	и содержащий элементы логики по асинхронному  урпавлению воротами.
*/

#ifndef UD_SOC
#define UD_SOC

#include <QUdpSocket>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QNetworkInterface>

class Udp_sock : public QObject {

	Q_OBJECT

private:

QUdpSocket* USoc;		///< Указатель на объект сокета для отправки
QUdpSocket* receivEsocket; ///< Указатель на объект сокета для получения данных
QHostAddress ipaddress; 	///< Переменная для хранения значения IP адреса который используется для BIND приемного сокета
QHostAddress ipremaddress; ///< Переменная для хранения значения IP адреса на который выполняется передача пакетов по умолчанию
QHostAddress multicastIp;	///< Переменная для хранения значения multicast IP адреса который используется для приема данных из multicast группы
quint16 lport;				///< Переменная для хранения значения порта который используется для приема данных
quint16 remport;			///< Переменная для хранения значения порта на который выполняется передача пакетов по умолчанию
//int globalDescriptor;


void multicastSet(QHostAddress, bool);

public:

//QString target_rec_ip;	/// < Переменная для хранения значения IP адреса на который выполняется передача пакетов по умолчанию
//QString target_rec_port;  /// < Переменная для хранения значения порта на который выполняется передача пакетов по умолчанию
bool bindresult;			///< Переменная, отражающая значение успешно ли выполнен BIND приемного сокета после конструктора
//bool miltisend;		
bool multirec;				///< Переменная, для индикации включения режима multicast
quint16 multicount; 		///< Переменная, для индикации колличества multicast групп в которых состоит сокет \warning контролировать!! по идее сокет должен быть только в одной группе.

Udp_sock(QString, QString, QString, QString);

virtual ~Udp_sock();

void drop();
void rise(QString, QString, QString);

private slots:
#ifndef QT6
	void socketSayError(QAbstractSocket::SocketError);
#endif
	void sockConnected();
	void sockDisconnected();
	void reading();

public slots:
	void sending(QByteArray,QString,quint16);
	void sending(QByteArray);

signals:
	void dataIncome(QByteArray, QHostAddress, quint16);
	void dataIncome(QByteArray, QString, quint16);

}; //clasout

#endif
