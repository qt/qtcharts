#include "qdonutgroup.h"
#include "qdonutgroup_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QDonutGroup::QDonutGroup(QObject *parent) :
    QObject(parent),
    d_ptr(new QDonutGroupPrivate(this))
{
}

void QDonutGroup::append(QPieSeries *donut)
{
    insert(count(), donut);
}

bool QDonutGroup::insert(int index, QPieSeries* donut)
{
    if (donut == 0)
        return false;

    donut->setDonut();
    Q_D(QDonutGroup);
    d->m_donuts.insert(index, donut);
    qreal donutFraction = 1.0 / (d->m_donuts.count() + 1);
    for(int i = 0; i < d->m_donuts.count(); i++) {
        d->m_donuts[i]->setPieSize( (i + 2) * donutFraction);
        d->m_donuts[i]->setDonutInnerSize( (i + 1)  * donutFraction);
    }
    return true;
}

bool QDonutGroup::remove(QPieSeries* donut)
{
    Q_D(QDonutGroup);
    int index = d->m_donuts.indexOf(donut);
    if (index == -1)
        return false;
    else
        d->m_donuts.removeOne(donut);

    return true;
}

void QDonutGroup::clear()
{
    Q_D(QDonutGroup);
    d->m_donuts.clear();
}

QList<QPieSeries*> QDonutGroup::donuts() const
{
    Q_D(const QDonutGroup);
    return d->m_donuts;
}

int QDonutGroup::count() const
{
    Q_D(const QDonutGroup);
    return d->m_donuts.count();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QDonutGroupPrivate::QDonutGroupPrivate(QDonutGroup *q):
    QObject(q),
    q_ptr(q)
{
    //
}

#include "moc_qdonutgroup.cpp"
#include "moc_qdonutgroup_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
