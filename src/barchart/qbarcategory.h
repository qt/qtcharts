#ifndef QBARCATEGORY_H
#define QBARCATEGORY_H

#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarCategory // TODO? : pubclic QObject
{
public:
    QBarCategory();

    QBarCategory& operator << (const QString &label);

    // Number of items in category
    int count();
    QString label(int category);

public:

    QList<QString> mList;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARCATEGORY_H
