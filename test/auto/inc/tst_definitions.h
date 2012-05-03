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

#endif // TST_DEFINITIONS_H
