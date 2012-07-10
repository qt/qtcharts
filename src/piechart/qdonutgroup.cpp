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
    if (donut == 0)
        return;

    donut->setDonut();
    Q_D(QDonutGroup);
    d->m_donuts.append(donut);
    qreal donutFraction = 1.0 / (d->m_donuts.count() + 1);
    for(int i = 0; i < d->m_donuts.count(); i++) {
        d->m_donuts[i]->setPieSize( (i + 2) * donutFraction);
        d->m_donuts[i]->setDonutInnerSize( (i + 1)  * donutFraction);
    }
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
