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

#ifndef QCHARTAXIS_H_
#define QCHARTAXIS_H_

#include <qchartglobal.h>
#include <qchartaxiscategories.h>
#include <QPen>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QChartAxis : public QObject
{
	Q_OBJECT
public:

    QChartAxis(QObject *parent =0);
    ~QChartAxis();

    //axis handling
    bool isAxisVisible() const;
    void setAxisVisible(bool visible);
    void setAxisPen(const QPen &pen);
    QPen axisPen() const;

    //grid handling
    bool isGridLineVisible() const;
    void setGridLineVisible(bool visible);
    void setGridLinePen(const QPen &pen);
    QPen gridLinePen() const;

    //labels handling
    bool labelsVisible() const;
    void setLabelsVisible(bool visible);
    void setLabelsPen(const QPen &pen);
    QPen labelsPen() const;
    void setLabelsBrush(const QBrush &brush);
    QBrush labelsBrush() const;
    void setLabelsFont(const QFont &font);
    QFont labelsFont() const;
    void setLabelsAngle(int angle);
    int labelsAngle() const;

    //shades handling
    bool shadesVisible() const;
    void setShadesVisible(bool visible);
    void setShadesPen(const QPen &pen);
    QPen shadesPen() const;
    void setShadesBrush(const QBrush &brush);
    QBrush shadesBrush() const;
    void setShadesOpacity(qreal opacity);
    qreal shadesOpacity() const;

    //range handling
    void setMin(qreal min);
    qreal min() const;
    void setMax(qreal max);
    qreal max() const;
    void setRange(qreal min, qreal max);

    //ticks handling
    void setTicksCount(int count);
    int ticksCount() const;

    void setNiceNumbers(bool enable);
    bool niceNumbers() const;

    QChartAxisCategories* categories();

    void show();
    void hide();

Q_SIGNALS:
	void minChanged(qreal min);
	void maxChanged(qreal max);
	void rangeChanged(qreal min, qreal max);
	void ticksCountChanged(int count);

private:
	QScopedPointer<QChartAxisPrivate> d_ptr;
    Q_DISABLE_COPY(QChartAxis);
    friend class ChartDataSet;
    friend class Axis;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif /* QCHARTAXIS_H_ */
