#include "qchart.h"
#include "qchartseries.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qpieseries.h"
#include "qxychartseries.h"

#include "barchartseries.h"
#include "bargroup.h"

#include "xylinechartitem_p.h"
#include "plotdomain_p.h"
#include "axisitem_p.h"
#include <QGraphicsScene>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChart::QChart(QGraphicsObject* parent) : QGraphicsObject(parent),
    m_background(new QGraphicsRectItem(this)),
    m_title(new QGraphicsTextItem(this)),
    m_axisX(new AxisItem(AxisItem::X_AXIS,this)),
    m_axisY(new AxisItem(AxisItem::Y_AXIS,this)),
    m_plotDataIndex(0),
    m_marginSize(0)
{
    // TODO: the default theme?
    setTheme(QChart::ChartThemeVanilla);
    //  setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    PlotDomain domain;
    m_plotDomainList<<domain;

    m_chartItems<<m_axisX;
    m_chartItems<<m_axisY;
}

QChart::~QChart(){}

QRectF QChart::boundingRect() const
{
    return m_rect;
}

void QChart::addSeries(QChartSeries* series)
{
    // TODO: we should check the series not already added

    m_chartSeries << series;

    switch(series->type())
    {
    case QChartSeries::SeriesTypeLine: {

        QXYChartSeries* xyseries = static_cast<QXYChartSeries*>(series);
        // Use color defined by theme in case the series does not define a custom color
        if (!xyseries->color().isValid() && m_themeColors.count())
            xyseries->setColor(nextColor());

        m_plotDataIndex = 0 ;
        m_plotDomainList.resize(1);

        PlotDomain& domain = m_plotDomainList[m_plotDataIndex];

        for (int i = 0 ; i < xyseries->count() ; i++)
        {
            qreal x = xyseries->x(i);
            qreal y = xyseries->y(i);
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
        }

        XYLineChartItem* item = new XYLineChartItem(xyseries,this);
        m_chartItems<<item;

        foreach(ChartItem* i ,m_chartItems)
            i->setPlotDomain(m_plotDomainList.at(m_plotDataIndex));

        break;
    }
    case QChartSeries::SeriesTypeBar: {

        qDebug() << "barSeries added";
        BarChartSeries* barSeries = static_cast<BarChartSeries*>(series);
        connect(this, SIGNAL(sizeChanged(QRectF)),
                barSeries, SLOT(chartSizeChanged(QRectF)));

        break;
        }
    case QChartSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
        scatterSeries->d->setParentItem(this);
        // Set pre-defined colors in case the series has no colors defined
        if (!scatterSeries->markerColor().isValid())
            scatterSeries->setMarkerColor(nextColor());
        connect(this, SIGNAL(sizeChanged(QRectF)),
                scatterSeries, SLOT(chartSizeChanged(QRectF)));
//        QColor nextColor = m_themeColors.takeFirst();
//        nextColor.setAlpha(150); // TODO: default opacity?
//        scatterSeries->setMarkerColor(nextColor);
        break;
        }
    case QChartSeries::SeriesTypePie: {
        QPieSeries *pieSeries = qobject_cast<QPieSeries *>(series);
        for (int i(0); i < pieSeries->sliceCount(); i++) {
            if (!pieSeries->sliceColor(i).isValid())
                pieSeries->setSliceColor(i, nextColor());
        }
        connect(this, SIGNAL(sizeChanged(QRectF)),
                pieSeries, SLOT(chartSizeChanged(QRectF)));

        // Set pre-defined colors in case the series has no colors defined
        // TODO: how to define the color for all the slices of a pie?
//        for (int (i); i < pieSeries.sliceCount(); i++)
        break;
        }
    }
}

QChartSeries* QChart::createSeries(QChartSeries::QChartSeriesType type)
{
    // TODO: support also other types; not only scatter and pie

    QChartSeries *series(0);

    switch (type) {
    case QChartSeries::SeriesTypeLine: {
        series = QXYChartSeries::create();
        break;
    }
    case QChartSeries::SeriesTypeBar: {
        series = new BarChartSeries(this);
        break;
    }
    case QChartSeries::SeriesTypeScatter: {
        series = new QScatterSeries(this);
        break;
    }
    case QChartSeries::SeriesTypePie: {
        series = new QPieSeries(this);
        break;
    }
    default:
        Q_ASSERT(false);
        break;
    }

    addSeries(series);
    return series;
}

void QChart::setSize(const QSize& size)
{
    m_rect = QRect(QPoint(0,0),size);
    QRect rect = m_rect.adjusted(margin(),margin(), -margin(), -margin());


    //recalculate background gradient
    m_background->setRect(rect);
    m_backgroundGradient.setFinalStop(0,m_background->rect().height());
    m_background->setBrush(m_backgroundGradient);

    //resize elements
    foreach (ChartItem* item ,m_chartItems) {
        item->setPos(rect.topLeft());
        item->setSize(rect.size());

    }
    // TODO: TTD for setting scale
    //emit scaleChanged(100, 100);
    // TODO: calculate the origo
    // TODO: not sure if emitting a signal here is the best from performance point of view
    emit sizeChanged(QRectF(0, 0, size.width(), size.height()));

    update();
}

void QChart::setBackgroundColor(const QColor& color)
{
    m_backgroundGradient.setColorAt( 0.0, Qt::white);
    m_backgroundGradient.setColorAt( 1.0, color);
    m_background->setBrush(m_backgroundGradient);
    m_background->setPen(Qt::NoPen);
    m_background->update();
}

