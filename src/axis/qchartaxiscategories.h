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

#ifndef QCHARTAXISCATEGORIES_H
#define QCHARTAXISCATEGORIES_H

#include <qchartglobal.h>
#include <qbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxisCategoriesPrivate;

class QTCOMMERCIALCHART_EXPORT QChartAxisCategories : public QObject
{
    Q_OBJECT
private:
    QChartAxisCategories();
public:
    ~QChartAxisCategories();

    void insert(const QBarCategories &category);
    void insert(qreal value,QString label);
    void remove(qreal value);
    QList<qreal> values() const;
    QString label(qreal value) const;
    void clear();
    int count();

private:
    QScopedPointer<QChartAxisCategoriesPrivate> d_ptr;
    friend class QChartAxisPrivate;
    friend class Axis;
};


QTCOMMERCIALCHART_END_NAMESPACE

#endif /* QCHARTAXISCATEGORIES_H_ */
