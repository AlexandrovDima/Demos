/* udpV2.h
 *
 *  Created on: 25.09.2018
 *  Author: alx
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
QUdpSocket* USoc;
QUdpSocket* senDsocket;
QUdpSocket* receivEsocket;
QList <QPair <QByteArray,QList<int> > >*  frames_to_go;
QHostAddress ipaddress;
QHostAddress ipremaddress;
QHostAddress multicastIp;
quint16 lport;
quint16 remport;
int globalDescriptor;

QByteArray datacontainer;

void mulicastSet(QHostAddress, bool);

public:
QString target_rec_ip;
QString target_rec_port;
bool bindresult;
bool miltisend;
bool multirec;
quint16 multicount;
Udp_sock(QString, QString, QString, QString);

void drop();
void rise(QString, QString, QString);
virtual ~Udp_sock();

private slots:
	
	void socketSayError(QAbstractSocket::SocketError);
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
