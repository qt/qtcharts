#include "customslice.h"

CustomSlice::CustomSlice(qreal value, QObject* parent)
    :QPieSlice(parent)
{
    setValue(value);
    setLabelVisible(true);
    setExploded(true);
    connect(this, SIGNAL(changed()), this, SLOT(updateLabel()));
    connect(this, SIGNAL(hoverEnter()), this, SLOT(toggleExploded()));
    connect(this, SIGNAL(hoverLeave()), this, SLOT(toggleExploded()));
}

void CustomSlice::updateLabel()
{
    setLabel(QString::number(this->percentage()*100) + "%");
}

void CustomSlice::toggleExploded()
{
    setExploded(!isExploded());
}
