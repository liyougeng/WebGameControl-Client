#include "webclient.h"


webClient::webClient(QObject *parent) :
    QObject(parent)
{
    bReady = false;
    socket = new QTcpSocket(this);
    host.setAddress("192.168.0.100");
    port = 8080;
    connect(socket,
            SIGNAL(connected()),
            this,
            SLOT(on_connected()));
    connect(socket,
            SIGNAL(disconnected()),
            this,
            SLOT(on_disconnect()));
}

void webClient::on_connected()
{
    qDebug()<<"webClient:connected.";
    bReady  = true;
    emit    connectState(true);
    char    buffer[1024]="10,0,0,0\n";
    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(on_readyread()));
    socket->write(buffer);
    socket->flush();
}

void webClient::on_disconnect()
{
    qDebug()<<"webClient:disconnect..";
    bReady = false;
    emit       connectState(false);
    disconnect(socket,
               SIGNAL(readyRead()),
               this,
               SLOT(on_readyread()));
    disconnect(socket,
               SIGNAL(connected()),
               this,
               SLOT(on_connected()));
    //socket->close();
    socket->deleteLater();
}

void webClient::on_readyread(){
    return ;
    QByteArray data;
    while(socket->canReadLine()){
        data.append(socket->readLine());
    }
    qDebug()<<"webClient:"<<QString(data);
    bufferedMessage.append(data);
    emit messageArrived(data);
}
void webClient::connectToServer(){
    if (socket == NULL) return;
    socket->connectToHost(host,port);
    qDebug()<<"webClient connect to host.";

}

void webClient::setHostInfo(QHostAddress host, uint port){
    this->host = host;
    this->port = port;
}

webClient::~webClient(){
    if(socket != NULL)
        delete socket;
}

void webClient::sendToServer(QByteArray data){

    if(socket->isOpen()&&socket->isWritable()){
        socket->write(data);
        socket->flush();
    }else{
        qDebug()<<"webClient:sorry,socket not writable or not open!";
    }

}

QByteArray webClient::getBufferedMessage()
{
    return bufferedMessage;
}
