#ifndef BARSERIES_H
#define BARSERIES_H

#include "qseries.h"
#include <QStringList>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSet;
class BarChartModel;
class BarCategory;

// Container for series
class QTCOMMERCIALCHART_EXPORT QBarSeries : public QSeries
{
    Q_OBJECT
public:
    QBarSeries(QStringList categories, QObject* parent=0);

    virtual QSeriesType type() const { return QSeries::SeriesTypeBar; }

    void addBarSet(QBarSet *set);               // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    int barsetCount();
    int categoryCount();
    QList<QBarSet*> barSets();
    QList<QSeries::LegendEntry> legendEntries();

public:
    // TODO: Functions below this are not part of api and will be moved
    // to private implementation, when we start using it
    // TODO: TO PIMPL --->
    QBarSet* barsetAt(int index);
    QString categoryName(int category);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal maxCategorySum();
    BarChartModel& model();
    bool separatorsVisible();
    // <--- TO PIMPL

signals:
    //void changed(int index);
    void clicked(QBarSet* barset, QString category);        // Up to user of api, what to do with these signals
    void rightClicked(QBarSet* barset, QString category);

    // TODO: internal signals, these to private implementation.
    // TODO: TO PIMPL --->
    void enableSeparators(bool enable);
    void showToolTip(QPoint pos, QString tip);
    // <--- TO PIMPL

public Q_SLOTS:
    void setToolTipEnabled(bool enabled=true);           // enables tooltips
    void setSeparatorsVisible(bool visible=true);        // enables separators between categories

    // TODO: TO PIMPL --->
    void barsetClicked(QString category);
    void barsetRightClicked(QString category);
    // <--- TO PIMPL

protected:
    BarChartModel* mModel;
    bool mSeparatorsVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARSERIES_H
