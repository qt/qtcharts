/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QXYSeries;
class QAbstractAxis;

class Q_CHARTS_PRIVATE_EXPORT QXYSeriesPrivate: public QAbstractSeriesPrivate
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
                               const QList<int> &indexesToSkip = {});

    void drawBestFitLine(QPainter *painter, const QRectF &clipRect);
    QPair<qreal, qreal> bestFitLineEquation(bool &ok) const;

    void setPointSelected(int index, bool selected, bool &callSignal);
    bool isPointSelected(int index);

    bool isMarkerSizeDefault();
    void setMarkerSize(qreal markerSize);

    QList<qreal> colorByData() const;

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
