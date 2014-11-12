/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QHPIEMODELMAPPER_H
#define QHPIEMODELMAPPER_H

#include <QtCharts/QPieModelMapper>

QT_CHARTS_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class QT_CHARTS_EXPORT QHPieModelMapper : public QPieModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QPieSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int valuesRow READ valuesRow WRITE setValuesRow NOTIFY valuesRowChanged)
    Q_PROPERTY(int labelsRow READ labelsRow WRITE setLabelsRow NOTIFY labelsRowChanged)
    Q_PROPERTY(int firstColumn READ firstColumn WRITE setFirstColumn NOTIFY firstColumnChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)

public:
    explicit QHPieModelMapper(QObject *parent = 0);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QPieSeries *series() const;
    void setSeries(QPieSeries *series);

    int valuesRow() const;
    void setValuesRow(int valuesRow);

    int labelsRow() const;
    void setLabelsRow(int labelsRow);

    int firstColumn() const;
    void setFirstColumn(int firstColumn);

    int columnCount() const;
    void setColumnCount(int columnCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void valuesRowChanged();
    void labelsRowChanged();
    void firstColumnChanged();
    void columnCountChanged();
};

QT_CHARTS_END_NAMESPACE

#endif // QHPIEMODELMAPPER_H
