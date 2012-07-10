#ifndef QDONUTGROUP_P_H
#define QDONUTGROUP_P_H

#include <QObject>
#include <qdonutgroup.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieSeries;

class QDonutGroupPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QDonutGroupPrivate(QDonutGroup *q);

    void append(QPieSeries *donut);

private:
    QList<QPieSeries *> m_donuts;

private:
    QDonutGroup *q_ptr;
    Q_DECLARE_PUBLIC(QDonutGroup)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QDONUTGROUP_P_H
