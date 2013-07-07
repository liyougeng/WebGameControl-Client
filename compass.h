#ifndef _COMPASS_H__
#define _COMPASS_H__

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui>
#include <QMainWindow>
#include <QtCore>
#include <qcompass.h>
#include <QObject>
#include <QByteArray>
#include "webclient.h"

#include <QAccelerometer>
#include <QRotationSensor>
#define null NULL;
QTM_USE_NAMESPACE

enum sensor {
    eACCELEROMETER = 0,
    eROTATION
};
enum packageState{
    NOT_CHANGE,
    CHANGED
};
struct DataPackage {
    uint    sensor_id;
    uint    package_state;
    double  x;
    double  y;
    double  z;

};
static webClient * instClient = NULL;
class MyAccelerometer : public QAccelerometerFilter
{
    public:
    MyAccelerometer():QAccelerometerFilter(){

        m_acce.setDataRate(10);
        m_acce.addFilter(this);
    }
    ~MyAccelerometer(){
    }
    bool filter(QAccelerometerReading *reading){
        QString str("");
        QString strx = QString("%1").arg(reading->x(),3,'f',0);
        QString stry = QString("%1").arg(reading->y(),3,'f',0);
        QString strz = QString("%1").arg(reading->z(),3,'f',0);
        str = str+"0,"+strx+","+stry+","+strz;
        qDebug()<<"acce:"<<str;
        if(instClient!=NULL )
            if(instClient->isReady())
                instClient->sendToServer(QByteArray().append(str+"\n"));
        return true;
    }
    void stop()
    {
        m_acce.stop();
    }
    void start(){
        m_acce.start();
        if(m_acce.isActive()){
            qDebug()<<"sorry,failed.";
        }
    }
private:
    QAccelerometer m_acce;

};
class MyQRotationSensor : public QRotationFilter
{
public:
    MyQRotationSensor():QRotationFilter(){
        m_rotation.setDataRate(10);
        m_rotation.addFilter(this);

    }

    ~MyQRotationSensor(){
    }
    bool filter(QRotationReading *reading){
        QString str("");
        QString strx = QString("%1").arg(reading->x(),3,'f',0);
        QString stry = QString("%1").arg(reading->y(),3,'f',0);
        QString strz = QString("%1").arg(reading->z(),3,'f',0);
        str = str+"1,"+strx+","+stry+","+strz;
        qDebug()<<"rota:"<<str;
        if(instClient!=NULL)
            if(instClient->isReady())
                instClient->sendToServer(QByteArray().append(str+"\n"));
        return true;
    }
    void stop(){
        m_rotation.stop();
    }
    void start(){
        m_rotation.start();
        if(m_rotation.isActive()){
            qDebug()<<"orient failed.";
        }
    }
private:
    QRotationSensor m_rotation;

};
class PixmapItem :  public QGraphicsPixmapItem
{

public:
    PixmapItem(QPixmap & ptrPixMap):QGraphicsPixmapItem(ptrPixMap)
        {
        }

};
class View : public QGraphicsView
{
public:
    View(QGraphicsScene *scene) : QGraphicsView(scene)
    {

    }

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};
class Compass : public QCompassFilter
{
public:
    Compass(QGraphicsPixmapItem  * aItem, QGraphicsScene *Scene, double imageheight);
    bool filter(QCompassReading *reading);
    ~Compass();
    void start(){
        m_sensor.start();
        if (!m_sensor.isActive())
        {
            qDebug() << "Compasssensor didn't start!" << endl;
        }
    }
    void stop(){m_sensor.stop();}
private:
    qtimestamp stamp;
    QGraphicsPixmapItem  * m_compassImage;
    QGraphicsScene  * m_Scene;
    double m_imageheight;

    int  m_rate_val;
    QCompass m_sensor;
};

class Controler : public QObject
{
    Q_OBJECT
public:
    explicit Controler(QObject *parent = NULL) {
        Client.connectToServer();
        instClient = getWebClientInst();
        if(instClient != NULL){
            connect(instClient,SIGNAL(messageArrived(QByteArray)),this,SLOT(handleControlData(QByteArray)));
            connect(instClient,SIGNAL(connectState(bool)),this,SLOT(HandleSensorState(bool)));
        }
    }
    ~Controler(){
        if(instClient != NULL) {
            disconnect(instClient,SIGNAL(messageArrived(QByteArray)),this,SLOT(handleControlData(QByteArray)));
            disconnect(instClient,SIGNAL(connectState(bool)),this,SLOT(HandleSensorState(bool)));
            instClient = NULL;
        }
    }
signals:

public slots:
   void handleControlData(QByteArray data) {
       qDebug()<<QString(data);
   }
   void HandleSensorState(bool isConnected){
       if(isConnected){
            m_acce.start();
            m_rota.start();
       }else{
            m_acce.stop();
            m_rota.stop();
       }
   }
private:
    MyAccelerometer m_acce;
    MyQRotationSensor m_rota;
    webClient Client;
public:
    webClient * getWebClientInst(){return &Client;}
};

#endif // _COMPASS_H__
