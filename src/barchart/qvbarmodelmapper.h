/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef QVBARMODELMAPPER_H
#define QVBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QAbstractBarSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int firstBarSetColumn READ firstBarSetColumn WRITE setFirstBarSetColumn NOTIFY firstBarSetColumnChanged)
    Q_PROPERTY(int lastBarSetColumn READ lastBarSetColumn WRITE setLastBarSetColumn NOTIFY lastBarSetColumnChanged)
    Q_PROPERTY(int firstRow READ firstRow WRITE setFirstRow NOTIFY firstRowChanged)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)

public:
    explicit QVBarModelMapper(QObject *parent = 0);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QAbstractBarSeries *series() const;
    void setSeries(QAbstractBarSeries *series);

    int firstBarSetColumn() const;
    void setFirstBarSetColumn(int firstBarSetColumn);

    int lastBarSetColumn() const;
    void setLastBarSetColumn(int lastBarSetColumn);

    int firstRow() const;
    void setFirstRow(int firstRow);

    int rowCount() const;
    void setRowCount(int rowCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void firstBarSetColumnChanged();
    void lastBarSetColumnChanged();
    void firstRowChanged();
    void rowCountChanged();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVBARMODELMAPPER_H
