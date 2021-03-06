/*
 * AVRPioRemote
 * Copyright (C) 2013  Andreas Müller, Ulrich Mensfeld
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef RECEIVERINTERFACE_H
#define RECEIVERINTERFACE_H

#include <QSettings>
#include <QtNetwork/QTcpSocket>
#include <string>
#include "logger.h"
#include "msgdistributor.h"

using namespace std;

class ReceiverInterface : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverInterface();

    bool IsConnected();

private:
    QTcpSocket      m_Socket;
    string          m_ReceivedString;
    bool            m_Connected;

    void InterpretString(const QString& data);

private slots:
    void ReadString();
    void TcpError(QAbstractSocket::SocketError socketError);
    void TcpConnected();
    void TcpDisconnected();
public slots:
    void ConnectToReceiver(const QString &IpAddress, const int IpPort);
    void Disconnect();
    //void SocketStateChanged(QAbstractSocket::SocketState State);
    bool SendCmd(const QString& cmd);

signals:
    bool CmdToBeSend(const QString& cmd); // for logging
    void CommError(QString error);
    void Connected();
    void Disconnected();
    void DataReceived(QString);
    void MuteData(bool muted);
    void Listenextended(QString id, QString name);
    void ListeningModeData(QString name);
    void NetData(QString data);
    void SpeakerData(QString name);
    void usbData (QString name);
    void ReceiverType (QString no, QString name);
    void ReceiverNetworkName (QString name);
    void ZoneInput (int zone, int input);
    void ZoneVolume (int zone, int volume, QString asString);
};

#endif // RECEIVERINTERFACE_H
