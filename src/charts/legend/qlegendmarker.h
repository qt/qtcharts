// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QLEGENDMARKER_H
#define QLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegend>
#include <QtCore/QObject>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QFont>

QT_BEGIN_NAMESPACE

class QLegendMarkerPrivate;
class QAbstractSeries;
class QLegend;

class Q_CHARTS_EXPORT QLegendMarker : public QObject
{
    Q_OBJECT

public:
    enum LegendMarkerType {
        LegendMarkerTypeArea,
        LegendMarkerTypeBar,
        LegendMarkerTypePie,
        LegendMarkerTypeXY,
        LegendMarkerTypeBoxPlot,
        LegendMarkerTypeCandlestick
    };

    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QBrush labelBrush READ labelBrush WRITE setLabelBrush NOTIFY labelBrushChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QLegend::MarkerShape shape READ shape WRITE setShape NOTIFY shapeChanged)
    Q_ENUMS(LegendMarkerType)

public:
    virtual ~QLegendMarker();
    virtual LegendMarkerType type() = 0;

    QString label() const;
    void setLabel(const QString &label);

    QBrush labelBrush() const;
    void setLabelBrush(const QBrush &brush);

    QFont font() const;
    void setFont(const QFont &font);

    QPen pen() const;
    void setPen(const QPen &pen);

    QBrush brush() const;
    void setBrush(const QBrush &brush);

    bool isVisible() const;
    void setVisible(bool visible);

    QLegend::MarkerShape shape() const;
    void setShape(QLegend::MarkerShape shape);

    virtual QAbstractSeries* series() = 0;

Q_SIGNALS:
    void clicked();
    void hovered(bool status);
    void labelChanged();
    void labelBrushChanged();
    void fontChanged();
    void penChanged();
    void brushChanged();
    void visibleChanged();
    void shapeChanged();

protected:
    explicit QLegendMarker(QLegendMarkerPrivate &d, QObject *parent = nullptr);

    QScopedPointer<QLegendMarkerPrivate> d_ptr;
    friend class QLegendPrivate;
    friend class QLegendMarkerPrivate;
    friend class LegendMarkerItem;
    friend class LegendLayout;
    friend class LegendScroller;

private:
    Q_DISABLE_COPY(QLegendMarker)
};

QT_END_NAMESPACE

#endif // QLEGENDMARKER_H
