#include "custombarset.h"

CustomBarSet::CustomBarSet(QString name, QObject *parent) :
    QBarSet(name, parent)
{
    // Using signal to signal connection here.
    connect(this,SIGNAL(clicked()),this,SIGNAL(toggleFloatingValues()));
}
