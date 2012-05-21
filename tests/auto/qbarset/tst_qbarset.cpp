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
#include <qbarset.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QBarSet : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qbarset_data();
    void qbarset();
    void name_data();
    void name();
    void append_data();
    void append();
    void appendOperator_data();
    void appendOperator();
    void insert_data();
    void insert();
    void remove_data();
    void remove();
    void replace_data();
    void replace();
    void at_data();
    void at();
    void atOperator_data();
    void atOperator();
    void count_data();
    void count();
    void sum_data();
    void sum();
    void setPen_data();
    void setPen();
    void setBrush_data();
    void setBrush();
    void setLabelPen_data();
    void setLabelPen();
    void setLabelBrush_data();
    void setLabelBrush();
    void setLabelFont_data();
    void setLabelFont();

private:
    QBarSet* m_barset;
};

void tst_QBarSet::initTestCase()
{
}

void tst_QBarSet::cleanupTestCase()
{
}

void tst_QBarSet::init()
{
     m_barset = new QBarSet(QString("Name"));
}

void tst_QBarSet::cleanup()
{
    delete m_barset;
    m_barset = 0;
}

void tst_QBarSet::qbarset_data()
{
}

void tst_QBarSet::qbarset()
{
    QBarSet barset(QString("Name"));
    QCOMPARE(barset.name(), QString("Name"));
    QCOMPARE(barset.count(), 0);
    QVERIFY(qFuzzyIsNull(barset.sum()));
}

void tst_QBarSet::name_data()
{
    QTest::addColumn<QString> ("name");
    QTest::addColumn<QString> ("result");
    QTest::newRow("name0") << QString("name0") << QString("name0");
    QTest::newRow("name1") << QString("name1") << QString("name1");
}

void tst_QBarSet::name()
{
    QFETCH(QString, name);
    QFETCH(QString, result);

    m_barset->setName(name);
    QCOMPARE(m_barset->name(), result);
}

void tst_QBarSet::append_data()
{
    QTest::addColumn<int> ("count");
    QTest::newRow("0") << 0;
    QTest::newRow("5") << 5;
    QTest::newRow("100") << 100;
    QTest::newRow("1000") << 1000;
}

void tst_QBarSet::append()
{
    QFETCH(int, count);

    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    qreal sum(0.0);
    qreal value(0.0);

    for (int i=0; i<count; i++) {
        m_barset->append(value);
        QCOMPARE(m_barset->at(i).y(), value);
        sum += value;
        value += 1.0;
    }

    QCOMPARE(m_barset->count(), count);
    QVERIFY(qFuzzyCompare(m_barset->sum(), sum));
}

void tst_QBarSet::appendOperator_data()
{
    append_data();
}

void tst_QBarSet::appendOperator()
{
    QFETCH(int, count);

    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    qreal sum(0.0);
    qreal value(0.0);

    for (int i=0; i<count; i++) {
        *m_barset << value;
        QCOMPARE(m_barset->at(i).y(), value);
        sum += value;
        value += 1.0;
    }

    QCOMPARE(m_barset->count(), count);
    QVERIFY(qFuzzyCompare(m_barset->sum(), sum));
}

void tst_QBarSet::insert_data()
{
}

void tst_QBarSet::insert()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->insert(0, 1.0);       // 1.0
    QCOMPARE(m_barset->at(0).y(), 1.0);
    QCOMPARE(m_barset->count(), 1);
    QVERIFY(qFuzzyCompare(m_barset->sum(), 1.0));

    m_barset->insert(0, 2.0);       // 2.0 1.0
    QCOMPARE(m_barset->at(0).y(), 2.0);
    QCOMPARE(m_barset->at(1).y(), 1.0);
    QCOMPARE(m_barset->count(), 2);
    QVERIFY(qFuzzyCompare(m_barset->sum(), 3.0));

    m_barset->insert(1, 3.0);       // 2.0 3.0 1.0
    QCOMPARE(m_barset->at(1).y(), 3.0);
    QCOMPARE(m_barset->at(0).y(), 2.0);
    QCOMPARE(m_barset->at(2).y(), 1.0);
    QCOMPARE(m_barset->count(), 3);
    QVERIFY(qFuzzyCompare(m_barset->sum(), 6.0));
}

void tst_QBarSet::remove_data()
{
}

