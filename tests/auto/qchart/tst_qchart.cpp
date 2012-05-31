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

Q_DECLARE_METATYPE(QAxis *)
Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QChart::AnimationOption)
Q_DECLARE_METATYPE(QBrush)
Q_DECLARE_METATYPE(QPen)
Q_DECLARE_METATYPE(QChart::ChartTheme)

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
    QVERIFY(m_chart->legend()->isVisible());

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

    QCOMPARE(m_chart->theme(), QChart::ChartThemeLight);
    QCOMPARE(m_chart->title(), QString());

    //QCOMPARE(m_chart->titleBrush(),QBrush());
    //QCOMPARE(m_chart->titleFont(),QFont());

    m_chart->removeAllSeries();
    m_chart->scrollDown();
    m_chart->scrollLeft();
    m_chart->scrollRight();
    m_chart->scrollUp();

    m_chart->zoomIn();
    m_chart->zoomIn(QRectF());
    m_chart->zoomOut();
}

void tst_QChart::addSeries_data()
{
    QTest::addColumn<QAbstractSeries *>("series");
    QTest::addColumn<QAxis *>("axis");

    QAbstractSeries* series0 = new QLineSeries(this);
    QAbstractSeries* series1 = new QAreaSeries(static_cast<QLineSeries*>(series0));
    QAbstractSeries* series2 = new QScatterSeries(this);
    QAbstractSeries* series3 = new QSplineSeries(this);
    QAbstractSeries* series4 = new QPieSeries(this);
    QAbstractSeries* series5 = new QBarSeries(this);
    QAbstractSeries* series6 = new QPercentBarSeries(this);
    QAbstractSeries* series7 = new QStackedBarSeries(this);

    QBarSeries* s5 = static_cast<QBarSeries*> (series5);
    s5->setCategories(QBarCategories());
    QPercentBarSeries* s6 = static_cast<QPercentBarSeries*> (series6);
    s6->setCategories(QBarCategories());
    QStackedBarSeries* s7 = static_cast<QStackedBarSeries*> (series7);
    s7->setCategories(QBarCategories());

    QAxis* axis = new QAxis(this);

    QTest::newRow("default axis: lineSeries") << series0 << (QAxis*) 0;
    QTest::newRow("axis0: lineSeries") << series0 << axis;
    QTest::newRow("default axis: areaSeries") << series1 << (QAxis*) 0;
    QTest::newRow("axis: areaSeries") << series1 << axis;
    QTest::newRow("default axis: scatterSeries") << series2 << (QAxis*) 0;
    QTest::newRow("axis1: scatterSeries") << series2 << axis;
    QTest::newRow("default axis: splineSeries") << series3 << (QAxis*) 0;
    QTest::newRow("axis: splineSeries") << series3 << axis;
    QTest::newRow("default axis: pieSeries") << series4 << (QAxis*) 0;
    QTest::newRow("axis: pieSeries") << series4 << axis;
    QTest::newRow("default axis: barSeries") << series5 << (QAxis*) 0;
    QTest::newRow("axis: barSeries") << series5 << axis;
    QTest::newRow("default axis: percentBarSeries") << series6 << (QAxis*) 0;
    QTest::newRow("axis: barSeries") << series6 << axis;
    QTest::newRow("default axis: stackedBarSeries") << series7 << (QAxis*) 0;
    QTest::newRow("axis: barSeries") << series7 << axis;

}

void tst_QChart::addSeries()
{
    QFETCH(QAbstractSeries *, series);
    QFETCH(QAxis *, axis);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    if(!axis) axis = m_chart->axisY();
    QVERIFY(!series->chart());
    m_chart->addSeries(series,axis);
    QVERIFY(series->chart() == m_chart);
    QCOMPARE(m_chart->axisY(series),axis);
    m_chart->removeSeries(series);
    QVERIFY(!series->chart());
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

}

void tst_QChart::axisX()
{
    QVERIFY(m_chart->axisX());
    QAxis* axis = m_chart->axisX();
    createTestData();
    //it should be the same axis
    QCOMPARE(axis,m_chart->axisX());
}

void tst_QChart::axisY_data()
{
    QTest::addColumn<QAxis*>("axis0");
    QTest::addColumn<QAxis*>("axis1");
    QTest::addColumn<QAxis*>("axis2");
    QTest::newRow("1 defualt, 2 optional") << (QAxis*)0 << new QAxis() << new QAxis();
    QTest::newRow("3 optional") << new QAxis() << new QAxis() << new QAxis();
}


