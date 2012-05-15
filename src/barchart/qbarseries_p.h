#ifndef QBARSERIES_P_H
#define QBARSERIES_P_H

#include "qbarseries.h"
#include "qabstractseries_p.h"
#include <QStringList>
#include <QAbstractSeries>

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarModelMapper;

// Container for series
class QBarSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT
public:
    QBarSeriesPrivate(QBarSeries *parent);
    void setCategories(QBarCategories categories);
    void setBarMargin(qreal margin);
    qreal barMargin();

    void scaleDomain(Domain& domain);
    Chart* createGraphics(ChartPresenter* presenter);
    QList<LegendMarker*> createLegendMarker(QLegend* legend);

    void insertCategory(int index, const QString category);
    void removeCategory(int index);

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
    void clicked(QBarSet *barset, QString category);
    void updatedBars();
    void restructuredBars();
    void categoriesUpdated();

private Q_SLOTS:
    // slots for updating bars when data in model changes
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);
    void initializeDataFromModel();
    void barsetChanged();

protected:
    QList<QBarSet *> m_barSets;
    QBarCategories m_categories;
    QBarModelMapper *m_mapper;
private:
    Q_DECLARE_PUBLIC(QBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSERIESPRIVATE_P_H
