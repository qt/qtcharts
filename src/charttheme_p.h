#ifndef CHARTTHEME_H
#define CHARTTHEME_H

#include "qchartglobal.h"
#include <QObject>
#include <QSharedData>
#include <QColor>
#include <QLinearGradient>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartTheme;

class ChartThemeObserver
{
public:
    virtual void themeChanged(ChartTheme *theme) = 0;
};

/*!
 * The theme specific settings for the appearance of a series. TODO: These can be overridden by setting
 * custom settings to a QChartSeries object.
 */
struct SeriesTheme {
public:
    SeriesTheme() :
        linePen(QPen()),
        markerPen(QPen()) {}
    SeriesTheme(QColor lineColor, qreal lineWidth/*, QPen marker*/) :
        linePen(QPen(QBrush(lineColor), lineWidth)),
        markerPen(linePen) {}

//const QBrush & brush, qreal width, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJo
    // TODO:
    //QColor lineColor;
    QPen linePen;
    //QBrush lineBrush;
    QPen markerPen;
    //QBrush markerBrush;
};

/*!
 * Explicitly shared data class for the themes.
 */
class ChartThemeData : public QSharedData
{
public:
    ChartThemeData() : m_currentTheme(0) {}
    ~ChartThemeData() {}

public:
    void setTheme(int theme);

public:
    int m_currentTheme;
    QList<ChartThemeObserver *> m_observers;
    QColor m_gradientStartColor;
    QColor m_gradientEndColor;
    QList<SeriesTheme> m_seriesThemes;
    int m_seriesIndex;
};

class ChartTheme : public QObject
{
    Q_OBJECT
public:
    explicit ChartTheme(QObject *parent = 0);
    explicit ChartTheme(const ChartTheme &other, QObject *parent = 0) : QObject(parent), d(other.d) {}
    void operator =(const ChartTheme &other) { d = other.d; }

    void setTheme(int theme);
    SeriesTheme themeForSeries();
    void addObserver(ChartThemeObserver *o) { d->m_observers << o; }

public:
    // All the graphical elements of a QChart share the same theme settings
    // so let's use explicitly shared data
    QExplicitlySharedDataPointer<ChartThemeData> d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTHEME_H
