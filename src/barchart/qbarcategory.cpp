#include "qbarcategory.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarCategory
    \brief part of QtCommercial chart API.

    QBarCategory is a container for labels of various bar charts. Before the
    bar chart can be constructed, the categories must be defined. This is done by
    creating a QBarCategory class and appending the labels of categories to it.
    The QBarCategory is then given to bar chart series class.

    \mainclass

    Example on how to create a category:
    \snippet ../example/barchart/main.cpp 1

    \sa QBarSeries, QStackedBarSeries, QPercentBarSeries
*/

/*!
    Constructs the category container
*/
QBarCategory::QBarCategory()
{
}

/*!
    Appends the \a label in the category.
*/
QBarCategory& QBarCategory::operator << (const QString &label)
{
    mList.append(label);
    return *this;
}

/*!
    Retrurns number of labels in category
*/
int QBarCategory::count()
{
    return mList.count();
}

/*!
    Retruns the label of category defined by index \a category
*/
QString QBarCategory::label(int category)
{
    return mList.at(category);
}

// TODO?:
//#include "moc_qbarcategory.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
