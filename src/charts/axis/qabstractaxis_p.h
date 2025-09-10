// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACTAXIS_P_H
#define QABSTRACTAXIS_P_H

#include <QtCharts/QAbstractAxis>
#include <private/chartaxiselement_p.h>
#include <QtCharts/QChart>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QDebug>

#include <memory>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class ChartPresenter;
class AbstractDomain;
class QChart;
class QAbstractSeries;
class ChartTheme;
class ChartElement;

class Q_CHARTS_EXPORT QAbstractAxisPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstractAxisPrivate(QAbstractAxis *q);
    ~QAbstractAxisPrivate();

public:
    Qt::Alignment alignment() const { return m_alignment; }
    Qt::Orientation orientation() const { return m_orientation; }
    void setAlignment(Qt::Alignment alignment);
    void setLabelsTruncated(bool labelsTruncated);

    virtual void initializeDomain(AbstractDomain *domain) = 0;
    virtual void initializeGraphics(QGraphicsItem *parent) = 0;
    virtual void initializeTheme(ChartTheme* theme, bool forced = false);
    virtual void initializeAnimations(QChart::AnimationOptions options, int duration,
                                      QEasingCurve &curve);

    //interface for manipulating range form base class
    virtual void setMin(const QVariant &min) = 0;
    virtual void setMax(const QVariant &max) = 0;
    virtual void setRange(const QVariant &min, const QVariant &max) = 0;

    //interface manipulating range form domain
    virtual void setRange(qreal min, qreal max) = 0;
    virtual qreal min() = 0;
    virtual qreal max() = 0;

    ChartAxisElement *axisItem() { return m_item.get(); }

public Q_SLOTS:
    void handleRangeChanged(qreal min, qreal max);

Q_SIGNALS:
    void rangeChanged(qreal min, qreal max);

protected:
    QAbstractAxis *q_ptr;
    QChart *m_chart = nullptr;
    std::unique_ptr<ChartAxisElement> m_item;

private:
    QList<QAbstractSeries*> m_series;

    Qt::Alignment m_alignment;
    Qt::Orientation m_orientation = Qt::Orientation(0);

    bool m_visible = true;

    bool m_arrowVisible = true;
    QPen m_axisPen;
    QBrush m_axisBrush;

    bool m_gridLineVisible = true;
    QPen m_gridLinePen;
    bool m_minorGridLineVisible = true;
    QPen m_minorGridLinePen;

    bool m_labelsVisible = true;
    bool m_labelsEditable = false;
    QBrush m_labelsBrush;
    QFont m_labelsFont;
    int m_labelsAngle = 0;

    bool m_labelsTruncated = false;
    bool m_truncateLabels = true;

    bool m_titleVisible = true;
    QBrush m_titleBrush;
    QFont m_titleFont;
    QString m_title;

    bool m_shadesVisible = false;
    QPen m_shadesPen;
    QBrush m_shadesBrush;
    qreal m_shadesOpacity = 1;

    bool m_dirty = false;

    bool m_reverse = false;

    Q_DECLARE_PUBLIC(QAbstractAxis);
    friend class QAbstractAxis;
    friend class QColorAxisPrivate;
    friend class ChartDataSet;
    friend class ChartPresenter;
};

QT_END_NAMESPACE

#endif
