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

#ifndef QCATEGORYAXIS_P_H
#define QCATEGORYAXIS_P_H

#include <QtCharts/QCategoryAxis>
#include <private/qvalueaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/qmap.h>
#include <QtCore/qstring.h>
#include <QtCore/qlist.h>

QT_BEGIN_NAMESPACE

typedef QPair<qreal, qreal> Range;

class Q_CHARTS_EXPORT QCategoryAxisPrivate : public QValueAxisPrivate
{
    Q_OBJECT

public:
    QCategoryAxisPrivate(QCategoryAxis *q);
    ~QCategoryAxisPrivate();

    void initializeGraphics(QGraphicsItem* parent) override;
    int ticksCount() const;

private:
    QMap<QString , Range> m_categoriesMap;
    QStringList m_categories;
    qreal m_categoryMinimum;
    QCategoryAxis::AxisLabelsPosition m_labelsPosition;

private:
    Q_DECLARE_PUBLIC(QCategoryAxis)
};

QT_END_NAMESPACE

#endif // QCATEGORYAXIS_P_H
