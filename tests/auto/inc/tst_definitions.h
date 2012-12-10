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

#ifndef TST_DEFINITIONS_H
#define TST_DEFINITIONS_H

#include <QtTest/QtTest>
#include <QPushButton>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
namespace QTest
{
    // This was deprecated in Qt5. This is a small hack for the sake of compatibility.
    inline static bool qWaitForWindowShown(QWidget *window)
    {
        return QTest::qWaitForWindowExposed(window);
    }
}
#endif

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
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    #define SKIP_IF_CANNOT_TEST_MOUSE_EVENTS() { \
        do { \
            QPushButton b; \
            b.resize(100, 100); \
            b.show(); \
            QTest::qWaitForWindowShown(&b); \
            QSignalSpy spy(&b, SIGNAL(clicked())); \
            QTest::mouseClick(&b, Qt::LeftButton, 0, b.rect().center()); \
            if (spy.count() == 0) \
                QSKIP("Cannot test mouse events in this environment"); \
        } while (0); \
    }
#else
    #define SKIP_IF_CANNOT_TEST_MOUSE_EVENTS() { \
        do { \
            QPushButton b; \
            b.resize(100, 100); \
            b.show(); \
            QTest::qWaitForWindowShown(&b); \
            QSignalSpy spy(&b, SIGNAL(clicked())); \
            QTest::mouseClick(&b, Qt::LeftButton, 0, b.rect().center()); \
            if (spy.count() == 0) \
                QSKIP("Cannot test mouse events in this environment", SkipAll); \
        } while (0); \
    }
#endif

#endif // TST_DEFINITIONS_H
