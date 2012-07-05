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

#include "chartdataset_p.h"
#include "qchart.h"
#include "qvaluesaxis.h"
#include "qbarcategoriesaxis.h"
#include "qvaluesaxis_p.h"
#include "qabstractseries_p.h"
#include "qabstractbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qpieseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDataSet::ChartDataSet(QChart *parent):QObject(parent),
    m_domainIndex(0)
{

}

ChartDataSet::~ChartDataSet()
{
    removeAllSeries();
}

void ChartDataSet::addSeries(QAbstractSeries* series)
{
    Domain* domain = m_seriesDomainMap.value(series);

    if(domain) {
        qWarning() << "Can not add series. Series already on the chart";
        return;
    }

    series->setParent(this); // take ownership

    domain = new Domain(series);

    m_seriesDomainMap.insert(series,domain);

    series->d_ptr->scaleDomain(*domain);

    QMapIterator<int, QAbstractSeries*> i(m_indexSeriesMap);

    int key=0;
    while (i.hasNext()) {
        i.next();
        if(i.key()!=key) {
            break;
        }
        key++;
    }

    m_indexSeriesMap.insert(key,series);

    series->d_ptr->m_chart = qobject_cast<QChart*>(parent());
    series->d_ptr->m_dataset = this;

    emit seriesAdded(series,domain);

}

void ChartDataSet::createDefaultAxes()
{

    if(m_seriesDomainMap.isEmpty()) return;

    QAbstractAxis::AxisTypes typeX(0);
    QAbstractAxis::AxisTypes typeY(0);

    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);
    while (i.hasNext()) {
               i.next();
               removeAxes(i.key());
    }

    i.toFront();

    while (i.hasNext()) {
            i.next();
            QAbstractAxis* axisX = m_seriesAxisXMap.value(i.key());
            QAbstractAxis* axisY = m_seriesAxisYMap.value(i.key());
            if(axisX) typeX&=axisX->type();
            else typeX|=i.key()->d_ptr->defaultAxisXType();
            if(axisY) typeY&=axisY->type();
            else typeY|=i.key()->d_ptr->defaultAxisYType();
    }


    if(typeX.testFlag(QAbstractAxis::AxisTypeValues) && typeX.testFlag(QAbstractAxis::AxisTypeCategories))
    {
        i.toFront();
        while (i.hasNext()) {
               i.next();
               QAbstractAxis* axis = createAxis(i.key()->d_ptr->defaultAxisXType());
               if(!axis) continue;
               i.key()->d_ptr->initializeAxisX(axis);
               addAxisX(axis,i.key());
               emit axisAdded(axis,i.value());
        }

    }else if(!typeY.testFlag(QAbstractAxis::AxisTypeNoAxis)){
        QAbstractAxis* axis = createAxis(QAbstractAxis::AxisType(int(typeX)));
        i.toFront();
              while (i.hasNext()) {
                     i.next();
                     i.key()->d_ptr->initializeAxisX(axis);
                     addAxisX(axis,i.key());
              }
        emit axisAdded(axis,i.value());

    }

    if(typeY.testFlag(QAbstractAxis::AxisTypeValues) && typeY.testFlag(QAbstractAxis::AxisTypeCategories))
    {
        i.toFront();
        while (i.hasNext()) {
               i.next();
               QAbstractAxis* axis = createAxis(i.key()->d_ptr->defaultAxisYType());
               i.key()->d_ptr->initializeAxisY(axis);
               addAxisY(axis,i.key());
               emit axisAdded(axis,i.value());
        }

    }else if(!typeY.testFlag(QAbstractAxis::AxisTypeNoAxis)){
        QAbstractAxis* axis = createAxis(QAbstractAxis::AxisType(int(typeY)));
        i.toFront();
              while (i.hasNext()) {
                     i.next();
                     i.key()->d_ptr->initializeAxisY(axis);
                     addAxisY(axis,i.key());
              }
              emit axisAdded(axis,i.value());

    }
}


QAbstractAxis* ChartDataSet::createAxis(QAbstractAxis::AxisType type)
{
    QAbstractAxis* axis =0;

    switch(type) {
        case QAbstractAxis::AxisTypeValues:
        axis = new QValuesAxis(this);
        break;
        case QAbstractAxis::AxisTypeCategories:
        axis = new QBarCategoriesAxis(this);
        break;
        default:
        axis = 0;
        break;
    }

    return axis;
}

