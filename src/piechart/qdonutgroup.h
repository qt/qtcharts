#ifndef QDONUTGROUP_H
#define QDONUTGROUP_H

#include <QObject>
#include <QPieSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

//class QPieSeries;
class QDonutGroupPrivate;

class QTCOMMERCIALCHART_EXPORT QDonutGroup : public QObject
{
    Q_OBJECT
public:
    explicit QDonutGroup(QObject *parent = 0);

    void append(QPieSeries *donut);

protected:
    QDonutGroupPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QDonutGroup)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QDONUTGROUP_H
