#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtCore/QtGlobal>
#include <QDeclarativeItem>
#include <qchart.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeChart : public QDeclarativeItem
// TODO: for QTQUICK2: extend QQuickPainterItem instead
//class DeclarativeChart : public QQuickPaintedItem, public Chart
{
    Q_OBJECT
    Q_ENUMS(ChartTheme)
    Q_PROPERTY(ChartTheme theme READ theme WRITE setTheme)

public:
    enum ChartTheme {
        ThemeDefault,
        ThemeLight,
        ThemeBlueCerulean,
        ThemeDark,
        ThemeBrownSand,
        ThemeBlueNcs,
        ThemeIcy,
        ThemeScientific
    };
    DeclarativeChart(QDeclarativeItem *parent = 0);
    ~DeclarativeChart();

public: // From QDeclarativeItem/QGraphicsItem
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
    void setTheme(ChartTheme theme) {m_chart->setTheme((QChart::ChartTheme) theme);}
    ChartTheme theme();

public:
    // Extending QChart with DeclarativeChart is not possible because QObject does not support
    // multi inheritance, so we now have a QChart as a member instead
    QChart *m_chart;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVECHART_H
