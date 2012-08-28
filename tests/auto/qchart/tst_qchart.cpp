/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <qchartview.h>
#include <qlineseries.h>
#include <qareaseries.h>
#include <qscatterseries.h>
#include <qsplineseries.h>
#include <qpieseries.h>
#include <qabstractbarseries.h>
#include <qbarseries.h>
#include <qpercentbarseries.h>
#include <qstackedbarseries.h>
#include <qvalueaxis.h>
#include <qbarcategoryaxis.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractAxis *)
Q_DECLARE_METATYPE(QValueAxis *)
Q_DECLARE_METATYPE(QBarCategoryAxis *)
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
    void plotArea_data();
    void plotArea();
    void removeAllSeries_data();
    void removeAllSeries();
    void removeSeries_data();
    void removeSeries();
    void scroll_right_data();
    void scroll_right();
    void scroll_left_data();
    void scroll_left();
    void scroll_up_data();
    void scroll_up();
    void scroll_down_data();
    void scroll_down();
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

void tst_QChart::cleanup()
{
    delete m_view;
    m_view = 0;
    m_chart = 0;
}


void tst_QChart::createTestData()
{
     QLineSeries* series0 = new QLineSeries(this);
     *series0 << QPointF(0, 0) << QPointF(100, 100);
     m_chart->addSeries(series0);
     m_view->show();
     QTest::qWaitForWindowShown(m_view);
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
    QVERIFY(!m_chart->axisX());
    QVERIFY(!m_chart->axisY());
    QVERIFY(m_chart->backgroundBrush()!=QBrush());
    QVERIFY(m_chart->backgroundPen()!=QPen());
    QCOMPARE(m_chart->isBackgroundVisible(), true);
    QVERIFY(m_chart->plotArea().top()==0);
    QVERIFY(m_chart->plotArea().left()==0);
    QVERIFY(m_chart->plotArea().right()==0);
    QVERIFY(m_chart->plotArea().bottom()==0);
    QCOMPARE(m_chart->theme(), QChart::ChartThemeLight);
    QCOMPARE(m_chart->title(), QString());

    //QCOMPARE(m_chart->titleBrush(),QBrush());
    //QCOMPARE(m_chart->titleFont(),QFont());

    m_chart->removeAllSeries();
    m_chart->scroll(0,0);

    m_chart->zoomIn();
    m_chart->zoomIn(QRectF());
    m_chart->zoomOut();

    m_view->show();

    QVERIFY(m_chart->plotArea().top()>0);
    QVERIFY(m_chart->plotArea().left()>0);
    QVERIFY(m_chart->plotArea().right()>0);
    QVERIFY(m_chart->plotArea().bottom()>0);
}

void tst_QChart::addSeries_data()
{
    QTest::addColumn<QAbstractSeries *>("series");

    QAbstractSeries* line = new QLineSeries(this);
    QAbstractSeries* area = new QAreaSeries(static_cast<QLineSeries*>(line));
    QAbstractSeries* scatter = new QScatterSeries(this);
    QAbstractSeries* spline = new QSplineSeries(this);
    QAbstractSeries* pie = new QPieSeries(this);
    QAbstractSeries* bar = new QBarSeries(this);
    QAbstractSeries* percent = new QPercentBarSeries(this);
    QAbstractSeries* stacked = new QStackedBarSeries(this);

    QTest::newRow("lineSeries") << line;
    QTest::newRow("areaSeries") << area;
    QTest::newRow("scatterSeries") << scatter;
    QTest::newRow("splineSeries") << spline;
    QTest::newRow("pieSeries") << pie;
    QTest::newRow("barSeries") << bar;
    QTest::newRow("percentBarSeries") << percent;
    QTest::newRow("stackedBarSeries") << stacked;

}

