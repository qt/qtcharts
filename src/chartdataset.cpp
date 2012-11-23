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
#include "chartpresenter_p.h"
#include "qchart.h"
#include "qchart_p.h"
#include "qvalueaxis.h"
#include "qbarcategoryaxis.h"
#include "qvalueaxis_p.h"
#include "qcategoryaxis.h"
#include "qabstractseries_p.h"
#include "qabstractbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qpieseries.h"
#include "chartitem_p.h"
#include "xydomain_p.h"
#include "xlogydomain_p.h"
#include "logxydomain_p.h"
#include "logxlogydomain_p.h"

#ifndef QT_ON_ARM
#include "qdatetimeaxis.h"
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDataSet::ChartDataSet(QChart *chart)
    : QObject(chart),
      m_chart(chart)
{

}

ChartDataSet::~ChartDataSet()
{
    removeAllSeries();
    removeAllAxes();
}

/*
 * This method adds series to chartdataset, series ownership is taken from caller.
 */
void ChartDataSet::addSeries(QAbstractSeries *series)
{
    if (m_seriesList.contains(series)) {
        qWarning() << QObject::tr("Can not add series. Series already on the chart.");
        return;
    }

    series->d_ptr->initializeDomain();
    m_seriesList.append(series);

    series->setParent(this); // take ownership
    series->d_ptr->m_chart = m_chart;

    emit seriesAdded(series);
}

/*
 * This method adds axis to chartdataset, axis ownership is taken from caller.
 */
void ChartDataSet::addAxis(QAbstractAxis *axis,Qt::Alignment aligment)
{
    if (m_axisList.contains(axis)) {
        qWarning() << QObject::tr("Can not add axis. Axis already on the chart.");
        return;
    }

    axis->d_ptr->setAlignment(aligment);

    if(!axis->alignment()) {
        qWarning()<< QObject::tr("No alignment specified !");
        return;
    };

    QSharedPointer<AbstractDomain> domain(new XYDomain());
    axis->d_ptr->initializeDomain(domain.data());

    axis->setParent(this);
    axis->d_ptr->m_chart = m_chart;
    m_axisList.append(axis);

    emit axisAdded(axis);
}

/*
 * This method removes series form chartdataset, series ownership is passed back to caller.
 */
void ChartDataSet::removeSeries(QAbstractSeries *series)
{

    if (! m_seriesList.contains(series)) {
        qWarning() << QObject::tr("Can not remove series. Series not found on the chart.");
        return;
    }

    emit seriesRemoved(series);
    m_seriesList.removeAll(series);

    series->setParent(0);
    series->d_ptr->m_chart = 0;
    series->d_ptr->m_domain.clear();

    QList<QAbstractAxis*> axes = series->d_ptr->m_axes;

    foreach(QAbstractAxis* axis, axes) {
        axis->d_ptr->m_series.removeAll(series);
        series->d_ptr->m_axes.removeAll(axis);
    }
}

/*
 * This method removes axis form chartdataset, series ownership is passed back to caller.
 */
void ChartDataSet::removeAxis(QAbstractAxis *axis)
{
    if (! m_axisList.contains(axis)) {
        qWarning() << QObject::tr("Can not remove axis. Axis not found on the chart.");
        return;
    }

    emit axisRemoved(axis);
    m_axisList.removeAll(axis);

    axis->setParent(0);
    axis->d_ptr->m_chart = 0;

    QList<QAbstractSeries*> series =  axis->d_ptr->m_series;

    foreach(QAbstractSeries* s, series) {
       s->d_ptr->m_axes.removeAll(axis);
       axis->d_ptr->m_series.removeAll(s);
    }
}

/*
 * This method attach axis to series, return true if success.
 */
