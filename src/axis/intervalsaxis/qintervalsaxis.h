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

#ifndef QCATEGORIESAXIS_H
#define QCATEGORIESAXIS_H

#include "qabstractaxis.h"
#include "qvaluesaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QIntervalsAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QIntervalsAxis : public QValuesAxis
{
    Q_OBJECT

public:
    explicit QIntervalsAxis(QObject *parent = 0);
    ~QIntervalsAxis();

protected:
    QIntervalsAxis(QIntervalsAxisPrivate &d,QObject *parent = 0);

public:
    AxisType type() const;

    void append(const QString& label, qreal interval = 1);
    void remove(const QString& label);

    void setFisrtIntervalMinimum(qreal min);

    qreal intervalMin(const QString& intervalLabel) const;
    qreal intervalMax(const QString& intervalLabel) const;

    QStringList intervalsLabels();
    int count() const;


private:
    Q_DECLARE_PRIVATE(QIntervalsAxis)
    Q_DISABLE_COPY(QIntervalsAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCATEGORIESAXIS_H
