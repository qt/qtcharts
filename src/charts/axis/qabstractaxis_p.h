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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACTAXIS_P_H
#define QABSTRACTAXIS_P_H

#include <QtCharts/QAbstractAxis>
#include <private/chartaxiselement_p.h>
#include <QtCharts/QChart>
#include <QtCore/QDebug>

class QGraphicsItem;

QT_CHARTS_BEGIN_NAMESPACE

class ChartPresenter;
class AbstractDomain;
class QChart;
class QAbstractSeries;
class ChartTheme;
class ChartElement;

class QT_CHARTS_AUTOTEST_EXPORT QAbstractAxisPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstractAxisPrivate(QAbstractAxis *q);
    ~QAbstractAxisPrivate();

public:
    Qt::Alignment alignment() const { return m_alignment; }
    Qt::Orientation orientation() const { return m_orientation; }
    void setAlignment( Qt::Alignment alignment);

    virtual void initializeDomain(AbstractDomain *domain) = 0;
    virtual void initializeGraphics(QGraphicsItem *parent) = 0;
    virtual void initializeTheme(ChartTheme* theme, bool forced = false);
    virtual void initializeAnimations(QChart::AnimationOptions options);

    //interface for manipulating range form base class
    virtual void setMin(const QVariant &min) = 0;
    virtual void setMax(const QVariant &max) = 0;
    virtual void setRange(const QVariant &min, const QVariant &max) = 0;

    //interface manipulating range form domain
    virtual void setRange(qreal min, qreal max) = 0;
    virtual qreal min() = 0;
    virtual qreal max() = 0;

    ChartAxisElement *axisItem() { return m_item.data(); }

public Q_SLOTS:
    void handleRangeChanged(qreal min, qreal max);

Q_SIGNALS:
    void rangeChanged(qreal min, qreal max);

protected:
    QAbstractAxis *q_ptr;
    QChart *m_chart;
    QScopedPointer<ChartAxisElement> m_item;

private:
    QList<QAbstractSeries*> m_series;

    Qt::Alignment m_alignment;
    Qt::Orientation m_orientation;

    bool m_visible;

    bool m_arrowVisible;
    QPen m_axisPen;
    QBrush m_axisBrush;

    bool m_gridLineVisible;
    QPen m_gridLinePen;

    bool m_labelsVisible;
    QBrush m_labelsBrush;
    QFont m_labelsFont;
    int m_labelsAngle;

    bool m_titleVisible;
    QBrush m_titleBrush;
    QFont m_titleFont;
    QString m_title;

    bool m_shadesVisible;
    QPen m_shadesPen;
    QBrush m_shadesBrush;
    qreal m_shadesOpacity;

    bool m_dirty;

    friend class QAbstractAxis;
    friend class ChartDataSet;
    friend class ChartPresenter;
};

QT_CHARTS_END_NAMESPACE

#endif
