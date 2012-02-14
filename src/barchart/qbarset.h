#ifndef QBARSET_H
#define QBARSET_H

#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarSet // : pubclic QObject // TODO: Need for this?
{
public:
    QBarSet();

    void setName(QString name);
    QString name();
    QBarSet& operator << (const qreal &value);

    //TODO: What is the way to set a single value to n:th item? Is there need for such functionality?

    int count();
    qreal valueAt(int index);

private:

    QString mName;
    QList<qreal> mValues;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
