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
    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);

    while (i.hasNext()) {
        i.next();

        if(!m_seriesAxisXMap.value(i.key()))
        {

            QAbstractAxis* axisX = i.key()->d_ptr->createAxisX(this);

            if(axisX) {
                QObject::connect(axisX->d_ptr.data(),SIGNAL(changed(qreal,qreal,int,bool)),i.value(),SLOT(handleAxisXChanged(qreal,qreal,int,bool)));
                QObject::connect(i.value(),SIGNAL(rangeXChanged(qreal,qreal,int)),axisX->d_ptr.data(),SLOT(handleAxisRangeChanged(qreal,qreal,int)));
                axisX->d_ptr->m_orientation=Qt::Horizontal;
                emit axisAdded(axisX,i.value());
                m_seriesAxisXMap.insert(i.key(),axisX);
            }

        }

        if(!m_seriesAxisYMap.value(i.key()))
        {
            QAbstractAxis* axisY = i.key()->d_ptr->createAxisY(this);

            if(axisY) {
                QObject::connect(axisY->d_ptr.data(),SIGNAL(changed(qreal,qreal,int,bool)),i.value(),SLOT(handleAxisYChanged(qreal,qreal,int,bool)));
                QObject::connect(i.value(),SIGNAL(rangeYChanged(qreal,qreal,int)),axisY->d_ptr.data(),SLOT(handleAxisRangeChanged(qreal,qreal,int)));
                axisY->d_ptr->m_orientation=Qt::Vertical;
                emit axisAdded(axisY,i.value());
                m_seriesAxisYMap.insert(i.key(),axisY);
            }
        }
    }
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
    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->zoomIn(rect,size);
    }
}

void ChartDataSet::zoomOutDomain(const QRectF& rect, const QSizeF& size)
{
    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->zoomOut(rect,size);
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
    if(series == 0) return m_seriesAxisXMap.begin().value();
    return m_seriesAxisXMap.value(series);
}

QAbstractAxis* ChartDataSet::axisY(QAbstractSeries *series) const
{
    if(series == 0) return m_seriesAxisYMap.begin().value();
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

    // Force range update
    axis->d_ptr->updateRange();
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
}

Domain* ChartDataSet::domain(QAbstractSeries *series) const
{
    return m_seriesDomainMap.value(series);
}

void ChartDataSet::scrollDomain(qreal dx,qreal dy,const QSizeF& size)
{
    QMapIterator<QAbstractSeries*, Domain*> i(m_seriesDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->move(dx,dy,size);
    }
}

QList<QAbstractSeries*> ChartDataSet::series() const
{
    return m_seriesAxisXMap.keys();
}

void ChartDataSet::updateSeries(QAbstractSeries *series)
{
    emit seriesUpdated(series);
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
