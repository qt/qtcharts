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

#ifndef QBARSET_H
#define QBARSET_H

#include <qchartglobal.h>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarSet : public QObject
{
    Q_OBJECT
public:
    QBarSet(QString name, QObject *parent = 0);

    void setName(QString name);
    QString name() const;
    QBarSet& operator << (const qreal &value);  // appends new value to set
    void insertValue(int i, qreal value);
    void removeValue(int i);

    // TODO: remove indices eventually. Use as internal?
    int count() const;                          // count of values in set
    qreal valueAt(int index) const;                   // for modifying individual values
    void setValue(int index, qreal value);      // setter for individual value
    qreal total() const;                              // total values in the set

    // TODO:
    //qreal value(QString category);
    //void setValue(QString category, qreal value);

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setLabelPen(const QPen &pen);
    QPen labelPen() const;

    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setLabelFont(const QFont &font);
    QFont labelFont() const;

    void setLabelsVisible(bool visible = true);
    bool labelsVisible() const;

Q_SIGNALS:
    void clicked(QString category, Qt::MouseButtons button);                         // Clicked and hover signals exposed to user

    // TODO: TO PIMPL --->
    void structureChanged();
    void valueChanged();
    void hoverEnter(QPoint pos);
    void hoverLeave();
    void showToolTip(QPoint pos, QString tip);  // Private signal
    void labelsVisibleChanged(bool visible);
    // <--- TO PIMPL

public Q_SLOTS:
    // These are for internal communication
    // TODO: TO PIMPL --->
    void barHoverEnterEvent(QPoint pos);
    void barHoverLeaveEvent();
    // <--- TO PIMPL

private:

    QString m_name;
    QList<qreal> m_values;   // TODO: replace with map (category, value)
    QMap<QString, qreal> m_mappedValues;
    QPen m_pen;
    QBrush m_brush;
    QPen m_labelPen;
    QBrush m_labelBrush;
    QFont m_labelFont;
    bool m_labelsVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