void QChart::setTitle(const QString& title)
{
    m_title->setPlainText(title);
}

int QChart::margin() const
{
    return m_marginSize;
}

void QChart::setMargin(int margin)
{
    m_marginSize = margin;
}

void QChart::setTheme(QChart::ChartThemeId theme)
{
//    if (theme != m_currentTheme) {
    m_themeColors.clear();

    // TODO: define color themes
    switch (theme) {
    case QChart::ChartThemeVanilla:
        m_themeColors.append(QColor(217, 197, 116));
        m_themeColors.append(QColor(214, 168, 150));
        m_themeColors.append(QColor(160, 160, 113));
        m_themeColors.append(QColor(210, 210, 52));
        m_themeColors.append(QColor(136, 114, 58));

        m_backgroundGradient.setColorAt(0.0, QColor(QRgb(0xff9d844d)));
        m_backgroundGradient.setColorAt(1.0, QColor(QRgb(0xffafafaf)));
        break;
    case QChart::ChartThemeIcy:
        m_themeColors.append(QColor(0, 3, 165));
        m_themeColors.append(QColor(49, 52, 123));
        m_themeColors.append(QColor(71, 114, 187));
        m_themeColors.append(QColor(48, 97, 87));
        m_themeColors.append(QColor(19, 71, 90));
        m_themeColors.append(QColor(110, 70, 228));

        m_backgroundGradient.setColorAt(0.0, QColor(QRgb(0xffe4ffff)));
        m_backgroundGradient.setColorAt(1.0, QColor(QRgb(0xffafafaf)));
        break;
    case QChart::ChartThemeGrayscale:
        m_themeColors.append(QColor(0, 0, 0));
        m_themeColors.append(QColor(50, 50, 50));
        m_themeColors.append(QColor(100, 100, 100));
        m_themeColors.append(QColor(140, 140, 140));
        m_themeColors.append(QColor(180, 180, 180));

        m_backgroundGradient.setColorAt(0.0, QColor(QRgb(0xffffffff)));
        m_backgroundGradient.setColorAt(1.0, QColor(QRgb(0xffafafaf)));
        break;
    case QChart::ChartThemeUnnamed1:
        m_themeColors.append(QColor(QRgb(0xff3fa9f5)));
        m_themeColors.append(QColor(QRgb(0xff7AC943)));
        m_themeColors.append(QColor(QRgb(0xffFF931E)));
        m_themeColors.append(QColor(QRgb(0xffFF1D25)));
        m_themeColors.append(QColor(QRgb(0xffFF7BAC)));

        m_backgroundGradient.setColorAt(0.0, QColor(QRgb(0xfff3dc9e)));
        m_backgroundGradient.setColorAt(1.0, QColor(QRgb(0xffafafaf)));
        break;
    default:
        Q_ASSERT(false);
        break;
    }

    m_background->setBrush(m_backgroundGradient);
    m_background->setPen(Qt::NoPen);

    foreach(QChartSeries* series, m_chartSeries) {
        // TODO: other series interested on themes?
        if (series->type() == QChartSeries::SeriesTypeLine) {
            QXYChartSeries *lineseries = reinterpret_cast<QXYChartSeries *>(series);
            lineseries->setColor(nextColor());
        } else if (series->type() == QChartSeries::SeriesTypeScatter) {
            QScatterSeries *scatter = qobject_cast<QScatterSeries *>(series);
            scatter->setMarkerColor(nextColor());
        } else if (series->type() == QChartSeries::SeriesTypePie) {
            QPieSeries *pieSeries = qobject_cast<QPieSeries *>(series);
            for (int i(0); i < pieSeries->sliceCount(); i++)
                pieSeries->setSliceColor(i, nextColor());
        }
    }
    update();
}

QColor QChart::nextColor()
{
    QColor nextColor = m_themeColors.first();
    m_themeColors.move(0, m_themeColors.size() - 1);
    return nextColor;
}

void QChart::zoomInToRect(const QRect& rectangle)
{

    if(!rectangle.isValid()) return;

    qreal margin = this->margin();

    QRect rect = rectangle.normalized();
    rect.translate(-margin, -margin);

    PlotDomain& oldDomain = m_plotDomainList[m_plotDataIndex];

    PlotDomain domain = oldDomain.subDomain(rect,m_rect.width() - 2 * margin,m_rect.height() - 2 * margin);

    m_plotDomainList.resize(m_plotDataIndex + 1);
    m_plotDomainList<<domain;
    m_plotDataIndex++;

    foreach (ChartItem* item ,m_chartItems)
        item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
    update();
}

void QChart::zoomIn()
{
    if (m_plotDataIndex < m_plotDomainList.count() - 1) {
        m_plotDataIndex++;
        foreach (ChartItem* item ,m_chartItems)
            item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
        update();
    }else{
        QRect rect = m_rect.adjusted(margin(),margin(), -margin(), -margin());
        rect.setWidth(rect.width()/2);
        rect.setHeight(rect.height()/2);
        rect.moveCenter(m_rect.center());
        zoomInToRect(rect);
    }
}

void QChart::zoomOut()
{
    if (m_plotDataIndex > 0) {
        m_plotDataIndex--;
        foreach (ChartItem* item ,m_chartItems)
            item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
        update();
    }
}

#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
