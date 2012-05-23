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

#ifndef QPIESLICE_H
#define QPIESLICE_H

#include <qchartglobal.h>
#include <QObject>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieSliceData;

class QTCOMMERCIALCHART_EXPORT QPieSlice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(bool labelVisible READ isLabelVisible WRITE setLabelVisible)
    Q_PROPERTY(bool exploded READ isExploded WRITE setExploded)
    Q_PROPERTY(qreal LabelArmLengthFactor READ labelArmLengthFactor WRITE setLabelArmLengthFactor)
    Q_PROPERTY(qreal explodeDistanceFactor READ explodeDistanceFactor WRITE setExplodeDistanceFactor)
    Q_PROPERTY(qreal percentage READ percentage NOTIFY calculatedDataChanged)
    Q_PROPERTY(qreal startAngle READ startAngle NOTIFY calculatedDataChanged)
    Q_PROPERTY(qreal endAngle READ endAngle NOTIFY calculatedDataChanged)

public:
    explicit QPieSlice(QObject *parent = 0);
    QPieSlice(QString label, qreal value, QObject *parent = 0);
    virtual ~QPieSlice();

    void setLabel(QString label);
    QString label() const;

    void setValue(qreal value);
    qreal value() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setLabelVisible(bool visible = true);
    bool isLabelVisible() const;

    void setLabelArmLengthFactor(qreal factor);
    qreal labelArmLengthFactor() const;

    void setLabelPen(const QPen &pen);
    QPen labelPen() const;

    void setLabelFont(const QFont &font);
    QFont labelFont() const;

    void setExploded(bool exploded = true);
    bool isExploded() const;

    void setExplodeDistanceFactor(qreal factor);
    qreal explodeDistanceFactor() const;

    qreal percentage() const;
    qreal startAngle() const;
    qreal endAngle() const;

Q_SIGNALS:
    void labelChanged();
    void valueChanged();
    void appearanceChanged();
    void calculatedDataChanged();
    void clicked();
    void hovered(bool state);

private:
    friend class PieSliceData;
    PieSliceData * const d;
    Q_DISABLE_COPY(QPieSlice)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICE_H
