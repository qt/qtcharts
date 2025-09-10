// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QXYSERIES_P_H
#define QXYSERIES_P_H

#include <private/qabstractseries_p.h>
#include <private/qxyseries_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/qvariant.h>
#include <QtCore/qhash.h>
#include <QtCore/qset.h>
#include <QtGui/qcolor.h>
#include <QtGui/qpen.h>
#include <QtCore/qlist.h>

QT_BEGIN_NAMESPACE

class QAbstractAxis;

class Q_CHARTS_EXPORT QXYSeriesPrivate: public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QXYSeriesPrivate(QXYSeries *q);

    void initializeDomain() override;
    void initializeAxes() override;
    void initializeAnimations(QChart::AnimationOptions options, int duration,
                              QEasingCurve &curve) override;

    QList<QLegendMarker*> createLegendMarkers(QLegend* legend) override;

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const override;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const override;

    void drawPointLabels(QPainter *painter, const QList<QPointF> &allPoints, const int offset = 0);
    void drawSeriesPointLabels(QPainter *painter, const QList<QPointF> &points,
                               const int offset = 0, const QHash<int, int> &offsets = {},
                               const QList<int> &indexesToSkip = {},
                               const QHash<int, QString> &customLabels = {});

    void drawBestFitLine(QPainter *painter, const QRectF &clipRect);
    QPair<qreal, qreal> bestFitLineEquation(bool &ok) const;

    void setPointSelected(int index, bool selected, bool &callSignal);
    bool isPointSelected(int index);

    bool isMarkerSizeDefault();
    void setMarkerSize(qreal markerSize);

    QList<qreal> colorByData() const;

    bool setPointConfiguration(const int index, const QXYSeries::PointConfiguration key,
                               const QVariant &value);


Q_SIGNALS:
    void seriesUpdated();

protected:
    QList<QPointF> m_points;
    QSet<int> m_selectedPoints;
    QPen m_pen;
    QColor m_selectedColor;
    QBrush m_brush;
    bool m_pointsVisible;
    QString m_pointLabelsFormat;
    bool m_pointLabelsVisible;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;
    QImage m_lightMarker;
    QImage m_selectedLightMarker;
    QPen m_bestFitLinePen;
    bool m_bestFitLineVisible;
    qreal m_markerSize;
    bool m_markerSizeDefault = true;

    QHash<int, QHash<QXYSeries::PointConfiguration, QVariant>> m_pointsConfiguration;
    QList<qreal> m_colorByData;

private:
    Q_DECLARE_PUBLIC(QXYSeries)
    friend class QScatterSeries;
};

QT_END_NAMESPACE

#endif
