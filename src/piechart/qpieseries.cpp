#include "qpieseries.h"
#include "qpieslice.h"
#include "piepresenter.h"
#include "pieslice.h"
#include <QFontMetrics>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

void QPieSeries::ChangeSet::appendAdded(QPieSlice* slice)
{
    if (!m_added.contains(slice))
        m_added << slice;
}

void QPieSeries::ChangeSet::appendAdded(QList<QPieSlice*> slices)
{
    foreach (QPieSlice* s, slices)
        appendAdded(s);
}

void QPieSeries::ChangeSet::appendChanged(QPieSlice* slice)
{
    if (!m_changed.contains(slice))
        m_changed << slice;
}

void QPieSeries::ChangeSet::appendRemoved(QPieSlice* slice)
{
    if (!m_removed.contains(slice))
        m_removed << slice;
}

QList<QPieSlice*> QPieSeries::ChangeSet::added() const
{
    return m_added;
}

QList<QPieSlice*> QPieSeries::ChangeSet::changed() const
{
    return m_changed;
}

QList<QPieSlice*> QPieSeries::ChangeSet::removed() const
{
    return m_removed;
}

bool QPieSeries::ChangeSet::isEmpty() const
{
    if (m_added.count() || m_changed.count() || m_removed.count())
        return false;
    return true;
}


QPieSeries::QPieSeries(QObject *parent) :
    QChartSeries(parent),
    m_sizeFactor(1.0),
    m_position(PiePositionMaximized),
    m_pieStartAngle(0),
    m_pieSpan(360)
{

}

QPieSeries::~QPieSeries()
{

}

bool QPieSeries::setData(QList<qreal> data)
{
    // TODO: remove this function
    QList<QPieSlice*> slices;
    foreach (qreal value, data)
        slices << new QPieSlice(value, QString::number(value));
    set(slices);
    return true;
}

void QPieSeries::set(QList<QPieSlice*> slices)
{
    clear();
    add(slices);
}

void QPieSeries::add(QList<QPieSlice*> slices)
{
    ChangeSet changeSet;
    foreach (QPieSlice* s, slices) {
        s->setParent(this);
        m_slices << s;
        changeSet.appendAdded(s);
    }

    updateDerivativeData();

    foreach (QPieSlice* s, slices) {
        connect(s, SIGNAL(changed()), this, SLOT(sliceChanged()));
        connect(s, SIGNAL(clicked()), this, SLOT(sliceClicked()));
        connect(s, SIGNAL(hoverEnter()), this, SLOT(sliceHoverEnter()));
        connect(s, SIGNAL(hoverLeave()), this, SLOT(sliceHoverLeave()));
    }

    emit changed(changeSet);
}

void QPieSeries::add(QPieSlice* slice)
{
    add(QList<QPieSlice*>() << slice);
}

QPieSlice* QPieSeries::add(qreal value, QString name)
{
    QPieSlice* slice = new QPieSlice(value, name);
    add(slice);
    return slice;
}

void QPieSeries::remove(QPieSlice* slice)
{
    if (!m_slices.removeOne(slice)) {
        Q_ASSERT(0); // TODO: how should this be reported?
        return;
    }

    ChangeSet changeSet;
    changeSet.appendRemoved(slice);
    emit changed(changeSet);

    delete slice;
    slice = NULL;

    updateDerivativeData();
}

void QPieSeries::clear()
{
    if (m_slices.count() == 0)
        return;

    ChangeSet changeSet;
    foreach (QPieSlice* s, m_slices) {
        changeSet.appendRemoved(s);
        m_slices.removeOne(s);
        delete s;
    }
    emit changed(changeSet);
    updateDerivativeData();
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

void QPieSeries::setSpan(qreal startAngle, qreal span)
{
    if (startAngle >= 0 && startAngle < 360 &&
        span > 0 && span <= 360) {
        m_pieStartAngle = startAngle;
        m_pieSpan = span;
        updateDerivativeData();
    }
}

void QPieSeries::setLabelsVisible(bool visible)
{
    foreach (QPieSlice* s, m_slices)
        s->setLabelVisible(visible);
}

void QPieSeries::enableClickExplodes(bool enable)
{
    if (enable)
        connect(this, SIGNAL(clicked(QPieSlice*)), this, SLOT(toggleExploded(QPieSlice*)));
    else
        disconnect(this, SLOT(toggleExploded(QPieSlice*)));
}

void QPieSeries::enableHoverHighlight(bool enable)
{
    if (enable) {
        connect(this, SIGNAL(hoverEnter(QPieSlice*)), this, SLOT(highlightOn(QPieSlice*)));
        connect(this, SIGNAL(hoverLeave(QPieSlice*)), this, SLOT(highlightOff(QPieSlice*)));
    } else {
        disconnect(this, SLOT(hoverEnter(QPieSlice*)));
        disconnect(this, SLOT(hoverLeave(QPieSlice*)));
    }
}

void QPieSeries::sliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));

    ChangeSet changeSet;
    changeSet.appendChanged(slice);
    emit changed(changeSet);

    updateDerivativeData();
}

void QPieSeries::sliceClicked()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    emit clicked(slice);
}

void QPieSeries::sliceHoverEnter()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    emit hoverEnter(slice);
}

void QPieSeries::sliceHoverLeave()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    emit hoverLeave(slice);
}

void QPieSeries::toggleExploded(QPieSlice* slice)
{
    Q_ASSERT(slice);
    slice->setExploded(!slice->isExploded());
}

void QPieSeries::highlightOn(QPieSlice* slice)
{
    Q_ASSERT(slice);
    QColor c = slice->brush().color().lighter();
    slice->setBrush(c);
}

void QPieSeries::highlightOff(QPieSlice* slice)
{
    Q_ASSERT(slice);
    QColor c = slice->brush().color().darker(150);
    slice->setBrush(c);
}

void QPieSeries::updateDerivativeData()
{
    m_total = 0;

    // nothing to do?
    if (m_slices.count() == 0)
        return;

    // calculate total
    foreach (QPieSlice* s, m_slices)
        m_total += s->value();

    // we must have some values
    Q_ASSERT(m_total > 0); // TODO: is this the correct way to handle this?

    // update slice attributes
    qreal sliceAngle = m_pieStartAngle;
    foreach (QPieSlice* s, m_slices) {

        bool changed = false;

        qreal percentage = s->value() / m_total;
        if (s->m_percentage != percentage) {
            s->m_percentage = percentage;
            changed = true;
        }

        qreal sliceSpan = m_pieSpan * percentage;
        if (s->m_angleSpan != sliceSpan) {
            s->m_angleSpan = sliceSpan;
            changed = true;
        }

        if (s->m_angle != sliceAngle) {
            s->m_angle = sliceAngle;
            changed = true;
        }
        sliceAngle += sliceSpan;

        if (changed)
            emit s->changed();
    }
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