void tst_QBarSet::remove()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->count(), 4);
    QCOMPARE(m_barset->sum(), 10.0);

    m_barset->remove(2);                // 1.0 2.0 4.0
    QCOMPARE(m_barset->at(0).y(), 1.0);
    QCOMPARE(m_barset->at(1).y(), 2.0);
    QCOMPARE(m_barset->at(2).y(), 4.0);
    QCOMPARE(m_barset->count(), 3);
    QCOMPARE(m_barset->sum(), 7.0);

    m_barset->remove(0);                // 2.0 4.0
    QCOMPARE(m_barset->at(0).y(), 2.0);
    QCOMPARE(m_barset->at(1).y(), 4.0);
    QCOMPARE(m_barset->count(), 2);
    QCOMPARE(m_barset->sum(), 6.0);
}

void tst_QBarSet::replace_data()
{

}

void tst_QBarSet::replace()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->count(), 4);
    QCOMPARE(m_barset->sum(), 10.0);

    m_barset->replace(0, 5.0);          // 5.0 2.0 3.0 4.0
    QCOMPARE(m_barset->count(), 4);
    QCOMPARE(m_barset->sum(), 14.0);
    QCOMPARE(m_barset->at(0).y(), 5.0);

    m_barset->replace(3, 6.0);
    QCOMPARE(m_barset->count(), 4);     // 5.0 2.0 3.0 6.0
    QCOMPARE(m_barset->sum(), 16.0);
    QCOMPARE(m_barset->at(0).y(), 5.0);
    QCOMPARE(m_barset->at(1).y(), 2.0);
    QCOMPARE(m_barset->at(2).y(), 3.0);
    QCOMPARE(m_barset->at(3).y(), 6.0);
}

void tst_QBarSet::at_data()
{

}

void tst_QBarSet::at()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->at(0).y(), 1.0);
    QCOMPARE(m_barset->at(1).y(), 2.0);
    QCOMPARE(m_barset->at(2).y(), 3.0);
    QCOMPARE(m_barset->at(3).y(), 4.0);
}

void tst_QBarSet::atOperator_data()
{

}

void tst_QBarSet::atOperator()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->operator [](0).y(), 1.0);
    QCOMPARE(m_barset->operator [](1).y(), 2.0);
    QCOMPARE(m_barset->operator [](2).y(), 3.0);
    QCOMPARE(m_barset->operator [](3).y(), 4.0);
}

void tst_QBarSet::count_data()
{

}

void tst_QBarSet::count()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    QCOMPARE(m_barset->count(),1);
    m_barset->append(2.0);
    QCOMPARE(m_barset->count(),2);
    m_barset->append(3.0);
    QCOMPARE(m_barset->count(),3);
    m_barset->append(4.0);
    QCOMPARE(m_barset->count(),4);
}

void tst_QBarSet::sum_data()
{

}

void tst_QBarSet::sum()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    QVERIFY(qFuzzyCompare(m_barset->sum(),1.0));
    m_barset->append(2.0);
    QVERIFY(qFuzzyCompare(m_barset->sum(),3.0));
    m_barset->append(3.0);
    QVERIFY(qFuzzyCompare(m_barset->sum(),6.0));
    m_barset->append(4.0);
    QVERIFY(qFuzzyCompare(m_barset->sum(),10.0));
}

void tst_QBarSet::setPen_data()
{

}

void tst_QBarSet::setPen()
{
    QVERIFY(m_barset->pen() == QPen());

    QPen pen;
    pen.setColor(QColor(128,128,128,128));
    m_barset->setPen(pen);

    QVERIFY(m_barset->pen() == pen);
}

void tst_QBarSet::setBrush_data()
{

}

void tst_QBarSet::setBrush()
{
    QVERIFY(m_barset->brush() == QBrush());

    QBrush brush;
    brush.setColor(QColor(128,128,128,128));
    m_barset->setBrush(brush);

    QVERIFY(m_barset->brush() == brush);
}

void tst_QBarSet::setLabelPen_data()
{

}

void tst_QBarSet::setLabelPen()
{
    QVERIFY(m_barset->labelPen() == QPen());

    QPen pen;
    pen.setColor(QColor(128,128,128,128));
    m_barset->setLabelPen(pen);

    QVERIFY(m_barset->labelPen() == pen);
}

void tst_QBarSet::setLabelBrush_data()
{

}

void tst_QBarSet::setLabelBrush()
{
    QVERIFY(m_barset->labelBrush() == QBrush());

    QBrush brush;
    brush.setColor(QColor(128,128,128,128));
    m_barset->setLabelBrush(brush);

    QVERIFY(m_barset->labelBrush() == brush);
}

void tst_QBarSet::setLabelFont_data()
{

}

void tst_QBarSet::setLabelFont()
{
    QVERIFY(m_barset->labelFont() == QFont());

    QFont font;
    font.setBold(true);
    font.setItalic(true);
    m_barset->setLabelFont(font);

    QVERIFY(m_barset->labelFont() == font);
}


QTEST_MAIN(tst_QBarSet)

#include "tst_qbarset.moc"

