#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QObject>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Model for bar chart. Internal class.
// TODO: Implement as QAbstractItemModel?

class QBarSet;
class QBarCategory;

class BarChartModel : public QObject //, public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BarChartModel(QBarCategory *category, QObject *parent = 0);
    ~BarChartModel();

    QBarCategory& category();
    void addBarSet(QBarSet *set);
    void removeBarSet(QBarSet *set);
    QBarSet* nextSet(bool getFirst);

    QBarSet& setAt(int index);  // Internal

    int countSets();            // Number of sets in model
    int countCategories();      // Number of categories
    int countTotalItems();      // Total items in all sets. Includes empty items.

    qreal max();                // Maximum value of all sets
    qreal min();                // Minimum value of all sets
    qreal valueAt(int set, int category);

    qreal categorySum(int column);
    qreal maxCategorySum();     // returns maximum sum of sets in all categories.

    QString label(int category);

signals:
    void modelUpdated();

public slots:
    
private:

    QList<QBarSet*> mDataModel;
    QBarCategory* mCategory;    // Owned

    int mCurrentSet;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTMODEL_H
