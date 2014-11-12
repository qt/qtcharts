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

#ifndef QABSTRACTSERIES_H
#define QABSTRACTSERIES_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QAbstractAxis>
#include <QtCore/QObject>
#include <QtGui/QPen>

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractSeriesPrivate;
class QChart;

class QT_CHARTS_EXPORT QAbstractSeries : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(SeriesType type READ type)
    Q_ENUMS(SeriesType)

public:
    enum SeriesType {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline,
        SeriesTypeHorizontalBar,
        SeriesTypeHorizontalStackedBar,
        SeriesTypeHorizontalPercentBar,
        SeriesTypeBoxPlot
    };

protected:
    QAbstractSeries(QAbstractSeriesPrivate &d, QObject *parent = 0);

public:
    ~QAbstractSeries();
    virtual SeriesType type() const = 0;

    void setName(const QString &name);
    QString name() const;
    void setVisible(bool visible = true);
    bool isVisible() const;
    qreal opacity() const;
    void setOpacity(qreal opacity);

    QChart *chart() const;

    bool attachAxis(QAbstractAxis *axis);
    bool detachAxis(QAbstractAxis *axis);
    QList<QAbstractAxis*> attachedAxes();

    void show();
    void hide();

Q_SIGNALS:
    void nameChanged();
    void visibleChanged();
    void opacityChanged();

protected:
    QScopedPointer<QAbstractSeriesPrivate> d_ptr;
    friend class ChartDataSet;
    friend class ChartPresenter;
    friend class ChartThemeManager;
    friend class QLegendPrivate;
    friend class DeclarativeChart;
};

QT_CHARTS_END_NAMESPACE

#endif // QABSTRACTSERIES_H
