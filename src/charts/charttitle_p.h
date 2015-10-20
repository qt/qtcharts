/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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

QT_CHARTS_BEGIN_NAMESPACE

class ChartTitle : public QGraphicsTextItem
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

QT_CHARTS_END_NAMESPACE

#endif /* CHARTTITLE_P_H_ */
