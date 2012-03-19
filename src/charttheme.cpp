#include "charttheme_p.h"
#include "qchart.h"
#include "qchartview.h"
#include "qlegend.h"
#include "qchartaxis.h"
#include <QTime>

//series
#include "qbarset.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qlineseries.h"
#include "qareaseries.h"
#include "qscatterseries.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include "qsplineseries.h"

//items
#include "axisitem_p.h"
#include "barpresenter_p.h"
#include "stackedbarpresenter_p.h"
#include "percentbarpresenter_p.h"
#include "linechartitem_p.h"
#include "areachartitem_p.h"
#include "scatterchartitem_p.h"
#include "piechartitem_p.h"
#include "splinechartitem_p.h"

//themes
#include "chartthemedefault_p.h"
#include "chartthemevanilla_p.h"
#include "chartthemeicy_p.h"
#include "chartthemegrayscale_p.h"
#include "chartthemescientific_p.h"
#include "chartthemebluecerulean_p.h"
#include "chartthemelight_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartTheme::ChartTheme(QChart::ChartTheme id) :
    m_masterFont(QFont()),
    m_titleBrush(QColor(QRgb(0x000000))),
    m_axisLinePen(QPen(QRgb(0x000000))),
    m_axisLabelBrush(QColor(QRgb(0x000000))),
    m_backgroundShadesPen(Qt::NoPen),
    m_backgroundShadesBrush(Qt::NoBrush),
    m_backgroundShades(BackgroundShadesNone),
    m_gridLinePen(QPen(QRgb(0x000000)))
{
    m_id = id;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}


ChartTheme* ChartTheme::createTheme(QChart::ChartTheme theme)
{
    switch(theme) {
        case QChart::ChartThemeVanilla:
            return new ChartThemeVanilla();
        case QChart::ChartThemeIcy:
            return new ChartThemeIcy();
        case QChart::ChartThemeGrayscale:
            return new ChartThemeGrayscale();
        case QChart::ChartThemeScientific:
            return new ChartThemeScientific();
        case QChart::ChartThemeBlueCerulean:
            return new ChartThemeBlueCerulean();
        case QChart::ChartThemeLight:
            return new ChartThemeLight();
        default:
            return new ChartThemeDefault();
    }
}

void ChartTheme::decorate(QChart* chart,bool force)
{
    QPen pen;
    QBrush brush;

    if(brush == chart->backgroundBrush() || force)
    {
        if (m_backgroundShades == BackgroundShadesNone) {
            chart->setBackgroundBrush(m_chartBackgroundGradient);
        }
        else {
            chart->setBackgroundBrush(Qt::NoBrush);
        }
    }
    chart->setTitleFont(m_masterFont);
    chart->setTitleBrush(m_titleBrush);
}

void ChartTheme::decorate(QLegend* legend,bool force)
{
    QPen pen;
    QBrush brush;

    if (pen == legend->pen() || force){
        //TODO:: legend->setPen();
    }


    if (brush == legend->brush() || force) {
        legend->setBrush(m_chartBackgroundGradient);
    }
}

void ChartTheme::decorate(QAreaSeries* series, int index,bool force)
{
    QPen pen;
    QBrush brush;

    if (pen == series->pen() || force){
        pen.setColor(colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 1.0));
        pen.setWidthF(2);
        series->setPen(pen);
    }

    if (brush == series->brush() || force) {
       QBrush brush(m_seriesColors.at(index % m_seriesColors.size()));
       series->setBrush(brush);
    }
}


void ChartTheme::decorate(QLineSeries* series,int index,bool force)
{
    QPen pen;
    if(pen == series->pen() || force ){
        pen.setColor(m_seriesColors.at(index%m_seriesColors.size()));
        pen.setWidthF(2);
        series->setPen(pen);
    }
}

void ChartTheme::decorate(QBarSeries* series,int index,bool force)
{
    QBrush brush;
    QList<QBarSet*> sets = series->barSets();

    for (int i=0; i<sets.count(); i++) {
        qreal pos = 0.5;
        if (sets.count() > 1)
            pos = (qreal) i / (qreal) (sets.count() - 1);

        if(brush == sets.at(i)->brush() || force ){
        QColor c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), pos);
        sets.at(i)->setBrush(QBrush(c));
        }
        // Pick label color as far as possible from bar color (within gradient).
        // 0.3 is magic number that was picked as value that gave enough contrast with icy theme gradient :)
        // TODO: better picking of label color?
        QColor c;

        if (pos < 0.3) {
            c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 1);
        } else {
            c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 0);
        }
        sets.at(i)->setFloatingValuePen(QPen(c));

    }
}

void ChartTheme::decorate(QStackedBarSeries* series,int index,bool force)
{
    QBrush brush;
    QList<QBarSet*> sets = series->barSets();

    for (int i=0; i<sets.count(); i++) {
        qreal pos = 0.5;
        if (sets.count() > 1)
            pos = (qreal) i / (qreal) (sets.count() - 1);
        if(brush == sets.at(i)->brush() || force){
        QColor c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), pos);
        sets.at(i)->setBrush(QBrush(c));
        }
        QColor c;
        if (pos < 0.3) {
            c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 1);
        } else {
            c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 0);
        }
        sets.at(i)->setFloatingValuePen(QPen(c));
    }
}

void ChartTheme::decorate(QPercentBarSeries* series,int index,bool force)
{
    QBrush brush;
    QList<QBarSet*> sets = series->barSets();

    for (int i=0; i<sets.count(); i++) {
        qreal pos = 0.5;
        if (sets.count() > 1)
            pos = (qreal) i / (qreal) (sets.count() - 1);

        if(brush == sets.at(i)->brush() || force){
        QColor c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), pos);
        sets.at(i)->setBrush(QBrush(c));
        }
        QColor c;
        if (pos < 0.3) {
            c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 1);
        } else {
            c = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 0);
        }
        sets.at(i)->setFloatingValuePen(QPen(c));
    }
}

