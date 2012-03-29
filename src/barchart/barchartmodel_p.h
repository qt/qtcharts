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
    void addBarSet(QBarSet *set);
    void removeBarSet(QBarSet *set);
    void insertBarSet(int i, QBarSet *set);
    void insertCategory(int i, QString category);
    void removeCategory(int i);
    QBarSet *setAt(int index);
    QList<QBarSet *> barSets();

    int barsetCount();          // Number of sets in model
    int categoryCount();        // Number of categories

    qreal max();                // Maximum value of all sets
    qreal min();                // Minimum value of all sets
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);

    qreal categorySum(int category);
    qreal maxCategorySum();     // returns maximum sum of sets in all categories.

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
