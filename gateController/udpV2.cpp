/* udpV2.cpp
 *
 *  Created on: 25.09.2018
 *  Author: alx
 */

#include "udpV2.h"

Udp_sock::Udp_sock(QString ip, QString locp, QString remp, QString remaddr) {
#ifdef MARKERS
qDebug() << "Udp_sock::Udp_sock(QString ip, QString locp, QString remp)********work** " << ip << " "<< locp<<"  "<<remp;
#endif
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
//globalDescriptor = receivEsocket->socketDescriptor();
#ifdef MARKERS
qDebug() << " Udp_sock::Udp_sock(QString ip, QString locp, QString remp)********bindresult** " << bindresult;
#endif
#ifndef QT6
	QObject::connect(USoc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
#endif
	QObject::connect(USoc, SIGNAL(connected()), this, SLOT(sockConnected()));
	QObject::connect(USoc, SIGNAL(disconnected()), this, SLOT(sockDisconnected()));
	QObject::connect(receivEsocket, SIGNAL(readyRead()), this, SLOT(reading()));
#ifndef QT6
    QObject::connect(receivEsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
#endif
//USoc->setSocketDescriptor(globalDescriptor);
} ///constr

Udp_sock::~Udp_sock() {
if (senDsocket) senDsocket->~QUdpSocket();
drop();
receivEsocket->~QUdpSocket();
USoc->~QUdpSocket();
}///func

void Udp_sock::drop() {
#ifdef MARKERS
qDebug()<<"*************************void Udp_sock::drop() {";
#endif
if (USoc) {
#ifndef QT6
QObject::disconnect(USoc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
#endif
QObject::disconnect(USoc, SIGNAL(connected()), this, SLOT(sockConnected()));
QObject::disconnect(USoc, SIGNAL(disconnected()), this, SLOT(sockDisconnected()));
USoc->close();
}

if (receivEsocket) {
QObject::disconnect(receivEsocket, SIGNAL(readyRead()), this, SLOT(reading()));
#ifndef QT6
QObject::disconnect(receivEsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
#endif
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
#ifdef MARKERS
qDebug()<<"*************************void Udp_sock::drop() { ---ends";
#endif
} ///func

void Udp_sock::rise(QString ip, QString port, QString multicast_ip) {
#ifdef MARKERS
qDebug()<<"void Udp_sock::rise(QString ip, QString port) { *******  " << ip <<  "  **  " << port << " ** " << multicast_ip;
#endif
    if (receivEsocket) {
        QObject::connect(receivEsocket, SIGNAL(readyRead()), this, SLOT(reading()));
#ifndef QT6
        QObject::connect(receivEsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketSayError(QAbstractSocket::SocketError)));
#endif
        bool ok = false;
        quint16 digitport = port.toUInt(&ok);
        if (!ok) return;
        QHostAddress causeip = QHostAddress(ip);
        QHostAddress multicIp = QHostAddress(multicast_ip);
        multirec = multicIp.isInSubnet(QHostAddress("224.0.0.0"),4); ///multicast
        if (multirec) {
           bindresult = receivEsocket->bind(QHostAddress::AnyIPv4,/*QHostAddress(ip),*/ digitport, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
		   #ifdef MARKERS
           qDebug() << " ------------------------- multicast bind " << bindresult;
		   #endif
        } else {
            bindresult = receivEsocket->bind(QHostAddress(ip), digitport, QUdpSocket::DontShareAddress);
			#ifdef MARKERS
            qDebug() << " ------------------------- unicast bind " << bindresult;
			#endif
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
#ifdef MARKERS
qDebug()<<"bindresult ***********" << bindresult;  
qDebug()<<"multicast ***********" << multirec;
#endif
} ///func

void Udp_sock::mulicastSet(QHostAddress multicIp, bool turnOn) {
#ifdef MARKERS
qDebug()<<" *********** void Udp_sock::mulicastSet(bool turnOn) { " << turnOn;
#endif
    bool dasmulti;
QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface oneface, ifaces) {
        QNetworkInterface::InterfaceFlags flgs = oneface.flags();
if (oneface.isValid() && !flgs.testFlag(QNetworkInterface::IsLoopBack) && flgs.testFlag(QNetworkInterface::CanMulticast) && flgs.testFlag(QNetworkInterface::IsRunning)) {
    qDebug() << " mulicastSet 2 ";
                foreach(QNetworkAddressEntry addr, oneface.addressEntries() ) {
                    //if (addr.ip() == causeip) {
                            if (addr.ip().protocol() == QAbstractSocket::IPv4Protocol) {
								#ifdef MARKERS
                                qDebug() << " oneface.humanReadableName() " << oneface.humanReadableName();
								#endif
                                    if (turnOn) {
                                        dasmulti = receivEsocket->joinMulticastGroup(multicIp, oneface);
                                         if (dasmulti) {
											 #ifdef MARKERS
                                             qDebug()<<"MULTICAST joining: "<<oneface.humanReadableName()<<" result "<<multirec;
											 #endif
                                             multicount++;
                                         }
                                    } else {
                                        dasmulti = receivEsocket->leaveMulticastGroup(multicIp, oneface);
                                         if (dasmulti) {
											 #ifdef MARKERS
                                             qDebug()<<"MULTICAST leaving: "<<oneface.humanReadableName()<<" result "<<multirec;
											 #endif
                                             multicount--;
                                         }
                                    }
                            } ///if IPv4Protocol
                   // } ///if addr.ip() == causeip 
                } ///foreach
        } ///if flags  
    } ///foreach
#ifdef MARKERS
qDebug()<<" leaving/joining count " << multicount;
#endif
} ///fucn

void Udp_sock::reading() {
#ifdef MARKERS
qDebug()<<"*************************Udp_sock::reading() {";
#endif
QHostAddress fromip;
quint16 fromport=0;
QByteArray arr;
arr.resize(receivEsocket->pendingDatagramSize());
receivEsocket->readDatagram(arr.data(), arr.size(),&fromip, &fromport);
emit dataIncome(arr, fromip.toString(), fromport);
} ///func

void Udp_sock::sending(QByteArray out) {
#ifdef MARKERS
qDebug()<<"**void Udp_sock::sending(QByteArray out) { **works   from" << this->ipaddress.toString() << "to "<<this->ipremaddress.toString() << "remote_port" << remport << " local_port  " << /*lport*/receivEsocket->localPort();
	qint64 howmany = -1;
		howmany = USoc->writeDatagram(out.constData(), out.size(), ipremaddress, remport);
	qDebug() <<"sending message size is..... " << howmany;
#else
		USoc->writeDatagram(out.constData(), out.size(), ipremaddress, remport);
#endif
} ///func

void Udp_sock::sending(QByteArray out, QString remip, quint16 nowport) {
#ifdef MARKERS
qDebug()<<"void Udp_sock::sending(QByteArray out, QString remip, quint16 nowport) { **works" << remip << " "<< nowport;
qint64 howmany = -1;
#endif
QHostAddress nowip;
nowip.setAddress(remip);
#ifdef MARKERS
howmany = /*USoc*/receivEsocket->writeDatagram(out.constData(), out.size(), nowip, nowport);
#else
receivEsocket->writeDatagram(out.constData(), out.size(), nowip, nowport);
#endif
#ifdef MARKERS
qDebug()<<"sending message to " << remip << " size is..... " << howmany << " From ip" << receivEsocket->localAddress().toString() << " From Port " << receivEsocket->localPort();
#endif
} ///func

#ifndef QT6
void Udp_sock::socketSayError(QAbstractSocket::SocketError err) {
#ifdef MARKERS
qDebug() <<"************************Udp_sock::socketSayError errorNum " << err;
#endif
} ///func
#endif

void Udp_sock::sockConnected() {
#ifdef MARKERS
qDebug()<<"*************************Udp_sock::sockConnected() { ";
#endif
} ///func

void Udp_sock::sockDisconnected() {
#ifdef MARKERS
qDebug()<<"*************************Udp_sock::sockDisconnected() {";
#endif
} ///func