void tst_QChart::axisY()
{
    QFETCH(QAxis*, axis0);
    QFETCH(QAxis*, axis1);
    QFETCH(QAxis*, axis2);

    QAxis* defaultAxisY = m_chart->axisY();

    QVERIFY2(defaultAxisY, "Missing axisY.");

    QLineSeries* series0 = new QLineSeries();
    m_chart->addSeries(series0, axis0);

    QLineSeries* series1 = new QLineSeries();
    m_chart->addSeries(series1, axis1);

    QLineSeries* series2 = new QLineSeries();
    m_chart->addSeries(series2, axis2);

    if (!axis0)
        axis0 = defaultAxisY;
    if (!axis1)
        axis1 = defaultAxisY;
    if (!axis2)
        axis2 = defaultAxisY;

    QVERIFY(m_chart->axisY(series0) == axis0);
    QVERIFY(m_chart->axisY(series1) == axis1);
    QVERIFY(m_chart->axisY(series2) == axis2);
}

void tst_QChart::backgroundBrush_data()
{
    QTest::addColumn<QBrush>("backgroundBrush");
    QTest::newRow("null") << QBrush();
    QTest::newRow("blue") << QBrush(Qt::blue);
    QTest::newRow("white") << QBrush(Qt::white);
    QTest::newRow("black") << QBrush(Qt::black);
}

void tst_QChart::backgroundBrush()
{
    QFETCH(QBrush, backgroundBrush);
    m_chart->setBackgroundBrush(backgroundBrush);
    QCOMPARE(m_chart->backgroundBrush(), backgroundBrush);
}