void ChartDataSet::addAxisX(QAbstractAxis* axis,QAbstractSeries* series) {
    Domain* domain = m_seriesDomainMap.value(series);
    axis->d_ptr->m_orientation=Qt::Horizontal;
    //TODO:axis->d_ptr->initialize(domain);
    QObject::connect(axis->d_ptr.data(),SIGNAL(changed(qreal,qreal,int,bool)),domain,SLOT(handleAxisXChanged(qreal,qreal,int,bool)));
    QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal,int)),axis->d_ptr.data(),SLOT(handleAxisRangeChanged(qreal,qreal,int)));
    m_seriesAxisXMap.insert(series,axis);
}

void ChartDataSet::addAxisY(QAbstractAxis* axis,QAbstractSeries* series) {
    Domain* domain = m_seriesDomainMap.value(series);
    axis->d_ptr->m_orientation=Qt::Vertical;
    //TODO:axis->d_ptr->initialize(domain);
    QObject::connect(axis->d_ptr.data(),SIGNAL(changed(qreal,qreal,int,bool)),domain,SLOT(handleAxisYChanged(qreal,qreal,int,bool)));
    QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal,int)),axis->d_ptr.data(),SLOT(handleAxisRangeChanged(qreal,qreal,int)));
    m_seriesAxisYMap.insert(series,axis);
}

void ChartDataSet::removeSeries(QAbstractSeries* series)
{
    Domain* domain = m_seriesDomainMap.take(series);

    if(!domain) {
        qWarning()<<"Can not remove series. Series not found on the chart.";
    }

    emit seriesRemoved(series);

    delete domain;
    domain = 0;

    int key = seriesIndex(series);
    Q_ASSERT(key!=-1);

    m_indexSeriesMap.remove(key);

    series->setParent(0);
    series->d_ptr->m_chart = 0;
    series->d_ptr->m_dataset = 0;

    removeAxes(series);
}

void ChartDataSet::removeAxes(QAbstractSeries* series)
{
    QAbstractAxis* axisX = m_seriesAxisXMap.take(series);

    if(axisX) {
        QList<QAbstractAxis*> axesX = m_seriesAxisXMap.values();
        int x = axesX.indexOf(axisX);

        if(x==-1) {
            emit axisRemoved(axisX);
            axisX->deleteLater();
        }
    }

    QAbstractAxis* axisY = m_seriesAxisYMap.take(series);

    if(axisY) {
        QList<QAbstractAxis*> axesY = m_seriesAxisYMap.values();

        int y = axesY.indexOf(axisY);

        if(y==-1) {
            emit axisRemoved(axisY);
            axisY->deleteLater();
        }
    }
}

void ChartDataSet::removeAllSeries()
{
    QList<QAbstractSeries*> series =   m_seriesDomainMap.keys();
    foreach(QAbstractSeries *s , series) {
        removeSeries(s);
    }

    Q_ASSERT(m_seriesAxisXMap.count()==0);
    Q_ASSERT(m_seriesAxisXMap.count()==0);
    Q_ASSERT(m_seriesDomainMap.count()==0);

    qDeleteAll(series);
}

void ChartDataSet::zoomInDomain(const QRectF& rect, const QSizeF& size)
{
    //for performance reasons block, signals and scale "full" domain one by one. Gives twice less screen updates


    blockAxisSignals(true);

    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);

    while (i.hasNext()) {
        i.next();
        i.value()->zoomIn(rect,size);
    }

    blockAxisSignals(false);

}

void ChartDataSet::zoomOutDomain(const QRectF& rect, const QSizeF& size)
{
    //for performance reasons block, signals and scale "full" domain one by one. Gives twice less screen updates

    blockAxisSignals(true);

    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);

    while (i.hasNext()) {
        i.next();
        i.value()->zoomOut(rect,size);
    }

    blockAxisSignals(false);
}

void ChartDataSet::blockAxisSignals(bool enabled)
{
    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);
Q_UNUSED(enabled);
    while (i.hasNext()) {
           i.next();
           QAbstractAxis* axisX = m_seriesAxisXMap.value(i.key());
           QAbstractAxis* axisY = m_seriesAxisYMap.value(i.key());
           if(axisX) axisX->d_ptr->blockSignals(true);
           if(axisY) axisY->d_ptr->blockSignals(true);
       }
}

int ChartDataSet::seriesCount(QAbstractSeries::SeriesType type)
{
    int count=0;
    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);
    while (i.hasNext()) {
           i.next();
           if(i.key()->type()==type) count++;
    }
    return count;
}

