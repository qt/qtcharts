#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QObject>
#include <QStringList>
#include "qchartglobal.h"
#include <qseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Model for bar chart. Internal class.
// TODO: Implement as QAbstractItemModel?

class QBarSet;

class BarChartModel : public QObject //, public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BarChartModel(QStringList categories, QObject *parent = 0);

    QStringList category();
    void appendBarSet(QBarSet *set);
    void removeBarSet(QBarSet *set);
    void insertBarSet(int i, QBarSet *set);
    void insertCategory(int i, QString category);
    void removeCategory(int i);
    QBarSet *barsetAt(int index) const;
    QList<QBarSet *> barSets() const;

    int barsetCount() const;          // Number of sets in model
    int categoryCount() const;        // Number of categories

    qreal max() const;                // Maximum value of all sets
    qreal min() const;                // Minimum value of all sets
    qreal valueAt(int set, int category) const;
    qreal percentageAt(int set, int category) const;

    qreal categorySum(int category) const;
    qreal maxCategorySum() const;     // returns maximum sum of sets in all categories.

    QString categoryName(int category);

Q_SIGNALS:
    void modelUpdated();

public Q_SLOTS:
    
private:

    QList<QBarSet *> m_dataModel;
    QStringList m_category;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTMODEL_H
