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

#ifndef QBARSERIES_P_H
#define QBARSERIES_P_H

#include "qbarseries.h"
#include "qabstractseries_p.h"
#include <QStringList>
#include <QAbstractSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarModelMapper;

class QBarSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT
public:
    QBarSeriesPrivate(QBarSeries *parent);
    // TODO: refactor/remove private category stuff
    void setCategories(QStringList categories);
    void insertCategory(int index, const QString category);
    void removeCategory(int index);
    int categoryCount() const;
    QStringList categories() const;

    void setBarMargin(qreal margin);
    qreal barMargin() const;

    void setVisible(bool visible);
    bool isVisible() const;

    void scaleDomain(Domain& domain);
    Chart* createGraphics(ChartPresenter* presenter);
    QList<LegendMarker*> createLegendMarker(QLegend* legend);

    bool append(QBarSet *set);
    bool remove(QBarSet *set);
    bool append(QList<QBarSet* > sets);
    bool remove(QList<QBarSet* > sets);

    QBarSet* barsetAt(int index);
    QString categoryName(int category);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal absoluteCategorySum(int category);
    qreal maxCategorySum();

Q_SIGNALS:
    void clicked(QBarSet *barset, int index);
    void updatedBars();
    void restructuredBars();
    void categoriesUpdated();
    void labelsVisibleChanged(bool visible);

private Q_SLOTS:
    void barsetChanged();

protected:
    QList<QBarSet *> m_barSets;
    QStringList m_categories;
    qreal m_barMargin;
    bool m_labelsVisible;
    bool m_visible;

private:
    Q_DECLARE_PUBLIC(QBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSERIESPRIVATE_P_H
