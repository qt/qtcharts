#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QObject>
#include <QStringList>
#include "qchartglobal.h"

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
    QBarSet *setAt(int index);
    QList<QBarSet*> barSets();

    QList<QString> legend();

    int countSets();            // Number of sets in model
    int countCategories();      // Number of categories
    int countTotalItems();      // Total items in all sets. Includes empty items.

    qreal max();                // Maximum value of all sets
    qreal min();                // Minimum value of all sets
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);

    qreal categorySum(int category);
    qreal maxCategorySum();     // returns maximum sum of sets in all categories.

    QString label(int category);

signals:
    void modelUpdated();

public slots:
    
private:

    QList<QBarSet*> mDataModel;
    QStringList mCategory;

    int mCurrentSet;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTMODEL_H