void tst_QChart::addSeries()
{
    QFETCH(QAbstractSeries *, series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QVERIFY(!series->chart());
    QCOMPARE(m_chart->series().count(), 0);
    m_chart->addSeries(series);
    QCOMPARE(m_chart->series().count(), 1);
    QCOMPARE(m_chart->series().first(), series);
    QVERIFY(series->chart() == m_chart);
    m_chart->createDefaultAxes();
    if(series->type()!=QAbstractSeries::SeriesTypePie){
        QVERIFY(m_chart->axisY(series));
        QVERIFY(m_chart->axisX(series));
    }else{
        QVERIFY(!m_chart->axisY(series));
        QVERIFY(!m_chart->axisX(series));
    }
    m_chart->removeSeries(series);
    QVERIFY(!series->chart());
    QCOMPARE(m_chart->series().count(), 0);
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

    QTest::addColumn<QAbstractAxis*>("axis");
    QTest::addColumn<QAbstractSeries *>("series");

    QTest::newRow("categories,lineSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QLineSeries(this);
    QTest::newRow("categories,areaSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QAreaSeries(new QLineSeries(this));
    QTest::newRow("categories,scatterSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QScatterSeries(this);
    QTest::newRow("categories,splineSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QSplineSeries(this);
    QTest::newRow("categories,pieSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QPieSeries(this);
    QTest::newRow("categories,barSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QBarSeries(this);
    QTest::newRow("categories,percentBarSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QPercentBarSeries(this);
    QTest::newRow("categories,stackedBarSeries") <<  (QAbstractAxis*) new QBarCategoryAxis() << (QAbstractSeries*) new QStackedBarSeries(this);

    QTest::newRow("value,lineSeries") << (QAbstractAxis*) new QValueAxis() << (QAbstractSeries*) new QLineSeries(this);
    QTest::newRow("value,areaSeries") << (QAbstractAxis*) new QValueAxis() << (QAbstractSeries*) new QAreaSeries(new QLineSeries(this));
    QTest::newRow("value,scatterSeries") << (QAbstractAxis*) new QValueAxis() << (QAbstractSeries*) new QScatterSeries(this);
    QTest::newRow("value,splineSeries") << (QAbstractAxis*) new QValueAxis() <<  (QAbstractSeries*) new QSplineSeries(this);
    QTest::newRow("value,pieSeries") << (QAbstractAxis*) new QValueAxis() << (QAbstractSeries*) new QPieSeries(this);
    QTest::newRow("value,barSeries") << (QAbstractAxis*) new QValueAxis() <<   (QAbstractSeries*) new QBarSeries(this);
    QTest::newRow("value,percentBarSeries") << (QAbstractAxis*) new QValueAxis() << (QAbstractSeries*) new QPercentBarSeries(this);
    QTest::newRow("value,stackedBarSeries") << (QAbstractAxis*) new QValueAxis() << (QAbstractSeries*) new QStackedBarSeries(this);

}

void tst_QChart::axisX()
{
    QFETCH(QAbstractAxis*, axis);
    QFETCH(QAbstractSeries*, series);
    QVERIFY(!m_chart->axisX());
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    m_chart->addSeries(series);
    m_chart->setAxisX(axis,series);
    QVERIFY(m_chart->axisX(series)==axis);
}

void tst_QChart::axisY_data()
{
    axisX_data();
}


void tst_QChart::axisY()
{
    QFETCH(QAbstractAxis*, axis);
    QFETCH(QAbstractSeries*, series);
    QVERIFY(!m_chart->axisY());
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    m_chart->addSeries(series);
    m_chart->setAxisY(axis,series);
    QVERIFY(m_chart->axisY(series)==axis);
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
    QLegend *legend = m_chart->legend();
    QVERIFY(legend);

    // Colors related signals
    QSignalSpy colorSpy(legend, SIGNAL(colorChanged(QColor)));
    QSignalSpy borderColorSpy(legend, SIGNAL(borderColorChanged(QColor)));
    QSignalSpy labelColorSpy(legend, SIGNAL(labelColorChanged(QColor)));

    // colorChanged
    legend->setColor(QColor("aliceblue"));
    QCOMPARE(colorSpy.count(), 1);
    QBrush b = legend->brush();
    b.setColor(QColor("aqua"));
    legend->setBrush(b);
    QCOMPARE(colorSpy.count(), 2);

    // borderColorChanged
    legend->setBorderColor(QColor("aliceblue"));
    QCOMPARE(borderColorSpy.count(), 1);
    QPen p = legend->pen();
    p.setColor(QColor("aqua"));
    legend->setPen(p);
    QCOMPARE(borderColorSpy.count(), 2);

    // labelColorChanged
    legend->setLabelColor(QColor("lightsalmon"));
    QCOMPARE(labelColorSpy.count(), 1);
    b = legend->labelBrush();
    b.setColor(QColor("lightseagreen"));
    legend->setLabelBrush(b);
    QCOMPARE(labelColorSpy.count(), 2);

    // fontChanged
    QSignalSpy fontSpy(legend, SIGNAL(fontChanged(QFont)));
    QFont f = legend->font();
    f.setBold(!f.bold());
    legend->setFont(f);
    QCOMPARE(fontSpy.count(), 1);
}

void tst_QChart::plotArea_data()
{

}

void tst_QChart::plotArea()
{
    createTestData();
    QRectF rect = m_chart->geometry();
    QVERIFY(m_chart->plotArea().isValid());
    QVERIFY(m_chart->plotArea().height() < rect.height());
    QVERIFY(m_chart->plotArea().width() < rect.width());
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
    m_chart->createDefaultAxes();
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
    axisX_data();
}

void tst_QChart::removeSeries()
{
    QFETCH(QAbstractAxis *, axis);
    QFETCH(QAbstractSeries *, series);
    QSignalSpy deleteSpy(series, SIGNAL(destroyed()));
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    if(!axis) axis = m_chart->axisY();
    m_chart->addSeries(series);
    m_chart->setAxisY(axis,series);
    QCOMPARE(m_chart->axisY(series),axis);
    m_chart->removeSeries(series);
    QVERIFY(m_chart->axisY(series)==0);
    QCOMPARE(deleteSpy.count(), 0);
}

void tst_QChart::scroll_right_data()
{
	 QTest::addColumn<QAbstractSeries *>("series");

	 QLineSeries* series0 = new QLineSeries(this);
	 *series0 << QPointF(0, 0) << QPointF(100, 100);

     QTest::newRow("lineSeries") << (QAbstractSeries*) series0;


}

void tst_QChart::scroll_right()
{
    QFETCH(QAbstractSeries *, series);
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QAbstractAxis * axis = m_chart->axisX();
    QVERIFY(axis!=0);

    switch(axis->type())
    {
        case QAbstractAxis::AxisTypeValue:{
            QValueAxis* vaxis = qobject_cast<QValueAxis*>(axis);
    		QVERIFY(vaxis!=0);
    		qreal min = vaxis->min();
    		qreal max = vaxis->max();
    		QVERIFY(max>min);
    		m_chart->scroll(50, 0);
    		QVERIFY(min<vaxis->min());
    		QVERIFY(max<vaxis->max());
    		break;
    	}
        case QAbstractAxis::AxisTypeBarCategory:{
            QBarCategoryAxis* caxis = qobject_cast<QBarCategoryAxis*>(axis);
    	   	QVERIFY(caxis!=0);
    	   	qreal min = caxis->min().toDouble();
    	   	qreal max = caxis->max().toDouble();
    	   	m_chart->scroll(50, 0);
    	   	QVERIFY(min<caxis->min().toDouble());
    	   	QVERIFY(max<caxis->max().toDouble());
    		break;
    	}
    	default:
    		qFatal("Unsupported type");
    		break;
    }
}

void tst_QChart::scroll_left_data()
{
	scroll_right_data();
}

void tst_QChart::scroll_left()
{
	 QFETCH(QAbstractSeries *, series);
	 m_chart->addSeries(series);
	 m_chart->createDefaultAxes();
	 m_view->show();
	 QTest::qWaitForWindowShown(m_view);
	 QAbstractAxis * axis = m_chart->axisX();
	 QVERIFY(axis!=0);

	 switch(axis->type())
	    {
            case QAbstractAxis::AxisTypeValue:{
                QValueAxis* vaxis = qobject_cast<QValueAxis*>(axis);
	    		QVERIFY(vaxis!=0);
	    		qreal min = vaxis->min();
	    		qreal max = vaxis->max();
	    		m_chart->scroll(-50, 0);
	    		QVERIFY(min>vaxis->min());
	    		QVERIFY(max>vaxis->max());
	    		break;
	    	}
            case QAbstractAxis::AxisTypeBarCategory:{
                QBarCategoryAxis* caxis = qobject_cast<QBarCategoryAxis*>(axis);
	    	   	QVERIFY(caxis!=0);
	    	   	qreal min = caxis->min().toDouble();
	    	   	qreal max = caxis->max().toDouble();
	    	   	m_chart->scroll(-50, 0);
	    	   	QVERIFY(min>caxis->min().toDouble());
	    	   	QVERIFY(max>caxis->max().toDouble());
	    		break;
	    	}
	    	default:
	    		qFatal("Unsupported type");
	    		break;
	    }
}

void tst_QChart::scroll_up_data()
{
	scroll_right_data();
}

void tst_QChart::scroll_up()
{
    QFETCH(QAbstractSeries *, series);
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QAbstractAxis * axis = m_chart->axisY();
    QVERIFY(axis!=0);

    switch(axis->type())
    {
        case QAbstractAxis::AxisTypeValue:{
            QValueAxis* vaxis = qobject_cast<QValueAxis*>(axis);
    		QVERIFY(vaxis!=0);
    		qreal min = vaxis->min();
    		qreal max = vaxis->max();
    		m_chart->scroll(0, 50);
    		QVERIFY(min<vaxis->min());
    		QVERIFY(max<vaxis->max());
    		break;
    	}
        case QAbstractAxis::AxisTypeBarCategory:{
            QBarCategoryAxis* caxis = qobject_cast<QBarCategoryAxis*>(axis);
    	   	QVERIFY(caxis!=0);
    	   	qreal min = caxis->min().toDouble();
    	   	qreal max = caxis->max().toDouble();
    	   	m_chart->scroll(0, 50);
    	   	QVERIFY(min<caxis->min().toDouble());
    	   	QVERIFY(max<caxis->max().toDouble());
    		break;
    	}
    	default:
    		qFatal("Unsupported type");
    		break;
    }
}

void tst_QChart::scroll_down_data()
{
	scroll_right_data();
}

void tst_QChart::scroll_down()
{
	 QFETCH(QAbstractSeries *, series);
	 m_chart->addSeries(series);
	 m_chart->createDefaultAxes();
	 m_view->show();
	 QTest::qWaitForWindowShown(m_view);
	 QAbstractAxis * axis = m_chart->axisY();
	 QVERIFY(axis!=0);

	 switch(axis->type())
	    {
            case QAbstractAxis::AxisTypeValue:{
                QValueAxis* vaxis = qobject_cast<QValueAxis*>(axis);
	    		QVERIFY(vaxis!=0);
	    		qreal min = vaxis->min();
	    		qreal max = vaxis->max();
	    		m_chart->scroll(0, -50);
	    		QVERIFY(min>vaxis->min());
	    		QVERIFY(max>vaxis->max());
	    		break;
	    	}
            case QAbstractAxis::AxisTypeBarCategory:{
                QBarCategoryAxis* caxis = qobject_cast<QBarCategoryAxis*>(axis);
	    	   	QVERIFY(caxis!=0);
	    	   	qreal min = caxis->min().toDouble();
	    	   	qreal max = caxis->max().toDouble();
	    	   	m_chart->scroll(0, -50);
	    	   	QVERIFY(min>caxis->min().toDouble());
	    	   	QVERIFY(max>caxis->max().toDouble());
	    		break;
	    	}
	    	default:
	    		qFatal("Unsupported type");
	    		break;
	    }
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
    m_chart->createDefaultAxes();
    QRectF marigns = m_chart->plotArea();
    rect.adjust(marigns.left(),marigns.top(),-marigns.right(),-marigns.bottom());
    QValueAxis* axisX = qobject_cast<QValueAxis*>(m_chart->axisX());
    QVERIFY(axisX!=0);
    QValueAxis* axisY = qobject_cast<QValueAxis*>(m_chart->axisY());
    QVERIFY(axisY!=0);
    qreal minX = axisX->min();
    qreal minY = axisY->min();
    qreal maxX = axisX->max();
    qreal maxY = axisY->max();
    m_chart->zoomIn(rect);
    if(rect.isValid()){
        QVERIFY(minX<axisX->min());
        QVERIFY(maxX>axisX->max());
        QVERIFY(minY<axisY->min());
        QVERIFY(maxY>axisY->max());
    }

}

void tst_QChart::zoomOut_data()
{

}

void tst_QChart::zoomOut()
{
    createTestData();
    m_chart->createDefaultAxes();

    QValueAxis* axisX = qobject_cast<QValueAxis*>(m_chart->axisX());
    QVERIFY(axisX!=0);
    QValueAxis* axisY = qobject_cast<QValueAxis*>(m_chart->axisY());
    QVERIFY(axisY!=0);

    qreal minX = axisX->min();
    qreal minY = axisY->min();
    qreal maxX = axisX->max();
    qreal maxY = axisY->max();

    m_chart->zoomIn();

    QVERIFY(minX < axisX->min());
    QVERIFY(maxX > axisX->max());
    QVERIFY(minY < axisY->min());
    QVERIFY(maxY > axisY->max());

    m_chart->zoomOut();

    // min x may be a zero value
    if (qFuzzyIsNull(minX))
        QVERIFY(qFuzzyIsNull(axisX->min()));
    else
        QCOMPARE(minX, axisX->min());

    // min y may be a zero value
    if (qFuzzyIsNull(minY))
        QVERIFY(qFuzzyIsNull(axisY->min()));
    else
        QCOMPARE(minY, axisY->min());

    QVERIFY(maxX == axisX->max());
    QVERIFY(maxY == axisY->max());

}

QTEST_MAIN(tst_QChart)
#include "tst_qchart.moc"

