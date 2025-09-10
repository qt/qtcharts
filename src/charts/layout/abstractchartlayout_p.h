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

#ifndef ABSTRACTCHARTLAYOUT_H
#define ABSTRACTCHARTLAYOUT_H

#include <QtWidgets/QGraphicsLayout>
#include <QtCore/QMargins>
#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class ChartTitle;
class ChartAxisElement;
class ChartPresenter;
class QLegend;
class ChartBackground;

class Q_CHARTS_EXPORT AbstractChartLayout : public QGraphicsLayout
{
public:
    AbstractChartLayout(ChartPresenter *presenter);
    virtual ~AbstractChartLayout();

    virtual void setMargins(const QMargins &margins);
    virtual QMargins margins() const;
    void setGeometry(const QRectF &rect) override;

protected:
    virtual QRectF calculateBackgroundGeometry(const QRectF &geometry, ChartBackground *background,
                                               bool update = true) const;
    virtual QRectF calculateBackgroundMinimum(const QRectF &minimum) const;
    virtual QRectF calculateContentGeometry(const QRectF &geometry) const;
    virtual QRectF calculateContentMinimum(const QRectF &minimum) const;
    virtual QRectF calculateTitleGeometry(const QRectF &geometry, ChartTitle *title,
                                          bool update = true) const;
    virtual QRectF calculateTitleMinimum(const QRectF &minimum, ChartTitle *title) const;
    virtual QRectF calculateLegendGeometry(const QRectF &geometry, QLegend *legend,
                                           bool update = true) const;
    virtual QRectF calculateLegendMinimum(const QRectF &minimum, QLegend *legend) const;

    virtual QRectF calculateAxisGeometry(const QRectF &geometry,
                                         const QList<ChartAxisElement *>& axes,
                                         bool update = true) const = 0;
    virtual QRectF calculateAxisMinimum(const QRectF &minimum,
                                        const QList<ChartAxisElement *>& axes) const = 0;

    // from QGraphicsLayout
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;
    int count() const override { return 0; }
    QGraphicsLayoutItem *itemAt(int) const override { return 0; };
    void removeAt(int) override {};

    ChartPresenter *m_presenter;
    QMargins m_margins;
    QRectF m_minAxisRect;
};

QT_END_NAMESPACE

#endif // ABSTRACTCHARTLAYOUT_H
