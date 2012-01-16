#include "qbarchart.h"
#include "qbarchartbar.h"
#include <QDebug>

QBarChart::QBarChart(QGraphicsItem *parent) :
    QGraphicsItem(parent)
    ,mBarDefaultWidth( 1 )
{
}

void QBarChart::addSeries(QList<int> data)
{
    mData.clear();
    mData.append(data);
    dataChanged();
}

void QBarChart::setSize( int h, int w )
{
    mHeight = h;
    mWidth = w;
    dataChanged();  // TODO: separate data from grid
}

void QBarChart::setBarWidth( int w )
{
    mBarDefaultWidth = w;
}

void QBarChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "QBarChart::paint";
}

QRectF QBarChart::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight); // TODO: size from layout
}


void QBarChart::dataChanged()
{
    int count = mData.count();

    if (count <= 0) {
        // No items
        return;
    }

    mMax = mData.at(0);
    mMin = mData.at(0);

    // Find out min and max values.
    for (int i=0; i<count; i++) {
        if (mData.at(i) > mMax) {
            mMax = mData.at(i);
        } else if (mData.at(i) < mMin) {
            mMin = mData.at(i);
        }
    }

    // Create items for data, delete old ones
    foreach (QGraphicsItem* i, childItems()) {
        delete i;
    }

    gridChanged();

    int posStep = (mWidth / count) / 2;     // TODO: Why I need magical 2 here to get correct step?

    for (int i=0; i<count; i++) {
        QBarChartBar *bar = new QBarChartBar(this);

        // Scaling. TODO: better one.
        int barHeight = mData.at(i) * mHeight / mMax;
        bar->setSize(barHeight, mBarDefaultWidth * 3 * i);        // TODO: widht settable by style or something.
        bar->setColor(QColor(255 - i*25, i*10, i*15));
        bar->setPos(i*posStep, 0);
        childItems().append(bar);
    }
}

void QBarChart::gridChanged()
{
    // Scale of grid has changed
    QBarChartGrid *grid =  new QBarChartGrid(this);
    grid->setSize(mHeight, mWidth);
    grid->setLimits(mMin,mMax);
    grid->setHorizontalLineCount(5);
    childItems().append(grid);
}

