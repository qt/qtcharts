#include <QtTest/QtTest>
#include <qchartview.h>
#include <qlineseries.h>
#include <qareaseries.h>
#include <qscatterseries.h>
#include <qsplineseries.h>
#include <qpieseries.h>
#include <qbarseries.h>
#include <qpercentbarseries.h>
#include <qstackedbarseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QChartAxis*)
Q_DECLARE_METATYPE(QSeries*)
Q_DECLARE_METATYPE(QChart::AnimationOption)

class tst_QChart : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qchart_data();
    void qchart();

    void addSeries_data();
    void addSeries();
    void animationOptions_data();
    void animationOptions();
    void axisX_data();
    void axisX();
    void axisY_data();
    void axisY();
    void backgroundBrush_data();
    void backgroundBrush();
    void backgroundPen_data();
    void backgroundPen();
    void isBackgroundVisible_data();
    void isBackgroundVisible();
    void legend_data();
    void legend();
    void margins_data();
    void margins();
    void removeAllSeries_data();
    void removeAllSeries();
    void removeSeries_data();
    void removeSeries();
    void scrollDown_data();
    void scrollDown();
    void scrollLeft_data();
    void scrollLeft();
    void scrollRight_data();
    void scrollRight();
    void scrollUp_data();
    void scrollUp();
    void setBackgroundBrush_data();
    void setBackgroundBrush();
    void setBackgroundPen_data();
    void setBackgroundPen();
    void setBackgroundVisible_data();
    void setBackgroundVisible();
    void setTheme_data();
    void setTheme();
    void setTitle_data();
    void setTitle();
    void setTitleBrush_data();
    void setTitleBrush();
    void setTitleFont_data();
    void setTitleFont();
    void theme_data();
    void theme();
    void title_data();
    void title();
    void titleBrush_data();
    void titleBrush();
    void titleFont_data();
    void titleFont();
    void zoomIn_data();
    void zoomIn();
    void zoomOut_data();
    void zoomOut();

private:
    void createTestData();

private:
    QChartView* m_view;
    QChart* m_chart;
};

void tst_QChart::initTestCase()
{

}

void tst_QChart::cleanupTestCase()
{

}

void tst_QChart::init()
{
    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
}

