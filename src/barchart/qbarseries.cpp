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

#include <QDebug>
#include "qbarseries.h"
#include "qbarset.h"
#include "barchartmodel_p.h"

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
QBarSeries::QBarSeries(QBarCategories categories, QObject *parent) : QSeries(parent),
    m_internalModel(new BarChartModel(categories, this))
{
    m_model = 0;
    m_mapCategories = -1;
    m_mapBarBottom = -1;
    m_mapBarTop = -1;
    m_mapFirst = 0;
    m_mapCount = 0;
    m_mapOrientation = Qt::Vertical;
}

/*!
    Adds a set of bars to series. Takes ownership of \a set.
    Connects the clicked(QString, Qt::MouseButtons) signal
    of \a set to this series
*/
void QBarSeries::appendBarSet(QBarSet *set)
{
    m_internalModel->appendBarSet(set);
    connect(set, SIGNAL(clicked(QString,Qt::MouseButtons)), this, SLOT(barsetClicked(QString,Qt::MouseButtons)));
    connect(set, SIGNAL(valueChanged()), this, SLOT(barsetChanged()));
    emit updatedBars();
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesnt delete \a set.
    Disconnects the clicked(QString, Qt::MouseButtons) signal
    of \a set from this series
*/
void QBarSeries::removeBarSet(QBarSet *set)
{
    disconnect(set, SIGNAL(clicked(QString,Qt::MouseButtons)), this, SLOT(barsetClicked(QString,Qt::MouseButtons)));
    m_internalModel->removeBarSet(set);
    emit updatedBars();
}

void QBarSeries::insertBarSet(int i, QBarSet *set)
{
    m_internalModel->insertBarSet(i, set);
    //    emit barsetChanged();
}

void QBarSeries::insertCategory(int i, QString category)
{
    m_internalModel->insertCategory(i, category);
}

void QBarSeries::removeCategory(int i)
{
    m_internalModel->removeCategory(i);
}

/*!
    Returns number of sets in series.
*/
int QBarSeries::barsetCount() const
{
    //    if(m_model)
    //        return m_mapBarTop - m_mapBarBottom;
    //    else
    return m_internalModel->barsetCount();
}

/*!
    Returns number of categories in series
*/
int QBarSeries::categoryCount() const
{
    return m_internalModel->categoryCount();
}

/*!
    Returns a list of sets in series. Keeps ownership of sets.
 */
QList<QBarSet*> QBarSeries::barSets() const
{
    return m_internalModel->barSets();
}

/*!
    \internal \a index
*/
QBarSet* QBarSeries::barsetAt(int index)
{
    return m_internalModel->barsetAt(index);
}

/*!
    \internal \a category
*/
QString QBarSeries::categoryName(int category)
{
    return m_internalModel->categoryName(category);
}

/*!
    Enables or disables tooltip depending on parameter \a enabled.
    Tooltip shows the name of set, when mouse is hovering on top of bar.
    Calling without parameter \a enabled, enables the tooltip
*/
void QBarSeries::setToolTipEnabled(bool enabled)
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


/*!
    \internal \a category
*/
void QBarSeries::barsetClicked(QString category, Qt::MouseButtons button)
{
    emit clicked(qobject_cast<QBarSet*>(sender()), category, button);
}

/*!
    \internal
*/
qreal QBarSeries::min()
{
    return m_internalModel->min();
}

/*!
    \internal
*/
qreal QBarSeries::max()
{
    return m_internalModel->max();
}

/*!
    \internal \a set \a category
*/
qreal QBarSeries::valueAt(int set, int category)
{
    return m_internalModel->valueAt(set, category);
}

/*!
    \internal \a set \a category
*/
qreal QBarSeries::percentageAt(int set, int category)
{
    return m_internalModel->percentageAt(set, category);
}

/*!
    \internal \a category
*/
qreal QBarSeries::categorySum(int category)
{
    return m_internalModel->categorySum(category);
}

/*!
    \internal
*/
qreal QBarSeries::maxCategorySum()
{
    return m_internalModel->maxCategorySum();
}

/*!
    \internal
*/
BarChartModel& QBarSeries::model()
{
    return *m_internalModel;
}

bool QBarSeries::setModel(QAbstractItemModel *model)
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

// TODO
void QBarSeries::setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation)
{
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
}

void QBarSeries::setModelMappingShift(int first, int count)
{
    m_mapFirst = first;
    m_mapCount = count;
}

void QBarSeries::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
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

void QBarSeries::modelDataAdded(QModelIndex /*parent*/, int start, int /*end*/)
{
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
    emit restructuredBar(1);
}

void QBarSeries::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    Q_UNUSED(end)

    removeCategory(start - m_mapFirst);
    for (int i = 0; i <= m_mapBarTop - m_mapBarBottom; i++)
    {
        barsetAt(i)->removeValue(start - m_mapFirst);
    }
    emit restructuredBar(1);
}

void QBarSeries::barsetChanged()
{
    emit updatedBars();
}

QBarCategories QBarSeries::categories() const
{
    QBarCategories categories;
    int count = m_internalModel->categoryCount();
    for (int i=1; i <= count; i++) {
          categories.insert(i, m_internalModel->categoryName(i - 1));
    }
    return categories;
}

void QBarSeries::setLabelsVisible(bool visible)
{
    foreach (QBarSet* s, barSets()) {
        s->setLabelsVisible(visible);
    }
}


#include "moc_qbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
