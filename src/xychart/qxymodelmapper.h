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

#ifndef QXYMODELMAPPER_H
#define QXYMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYModelMapperPrivate;
class QXYSeries;

class QTCOMMERCIALCHART_EXPORT QXYModelMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QXYSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int first READ first WRITE setFirst NOTIFY firstChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_ENUMS(Qt::Orientation)

protected:
    explicit QXYModelMapper(QObject *parent = 0);

public:
    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel *model);

    QXYSeries* series() const;
    void setSeries(QXYSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    void reset();

protected:
    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int xSection() const;
    void setXSection(int xSection);

    int ySection() const;
    void setYSection(int ySection);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void firstChanged();
    void countChanged();

protected:
    QXYModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QXYModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QXYMODELMAPPER_H
