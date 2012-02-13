#ifndef QBARCATEGORY_H
#define QBARCATEGORY_H

#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarCategory // : pubclic QObject // TODO: Need for this?
{
public:
    QBarCategory();

    QBarCategory& operator << (const QString &label);

    // Number of items in category
    int count();
    QList<QString>& items();

public:

    QList<QString> mList;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARCATEGORY_H
