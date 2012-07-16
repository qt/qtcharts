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

#include "tst_qabstractaxis.h"

Q_DECLARE_METATYPE(QPen)

void tst_QAbstractAxis::initTestCase()
{
}

void tst_QAbstractAxis::cleanupTestCase()
{
}

void tst_QAbstractAxis::init(QAbstractAxis* axis)
{
    m_axis = axis;
    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
}

void tst_QAbstractAxis::cleanup()
{

    delete m_view;
    m_view = 0;
    m_chart = 0;
    m_axis = 0;
}

void tst_QAbstractAxis::qabstractaxis()
{
    QCOMPARE(m_axis->axisPen(), QPen());
    //TODO QCOMPARE(m_axis->axisPenColor(), QColor());
    QCOMPARE(m_axis->gridLinePen(), QPen());
    QCOMPARE(m_axis->isArrowVisible(), true);
    QCOMPARE(m_axis->isGridLineVisible(), true);
    QCOMPARE(m_axis->isVisible(), false);
    QCOMPARE(m_axis->labelsAngle(), 0);
    QCOMPARE(m_axis->labelsBrush(), QBrush());
    //TODO QCOMPARE(m_axis->labelsColor(), QColor());
    QCOMPARE(m_axis->labelsFont(), QFont());
    QCOMPARE(m_axis->labelsPen(), QPen());
    QCOMPARE(m_axis->labelsVisible(), true);
    QCOMPARE(m_axis->orientation(), Qt::Orientation(0));
    m_axis->setArrowVisible(false);
    m_axis->setAxisPen(QPen());
    m_axis->setAxisPenColor(QColor());
    m_axis->setGridLinePen(QPen());
    m_axis->setGridLineVisible(false);
    m_axis->setLabelsAngle(-1);
    m_axis->setLabelsBrush(QBrush());
    m_axis->setLabelsColor(QColor());
    m_axis->setLabelsFont(QFont());
    m_axis->setLabelsPen(QPen());
    m_axis->setLabelsVisible(false);
    m_axis->setMax(QVariant());
    m_axis->setMin(QVariant());
    m_axis->setRange(QVariant(), QVariant());
    m_axis->setShadesBorderColor(QColor());
    m_axis->setShadesBrush(QBrush());
    m_axis->setShadesColor(QColor());
    m_axis->setShadesPen(QPen());
    m_axis->setShadesVisible(false);
    m_axis->setVisible(false);
    //TODO QCOMPARE(m_axis->shadesBorderColor(), QColor());
    //TODO QCOMPARE(m_axis->shadesBrush(), QBrush());
    //TODO QCOMPARE(m_axis->shadesColor(), QColor());
    QCOMPARE(m_axis->shadesPen(), QPen());
    QCOMPARE(m_axis->shadesVisible(), false);
    m_axis->show();
    m_axis->hide();
}

