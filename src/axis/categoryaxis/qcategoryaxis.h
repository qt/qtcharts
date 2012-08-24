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
#include "qvalueaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QCategoryAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QCategoryAxis : public QValueAxis
{
    Q_OBJECT

public:
    explicit QCategoryAxis(QObject *parent = 0);
    ~QCategoryAxis();

protected:
    QCategoryAxis(QCategoryAxisPrivate &d,QObject *parent = 0);

public:
    AxisType type() const;

    void append(const QString& label, qreal categoryHighEnd);
    void remove(const QString& label);
    void replaceLabel(const QString& oldLabel, const QString& newLabel);

    void setStartValue(qreal min);

    qreal categoryStart(const QString& categoryLabel) const;
    qreal categoryEnd(const QString& categoryLabel) const;

    QStringList categoriesLabels();
    int count() const;


private:
    Q_DECLARE_PRIVATE(QCategoryAxis)
    Q_DISABLE_COPY(QCategoryAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCATEGORIESAXIS_H