bool ChartDataSet::attachAxis(QAbstractSeries* series,QAbstractAxis *axis)
{
    Q_ASSERT(series);
    Q_ASSERT(axis);

    QList<QAbstractSeries* > attachedSeriesList = axis->d_ptr->m_series;
    QList<QAbstractAxis* > attachedAxisList = series->d_ptr->m_axes;
    QSharedPointer<AbstractDomain> domain =  series->d_ptr->m_domain;

    if (!m_seriesList.contains(series)) {
        qWarning() << QObject::tr("Can not find series on the chart.");
        return false;
    }

    if (axis && !m_axisList.contains(axis)) {
        qWarning() << QObject::tr("Can not find axis on the chart.");
        return false;
    }

    if (attachedAxisList.contains(axis)) {
        qWarning() << QObject::tr("Axis already attached to series.");
        return false;
    }

    Q_ASSERT(!attachedSeriesList.contains(series));
    Q_ASSERT(!domain.isNull());

    if(attachedSeriesList.isEmpty()){

    }else{
        domain = attachedSeriesList.first()->d_ptr->domain();
        Q_ASSERT(!domain.isNull());
        series->d_ptr->setDomain(domain);
    }

    series->d_ptr->m_axes<<axis;
    axis->d_ptr->m_series<<series;

    series->d_ptr->initializeAxes();
    axis->d_ptr->initializeDomain(domain.data());

    if(axis->orientation()==Qt::Vertical){
        QObject::connect(axis->d_ptr.data(), SIGNAL(rangeChanged(qreal,qreal)), domain.data(), SLOT(handleVerticalAxisRangeChanged(qreal,qreal)));
        QObject::connect(domain.data(), SIGNAL(rangeVerticalChanged(qreal,qreal)), axis->d_ptr.data(), SLOT(handleRangeChanged(qreal,qreal)));
    }

    if(axis->orientation()==Qt::Horizontal){
        QObject::connect(axis->d_ptr.data(), SIGNAL(rangeChanged(qreal,qreal)), domain.data(), SLOT(handleHorizontalAxisRangeChanged(qreal,qreal)));
        QObject::connect(domain.data(), SIGNAL(rangeHorizontalChanged(qreal,qreal)), axis->d_ptr.data(), SLOT(handleRangeChanged(qreal,qreal)));
    }

    return true;
}

/*
 * This method detach axis to series, return true if success.
 */
bool ChartDataSet::detachAxis(QAbstractSeries* series,QAbstractAxis *axis)
{
    Q_ASSERT(series);
    Q_ASSERT(axis);

    QList<QAbstractSeries* > attachedSeriesList = axis->d_ptr->m_series;
    QList<QAbstractAxis* > attachedAxisList = series->d_ptr->m_axes;
    QSharedPointer<AbstractDomain> domain =  series->d_ptr->m_domain;

    if (!m_seriesList.contains(series)) {
        qWarning() << QObject::tr("Can not find series on the chart.");
        return false;
    }

    if (axis && !m_axisList.contains(axis)) {
        qWarning() << QObject::tr("Can not find axis on the chart.");
        return false;
    }

    if (!attachedAxisList.contains(axis)) {
        qWarning() << QObject::tr("Axis not attached to series.");
        return false;
    }

    Q_ASSERT(axis->d_ptr->m_series.contains(series));

    series->d_ptr->m_axes.removeAll(axis);
    axis->d_ptr->m_series.removeAll(series);

    if(axis->orientation()==Qt::Vertical){
        QObject::disconnect(axis->d_ptr.data(), SIGNAL(rangeChanged(qreal,qreal)), domain.data(), SLOT(handleVerticalAxisRangeChanged(qreal,qreal)));
        QObject::disconnect(domain.data(), SIGNAL(rangeVerticalChanged(qreal,qreal)), axis->d_ptr.data(), SLOT(handleRangeChanged(qreal,qreal)));
    }

    if(axis->orientation()==Qt::Horizontal){
        QObject::disconnect(axis->d_ptr.data(), SIGNAL(rangeChanged(qreal,qreal)), domain.data(), SLOT(handleHorizontalAxisRangeChanged(qreal,qreal)));
        QObject::disconnect(domain.data(), SIGNAL(rangeHorizontalChanged(qreal,qreal)), axis->d_ptr.data(), SLOT(handleRangeChanged(qreal,qreal)));
    }

    return true;
}

void ChartDataSet::createDefaultAxes()
{
    if (m_seriesList.isEmpty())
        return;

    QAbstractAxis::AxisTypes typeX(0);
    QAbstractAxis::AxisTypes typeY(0);

    // Remove possibly existing axes
    removeAllAxes();

    Q_ASSERT(m_axisList.isEmpty());

    // Select the required axis x and axis y types based on the types of the current series
    foreach(QAbstractSeries* s, m_seriesList) {
        typeX |= s->d_ptr->defaultAxisType(Qt::Horizontal);
        typeY |= s->d_ptr->defaultAxisType(Qt::Vertical);
    }

    // Create the axes of the types selected
    createAxes(typeX, Qt::Horizontal);
    createAxes(typeY, Qt::Vertical);

}

