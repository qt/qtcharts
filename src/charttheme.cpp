#include "charttheme_p.h"
#include "qchart.h"
#include "qchartaxis.h"
#include <QTime>

//series
#include "qbarset.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qlinechartseries.h"
#include "qscatterseries.h"
#include "qpieseries.h"
#include "qpieslice.h"

//items
#include "axisitem_p.h"
#include "barpresenter.h"
#include "stackedbarpresenter.h"
#include "linechartitem_p.h"
#include "percentbarpresenter.h"
#include "scatterpresenter_p.h"
#include "piepresenter.h"

//themes
#include "chartthemevanilla_p.h"
#include "chartthemeicy_p.h"
#include "chartthemegrayscale_p.h"
#include "chartthemescientific_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

/* TODO
    case QChart::ChartThemeUnnamed1:
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff3fa9f5)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff7AC943)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF931E)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF1D25)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF7BAC)), 2));

        m_gradientStartColor = QColor(QRgb(0xfff3dc9e));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
*/

ChartTheme::ChartTheme(QChart::ChartTheme id)
{
    m_id = id;
    m_seriesColor.append(QRgb(0xff000000));
    m_seriesColor.append(QRgb(0xff707070));
    m_gradientStartColor = QColor(QRgb(0xffffffff));
    m_gradientEndColor = QColor(QRgb(0xffafafaf));

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}


ChartTheme* ChartTheme::createTheme(QChart::ChartTheme theme)
{
    switch(theme) {
        case QChart::ChartThemeDefault:
            return new ChartThemeIcy();
        case QChart::ChartThemeVanilla:
            return new ChartThemeVanilla();
        case QChart::ChartThemeIcy:
            return new ChartThemeIcy();
        case QChart::ChartThemeGrayscale:
            return new ChartThemeGrayscale();
        case QChart::ChartThemeScientific:
            return new ChartThemeScientific();
    }
}

void ChartTheme::decorate(QChart* chart)
{
    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, m_gradientStartColor);
    backgroundGradient.setColorAt(1.0, m_gradientEndColor);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setChartBackgroundBrush(backgroundGradient);
}
//TODO helper to by removed later
void ChartTheme::decorate(ChartItem* item, QChartSeries* series,int count)
{
    switch(series->type())
    {
        case QChartSeries::SeriesTypeLine: {
            QLineChartSeries* s = static_cast<QLineChartSeries*>(series);
            LineChartItem* i = static_cast<LineChartItem*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypeBar: {
            QBarSeries* b = static_cast<QBarSeries*>(series);
            BarPresenter* i = static_cast<BarPresenter*>(item);
            decorate(i,b,count);
            break;
        }
        case QChartSeries::SeriesTypeStackedBar: {
            QStackedBarSeries* s = static_cast<QStackedBarSeries*>(series);
            StackedBarPresenter* i = static_cast<StackedBarPresenter*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypePercentBar: {
            QPercentBarSeries* s = static_cast<QPercentBarSeries*>(series);
            PercentBarPresenter* i = static_cast<PercentBarPresenter*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypeScatter: {
            QScatterSeries* s = qobject_cast<QScatterSeries*>(series);
            Q_ASSERT(s);
            ScatterPresenter* i = static_cast<ScatterPresenter*>(item);
            Q_ASSERT(i);
            decorate(i, s, count);
            break;
        }
        case QChartSeries::SeriesTypePie: {
            QPieSeries* s = static_cast<QPieSeries*>(series);
            PiePresenter* i = static_cast<PiePresenter*>(item);
            decorate(i,s,count);
            break;
        }
        default:
        qDebug()<<"Wrong item to be decorated by theme";
        break;
    }

}

void ChartTheme::decorate(LineChartItem* item, QLineChartSeries* series,int count)
{
    QPen pen;
    if(pen != series->pen()){
        item->setPen(series->pen());
        return;
    }
    pen.setColor(m_seriesColor.at(count%m_seriesColor.size()));
    pen.setWidthF(2);
    item->setPen(pen);
}

void ChartTheme::decorate(BarPresenter* item, QBarSeries* series,int count)
{
    for (int i=0; i<series->countSets(); i++) {
        series->nextSet(0==i)->setBrush(QBrush(m_seriesColor.at(i%m_seriesColor.count())));
    }
}

void ChartTheme::decorate(StackedBarPresenter* item, QStackedBarSeries* series,int count)
{
    for (int i=0; i<series->countSets(); i++) {
        series->nextSet(0==i)->setBrush(QBrush(m_seriesColor.at(i%m_seriesColor.count())));
    }
}

void ChartTheme::decorate(PercentBarPresenter* item, QPercentBarSeries* series,int count)
{
    for (int i=0; i<series->countSets(); i++) {
        series->nextSet(0==i)->setBrush(QBrush(m_seriesColor.at(i%m_seriesColor.count())));
    }
}

void ChartTheme::decorate(ScatterPresenter* presenter, QScatterSeries* series, int count)
{
    Q_ASSERT(presenter);
    Q_ASSERT(series);

    QColor color = m_seriesColor.at(count % m_seriesColor.size());
    // TODO: define alpha in the theme? or in the series?
    //color.setAlpha(120);

    QBrush brush(color, Qt::SolidPattern);
    presenter->m_markerBrush = brush;

    QPen pen(brush, 3);
    pen.setColor(color);
    presenter->m_markerPen = pen;
}

void ChartTheme::decorate(PiePresenter* item, QPieSeries* series, int /*count*/)
{
    // create a list of slice colors based on current theme
    int i = 0;
    QList<QColor> colors;
    while (colors.count() < series->count()) {

        // get base color
        QColor c = m_seriesColor[i++];
        i = i % m_seriesColor.count();

        // by default use the "raw" theme color
        if (!colors.contains(c)) {
            colors << c;
            continue;
        }
        // ...ok we need to generate something that looks like the same color
        // but different lightness

        int tryCount = 0;
        while (tryCount++ < 100) {

            // find maximum value we can raise the lightness
            int lMax = 255;
            if (lMax > 255 - c.red())
                lMax = 255 - c.red();
            if (lMax > 255 - c.green())
                lMax = 255 - c.green();
            if (lMax > 255 - c.blue())
                lMax = 255 - c.blue();

            // find maximum value we can make it darker
            int dMax = 255;
            if (dMax > c.red())
                dMax = c.red();
            if (dMax > c.green())
                dMax = c.green();
            if (dMax > c.blue())
                dMax = c.blue();

            int max = dMax + lMax;
            if (max == 0) {
                // no room to make color lighter or darker...
                qDebug() << "cannot generate a color for pie!";
                break;
            }

            // generate random color
            int r = c.red() - dMax;
            int g = c.green() - dMax;
            int b = c.blue() - dMax;
            int d = qrand() % max;
            c.setRgb(r+d, g+d, b+d);

            // found a unique color?
            if (!colors.contains(c))
                break;
        }

        qDebug() << "generated a color for pie" << c;
        colors << c;
    }

    // finally update colors
    foreach (QPieSlice* s, series->slices()) {
        QColor c = colors.takeFirst();
        s->setPen(c);
        s->setBrush(c);
    }
}


void ChartTheme::decorate(QChartAxis* axis,AxisItem* item)
{
    //TODO: dummy defults for now
    axis->setLabelsBrush(Qt::black);
    axis->setLabelsPen(Qt::NoPen);
    axis->setShadesPen(Qt::NoPen);
    axis->setShadesOpacity(0.5);
}

QTCOMMERCIALCHART_END_NAMESPACE
