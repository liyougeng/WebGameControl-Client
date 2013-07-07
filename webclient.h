#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include <QObject>

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

class webClient : public QObject
{
    Q_OBJECT
public:
    explicit webClient(QObject *parent = 0);
    ~webClient();
    void connectToServer();
    void setHostInfo(QHostAddress host = QHostAddress::LocalHost,uint port=8080);
    void sendToServer(QByteArray data);
    bool isReady(){return bReady;}
    QByteArray getBufferedMessage();
signals:
    void messageArrived(QByteArray data);
    void connectState(bool bConnected);
public slots:
    void on_connected();
    void on_disconnect();
    void on_readyread();
private:
    bool         bReady;
    QHostAddress host;
    quint16      port;
    QTcpSocket *socket;
    QByteArray bufferedMessage;
    
};

#endif // WEBCLIENT_H
