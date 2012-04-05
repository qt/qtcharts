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

#include "qbarseries.h"
#include "qbarseries_p.h"
#include "qbarset.h"
#include "qbarset_p.h"
#include "barchartmodel_p.h"

#include <QAbstractItemModel>
#include <QModelIndex>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \brief part of QtCommercial chart API.

    QBarSeries represents a series of data shown as bars. One QBarSeries can contain multible
    QBarSet data sets. QBarSeries groups the data from sets to categories, which are defined
    by QStringList.

    \mainclass

    \sa QBarSet, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn virtual QSeriesType QBarSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
    \fn void QBarSeries::showToolTip(QPoint pos, QString tip)
    \brief \internal \a pos \a tip
*/

/*!
    Constructs empty QBarSeries. Parameter \a categories defines the categories for chart.
    QBarSeries is QObject which is a child of a \a parent.
*/

QBarSeries::QBarSeries(QBarCategories categories, QObject *parent) : QSeries(*new QBarSeriesPrivate(categories, this),parent)
{

}

QSeries::QSeriesType QBarSeries::type() const
{
    return QSeries::SeriesTypeBar;
}

/*!
    Adds a set of bars to series. Takes ownership of \a set.
    Connects the clicked(QString, Qt::MouseButtons) signal
    of \a set to this series
*/
void QBarSeries::appendBarSet(QBarSet *set)
{
    Q_D(QBarSeries);
    d->m_internalModel->appendBarSet(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(clicked(QString,Qt::MouseButtons)), d, SLOT(barsetClicked(QString,Qt::MouseButtons)));
    QObject::connect(set->d_ptr.data(), SIGNAL(valueChanged()), d, SLOT(barsetChanged()));
    emit d->restructuredBars();
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesnt delete \a set.
    Disconnects the clicked(QString, Qt::MouseButtons) signal
    of \a set from this series
*/
void QBarSeries::removeBarSet(QBarSet *set)
{
    Q_D(QBarSeries);
    QObject::disconnect(set->d_ptr.data(), SIGNAL(clicked(QString,Qt::MouseButtons)), d, SLOT(barsetClicked(QString,Qt::MouseButtons)));
    d->m_internalModel->removeBarSet(set);
    emit d->restructuredBars();
}

/*!
    Adds a list of barsets to series. Takes ownership of \a sets.
    Connects the clicked(QString, Qt::MouseButtons) signals
    of \a sets to this series
*/
void QBarSeries::appendBarSets(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);
    foreach (QBarSet* barset, sets) {
        d->m_internalModel->appendBarSet(barset);
        QObject::connect(barset, SIGNAL(clicked(QString,Qt::MouseButtons)), this, SLOT(barsetClicked(QString,Qt::MouseButtons)));
        QObject::connect(barset, SIGNAL(valueChanged()), this, SLOT(barsetChanged()));
    }
    emit d->restructuredBars();

}

/*!
    Removes a list of barsets from series. Releases ownership of \a sets. Doesnt delete \a sets.
    Disconnects the clicked(QString, Qt::MouseButtons) signal
    of \a sets from this series
*/
void QBarSeries::removeBarSets(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);

    foreach (QBarSet* barset, sets) {
        QObject::disconnect(barset, SIGNAL(clicked(QString,Qt::MouseButtons)), this, SLOT(barsetClicked(QString,Qt::MouseButtons)));
        d->m_internalModel->removeBarSet(barset);
    }
    emit d->restructuredBars();
}

/*!
    Inserts new \a set on the \a i position.
    The barset that is currently at this postion is moved to postion i + 1
*/
void QBarSeries::insertBarSet(int i, QBarSet *set)
{
    Q_D(QBarSeries);
    d->m_internalModel->insertBarSet(i, set);
    emit d->barsetChanged();
}

/*!
    Inserts new \a category on the \a i position.
    The category that is currently at this postion is moved to postion i + 1
    \sa removeCategory()
*/
void QBarSeries::insertCategory(int i, QString category)
{
    Q_D(QBarSeries);
    d->m_internalModel->insertCategory(i, category);
}

/*!
    Removes the category specified by \a i
    \sa insertCategory()
*/
void QBarSeries::removeCategory(int i)
{
    Q_D(QBarSeries);
    d->m_internalModel->removeCategory(i);
}

/*!
    Returns number of sets in series.
*/
int QBarSeries::barsetCount() const
{
    Q_D(const QBarSeries);
    /*
    //    if(m_model)
    //        return m_mapBarTop - m_mapBarBottom;
    //    else

    */
    return d->m_internalModel->barsetCount();
}

