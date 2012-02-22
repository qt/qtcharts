#include "custombarset.h"

CustomBarSet::CustomBarSet(QObject *parent) :
    QBarSet(parent)
{
    // Using signal to signal connection here.
    connect(this,SIGNAL(clicked()),this,SIGNAL(toggleFloatingValues()));
}
