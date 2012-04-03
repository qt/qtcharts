/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QTimer>
#include <QTime>
#include <QObject>
#include <cmath>
#include <qlineseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979
static const int numPoints =100;

class WaveGenerator: public QObject
{
    Q_OBJECT

public:
    WaveGenerator(QLineSeries* series1, QLineSeries* series2) :
        m_series1(series1),
        m_series2(series2),
        m_wave(0),
        m_step(2*PI/numPoints)
    {

        QTime now = QTime::currentTime();
        qsrand((uint)now.msec());

        int fluctuate = 100;

        for (qreal x = 0; x <= 2*PI; x+=m_step) {
              series1->append(x, fabs(sin(x)*fluctuate));
              series2->append(x, fabs(cos(x)*fluctuate));
        }

        QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(update()));
        m_timer.setInterval(5000);
        m_timer.start();

    };

public slots:
    void update()
    {
        int fluctuate;

        for (qreal i = 0, x = 0; x <= 2*PI; x+=m_step, i++) {
            fluctuate = qrand() % 100;
            m_series1->replace(x, fabs(sin(x)*fluctuate));
            fluctuate = qrand() % 100;
            m_series2->replace(x, fabs(cos(x)*fluctuate));
        }

    }

private:
    QLineSeries* m_series1;
    QLineSeries* m_series2;
    int m_wave;
    qreal m_step;
    QTimer m_timer;
};
