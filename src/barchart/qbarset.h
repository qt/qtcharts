#ifndef QBARSET_H
#define QBARSET_H

#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarSet // : pubclic QObject // TODO: Need for this?
{
public:
    QBarSet();

    void setName(QString name);
//    void setValues(QList<qreal> &values);

    // TODO:
    QBarSet& operator << (const qreal &value);

    // TODO: Hide these from user of QBarSet. (but data model needs access to these)
public:

    QString mName;
    QList<qreal> mValues;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