/*!
    Returns number of categories in series
*/
int QBarSeries::categoryCount() const
{
    Q_D(const QBarSeries);
    return d->m_internalModel->categoryCount();
}

/*!
    Returns a list of sets in series. Keeps ownership of sets.
 */
QList<QBarSet*> QBarSeries::barSets() const
{
    Q_D(const QBarSeries);
    return d->m_internalModel->barSets();
}

/*!
    \internal \a index
*/
QBarSet* QBarSeries::barsetAt(int index)
{
    Q_D(QBarSeries);
    return d->barsetAt(index);
//    return m_internalModel->barsetAt(index);
}

/*!
    \internal \a category
*/
QString QBarSeries::categoryName(int category)
{
    Q_D(QBarSeries);
    return d->categoryName(category);
//    return m_internalModel->categoryName(category);
}

/*!
    Enables or disables tooltip depending on parameter \a enabled.
    Tooltip shows the name of set, when mouse is hovering on top of bar.
    Calling without parameter \a enabled, enables the tooltip
*/
void QBarSeries::setToolTipEnabled(bool enabled)
{
    Q_D(QBarSeries);
    d->setToolTipEnabled(enabled);
    /*
    // TODO: what if we add sets after call to this function? Those sets won't have tooltip enabled.
    if (enabled) {
        for (int i=0; i<m_internalModel->barsetCount(); i++) {
            QBarSet *set = m_internalModel->barsetAt(i);
            connect(set, SIGNAL(showToolTip(QPoint,QString)), this, SIGNAL(showToolTip(QPoint,QString)));
        }
    } else {
        for (int i=0; i<m_internalModel->barsetCount(); i++) {
            QBarSet *set = m_internalModel->barsetAt(i);
            disconnect(set, SIGNAL(showToolTip(QPoint,QString)), this, SIGNAL(showToolTip(QPoint,QString)));
        }
    }
    */
}


/*!
    \internal \a category
*/
void QBarSeries::barsetClicked(QString category, Qt::MouseButtons button)
{
    Q_D(QBarSeries);
    d->barsetClicked(category,button);
//    emit clicked(qobject_cast<QBarSet*>(sender()), category, button);
}

/*!
    \internal
*/
qreal QBarSeries::min()
{
    Q_D(QBarSeries);
    return d->min();
    //return m_internalModel->min();
}

/*!
    \internal
*/
qreal QBarSeries::max()
{
    Q_D(QBarSeries);
    return d->max();
//    return m_internalModel->max();
}

/*!
    \internal \a set \a category
*/
qreal QBarSeries::valueAt(int set, int category)
{
    Q_D(QBarSeries);
    return d->valueAt(set,category);
//    return m_internalModel->valueAt(set, category);
}

/*!
    \internal \a set \a category
*/
qreal QBarSeries::percentageAt(int set, int category)
{
    Q_D(QBarSeries);
    return d->percentageAt(set,category);
//    return m_internalModel->percentageAt(set, category);
}

/*!
    \internal \a category
*/
qreal QBarSeries::categorySum(int category)
{
    Q_D(QBarSeries);
    return d->categorySum(category);
//    return m_internalModel->categorySum(category);
}

/*!
    \internal \a category
*/
qreal QBarSeries::absoluteCategorySum(int category)
{
    Q_D(QBarSeries);
    return d->absoluteCategorySum(category);
//    return m_internalModel->absoluteCategorySum(category);
}

/*!
    \internal
*/
qreal QBarSeries::maxCategorySum()
{
    Q_D(QBarSeries);
    return d->maxCategorySum();
//    return m_internalModel->maxCategorySum();
}

/*!
    \internal
*/
BarChartModel& QBarSeries::modelInternal()
{
    Q_D(QBarSeries);
    return d->modelInternal();
//    return *m_internalModel;
}

/*!
     \fn bool QBarSeries::setModel(QAbstractItemModel *model)
     Sets the \a model to be used as a data source
 */
bool QBarSeries::setModel(QAbstractItemModel *model)
{
    Q_D(QBarSeries);
    return d->setModel(model);
    /*
    // disconnect signals from old model
    if(m_model)
    {
        disconnect(m_model, 0, this, 0);
        m_mapCategories = -1;
        m_mapBarBottom = -1;
        m_mapBarTop = -1;
        m_mapFirst = 0;
        m_mapCount = 0;
        m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if(model)
    {
        m_model = model;
        return true;
    }
    else
    {
        m_model = 0;
        return false;
    }
    */
}

