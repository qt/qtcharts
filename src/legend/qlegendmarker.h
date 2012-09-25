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

// TODO: should this be QAbstractLegendMarker?
class QTCOMMERCIALCHART_EXPORT QLegendMarker : public QObject
{
    Q_OBJECT

// TODO: need for these?
//    Q_PROPERTY(QString label READ label WRITE setlabel NOTIFY labelChanged);
//    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged);
//    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged);

public:
//    explicit QLegendMarker(QAbstractSeries* series, QObject *parent = 0);
    virtual ~QLegendMarker();

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

//    virtual QAbstractSeries::SeriesType type() = 0; // TODO?
    virtual QAbstractSeries* series() = 0;
    virtual QObject* peerObject() = 0;

protected:
    explicit QLegendMarker(QLegendMarkerPrivate &d, QObject *parent = 0);

Q_SIGNALS:
    void clicked();
    void hovered(bool status);

protected:
    QScopedPointer<QLegendMarkerPrivate> d_ptr;
    Q_DISABLE_COPY(QLegendMarker)
    friend class QLegendPrivate;
    friend class QLegendMarkerPrivate;
    friend class LegendLayout;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGENDMARKER_H
