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

#ifndef CHARTCATEGORYAXISY_H
#define CHARTCATEGORYAXISY_H

#include <private/verticalaxis_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QCategoryAxis;

class ChartCategoryAxisY : public VerticalAxis
{
    Q_OBJECT
public:
    ChartCategoryAxisY(QCategoryAxis *axis, QGraphicsItem* item = 0);
    ~ChartCategoryAxisY();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;

public Q_SLOTS:
    void handleCategoriesChanged();

protected:
    QVector<qreal> calculateLayout() const;
    void updateGeometry();

private:
    QCategoryAxis *m_axis;
};

QT_CHARTS_END_NAMESPACE

#endif /* CHARTCATEGORYAXISY_H */