void tst_QChart::backgroundPen_data()
{
    QTest::addColumn<QPen>("backgroundPen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("white") << QPen(Qt::white);
    QTest::newRow("black") << QPen(Qt::black);
}


void tst_QChart::backgroundPen()
{
    QFETCH(QPen, backgroundPen);
    m_chart->setBackgroundPen(backgroundPen);
    QCOMPARE(m_chart->backgroundPen(), backgroundPen);
}

void tst_QChart::isBackgroundVisible_data()
{
    QTest::addColumn<bool>("isBackgroundVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QChart::isBackgroundVisible()
{
    QFETCH(bool, isBackgroundVisible);
    m_chart->setBackgroundVisible(isBackgroundVisible);
    QCOMPARE(m_chart->isBackgroundVisible(), isBackgroundVisible);
}

void tst_QChart::legend_data()
{

}

void tst_QChart::legend()
{
    QVERIFY(m_chart->legend());
}

void tst_QChart::margins_data()
{

}

void tst_QChart::margins()
{
    createTestData();
    QRectF rect = m_chart->geometry();

    QVERIFY(m_chart->margins().top()+m_chart->margins().bottom() < rect.height());
    QVERIFY(m_chart->margins().left()+m_chart->margins().right() < rect.width());
}

void tst_QChart::removeAllSeries_data()
{

}

void tst_QChart::removeAllSeries()
{
    QLineSeries* series0 = new QLineSeries(this);
    QLineSeries* series1 = new QLineSeries(this);
    QLineSeries* series2 = new QLineSeries(this);
    QSignalSpy deleteSpy1(series0, SIGNAL(destroyed()));
    QSignalSpy deleteSpy2(series1, SIGNAL(destroyed()));
    QSignalSpy deleteSpy3(series2, SIGNAL(destroyed()));

    m_chart->addSeries(series0);
    m_chart->addSeries(series1);
    m_chart->addSeries(series2);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    QVERIFY(m_chart->axisY(series0)!=0);
    QVERIFY(m_chart->axisY(series1)!=0);
    QVERIFY(m_chart->axisY(series2)!=0);

    m_chart->removeAllSeries();
    QVERIFY(m_chart->axisY(series0)==0);
    QVERIFY(m_chart->axisY(series1)==0);
    QVERIFY(m_chart->axisY(series2)==0);
    QCOMPARE(deleteSpy1.count(), 1);
    QCOMPARE(deleteSpy2.count(), 1);
    QCOMPARE(deleteSpy3.count(), 1);
}

void tst_QChart::removeSeries_data()
{
    addSeries_data();
}

void tst_QChart::removeSeries()
{
    QFETCH(QAbstractSeries *, series);
    QFETCH(QAxis *, axis);
    QSignalSpy deleteSpy(series, SIGNAL(destroyed()));
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    if(!axis) axis = m_chart->axisY();
    m_chart->addSeries(series,axis);
    QCOMPARE(m_chart->axisY(series),axis);
    m_chart->removeSeries(series);
    QVERIFY(m_chart->axisY(series)==0);
    QCOMPARE(deleteSpy.count(), 0);
}

void tst_QChart::scrollDown_data()
{

}

void tst_QChart::scrollDown()
{
    createTestData();
    qreal min = m_chart->axisY()->min();
    m_chart->scrollDown();
    QVERIFY(m_chart->axisY()->min()<min);
}

void tst_QChart::scrollLeft_data()
{

}

void tst_QChart::scrollLeft()
{
    createTestData();
    qreal min = m_chart->axisX()->min();
    m_chart->scrollLeft();
    QVERIFY(m_chart->axisX()->min()<min);
}

void tst_QChart::scrollRight_data()
{

}

void tst_QChart::scrollRight()
{
    createTestData();
    qreal min = m_chart->axisX()->min();
    m_chart->scrollRight();
    QVERIFY(m_chart->axisX()->min()>min);
}

void tst_QChart::scrollUp_data()
{

}

void tst_QChart::scrollUp()
{
    createTestData();
    qreal min = m_chart->axisY()->min();
    m_chart->scrollUp();
    QVERIFY(m_chart->axisY()->min()>min);
}

void tst_QChart::theme_data()
{
    QTest::addColumn<QChart::ChartTheme>("theme");
    QTest::newRow("ChartThemeBlueCerulean") << QChart::ChartThemeBlueCerulean;
    QTest::newRow("ChartThemeBlueIcy") << QChart::ChartThemeBlueIcy;
    QTest::newRow("ChartThemeBlueNcs") << QChart::ChartThemeBlueNcs;
    QTest::newRow("ChartThemeBrownSand") << QChart::ChartThemeBrownSand;
    QTest::newRow("ChartThemeDark") << QChart::ChartThemeDark;
    QTest::newRow("hartThemeHighContrast") << QChart::ChartThemeHighContrast;
    QTest::newRow("ChartThemeLight") << QChart::ChartThemeLight;
}

void tst_QChart::theme()
{
    QFETCH(QChart::ChartTheme, theme);
    createTestData();
    m_chart->setTheme(theme);
    QVERIFY(m_chart->theme()==theme);
}

void tst_QChart::title_data()
{
    QTest::addColumn<QString>("title");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

void tst_QChart::title()
{
    QFETCH(QString, title);
    m_chart->setTitle(title);
    QCOMPARE(m_chart->title(), title);
}

void tst_QChart::titleBrush_data()
{
    QTest::addColumn<QBrush>("titleBrush");
    QTest::newRow("null") << QBrush();
    QTest::newRow("blue") << QBrush(Qt::blue);
    QTest::newRow("white") << QBrush(Qt::white);
    QTest::newRow("black") << QBrush(Qt::black);
}

void tst_QChart::titleBrush()
{
    QFETCH(QBrush, titleBrush);
    m_chart->setTitleBrush(titleBrush);
    QCOMPARE(m_chart->titleBrush(), titleBrush);
}

void tst_QChart::titleFont_data()
{
    QTest::addColumn<QFont>("titleFont");
    QTest::newRow("null") << QFont();
    QTest::newRow("courier") << QFont("Courier", 8, QFont::Bold, true);
}

void tst_QChart::titleFont()
{
    QFETCH(QFont, titleFont);
    m_chart->setTitleFont(titleFont);
    QCOMPARE(m_chart->titleFont(), titleFont);
}

void tst_QChart::zoomIn_data()
{
    QTest::addColumn<QRectF>("rect");
    QTest::newRow("null") << QRectF();
    QTest::newRow("100x100") << QRectF(10,10,100,100);
    QTest::newRow("200x200") << QRectF(10,10,200,200);
}


void tst_QChart::zoomIn()
{
    QFETCH(QRectF, rect);
    createTestData();
    QRectF marigns = m_chart->margins();
    rect.adjust(marigns.left(),marigns.top(),-marigns.right(),-marigns.bottom());
    qreal minX = m_chart->axisX()->min();
    qreal minY = m_chart->axisY()->min();
    qreal maxX = m_chart->axisX()->max();
    qreal maxY = m_chart->axisY()->max();
    m_chart->zoomIn(rect);
    if(rect.isValid()){
        QVERIFY(minX<m_chart->axisX()->min());
        QVERIFY(maxX>m_chart->axisX()->max());
        QVERIFY(minY<m_chart->axisY()->min());
        QVERIFY(maxY>m_chart->axisY()->max());
    }
}

void tst_QChart::zoomOut_data()
{

}

void tst_QChart::zoomOut()
{
    createTestData();
    qreal minX = m_chart->axisX()->min();
    qreal minY = m_chart->axisY()->min();
    qreal maxX = m_chart->axisX()->max();
    qreal maxY = m_chart->axisY()->max();

    m_chart->zoomIn();

    QVERIFY(minX < m_chart->axisX()->min());
    QVERIFY(maxX > m_chart->axisX()->max());
    QVERIFY(minY < m_chart->axisY()->min());
    QVERIFY(maxY > m_chart->axisY()->max());

    m_chart->zoomOut();

    // min x may be a zero value
    if (qFuzzyIsNull(minX))
        QVERIFY(qFuzzyIsNull(m_chart->axisX()->min()));
    else
        QCOMPARE(minX, m_chart->axisX()->min());

    // min y may be a zero value
    if (qFuzzyIsNull(minY))
        QVERIFY(qFuzzyIsNull(m_chart->axisY()->min()));
    else
        QCOMPARE(minY, m_chart->axisY()->min());

    QVERIFY(maxX == m_chart->axisX()->max());
    QVERIFY(maxY == m_chart->axisY()->max());
}

QTEST_MAIN(tst_QChart)
#include "tst_qchart.moc"

