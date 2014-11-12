/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBARCATEGORYAXIS_P_H
#define QBARCATEGORYAXIS_P_H

#include <QtCharts/QBarCategoryAxis>
#include <private/qabstractaxis_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class AbstractDomain;

class QBarCategoryAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT

public:
    QBarCategoryAxisPrivate(QBarCategoryAxis *q);
    ~QBarCategoryAxisPrivate();

public:
    void initializeGraphics(QGraphicsItem* parent);
    void initializeDomain(AbstractDomain *domain);
    void updateCategoryDomain();

    //interface for manipulating range form base class
    void setRange(const QVariant &min, const QVariant &max);
    void setMin(const QVariant &min);
    void setMax(const QVariant &max);

    //interface manipulating range form domain
    qreal min() { return m_min; }
    qreal max() { return m_max; }
    void setRange(qreal min,qreal max);

private:
    //range handling
    void setRange(const QString &minCategory, const QString &maxCategory);

private:
    QStringList m_categories;
    QString m_minCategory;
    QString m_maxCategory;
    qreal m_min;
    qreal m_max;
    int m_count;

private:
    Q_DECLARE_PUBLIC(QBarCategoryAxis);
};

QT_CHARTS_END_NAMESPACE

#endif // QBARCATEGORYAXIS_P_H
