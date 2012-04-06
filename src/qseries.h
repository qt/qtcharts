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
#include <QPen>

class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QSeries : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_ENUMS(QSeriesType)

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
    QSeries(QSeriesPrivate &d,QObject *parent = 0);

public:
    ~QSeries();
    virtual QSeriesType type() const = 0;
    // TODO
    virtual bool setModel(QAbstractItemModel* model) = 0;
    QAbstractItemModel* model() const;
    void setName(const QString& name);
    QString name() const;

protected:
    QScopedPointer<QSeriesPrivate> d_ptr;
    friend class ChartDataSet;
    friend class ChartPresenter;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