void tst_QChart::createTestData()
{
    QLineSeries* series0 = new QLineSeries(this);
    *series0 << QPointF(0, 0) << QPointF(100, 100);
    m_chart->addSeries(series0);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QChart::cleanup()
{
    delete m_view;
    m_view = 0;
    m_chart = 0;
}

void tst_QChart::qchart_data()
{
}

void tst_QChart::qchart()
{
    QVERIFY(m_chart);
    QVERIFY(m_chart->legend());
    QVERIFY(!m_chart->legend()->isVisible());

    QCOMPARE(m_chart->animationOptions(), QChart::NoAnimation);
    QVERIFY(m_chart->axisX());
    QVERIFY(m_chart->axisY());
    QVERIFY(m_chart->backgroundBrush()!=QBrush());
    QVERIFY(m_chart->backgroundPen()!=QPen());
    QCOMPARE(m_chart->isBackgroundVisible(), true);

    QVERIFY(m_chart->margins().top()>0);
    QVERIFY(m_chart->margins().left()>0);
    QVERIFY(m_chart->margins().right()>0);
    QVERIFY(m_chart->margins().bottom()>0);
    m_chart->removeAllSeries();
    m_chart->scrollDown();
    m_chart->scrollLeft();
    m_chart->scrollRight();
    m_chart->scrollUp();
    QCOMPARE(m_chart->theme(), QChart::ChartThemeLight);
    QCOMPARE(m_chart->title(), QString());
    QCOMPARE(m_chart->titleBrush(),QBrush());
    QCOMPARE(m_chart->titleFont(),QFont());
    m_chart->zoomIn();
    m_chart->zoomIn(QRectF());
    m_chart->zoomOut();
}

void tst_QChart::addSeries_data()
{
    QTest::addColumn<QSeries*>("series");
    QTest::addColumn<QChartAxis*>("axis");

    QSeries* series0 = new QLineSeries(this);
    QSeries* series1 = new QAreaSeries(static_cast<QLineSeries*>(series0));
    QSeries* series2 = new QScatterSeries(this);
    QSeries* series3 = new QSplineSeries(this);
    QSeries* series4 = new QPieSeries(this);
    QSeries* series5 = new QBarSeries(QBarCategories(),this);
    QSeries* series6 = new QPercentBarSeries(QBarCategories(),this);
    QSeries* series7 = new QStackedBarSeries(QBarCategories(),this);

    QChartAxis* axis = new QChartAxis(this);

    QTest::newRow("default axis: lineSeries") << series0 << (QChartAxis*) 0;
    QTest::newRow("axis0: lineSeries") << series0 << axis;
    QTest::newRow("default axis: areaSeries") << series1 << (QChartAxis*) 0;
    QTest::newRow("axis: areaSeries") << series1 << axis;
    QTest::newRow("default axis: scatterSeries") << series2 << (QChartAxis*) 0;
    QTest::newRow("axis1: scatterSeries") << series2 << axis;
    QTest::newRow("default axis: splineSeries") << series3 << (QChartAxis*) 0;
    QTest::newRow("axis: splineSeries") << series3 << axis;
    QTest::newRow("default axis: pieSeries") << series4 << (QChartAxis*) 0;
    QTest::newRow("axis: pieSeries") << series4 << axis;
    QTest::newRow("default axis: barSeries") << series5 << (QChartAxis*) 0;
    QTest::newRow("axis: barSeries") << series5 << axis;
    QTest::newRow("default axis: percentBarSeries") << series6 << (QChartAxis*) 0;
    QTest::newRow("axis: barSeries") << series6 << axis;
    QTest::newRow("default axis: stackedBarSeries") << series7 << (QChartAxis*) 0;
    QTest::newRow("axis: barSeries") << series7 << axis;

}

void tst_QChart::addSeries()
{
    QFETCH(QSeries*, series);
    QFETCH(QChartAxis*, axis);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    if(!axis) axis = m_chart->axisY();
    //m_chart->addSeries(series,axis);
    QCOMPARE(m_chart->axisY(series),axis);
}

void tst_QChart::animationOptions_data()
{
    QTest::addColumn<QChart::AnimationOption>("animationOptions");
    QTest::newRow("AllAnimations") << QChart::AllAnimations;
    QTest::newRow("NoAnimation") << QChart::NoAnimation;
    QTest::newRow("GridAxisAnimations") << QChart::GridAxisAnimations;
    QTest::newRow("SeriesAnimations") << QChart::SeriesAnimations;
}

void tst_QChart::animationOptions()
{
    createTestData();
    QFETCH(QChart::AnimationOption, animationOptions);
    m_chart->setAnimationOptions(animationOptions);
    QCOMPARE(m_chart->animationOptions(), animationOptions);

}

void tst_QChart::axisX_data()
{
#if 0
    QTest::addColumn<QChartAxis*>("axisX");
    QTest::newRow("null") << QChartAxis*();
#endif
}

// public QChartAxis* axisX() const
void tst_QChart::axisX()
{
#if 0
    QFETCH(QChartAxis*, axisX);

    SubQChart chart;

    QCOMPARE(chart.axisX(), axisX);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::axisY_data()
{
#if 0
    QTest::addColumn<QChartAxis*>("axisY");
    QTest::newRow("null") << QChartAxis*();
#endif
}

// public QChartAxis* axisY() const
void tst_QChart::axisY()
{
#if 0
    QFETCH(QChartAxis*, axisY);

    SubQChart chart;

    QCOMPARE(chart.axisY(), axisY);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QBrush)
void tst_QChart::backgroundBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("backgroundBrush");
    QTest::newRow("null") << QBrush();
#endif
}

// public QBrush backgroundBrush() const
void tst_QChart::backgroundBrush()
{
#if 0
    QFETCH(QBrush, backgroundBrush);

    SubQChart chart;

    QCOMPARE(chart.backgroundBrush(), backgroundBrush);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QPen)
void tst_QChart::backgroundPen_data()
{
#if 0
    QTest::addColumn<QPen>("backgroundPen");
    QTest::newRow("null") << QPen();
#endif
}

// public QPen backgroundPen() const
void tst_QChart::backgroundPen()
{
#if 0
    QFETCH(QPen, backgroundPen);

    SubQChart chart;

    QCOMPARE(chart.backgroundPen(), backgroundPen);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::isBackgroundVisible_data()
{
    QTest::addColumn<bool>("isBackgroundVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool isBackgroundVisible() const
void tst_QChart::isBackgroundVisible()
{
#if 0
    QFETCH(bool, isBackgroundVisible);

    SubQChart chart;

    QCOMPARE(chart.isBackgroundVisible(), isBackgroundVisible);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QLegend*)
void tst_QChart::legend_data()
{
#if 0
    QTest::addColumn<QLegend*>("legend");
    QTest::newRow("null") << QLegend*();
#endif
}

// public QLegend* legend() const
void tst_QChart::legend()
{
#if 0
    QFETCH(QLegend*, legend);

    SubQChart chart;

    QCOMPARE(chart.legend(), legend);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::margins_data()
{
    QTest::addColumn<QRectF>("margins");
    QTest::newRow("null") << QRectF();
}

// public QRectF margins() const
void tst_QChart::margins()
{
#if 0
    QFETCH(QRectF, margins);

    SubQChart chart;

    QCOMPARE(chart.margins(), margins);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::removeAllSeries_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void removeAllSeries()
void tst_QChart::removeAllSeries()
{
#if 0
    QFETCH(int, foo);

    SubQChart chart;

    chart.removeAllSeries();
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::removeSeries_data()
{
    QTest::addColumn<int>("seriesCount");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void removeSeries(QSeries* series)
void tst_QChart::removeSeries()
{
#if 0
    QFETCH(int, seriesCount);

    SubQChart chart;

    chart.removeSeries(series);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::scrollDown_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void scrollDown()
void tst_QChart::scrollDown()
{
#if 0
    QFETCH(int, foo);

    SubQChart chart;

    chart.scrollDown();
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::scrollLeft_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void scrollLeft()
void tst_QChart::scrollLeft()
{
#if 0
    QFETCH(int, foo);

    SubQChart chart;

    chart.scrollLeft();
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::scrollRight_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void scrollRight()
void tst_QChart::scrollRight()
{
#if 0
    QFETCH(int, foo);

    SubQChart chart;

    chart.scrollRight();
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::scrollUp_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void scrollUp()
void tst_QChart::scrollUp()
{
#if 0
    QFETCH(int, foo);

    SubQChart chart;

    chart.scrollUp();
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::setBackgroundBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("brush");
    QTest::newRow("null") << QBrush();
#endif
}

// public void setBackgroundBrush(QBrush const& brush)
void tst_QChart::setBackgroundBrush()
{
#if 0
    QFETCH(QBrush, brush);

    SubQChart chart;

    chart.setBackgroundBrush(brush);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::setBackgroundPen_data()
{
#if 0
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
#endif
}

// public void setBackgroundPen(QPen const& pen)
void tst_QChart::setBackgroundPen()
{
#if 0
    QFETCH(QPen, pen);

    SubQChart chart;

    chart.setBackgroundPen(pen);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::setBackgroundVisible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setBackgroundVisible(bool visible)
void tst_QChart::setBackgroundVisible()
{
#if 0
    QFETCH(bool, visible);

    SubQChart chart;

    chart.setBackgroundVisible(visible);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QChart::ChartTheme)
void tst_QChart::setTheme_data()
{
#if 0
    QTest::addColumn<QChart::ChartTheme>("theme");
    QTest::newRow("null") << QChart::ChartTheme();
#endif
}

// public void setTheme(QChart::ChartTheme theme)
void tst_QChart::setTheme()
{
#if 0
    QFETCH(QChart::ChartTheme, theme);

    SubQChart chart;

    chart.setTheme(theme);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::setTitle_data()
{
    QTest::addColumn<QString>("title");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// public void setTitle(QString const& title)
void tst_QChart::setTitle()
{
#if 0
    QFETCH(QString, title);

    SubQChart chart;

    chart.setTitle(title);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::setTitleBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("brush");
    QTest::newRow("null") << QBrush();
#endif
}

// public void setTitleBrush(QBrush const& brush)
void tst_QChart::setTitleBrush()
{
#if 0
    QFETCH(QBrush, brush);

    SubQChart chart;

    chart.setTitleBrush(brush);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::setTitleFont_data()
{
    QTest::addColumn<QFont>("font");
    QTest::newRow("null") << QFont();
}

// public void setTitleFont(QFont const& font)
void tst_QChart::setTitleFont()
{
#if 0
    QFETCH(QFont, font);

    SubQChart chart;

    chart.setTitleFont(font);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::theme_data()
{
#if 0
    QTest::addColumn<QChart::ChartTheme>("theme");
    QTest::newRow("null") << QChart::ChartTheme();
#endif
}

// public QChart::ChartTheme theme() const
void tst_QChart::theme()
{
#if 0
    QFETCH(QChart::ChartTheme, theme);

    SubQChart chart;

    QCOMPARE(chart.theme(), theme);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::title_data()
{
    QTest::addColumn<QString>("title");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// public QString title() const
void tst_QChart::title()
{
#if 0
    QFETCH(QString, title);

    SubQChart chart;

    QCOMPARE(chart.title(), title);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::titleBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("titleBrush");
    QTest::newRow("null") << QBrush();
#endif
}

// public QBrush titleBrush() const
void tst_QChart::titleBrush()
{
#if 0
    QFETCH(QBrush, titleBrush);

    SubQChart chart;

    QCOMPARE(chart.titleBrush(), titleBrush);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::titleFont_data()
{
    QTest::addColumn<QFont>("titleFont");
    QTest::newRow("null") << QFont();
}

// public QFont titleFont() const
void tst_QChart::titleFont()
{
#if 0
    QFETCH(QFont, titleFont);

    SubQChart chart;

    QCOMPARE(chart.titleFont(), titleFont);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::zoomIn_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void zoomIn()
void tst_QChart::zoomIn()
{
#if 0
    QFETCH(int, foo);

    SubQChart chart;

    chart.zoomIn();
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QChart::zoomOut_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void zoomOut()
void tst_QChart::zoomOut()
{
#if 0
    QFETCH(int, foo);

    SubQChart chart;

    chart.zoomOut();
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

QTEST_MAIN(tst_QChart)
#include "tst_qchart.moc"

