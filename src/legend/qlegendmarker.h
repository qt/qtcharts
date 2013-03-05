/****************************************************************************
 **
 ** Copyright (C) 2013 Digia Plc
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

#ifndef QLEGENDMARKER_H
#define QLEGENDMARKER_H

#include <QChartGlobal>
#include <QObject>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLegendMarkerPrivate;
class QAbstractSeries;
class QLegend;

class QTCOMMERCIALCHART_EXPORT QLegendMarker : public QObject
{
    Q_OBJECT

public:
    enum LegendMarkerType {
        LegendMarkerTypeArea,
        LegendMarkerTypeBar,
        LegendMarkerTypePie,
        LegendMarkerTypeXY
    };

    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QBrush labelBrush READ labelBrush WRITE setLabelBrush NOTIFY labelBrushChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
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

protected:
    explicit QLegendMarker(QLegendMarkerPrivate &d, QObject *parent = 0);

    QScopedPointer<QLegendMarkerPrivate> d_ptr;
    Q_DISABLE_COPY(QLegendMarker)
    friend class QLegendPrivate;
    friend class QLegendMarkerPrivate;
    friend class LegendMarkerItem;
    friend class LegendLayout;
    friend class LegendScroller;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGENDMARKER_H
