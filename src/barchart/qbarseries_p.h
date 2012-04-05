#ifndef QBARSERIES_P_H
#define QBARSERIES_P_H

#include "qbarseries.h"
#include "qseries_p.h"
#include <QStringList>
#include <QSeries>

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QBarSeriesPrivate : public QSeriesPrivate
{
    Q_OBJECT
public:
    QBarSeriesPrivate(QBarCategories categories, QBarSeries *parent);

    bool setModel(QAbstractItemModel *model);
    void setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation = Qt::Vertical);

    QBarSet* barsetAt(int index);
    QString categoryName(int category);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal absoluteCategorySum(int category);
    qreal maxCategorySum();
    BarChartModel& modelInternal();

Q_SIGNALS:
    void clicked(QBarSet *barset, QString category, Qt::MouseButtons button);        // Up to user of api, what to do with these signals
    void selected();
    void updatedBars();
    void restructuredBars();
    void showToolTip(QPoint pos, QString tip);

public Q_SLOTS:
    void setToolTipEnabled(bool enabled = true);           // enables tooltips
    void barsetClicked(QString category, Qt::MouseButtons button);

private Q_SLOTS:
    // slots for updating bars when data in model changes
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);
    void barsetChanged();

protected:
    BarChartModel *m_internalModel;     // TODO: this may change... current "2 models" situation doesn't look good.
    QAbstractItemModel* m_model;
    int m_mapCategories;
    int m_mapBarBottom;
    int m_mapBarTop;
    int m_mapFirst;
    int m_mapCount;
    Qt::Orientation m_mapOrientation;
private:
    Q_DECLARE_PUBLIC(QBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSERIESPRIVATE_P_H
