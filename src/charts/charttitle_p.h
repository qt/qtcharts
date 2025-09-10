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

#ifndef CHARTTITLE_P_H_
#define CHARTTITLE_P_H_

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsTextItem>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartTitle : public QGraphicsTextItem
{
public:
    ChartTitle(QGraphicsItem *parent = 0);
    ~ChartTitle();
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
    void setText(const QString &text);
    QString text() const;
    void setGeometry(const QRectF &rect);
private:
    QString m_text;
};

QT_END_NAMESPACE

#endif /* CHARTTITLE_P_H_ */
