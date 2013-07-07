
#include "compass.h"


Compass::Compass(QGraphicsPixmapItem *aItem, QGraphicsScene *Scene, double imageheight) :
    m_compassImage(aItem), m_Scene(Scene), m_imageheight(imageheight)
{
    if (m_rate_val > 0)
    {
        qDebug() << "Compasssensor setdatarate " << endl;
        m_sensor.setDataRate(m_rate_val);
    }
    m_sensor.addFilter(this);
}
bool Compass::filter(QCompassReading *reading)
{
    int diff = ( reading->timestamp() - stamp );
    stamp = reading->timestamp();
    QString str;
    str = QString("%1\n").arg(reading->azimuth(), 3, 'f', 0);
    m_compassImage->setRotation(-reading->azimuth());
    qDebug() << str << endl;
    return true;
}
Compass::~Compass()
{

}



