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

#ifndef QVBOXPLOTMODELMAPPER_H
#define QVBOXPLOTMODELMAPPER_H

#include <QBoxPlotModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVBoxPlotModelMapper : public QBoxPlotModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QBoxPlotSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int firstBoxSetColumn READ firstBoxSetColumn WRITE setFirstBoxSetColumn NOTIFY firstBoxSetColumnChanged)
    Q_PROPERTY(int lastBoxSetColumn READ lastBoxSetColumn WRITE setLastBoxSetColumn NOTIFY lastBoxSetColumnChanged)
    Q_PROPERTY(int firstRow READ firstRow WRITE setFirstRow NOTIFY firstRowChanged)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)

public:
    explicit QVBoxPlotModelMapper(QObject *parent = 0);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QBoxPlotSeries *series() const;
    void setSeries(QBoxPlotSeries *series);

    int firstBoxSetColumn() const;
    void setFirstBoxSetColumn(int firstBoxSetColumn);

    int lastBoxSetColumn() const;
    void setLastBoxSetColumn(int lastBoxSetColumn);

    int firstRow() const;
    void setFirstRow(int firstRow);

    int rowCount() const;
    void setRowCount(int rowCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void firstBoxSetColumnChanged();
    void lastBoxSetColumnChanged();
    void firstRowChanged();
    void rowCountChanged();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVBOXPLOTMODELMAPPER_H
