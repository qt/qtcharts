/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
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

#ifndef CHARTLOGVALUEAXISY_H
#define CHARTLOGVALUEAXISY_H

#include <private/verticalaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QLogValueAxis;

class Q_CHARTS_PRIVATE_EXPORT ChartLogValueAxisY : public VerticalAxis
{
    Q_OBJECT

public:
    ChartLogValueAxisY(QLogValueAxis *axis, QGraphicsItem *item);
    ~ChartLogValueAxisY();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;

protected:
    QVector<qreal> calculateLayout() const;
    void updateGeometry();

private Q_SLOTS:
    void handleBaseChanged(qreal base);
    void handleLabelFormatChanged(const QString &format);

private:
    QLogValueAxis *m_axis;
};

QT_CHARTS_END_NAMESPACE

#endif /* CHARTLOGVALUEAXISY_H */