int ChartDataSet::seriesIndex(QAbstractSeries *series)
{
    QMapIterator<int, QAbstractSeries*> i(m_indexSeriesMap);
    while (i.hasNext()) {
        i.next();
        if (i.value() == series)
            return i.key();
    }
    return -1;
}

QAbstractAxis* ChartDataSet::axisX(QAbstractSeries *series) const
{
    if(series == 0) {

           QMapIterator<QAbstractSeries*, QAbstractAxis *> i(m_seriesAxisXMap);

           while (i.hasNext()) {
                  i.next();
                  if(i.value()->isVisible()) return i.value();
           }
           return 0;
    }
    return m_seriesAxisXMap.value(series);
}

QAbstractAxis* ChartDataSet::axisY(QAbstractSeries *series) const
{
    if(series == 0) {
        QMapIterator<QAbstractSeries*, QAbstractAxis *> i(m_seriesAxisYMap);

        while (i.hasNext()) {
            i.next();
            if(i.value()->isVisible()) return i.value();
        }
        return 0;
    }
    return m_seriesAxisYMap.value(series);
}

void ChartDataSet::setAxisX(QAbstractSeries *series, QAbstractAxis *axis)
{
    Q_ASSERT(axis);
    Domain* domain = m_seriesDomainMap.value(series);

    if(!domain) {
        qWarning() << "Series not found on the chart.";
        return;
    }

    if(axis->d_ptr->m_orientation==Qt::Vertical) {
        qWarning()<<"Axis already defined as axis Y";
        return;
    }

    QAbstractAxis *oldAxis = m_seriesAxisXMap.take(series);
    QList<QAbstractAxis*> axesX = m_seriesAxisXMap.values();

    if(oldAxis) {

        int x = axesX.indexOf(oldAxis);
        if(x==-1) {
            emit axisRemoved(oldAxis);
            oldAxis->deleteLater();
        }
    }

    QObject::connect(axis->d_ptr.data(),SIGNAL(changed(qreal,qreal,int,bool)),domain,SLOT(handleAxisXChanged(qreal,qreal,int,bool)));
    QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal,int)),axis->d_ptr.data(),SLOT(handleAxisRangeChanged(qreal,qreal,int)));

    int x = axesX.indexOf(axis);
    if(x==-1) {
        axis->d_ptr->m_orientation=Qt::Horizontal;
        emit axisAdded(axis,domain);
    }

    m_seriesAxisXMap.insert(series,axis);
    axis->d_ptr->emitRange();
}

void ChartDataSet::setAxisY(QAbstractSeries *series, QAbstractAxis *axis)
{
    Q_ASSERT(axis);
    Domain* domain = m_seriesDomainMap.value(series);

    if(!domain) {
        qWarning() << "Series not found on the chart.";
        return;
    }

    if(axis->d_ptr->m_orientation==Qt::Horizontal) {
        qWarning()<<"Axis already defined as axis X";
        return;
    }

    QAbstractAxis *oldAxis = m_seriesAxisYMap.take(series);
    QList<QAbstractAxis*> axesY = m_seriesAxisYMap.values();

    if(oldAxis) {
        int y = axesY.indexOf(oldAxis);
        if(y==-1) {
            emit axisRemoved(oldAxis);
            oldAxis->deleteLater();
        }
    }

    QObject::connect(axis->d_ptr.data(),SIGNAL(changed(qreal,qreal,int,bool)),domain,SLOT(handleAxisYChanged(qreal,qreal,int,bool)));
    QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal,int)),axis->d_ptr.data(),SLOT(handleAxisRangeChanged(qreal,qreal,int)));

    int y = axesY.indexOf(axis);
    if(y==-1) {
        axis->d_ptr->m_orientation=Qt::Vertical;
        emit axisAdded(axis,domain);
    }

    m_seriesAxisYMap.insert(series,axis);
    axis->d_ptr->emitRange();
}

Domain* ChartDataSet::domain(QAbstractSeries *series) const
{
    return m_seriesDomainMap.value(series);
}

void ChartDataSet::scrollDomain(qreal dx,qreal dy,const QSizeF& size)
{
    blockAxisSignals(true);
    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->move(dx,dy,size);
    }
    blockAxisSignals(false);
}

QList<QAbstractSeries*> ChartDataSet::series() const
{
    return m_seriesDomainMap.keys();
}

void ChartDataSet::updateSeries(QAbstractSeries *series)
{
    emit seriesUpdated(series);
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
