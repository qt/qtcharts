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

#ifndef QSERIES_H
#define QSERIES_H

#include <qchartglobal.h>
#include <QObject>
//#include <QAbstractItemModel>
#include <QPen>

class QAbstractItemModel;
class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QSeries : public QObject
{
    Q_OBJECT
public:
    enum QSeriesType {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline
    };

protected:
    QSeries(QObject *parent = 0) : QObject(parent) {m_model = 0;}

public:
    virtual ~QSeries() {}
    virtual QSeriesType type() const = 0;
    // TODO
    virtual bool setModel(QAbstractItemModel* /*model*/) { return false; }
    void setName(QString name) { m_name = name; }
    QString name() const { return m_name; }

protected:
    QAbstractItemModel* m_model;

private:
    QString m_name;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
