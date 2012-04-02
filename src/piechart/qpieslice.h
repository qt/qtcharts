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
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY changed)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY changed)

public:
    QPieSlice(QObject *parent = 0);
    QPieSlice(qreal value, QString label, QObject *parent = 0);
    virtual ~QPieSlice();

    // data
    void setValue(qreal value);
    qreal value() const;
    void setLabel(QString label);
    QString label() const;
    void setLabelVisible(bool visible = true);
    bool isLabelVisible() const;
    void setExploded(bool exploded = true);
    bool isExploded() const;

    // generated data
    qreal percentage() const;
    qreal startAngle() const;
    qreal endAngle() const;

    // customization
    void setPen(const QPen &pen);
    QPen pen() const;
    void setBrush(const QBrush &brush);
    QBrush brush() const;
    void setLabelPen(const QPen &pen);
    QPen labelPen() const;
    void setLabelFont(const QFont &font);
    QFont labelFont() const;
    void setLabelArmLengthFactor(qreal factor);
    qreal labelArmLengthFactor() const;
    void setExplodeDistanceFactor(qreal factor);
    qreal explodeDistanceFactor() const;

Q_SIGNALS:
    void clicked(Qt::MouseButtons buttons);
    void hoverEnter();
    void hoverLeave();
    void changed();
    void selected();

private:
    friend class PieSliceData;
    PieSliceData * const d;
    Q_DISABLE_COPY(QPieSlice)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICE_H