void tst_QAbstractAxis::axisPen_data()
{
    QTest::addColumn<QPen>("axisPen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);
}

void tst_QAbstractAxis::axisPen()
{

    QFETCH(QPen, axisPen);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setAxisPen(axisPen);
    QCOMPARE(m_axis->axisPen(), axisPen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

}

void tst_QAbstractAxis::axisPenColor_data()
{
#if 0
    QTest::addColumn<QColor>("axisPenColor");
    QTest::newRow("null") << QColor();
#endif
}

void tst_QAbstractAxis::axisPenColor()
{
#if 0
    QFETCH(QColor, axisPenColor);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.axisPenColor(), axisPenColor);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::gridLinePen_data()
{

    QTest::addColumn<QPen>("gridLinePen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);

}

void tst_QAbstractAxis::gridLinePen()
{
    QFETCH(QPen, gridLinePen);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setGridLinePen(gridLinePen);
    QCOMPARE(m_axis->gridLinePen(), gridLinePen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

}

void tst_QAbstractAxis::hide_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void hide()
void tst_QAbstractAxis::hide()
{
#if 0
    QFETCH(int, foo);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.hide();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::isArrowVisible_data()
{
    QTest::addColumn<bool>("isArrowVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool isArrowVisible() const
void tst_QAbstractAxis::isArrowVisible()
{
#if 0
    QFETCH(bool, isArrowVisible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.isArrowVisible(), isArrowVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::isGridLineVisible_data()
{
    QTest::addColumn<bool>("isGridLineVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool isGridLineVisible() const
void tst_QAbstractAxis::isGridLineVisible()
{
#if 0
    QFETCH(bool, isGridLineVisible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.isGridLineVisible(), isGridLineVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::isVisible_data()
{
    QTest::addColumn<bool>("isVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool isVisible() const
void tst_QAbstractAxis::isVisible()
{
#if 0
    QFETCH(bool, isVisible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.isVisible(), isVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::labelsAngle_data()
{
    QTest::addColumn<int>("labelsAngle");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public int labelsAngle() const
void tst_QAbstractAxis::labelsAngle()
{
#if 0
    QFETCH(int, labelsAngle);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.labelsAngle(), labelsAngle);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QBrush)
void tst_QAbstractAxis::labelsBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("labelsBrush");
    QTest::newRow("null") << QBrush();
#endif
}

// public QBrush labelsBrush() const
void tst_QAbstractAxis::labelsBrush()
{
#if 0
    QFETCH(QBrush, labelsBrush);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.labelsBrush(), labelsBrush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::labelsColor_data()
{
#if 0
    QTest::addColumn<QColor>("labelsColor");
    QTest::newRow("null") << QColor();
#endif
}

// public QColor labelsColor() const
void tst_QAbstractAxis::labelsColor()
{
#if 0
    QFETCH(QColor, labelsColor);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.labelsColor(), labelsColor);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::labelsFont_data()
{
    QTest::addColumn<QFont>("labelsFont");
    QTest::newRow("null") << QFont();
}

// public QFont labelsFont() const
void tst_QAbstractAxis::labelsFont()
{
#if 0
    QFETCH(QFont, labelsFont);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.labelsFont(), labelsFont);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::labelsPen_data()
{
#if 0
    QTest::addColumn<QPen>("labelsPen");
    QTest::newRow("null") << QPen();
#endif
}

// public QPen labelsPen() const
void tst_QAbstractAxis::labelsPen()
{
#if 0
    QFETCH(QPen, labelsPen);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.labelsPen(), labelsPen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::labelsVisible_data()
{
    QTest::addColumn<bool>("labelsVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool labelsVisible() const
void tst_QAbstractAxis::labelsVisible()
{
#if 0
    QFETCH(bool, labelsVisible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.labelsVisible(), labelsVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(Qt::Orientation)
void tst_QAbstractAxis::orientation_data()
{
#if 0
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::newRow("null") << Qt::Orientation();
#endif
}

// public Qt::Orientation orientation()
void tst_QAbstractAxis::orientation()
{
#if 0
    QFETCH(Qt::Orientation, orientation);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.orientation(), orientation);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setArrowVisible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setArrowVisible(bool visible = true)
void tst_QAbstractAxis::setArrowVisible()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setArrowVisible(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setAxisPen_data()
{
#if 0
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
#endif
}

// public void setAxisPen(QPen const& pen)
void tst_QAbstractAxis::setAxisPen()
{
#if 0
    QFETCH(QPen, pen);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setAxisPen(pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setAxisPenColor_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// public void setAxisPenColor(QColor color)
void tst_QAbstractAxis::setAxisPenColor()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setAxisPenColor(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setGridLinePen_data()
{
#if 0
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
#endif
}

// public void setGridLinePen(QPen const& pen)
void tst_QAbstractAxis::setGridLinePen()
{
#if 0
    QFETCH(QPen, pen);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setGridLinePen(pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setGridLineVisible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setGridLineVisible(bool visible = true)
void tst_QAbstractAxis::setGridLineVisible()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setGridLineVisible(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setLabelsAngle_data()
{
    QTest::addColumn<int>("angle");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void setLabelsAngle(int angle)
void tst_QAbstractAxis::setLabelsAngle()
{
#if 0
    QFETCH(int, angle);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setLabelsAngle(angle);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setLabelsBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("brush");
    QTest::newRow("null") << QBrush();
#endif
}

// public void setLabelsBrush(QBrush const& brush)
void tst_QAbstractAxis::setLabelsBrush()
{
#if 0
    QFETCH(QBrush, brush);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setLabelsBrush(brush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setLabelsColor_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// public void setLabelsColor(QColor color)
void tst_QAbstractAxis::setLabelsColor()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setLabelsColor(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setLabelsFont_data()
{
    QTest::addColumn<QFont>("font");
    QTest::newRow("null") << QFont();
}

// public void setLabelsFont(QFont const& font)
void tst_QAbstractAxis::setLabelsFont()
{
#if 0
    QFETCH(QFont, font);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setLabelsFont(font);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setLabelsPen_data()
{
#if 0
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
#endif
}

// public void setLabelsPen(QPen const& pen)
void tst_QAbstractAxis::setLabelsPen()
{
#if 0
    QFETCH(QPen, pen);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setLabelsPen(pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setLabelsVisible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setLabelsVisible(bool visible = true)
void tst_QAbstractAxis::setLabelsVisible()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setLabelsVisible(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QVariant)
void tst_QAbstractAxis::setMax_data()
{
#if 0
    QTest::addColumn<QVariant>("max");
    QTest::newRow("null") << QVariant();
#endif
}

// public void setMax(QVariant const& max)
void tst_QAbstractAxis::setMax()
{
#if 0
    QFETCH(QVariant, max);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setMax(max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setMin_data()
{
#if 0
    QTest::addColumn<QVariant>("min");
    QTest::newRow("null") << QVariant();
#endif
}

// public void setMin(QVariant const& min)
void tst_QAbstractAxis::setMin()
{
#if 0
    QFETCH(QVariant, min);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setMin(min);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setRange_data()
{
#if 0
    QTest::addColumn<QVariant>("min");
    QTest::addColumn<QVariant>("max");
    QTest::newRow("null") << QVariant() << QVariant();
#endif
}

// public void setRange(QVariant const& min, QVariant const& max)
void tst_QAbstractAxis::setRange()
{
#if 0
    QFETCH(QVariant, min);
    QFETCH(QVariant, max);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setRange(min, max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setShadesBorderColor_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// public void setShadesBorderColor(QColor color)
void tst_QAbstractAxis::setShadesBorderColor()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setShadesBorderColor(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setShadesBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("brush");
    QTest::newRow("null") << QBrush();
#endif
}

// public void setShadesBrush(QBrush const& brush)
void tst_QAbstractAxis::setShadesBrush()
{
#if 0
    QFETCH(QBrush, brush);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setShadesBrush(brush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setShadesColor_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// public void setShadesColor(QColor color)
void tst_QAbstractAxis::setShadesColor()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setShadesColor(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setShadesPen_data()
{
#if 0
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
#endif
}

// public void setShadesPen(QPen const& pen)
void tst_QAbstractAxis::setShadesPen()
{
#if 0
    QFETCH(QPen, pen);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setShadesPen(pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setShadesVisible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setShadesVisible(bool visible = true)
void tst_QAbstractAxis::setShadesVisible()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setShadesVisible(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::setVisible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setVisible(bool visible = true)
void tst_QAbstractAxis::setVisible()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.setVisible(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesBorderColor_data()
{
#if 0
    QTest::addColumn<QColor>("shadesBorderColor");
    QTest::newRow("null") << QColor();
#endif
}

// public QColor shadesBorderColor() const
void tst_QAbstractAxis::shadesBorderColor()
{
#if 0
    QFETCH(QColor, shadesBorderColor);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.shadesBorderColor(), shadesBorderColor);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("shadesBrush");
    QTest::newRow("null") << QBrush();
#endif
}

// public QBrush shadesBrush() const
void tst_QAbstractAxis::shadesBrush()
{
#if 0
    QFETCH(QBrush, shadesBrush);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.shadesBrush(), shadesBrush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesColor_data()
{
#if 0
    QTest::addColumn<QColor>("shadesColor");
    QTest::newRow("null") << QColor();
#endif
}

// public QColor shadesColor() const
void tst_QAbstractAxis::shadesColor()
{
#if 0
    QFETCH(QColor, shadesColor);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.shadesColor(), shadesColor);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesPen_data()
{
#if 0
    QTest::addColumn<QPen>("shadesPen");
    QTest::newRow("null") << QPen();
#endif
}

// public QPen shadesPen() const
void tst_QAbstractAxis::shadesPen()
{
#if 0
    QFETCH(QPen, shadesPen);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.shadesPen(), shadesPen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesVisible_data()
{
    QTest::addColumn<bool>("shadesVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool shadesVisible() const
void tst_QAbstractAxis::shadesVisible()
{
#if 0
    QFETCH(bool, shadesVisible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.shadesVisible(), shadesVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::show_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void show()
void tst_QAbstractAxis::show()
{
#if 0
    QFETCH(int, foo);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.show();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QAbstractAxis::AxisType)
void tst_QAbstractAxis::type_data()
{
#if 0
    QTest::addColumn<QAbstractAxis::AxisType>("type");
    QTest::newRow("null") << QAbstractAxis::AxisType();
#endif
}

// public QAbstractAxis::AxisType type() const
void tst_QAbstractAxis::type()
{
#if 0
    QFETCH(QAbstractAxis::AxisType, type);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    QCOMPARE(axis.type(), type);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::arrowVisibleChanged_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// protected void arrowVisibleChanged(bool visible)
void tst_QAbstractAxis::arrowVisibleChanged()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_arrowVisibleChanged(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::colorChanged_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// protected void colorChanged(QColor color)
void tst_QAbstractAxis::colorChanged()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_colorChanged(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::gridVisibleChanged_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// protected void gridVisibleChanged(bool visible)
void tst_QAbstractAxis::gridVisibleChanged()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_gridVisibleChanged(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::labelsColorChanged_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// protected void labelsColorChanged(QColor color)
void tst_QAbstractAxis::labelsColorChanged()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_labelsColorChanged(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::labelsVisibleChanged_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// protected void labelsVisibleChanged(bool visible)
void tst_QAbstractAxis::labelsVisibleChanged()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_labelsVisibleChanged(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesBorderColorChanged_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// protected void shadesBorderColorChanged(QColor color)
void tst_QAbstractAxis::shadesBorderColorChanged()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_shadesBorderColorChanged(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesColorChanged_data()
{
#if 0
    QTest::addColumn<QColor>("color");
    QTest::newRow("null") << QColor();
#endif
}

// protected void shadesColorChanged(QColor color)
void tst_QAbstractAxis::shadesColorChanged()
{
#if 0
    QFETCH(QColor, color);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_shadesColorChanged(color);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::shadesVisibleChanged_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// protected void shadesVisibleChanged(bool visible)
void tst_QAbstractAxis::shadesVisibleChanged()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_shadesVisibleChanged(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QAbstractAxis::visibleChanged_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// protected void visibleChanged(bool visible)
void tst_QAbstractAxis::visibleChanged()
{
#if 0
    QFETCH(bool, visible);

    SubQAbstractAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(&axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(&axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(&axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(&axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(&axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(&axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(&axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(&axis, SIGNAL(visibleChanged(bool)));

    axis.call_visibleChanged(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}
