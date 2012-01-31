#ifndef CHARTTHEME_H
#define CHARTTHEME_H

#include "qchartglobal.h"
#include <QObject>
#include <QSharedData>
#include <QColor>
#include <QLinearGradient>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 * The theme specific settings for the appearance of a series. TODO: These can be overridden by setting
 * custom settings to a QChartSeries object.
 */
struct SeriesTheme {
public:
//    SeriesTheme() :
//        themeIndex(-1), lineColor(QColor()) {}
//    SeriesTheme(int index, QColor line) :
//        themeIndex(index), lineColor(line) {}
    SeriesTheme() :
        themeIndex(-1), linePen(QPen()), markerPen(QPen()) {}
    SeriesTheme(int index, QColor lineColor, qreal lineWidth/*, QPen marker*/) :
        themeIndex(index),
        linePen(QPen(QBrush(lineColor), lineWidth)),
        markerPen(linePen) {}

//const QBrush & brush, qreal width, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJo
    int themeIndex;
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
    explicit ChartTheme(const ChartTheme &other) : d(other.d) {}
    void operator =(const ChartTheme &other) { d = other.d; }

//signals:
//    void themeChanged(ChartTheme theme);
    SeriesTheme themeForSeries();

public:
    // All the graphical elements of a QChart share the same theme settings
    // so let's use explicitly shared data
    QExplicitlySharedDataPointer<ChartThemeData> d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTHEME_H
