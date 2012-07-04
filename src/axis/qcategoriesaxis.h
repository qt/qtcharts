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

class QCategoriesAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QCategoriesAxis : public QValuesAxis
{
    Q_OBJECT

public:
    explicit QCategoriesAxis(QObject *parent = 0);
    ~QCategoriesAxis();

protected:
    QCategoriesAxis(QCategoriesAxisPrivate &d,QObject *parent = 0);

public:
    AxisType type() const;

    void append(const QString& category, qreal interval = 1);
    void remove(const QString& category);

    void setFisrtCategoryMinimum(qreal x);

    qreal categoryMin(const QString& category) const;
    qreal categoryMax(const QString& category) const;

    QStringList categories();
    int count() const;


private:
    Q_DECLARE_PRIVATE(QCategoriesAxis)
    Q_DISABLE_COPY(QCategoriesAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCATEGORIESAXIS_H