/*!
     \fn bool QBarSeries::setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation)
     Sets column/row specified by \a categories to be used as a list of bar series categories.
     Parameter \a bottomBoundry indicates the column/row where the first bar set is located in the model.
     Parameter \a topBoundry indicates the column/row where the last bar set is located in the model.
     All the columns/rows inbetween those two values are also used as data for bar sets.
     The \a orientation paramater specifies whether the data is in columns or in rows.
 */
void QBarSeries::setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation)
{
    Q_D(QBarSeries);
    d->setModelMapping(categories,bottomBoundary,topBoundary,orientation);
/*
    if (!m_model)
        return;

    m_mapCategories = categories;
    m_mapBarBottom = bottomBoundry;
    m_mapBarTop = topBoundry;
//    m_mapFirst = 1;
    m_mapOrientation = orientation;

    // connect the signals
    if (m_mapOrientation == Qt::Vertical) {
        m_mapCount = m_model->rowCount() - m_mapFirst;
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(rowsInserted(QModelIndex, int, int)),
                this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    } else {
        m_mapCount = m_model->columnCount() - m_mapFirst;
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(columnsInserted(QModelIndex, int, int)),
                this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(columnsRemoved(QModelIndex, int, int)),
                this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }

    // create the initial bars
    delete m_internalModel;
    if (m_mapOrientation == Qt::Vertical) {
        QStringList categories;
        for (int k = m_mapFirst; k < m_mapFirst + m_mapCount; k++)
            categories << m_model->data(m_model->index(k, m_mapCategories), Qt::DisplayRole).toString();
        m_internalModel = new BarChartModel(categories, this);

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(QString("Column: %1").arg(i + 1));
            for(int m = m_mapFirst; m < m_mapFirst + m_mapCount; m++)
                *barSet << m_model->data(m_model->index(m, i), Qt::DisplayRole).toDouble();
            appendBarSet(barSet);
        }
    } else {
        QStringList categories;
        for (int k = m_mapFirst; k < m_mapFirst + m_mapCount; k++)
            categories << m_model->data(m_model->index(m_mapCategories, k), Qt::DisplayRole).toString();
        m_internalModel = new BarChartModel(categories, this);

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(QString("Row: %1").arg(i + 1));
            for(int m = m_mapFirst; m < m_mapFirst + m_mapCount; m++)
                *barSet << m_model->data(m_model->index(i, m), Qt::DisplayRole).toDouble();
            appendBarSet(barSet);
        }
    }
*/
}

/*!
    \internal
*/
void QBarSeries::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    Q_D(QBarSeries);
    d->modelUpdated(topLeft,bottomRight);
    /*
    Q_UNUSED(bottomRight)

    if (m_mapOrientation == Qt::Vertical)
    {
        // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
        if (topLeft.column() >= m_mapBarBottom && topLeft.column() <= m_mapBarTop && topLeft.row() >= m_mapFirst && topLeft.row() < m_mapFirst + m_mapCount)
            barsetAt(topLeft.column() - m_mapBarBottom)->setValue(topLeft.row() - m_mapFirst, m_model->data(topLeft, Qt::DisplayRole).toDouble());
    }
    else
    {
        // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
        if (topLeft.row() >= m_mapBarBottom && topLeft.row() <= m_mapBarTop && topLeft.column() >= m_mapFirst && topLeft.column() < m_mapFirst + m_mapCount)
            barsetAt(topLeft.row() - m_mapBarBottom)->setValue(topLeft.column() - m_mapFirst, m_model->data(topLeft, Qt::DisplayRole).toDouble());
    }
    */
}

/*!
    \internal
*/
void QBarSeries::modelDataAdded(QModelIndex parent, int start, int end)
{
    Q_D(QBarSeries);
    d->modelDataAdded(parent,start,end);
/*
    if (m_mapOrientation == Qt::Vertical) {
        insertCategory(start - m_mapFirst, QString("Row: %1").arg(start + 1));
        for (int i = 0; i <= m_mapBarTop - m_mapBarBottom; i++) {
            barsetAt(i)->insertValue(start - m_mapFirst, m_model->data(m_model->index(start, i), Qt::DisplayRole).toDouble());
        }
    } else {
        insertCategory(start - m_mapFirst, QString("Column: %1").arg(start + 1));
        for (int i = 0; i <= m_mapBarTop - m_mapBarBottom; i++) {
            barsetAt(i)->insertValue(start - m_mapFirst, m_model->data(m_model->index(i, start), Qt::DisplayRole).toDouble());
        }
    }
    emit restructuredBars();
*/
}

