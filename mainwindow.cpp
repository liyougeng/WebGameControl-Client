/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QLabel>
#include <math.h>
#include "mainwindow.h"
#include "compass.h"



MainWindow::MainWindow()
{
    scene = new QGraphicsScene();   
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, tr("QtCompass")));

    qDebug()  << "Checking version" << endl;
    qDebug() << QTM_VERSION_STR << QT_VERSION_STR;

    qDebug()  << scene->width() << scene->height() << endl;

    compassPix = new QPixmap();
    bgPix = new QPixmap();

    compassPix->load(":/images/compass.png");
    bgPix->load(":/images/bg.jpg");


    int imagewidth =  compassPix->size().width();
    int imageheight =  compassPix->size().height();


    double imgincrease =  ::sqrt( (imagewidth*imagewidth) + (imageheight*imageheight));
    double bigger= (imagewidth > imageheight) ? imagewidth : imageheight;
    double ratio = imgincrease/bigger;


    PixItemCompass  = new PixmapItem(*compassPix);

    scene->addItem(PixItemCompass);


    qDebug()  << imagewidth << imageheight << imgincrease << imgincrease<< ratio <<endl;

    PixItemCompass->setPos(-imagewidth/2,-imageheight/2);
    PixItemCompass->setTransformOriginPoint(imagewidth/2,imageheight/2);

    view = new View(scene);
    view->setBackgroundBrush(*bgPix);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);

    controler = new Controler(this);
    compass = new Compass(PixItemCompass, scene, imageheight); // scene is necessary if you want to do something this

    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    qDebug()  << scene->width() << scene->height() << endl;
    setCentralWidget(view);

}