void ChartTheme::decorate(QScatterSeries* series, int index,bool force)
{

    QPen pen;
    QBrush brush;

    if (pen == series->pen() || force) {
        pen.setColor(colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 1.0));
        pen.setWidthF(2);
        series->setPen(pen);
    }

    if (brush == series->brush() || force) {
        QBrush brush(m_seriesColors.at(index % m_seriesColors.size()));
        series->setBrush(brush);
    }
}

void ChartTheme::decorate(QPieSeries* series, int index, bool force)
{
    // Get color for a slice from a gradient linearly, beginning from the start of the gradient

    QPen pen;
    QBrush brush;

    for (int i(0); i < series->slices().count(); i++) {
        qreal pos = (qreal) i / (qreal) series->count();
        if( pen == series->slices().at(i)->slicePen() || force){
        QColor penColor = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), 0.1);
        series->slices().at(i)->setSlicePen(penColor);
        }
        if( brush == series->slices().at(i)->sliceBrush() || force){
        QColor brushColor = colorAt(m_seriesGradients.at(index % m_seriesGradients.size()), pos);
        series->slices().at(i)->setSliceBrush(brushColor);
        }
    }
}

void ChartTheme::decorate(QSplineSeries* series, int index, bool force)
{
    QPen pen;
    if(pen == series->pen() || force){
        pen.setColor(m_seriesColors.at(index%m_seriesColors.size()));
        pen.setWidthF(2);
        series->setPen(pen);
    }
}

void ChartTheme::decorate(QChartAxis* axis,bool axisX, bool force)
{
    QPen pen;
    QBrush brush;
    QFont font;

    if (axis->isAxisVisible()) {

        if(brush == axis->labelsBrush() || force){
            axis->setLabelsBrush(m_axisLabelBrush);
        }
        if(pen == axis->labelsPen() || force){
            axis->setLabelsPen(Qt::NoPen); // NoPen for performance reasons
        }


       if (axis->shadesVisible() || force) {

         if(brush == axis->shadesBrush() || force){
             axis->setShadesBrush(m_backgroundShadesBrush);
         }

         if(pen == axis->shadesPen() || force){
             axis->setShadesPen(m_backgroundShadesPen);
         }

         if(force && (m_backgroundShades == BackgroundShadesBoth
                         || (m_backgroundShades == BackgroundShadesVertical && axisX)
                         || (m_backgroundShades == BackgroundShadesHorizontal && !axisX))){
             axis->setShadesVisible(true);

         }
       }

        if(pen == axis->axisPen() || force){
            axis->setAxisPen(m_axisLinePen);
        }

        if(pen == axis->gridLinePen() || force){
            axis->setGridLinePen(m_gridLinePen);
        }

        if(font == axis->labelsFont() || force){
            axis->setLabelsFont(m_masterFont);
        }
    }
}

void ChartTheme::generateSeriesGradients()
{
    // Generate gradients in HSV color space
    foreach (QColor color, m_seriesColors) {
        QLinearGradient g;
        qreal h = color.hsvHueF();
        qreal s = color.hsvSaturationF();

        // TODO: tune the algorithm to give nice results with most base colors defined in
        // most themes. The rest of the gradients we can define manually in theme specific
        // implementation.
        QColor start = color;
        start.setHsvF(h, 0.05, 0.95);
        g.setColorAt(0.0, start);

        g.setColorAt(0.5, color);

        QColor end = color;
        end.setHsvF(h, s, 0.25);
        g.setColorAt(1.0, end);

        m_seriesGradients << g;
    }
}


QColor ChartTheme::colorAt(const QColor &start, const QColor &end, qreal pos)
{
    Q_ASSERT(pos >=0.0 && pos <= 1.0);
    qreal r = start.redF() + ((end.redF() - start.redF()) * pos);
    qreal g = start.greenF() + ((end.greenF() - start.greenF()) * pos);
    qreal b = start.blueF() + ((end.blueF() - start.blueF()) * pos);
    QColor c;
    c.setRgbF(r, g, b);
    return c;
}

QColor ChartTheme::colorAt(const QGradient &gradient, qreal pos)
{
    Q_ASSERT(pos >=0 && pos <= 1.0);

    // another possibility:
    // http://stackoverflow.com/questions/3306786/get-intermediate-color-from-a-gradient

    QGradientStops stops = gradient.stops();
    int count = stops.count();

    // find previous stop relative to position
    QGradientStop prev = stops.first();
    for (int i=0; i<count; i++) {
        QGradientStop stop = stops.at(i);
        if (pos > stop.first)
            prev = stop;

        // given position is actually a stop position?
        if (pos == stop.first) {
            //qDebug() << "stop color" << pos;
            return stop.second;
        }
    }

    // find next stop relative to position
    QGradientStop next = stops.last();
    for (int i=count-1; i>=0; i--) {
        QGradientStop stop = stops.at(i);
        if (pos < stop.first)
            next = stop;
    }

    //qDebug() << "prev" << prev.first << "pos" << pos << "next" << next.first;

    qreal range = next.first - prev.first;
    qreal posDelta = pos - prev.first;
    qreal relativePos = posDelta / range;

    //qDebug() << "range" << range << "posDelta" << posDelta << "relativePos" << relativePos;

    return colorAt(prev.second, next.second, relativePos);
}

QTCOMMERCIALCHART_END_NAMESPACE
