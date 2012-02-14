#include "qpieseries.h"
#include "piepresenter.h"
#include "pieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieSeries::QPieSeries(QObject *parent) :
    QChartSeries(parent),
    m_sizeFactor(1.0),
    m_position(PiePositionMaximized),
    m_sliceIdSeed(0)
{
}

QPieSeries::~QPieSeries()
{

}

bool QPieSeries::setData(QList<qreal> data)
{
    // TODO: remove this function
    QList<QPieSlice> slices;
    foreach (int value, data)
        slices << QPieSlice(value, QString::number(value));
    return set(slices);
}

bool QPieSeries::set(const QList<QPieSlice>& slices)
{
    if (!slices.count())
        return false;

    ChangeSet changeSet;

    foreach (QPieSlice s, m_slices.values())
        changeSet.m_removed << s.id();

    m_slices.clear();

    foreach (QPieSlice s, slices) {
        s.m_id = generateSliceId();
        m_slices.insert(s.id(), s);
        changeSet.m_added << s.id();
    }

    updateDerivativeData();
    emit changed(changeSet);

    return true;
}

bool QPieSeries::add(const QList<QPieSlice>& slices)
{
    if (!slices.count())
        return false;

    ChangeSet changeSet;
    foreach (QPieSlice s, slices) {
        s.m_id = generateSliceId();
        m_slices.insert(s.id(), s);
        changeSet.m_added << s.id();
    }

    updateDerivativeData();
    emit changed(changeSet);

    return true;
}

bool QPieSeries::add(const QPieSlice& slice)
{
    return add(QList<QPieSlice>() << slice);
}

bool QPieSeries::update(const QPieSlice& slice)
{
    if (!m_slices.contains(slice.id()))
        return false; // series does not contain this slice

    m_slices[slice.id()] = slice;

    ChangeSet changeSet;
    changeSet.m_changed << slice.id();
    updateDerivativeData();
    emit changed(changeSet);

    return true;
}

bool QPieSeries::remove(QPieSliceId id)
{
    if (!m_slices.contains(id))
        return false; // series does not contain this slice

    m_slices.remove(id);

    ChangeSet changeSet;
    changeSet.m_removed << id;
    updateDerivativeData();
    emit changed(changeSet);

    return true;
}

QPieSlice QPieSeries::slice(QPieSliceId id) const
{
    return m_slices.value(id);
}

void QPieSeries::setSizeFactor(qreal factor)
{
    if (factor < 0.0)
        return;

    if (m_sizeFactor != factor) {
        m_sizeFactor = factor;
        emit sizeFactorChanged();
    }
}

void QPieSeries::setPosition(PiePosition position)
{
    if (m_position != position) {
        m_position = position;
        emit positionChanged();
    }
}

QPieSliceId QPieSeries::generateSliceId()
{
    // Id is quint64 so it should be enough for us.
    // Note that id is not unique between pie series.
    return m_sliceIdSeed++;
}

void QPieSeries::updateDerivativeData()
{
    m_total = 0;
    foreach (const QPieSlice& s, m_slices.values())
        m_total += s.value();

    Q_ASSERT(m_total > 0); // TODO: remove this before release

    foreach (QPieSliceId id, m_slices.keys())
        m_slices[id].m_percentage = m_slices.value(id).value() / m_total;
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