/*!
    \internal
*/
void QBarSeries::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_D(QBarSeries);
    d->modelDataRemoved(parent,start,end);
/*
    Q_UNUSED(parent)
    Q_UNUSED(end)

    removeCategory(start - m_mapFirst);
    for (int i = 0; i <= m_mapBarTop - m_mapBarBottom; i++)
    {
        barsetAt(i)->removeValue(start - m_mapFirst);
    }
    emit restructuredBars();
*/
}

void QBarSeries::barsetChanged()
{
    Q_D(QBarSeries);
    d->barsetChanged();
//    emit updatedBars();
}

QBarCategories QBarSeries::categories() const
{
    Q_D(const QBarSeries);

    QBarCategories categories;
    int count = d->m_internalModel->categoryCount();
    for (int i=1; i <= count; i++) {
          categories.insert(i, d->m_internalModel->categoryName(i - 1));
    }
    return categories;

}

/*!
    Sets the visibility of labels in series to \a visible
*/
void QBarSeries::setLabelsVisible(bool visible)
{
    foreach (QBarSet* s, barSets()) {
        s->setLabelsVisible(visible);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSeriesPrivate::QBarSeriesPrivate(QBarCategories categories, QBarSeries *q) : QSeriesPrivate(q),
    m_internalModel(new BarChartModel(categories,this)),
    m_model(0),
    m_mapCategories(-1),
    m_mapBarBottom(-1),
    m_mapBarTop(-1),
    m_mapFirst(0),
    m_mapCount(0),
    m_mapOrientation(Qt::Vertical)
{
}

QBarSet* QBarSeriesPrivate::barsetAt(int index)
{
    return m_internalModel->barsetAt(index);
}

QString QBarSeriesPrivate::categoryName(int category)
{
    return m_internalModel->categoryName(category);
}

void QBarSeriesPrivate::setToolTipEnabled(bool enabled)
{
    // TODO: what if we add sets after call to this function? Those sets won't have tooltip enabled.
    if (enabled) {
        for (int i=0; i<m_internalModel->barsetCount(); i++) {
            QBarSet *set = m_internalModel->barsetAt(i);
            connect(set, SIGNAL(showToolTip(QPoint,QString)), this, SIGNAL(showToolTip(QPoint,QString)));
        }
    } else {
        for (int i=0; i<m_internalModel->barsetCount(); i++) {
            QBarSet *set = m_internalModel->barsetAt(i);
            disconnect(set, SIGNAL(showToolTip(QPoint,QString)), this, SIGNAL(showToolTip(QPoint,QString)));
        }
    }
}

void QBarSeriesPrivate::barsetClicked(QString category, Qt::MouseButtons button)
{
    emit clicked(qobject_cast<QBarSet*>(sender()), category, button);
}

qreal QBarSeriesPrivate::min()
{
    return m_internalModel->min();
}

qreal QBarSeriesPrivate::max()
{
    return m_internalModel->max();
}

qreal QBarSeriesPrivate::valueAt(int set, int category)
{
    return m_internalModel->valueAt(set, category);
}

qreal QBarSeriesPrivate::percentageAt(int set, int category)
{
    return m_internalModel->percentageAt(set, category);
}

qreal QBarSeriesPrivate::categorySum(int category)
{
    return m_internalModel->categorySum(category);
}

qreal QBarSeriesPrivate::absoluteCategorySum(int category)
{
    return m_internalModel->absoluteCategorySum(category);
}

qreal QBarSeriesPrivate::maxCategorySum()
{
    return m_internalModel->maxCategorySum();
}

BarChartModel& QBarSeriesPrivate::modelInternal()
{
    return *m_internalModel;
}

bool QBarSeriesPrivate::setModel(QAbstractItemModel *model)
{
    // disconnect signals from old model
    if(m_model)
    {
        disconnect(m_model, 0, this, 0);
        m_mapCategories = -1;
        m_mapBarBottom = -1;
        m_mapBarTop = -1;
        m_mapFirst = 0;
        m_mapCount = 0;
        m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if(model)
    {
        m_model = model;
        return true;
    }
    else
    {
        m_model = 0;
        return false;
    }
}

void QBarSeriesPrivate::setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation)
{
    Q_Q(QBarSeries);

    if (!m_model)
        return;

    m_mapCategories = categories;
    m_mapBarBottom = bottomBoundry;
    m_mapBarTop = topBoundry;
//    m_mapFirst = 1;
    m_mapOrientation = orientation;

    // connect the signals
    if (m_mapOrientation == Qt::Vertical) {
        m_mapCount = m_model->rowCount() - m_mapFirst;
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(rowsInserted(QModelIndex, int, int)),
                this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    } else {
        m_mapCount = m_model->columnCount() - m_mapFirst;
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(columnsInserted(QModelIndex, int, int)),
                this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(columnsRemoved(QModelIndex, int, int)),
                this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }

    // create the initial bars
    delete m_internalModel;
    if (m_mapOrientation == Qt::Vertical) {
        QStringList categories;
        for (int k = m_mapFirst; k < m_mapFirst + m_mapCount; k++)
            categories << m_model->data(m_model->index(k, m_mapCategories), Qt::DisplayRole).toString();
        m_internalModel = new BarChartModel(categories, this);

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(QString("Column: %1").arg(i + 1));
            for(int m = m_mapFirst; m < m_mapFirst + m_mapCount; m++)
                *barSet << m_model->data(m_model->index(m, i), Qt::DisplayRole).toDouble();
            q->appendBarSet(barSet);
        }
    } else {
        QStringList categories;
        for (int k = m_mapFirst; k < m_mapFirst + m_mapCount; k++)
            categories << m_model->data(m_model->index(m_mapCategories, k), Qt::DisplayRole).toString();
        m_internalModel = new BarChartModel(categories, this);

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(QString("Row: %1").arg(i + 1));
            for(int m = m_mapFirst; m < m_mapFirst + m_mapCount; m++)
                *barSet << m_model->data(m_model->index(i, m), Qt::DisplayRole).toDouble();
            q->appendBarSet(barSet);
        }
    }
}

void QBarSeriesPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    Q_UNUSED(bottomRight)

    if (m_mapOrientation == Qt::Vertical)
    {
        // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
        if (topLeft.column() >= m_mapBarBottom && topLeft.column() <= m_mapBarTop && topLeft.row() >= m_mapFirst && topLeft.row() < m_mapFirst + m_mapCount)
            barsetAt(topLeft.column() - m_mapBarBottom)->setValue(topLeft.row() - m_mapFirst, m_model->data(topLeft, Qt::DisplayRole).toDouble());
    }
    else
    {
        // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
        if (topLeft.row() >= m_mapBarBottom && topLeft.row() <= m_mapBarTop && topLeft.column() >= m_mapFirst && topLeft.column() < m_mapFirst + m_mapCount)
            barsetAt(topLeft.row() - m_mapBarBottom)->setValue(topLeft.column() - m_mapFirst, m_model->data(topLeft, Qt::DisplayRole).toDouble());
    }
}

void QBarSeriesPrivate::modelDataAdded(QModelIndex /*parent*/, int start, int /*end*/)
{
    Q_Q(QBarSeries);

    if (m_mapOrientation == Qt::Vertical) {
        q->insertCategory(start - m_mapFirst, QString("Row: %1").arg(start + 1));
        for (int i = 0; i <= m_mapBarTop - m_mapBarBottom; i++) {
            barsetAt(i)->insertValue(start - m_mapFirst, m_model->data(m_model->index(start, i), Qt::DisplayRole).toDouble());
        }
    } else {
        q->insertCategory(start - m_mapFirst, QString("Column: %1").arg(start + 1));
        for (int i = 0; i <= m_mapBarTop - m_mapBarBottom; i++) {
            barsetAt(i)->insertValue(start - m_mapFirst, m_model->data(m_model->index(i, start), Qt::DisplayRole).toDouble());
        }
    }
    emit restructuredBars();
}

void QBarSeriesPrivate::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_Q(QBarSeries);
    Q_UNUSED(parent)
    Q_UNUSED(end)

    q->removeCategory(start - m_mapFirst);
    for (int i = 0; i <= m_mapBarTop - m_mapBarBottom; i++)
    {
        barsetAt(i)->removeValue(start - m_mapFirst);
    }
    emit restructuredBars();
}

void QBarSeriesPrivate::barsetChanged()
{
    emit updatedBars();
}

#include "moc_qbarseries.cpp"
#include "moc_qbarseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
