#include "qpieseries.h"
#include "piepresenter.h"
#include "pieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieSeries::QPieSeries(QObject *parent) :
    QChartSeries(parent),
    m_piePresenter(0),
    m_sizeFactor(1.0),
    m_position(PiePositionMaximized)
{
}

QPieSeries::~QPieSeries()
{

}

void QPieSeries::set(QList<QPieSlice> slices)
{
    m_slices = slices;
    if (m_piePresenter) {
        m_piePresenter->seriesChanged();
        m_piePresenter->update();
    }
}

void QPieSeries::add(QList<QPieSlice> slices)
{
    m_slices += slices;
    if (m_piePresenter) {
        m_piePresenter->seriesChanged();
        // TODO: m_piePresenter->seriesAppended()??
        m_piePresenter->update();
    }
}

void QPieSeries::add(QPieSlice slice)
{
    add(QList<QPieSlice>() << slice);
}

QPieSlice QPieSeries::slice(int index) const
{
    if ((index >= 0) && (index < m_slices.count()))
        return m_slices.at(index);
    return QPieSlice();
}

bool QPieSeries::update(int index, QPieSlice slice)
{
    if ((index >= 0) && (index < m_slices.count())) {
        m_slices[index] = slice;
        if (m_piePresenter) {
            m_piePresenter->seriesChanged();
            // TODO: for a nice animation we need something like
            // m_piePresenter->sliceChanged(index, oldslice, newslice)
            m_piePresenter->update();
        }
        return true;
    }
    return false;
}

void QPieSeries::setSizeFactor(qreal factor)
{
    if (factor > 0.0)
        m_sizeFactor = factor;

    if (m_piePresenter) {
        m_piePresenter->resize();
        m_piePresenter->update();
        // TODO: do we have to update the parent item also?
        //  - potential issue: what if this function is called from the parent context?
    }
}

void QPieSeries::setPosition(PiePosition position)
{
    m_position = position;
    if (m_piePresenter) {
        m_piePresenter->resize();
        m_piePresenter->update();
        // TODO: do we have to update the parent item also?
        //  - potential issue: what if this function is called from the parent context?
    }
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
