/* udpV2.cpp
 *
 *  Created on: 25.09.2018
 *  Author: alx
 */

#include "udpV2.h"

Udp_sock::Udp_sock(QString ip, QString locp, QString remp, QString remaddr) {

qDebug() << "Udp_sock::Udp_sock(QString ip, QString locp, QString remp)********work** " << ip << " "<< locp<<"  "<<remp;
bindresult = false;
multirec = false;
miltisend = false;
senDsocket = NULL;
frames_to_go = NULL;
receivEsocket = NULL;
multicount=0;
USoc = new QUdpSocket();
receivEsocket = new QUdpSocket();
	this->ipaddress.setAddress(ip);
	this->lport = (quint16)locp.toUInt();
	this->remport = (quint16)remp.toUInt();
	this->ipremaddress.setAddress(remaddr);
       
bindresult = receivEsocket->bind(this->ipaddress, this->lport, QUdpSocket::DontShareAddress);

globalDescriptor = receivEsocket->socketDescriptor();

qDebug() << " Udp_sock::Udp_sock(QString ip, QString locp, QString remp)********bindresult** " << bindresult;

	QObject::connect(USoc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
	QObject::connect(USoc, SIGNAL(connected()), this, SLOT(sockConnected()));
	QObject::connect(USoc, SIGNAL(disconnected()), this, SLOT(sockDisconnected()));
	QObject::connect(receivEsocket, SIGNAL(readyRead()), this, SLOT(reading()));
    QObject::connect(receivEsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
USoc->setSocketDescriptor(globalDescriptor);
} ///constr

Udp_sock::~Udp_sock() {
if (senDsocket) senDsocket->~QUdpSocket();
drop();
receivEsocket->~QUdpSocket();
USoc->~QUdpSocket();
}///func

void Udp_sock::drop() {
qDebug()<<"*************************void Udp_sock::drop() { ";
if (USoc) {
QObject::disconnect(USoc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
QObject::disconnect(USoc, SIGNAL(connected()), this, SLOT(sockConnected()));
QObject::disconnect(USoc, SIGNAL(disconnected()), this, SLOT(sockDisconnected()));
USoc->close();
}

if (receivEsocket) {
QObject::disconnect(receivEsocket, SIGNAL(readyRead()), this, SLOT(reading()));
QObject::disconnect(receivEsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));

if (multirec) {
    //receivEsocket->leaveMulticastGroup(this->multicastIp);
    mulicastSet(this->multicastIp, false);
    multicount=0;
}
receivEsocket->close();
bindresult = false;
multirec = false;
//multicount=0;
}
qDebug()<<"*************************void Udp_sock::drop() { ---ends";
} ///func

void Udp_sock::rise(QString ip, QString port, QString multicast_ip) {
qDebug()<<"void Udp_sock::rise(QString ip, QString port) { *******  " << ip <<  "  **  " << port << " ** " << multicast_ip;
    if (receivEsocket) {
        QObject::connect(receivEsocket, SIGNAL(readyRead()), this, SLOT(reading()));
        QObject::connect(receivEsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
        bool ok = false;
        quint16 digitport = port.toUInt(&ok);
        if (!ok) return;
        QHostAddress causeip = QHostAddress(ip);
        QHostAddress multicIp = QHostAddress(multicast_ip);
        multirec = multicIp.isInSubnet(QHostAddress("224.0.0.0"),4); ///multicast
        if (multirec) {
           bindresult = receivEsocket->bind(QHostAddress::AnyIPv4,/*QHostAddress(ip),*/ digitport, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
           qDebug() << " ------------------------- multicast bind " << bindresult;
        } else {
            bindresult = receivEsocket->bind(QHostAddress(ip), digitport, QUdpSocket::DontShareAddress);
            qDebug() << " ------------------------- unicast bind " << bindresult;
        }
///open multibind
if (bindresult) {
    mulicastSet(multicIp, true);
} //if bindresult
///open multi
        this->ipaddress = causeip;
        this->lport = digitport;
        if (multirec) this->multicastIp = multicIp;
    }
qDebug()<<"bindresult ***********" << bindresult;  
qDebug()<<"multicast ***********" << multirec;

} ///func

void Udp_sock::mulicastSet(QHostAddress multicIp, bool turnOn) {
qDebug()<<" *********** void Udp_sock::mulicastSet(bool turnOn) { " << turnOn;
    bool dasmulti;
QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface oneface, ifaces) {
        qDebug() << " mulicastSet 1 ";
        QNetworkInterface::InterfaceFlags flgs = oneface.flags();
if (oneface.isValid() && !flgs.testFlag(QNetworkInterface::IsLoopBack) && flgs.testFlag(QNetworkInterface::CanMulticast) && flgs.testFlag(QNetworkInterface::IsRunning)) {
    qDebug() << " mulicastSet 2 ";
                foreach(QNetworkAddressEntry addr, oneface.addressEntries() ) {
                     qDebug() << " mulicastSet 3 ";
                    //if (addr.ip() == causeip) {
                        qDebug() << " mulicastSet 4 ";
                            if (addr.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                                qDebug() << " oneface.humanReadableName() " << oneface.humanReadableName();
                                    if (turnOn) {
                                        dasmulti = receivEsocket->joinMulticastGroup(multicIp, oneface);
                                         if (dasmulti) {
                                             qDebug()<<"MULTICAST joining: "<<oneface.humanReadableName()<<" result "<<multirec;
                                             multicount++;
                                         }
                                    } else {
                                        dasmulti = receivEsocket->leaveMulticastGroup(multicIp, oneface);
                                         if (dasmulti) {
                                             qDebug()<<"MULTICAST leaving: "<<oneface.humanReadableName()<<" result "<<multirec;
                                             multicount--;
                                         }
                                    }
                            } ///if IPv4Protocol
                   // } ///if addr.ip() == causeip 
                } ///foreach
        } ///if flags  
    } ///foreach
qDebug()<<" leaving/joining count " << multicount;
} ///fucn

void Udp_sock::reading() {
//qDebug()<<"*************************Udp_sock::reading() { ";
QHostAddress fromip;
quint16 fromport=0;
QByteArray arr;
arr.resize(receivEsocket->pendingDatagramSize());
receivEsocket->readDatagram(arr.data(), arr.size(),&fromip, &fromport);
emit dataIncome(arr, fromip.toString(), fromport);
} ///func

void Udp_sock::sending(QByteArray out) {
//qDebug()<<"**void Udp_sock::sending(QByteArray out) { **works   from" << this->ipaddress.toString() << "to "<<this->ipremaddress.toString() << "remote_port" << remport << " local_port  " << /*lport*/receivEsocket->localPort();
	qint64 howmany = -1;
		howmany = USoc->writeDatagram(out.constData(), out.size(), ipremaddress, remport);
qDebug() <<"sending message size is..... " << howmany;
} ///func

void Udp_sock::sending(QByteArray out, QString remip, quint16 nowport) {
//qDebug()<<"void Udp_sock::sending(QByteArray out, QString remip, quint16 nowport) { **works" << remip << " "<< nowport;
QHostAddress nowip;
nowip.setAddress(remip);
qint64 howmany = -1;
howmany = /*USoc*/receivEsocket->writeDatagram(out.constData(), out.size(), nowip, nowport);
qDebug()<<"sending message to " << remip << " size is..... " << howmany << " From ip" << receivEsocket->localAddress().toString() << " From Port " << receivEsocket->localPort();
} ///func

void Udp_sock::socketSayError(QAbstractSocket::SocketError err) {
qDebug() <<"************************Udp_sock::socketSayError errorNum " << err;
} ///func

void Udp_sock::sockConnected() {
qDebug()<<"*************************Udp_sock::sockConnected() { ";
} ///func

void Udp_sock::sockDisconnected() {
qDebug()<<"*************************Udp_sock::sockDisconnected() { ";
} ///func
