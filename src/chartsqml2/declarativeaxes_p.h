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

#ifndef DECLARATIVEAXES_H
#define DECLARATIVEAXES_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/qabstractaxis.h>
#include <QtCore/QObject>
#include <private/declarativechartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativeAxes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)
    QML_NAMED_ELEMENT(DeclarativeAxes)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Abstract base type")

public:
    explicit DeclarativeAxes(QObject *parent = 0);

    QAbstractAxis *axisX() { return m_axisX; }
    void setAxisX(QAbstractAxis *axis);
    QAbstractAxis *axisY() { return m_axisY; }
    void setAxisY(QAbstractAxis *axis);
    QAbstractAxis *axisXTop() { return m_axisXTop; }
    void setAxisXTop(QAbstractAxis *axis);
    QAbstractAxis *axisYRight() { return m_axisYRight; }
    void setAxisYRight(QAbstractAxis *axis);

public:
    void emitAxisXChanged() { emit axisXChanged(m_axisX); }
    void emitAxisYChanged() { emit axisYChanged(m_axisY); }
    void emitAxisXTopChanged() { emit axisXTopChanged(m_axisXTop); }
    void emitAxisYRightChanged() { emit axisYRightChanged(m_axisYRight); }

Q_SIGNALS:
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);
    void axisXTopChanged(QAbstractAxis *axis);
    void axisYRightChanged(QAbstractAxis *axis);

private:
    QAbstractAxis *m_axisX;
    QAbstractAxis *m_axisY;
    QAbstractAxis *m_axisXTop;
    QAbstractAxis *m_axisYRight;
};

QT_END_NAMESPACE

#endif // DECLARATIVEAXES_H