void ChartDataSet::createAxes(QAbstractAxis::AxisTypes type, Qt::Orientation orientation)
{
    QAbstractAxis *axis = 0;
    //decide what axis should be created

    switch (type) {
        case QAbstractAxis::AxisTypeValue:
        axis = new QValueAxis(this);
        break;
        case QAbstractAxis::AxisTypeBarCategory:
        axis = new QBarCategoryAxis(this);
        break;
        case QAbstractAxis::AxisTypeCategory:
        axis = new QCategoryAxis(this);
        break;
#ifndef Q_WS_QWS
        case QAbstractAxis::AxisTypeDateTime:
        axis = new QDateTimeAxis(this);
        break;
#endif
        default:
        axis = 0;
        break;
    }

    if (axis) {
        //create one axis for all

        addAxis(axis,orientation==Qt::Horizontal?Qt::AlignBottom:Qt::AlignLeft);

        foreach(QAbstractSeries *s, m_seriesList) {
            attachAxis(s,axis);
        }

    }
    else if (!type.testFlag(QAbstractAxis::AxisTypeNoAxis)) {
        //create separate axis
        foreach(QAbstractSeries *s, m_seriesList) {
            QAbstractAxis *axis = s->d_ptr->createDefaultAxis(orientation);
            if(axis) {
                addAxis(axis,orientation==Qt::Horizontal?Qt::AlignBottom:Qt::AlignLeft);
                attachAxis(s,axis);
            }
        }
    }
}

void ChartDataSet::removeAllSeries()
{
    foreach (QAbstractSeries *s , m_seriesList)
        removeSeries(s);

    Q_ASSERT(m_seriesList.count() == 0);
    qDeleteAll(m_seriesList);
}

void ChartDataSet::removeAllAxes()
{
    foreach (QAbstractAxis *a , m_axisList)
        removeAxis(a);

    Q_ASSERT(m_axisList.count() == 0);
    qDeleteAll(m_axisList);
}

void ChartDataSet::zoomInDomain(const QRectF &rect)
{
    QList<AbstractDomain*> domains;
    foreach(QAbstractSeries *s, m_seriesList) {
        AbstractDomain* domain = s->d_ptr->m_domain.data();
        if(domains.contains(domain)) continue;
        s->d_ptr->m_domain->blockAxisSignals(true);
        domains<<domain;
    }

    foreach(AbstractDomain *domain, domains)
        domain->zoomIn(rect);

    foreach(AbstractDomain *domain, domains)
        domain->blockAxisSignals(false);
}

void ChartDataSet::zoomOutDomain(const QRectF &rect)
{
    QList<AbstractDomain*> domains;
    foreach(QAbstractSeries *s, m_seriesList) {
        AbstractDomain* domain = s->d_ptr->m_domain.data();
        if(domains.contains(domain)) continue;
        s->d_ptr->m_domain->blockAxisSignals(true);
        domains<<domain;
    }

    foreach(AbstractDomain *domain, domains)
        domain->zoomOut(rect);

    foreach(AbstractDomain *domain, domains)
        domain->blockAxisSignals(false);
}

void ChartDataSet::scrollDomain(qreal dx, qreal dy)
{
    QList<AbstractDomain*> domains;
    foreach(QAbstractSeries *s, m_seriesList) {
        AbstractDomain* domain = s->d_ptr->m_domain.data();
        if(domains.contains(domain)) continue;
        s->d_ptr->m_domain->blockAxisSignals(true);
        domains<<domain;
    }

    foreach(AbstractDomain *domain, domains)
        domain->move(dx, dy);

    foreach(AbstractDomain *domain, domains)
        domain->blockAxisSignals(false);
}

QList<QAbstractAxis*> ChartDataSet::axes() const
{
   return m_axisList;
}

QList<QAbstractSeries *> ChartDataSet::series() const
{
    return m_seriesList;
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
