/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QIODevice>
#include <QChartGlobal>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QXYSeries;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

class XYSeriesIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit XYSeriesIODevice(QXYSeries * series, QObject *parent = 0);
        
protected:
    qint64 readData(char * data, qint64 maxSize);
    qint64 writeData(const char * data, qint64 maxSize);
    
private:
    QXYSeries *m_series;
};

#endif // XYSERIESIODEVICE_H
