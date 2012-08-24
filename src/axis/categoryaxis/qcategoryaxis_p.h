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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QCATEGORYAXIS_P_H
#define QCATEGORYAXIS_P_H

#include "qcategoryaxis.h"
#include "qvalueaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

typedef QPair<qreal, qreal> Range;

class QCategoryAxisPrivate : public QValueAxisPrivate
{
    Q_OBJECT

public:
    QCategoryAxisPrivate(QCategoryAxis *q);
    ~QCategoryAxisPrivate();


public:
    ChartAxis* createGraphics(ChartPresenter* presenter);
    int ticksCount() const;

Q_SIGNALS:
    void changed(qreal min, qreal max, int tickCount,bool niceNumbers);

public Q_SLOTS:
    void handleAxisRangeChanged(qreal min, qreal max,int count);

private:
    QMap<QString , Range> m_categoriesMap;
    QStringList m_categories;
    qreal m_categoryMinimum;

private:
    Q_DECLARE_PUBLIC(QCategoryAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCATEGORYAXIS_P_H
