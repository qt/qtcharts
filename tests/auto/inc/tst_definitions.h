// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef TST_DEFINITIONS_H
#define TST_DEFINITIONS_H

#include <QtCharts/qpolarchart.h>
#include <QtTest/QtTest>
#include <QtWidgets/QPushButton>

#define TRY_COMPARE(actual, expected) { \
    do { \
        const int timeout(1000); \
        const int waitStep(30); \
        /* always wait before comparing to catch possible extra signals */ \
        QTest::qWait(waitStep); \
        for (int time(0); (actual != expected) && (time < timeout); time += waitStep) \
            QTest::qWait(waitStep); \
        QCOMPARE(actual, expected); \
    } while (0); \
}

// Some bamboo clients have trouble passing mouse events to the test application.
// This can be used to skip those tests so that they don't show up as a failure
// in the test report.
    #define SKIP_IF_CANNOT_TEST_MOUSE_EVENTS() { \
        do { \
            QPushButton b; \
            b.resize(120, 100); \
            b.show(); \
            QVERIFY(QTest::qWaitForWindowExposed(&b)); \
            QSignalSpy spy(&b, SIGNAL(clicked())); \
            QTest::mouseClick(&b, Qt::LeftButton, {}, b.rect().center()); \
            QApplication::processEvents(); \
            if (spy.count() == 0) \
                QSKIP("Cannot test mouse events in this environment"); \
        } while (0); \
        QApplication::processEvents(); \
    }

    #define SKIP_ON_POLAR() { \
        if (isPolarTest()) \
            QSKIP("Test not supported by polar chart"); \
        }

    #define SKIP_ON_CARTESIAN() { \
        if (!isPolarTest()) \
            QSKIP("Test not supported by cartesian chart"); \
        }

// Synthetic mouse moves do not trigger hover events reliably in many virtual machines,
// so we skip tests involving mouse moves.
    #define SKIP_IF_FLAKY_MOUSE_MOVE() { \
        QSKIP("Skipping test with synthetic mouse moves."); \
    }

static inline bool isPolarTest()
{
    static bool isPolar = false;
    static bool polarEnvChecked = false;
    if (!polarEnvChecked) {
        isPolar = !(qgetenv("TEST_POLAR_CHART").isEmpty());
        polarEnvChecked = true;
        if (isPolar)
            qDebug() << "TEST_POLAR_CHART found -> Testing polar chart!";
    }
    return isPolar;
}

static inline QChart *newQChartOrQPolarChart()
{
    if (isPolarTest())
        return new QPolarChart();
    else
        return new QChart();
}



#endif // TST_DEFINITIONS_H
