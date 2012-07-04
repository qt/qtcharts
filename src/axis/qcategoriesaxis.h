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

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QCategoriesAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QCategoriesAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(QStringList categories READ categories WRITE setCategories NOTIFY categoriesChanged)
    Q_PROPERTY(QString min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(QString max READ max WRITE setMax NOTIFY maxChanged)

public:
    explicit QCategoriesAxis(QObject *parent = 0);
    ~QCategoriesAxis();

protected:
    QCategoriesAxis(QCategoriesAxisPrivate &d,QObject *parent = 0);

public:
    AxisType type() const;
    void append(const QStringList &categories);
    void append(const QString &category);
    void remove(const QString &category);
    void insert(int index, const QString &category);
    void clear();
    void setCategories(const QStringList &categories);
    QStringList categories();
    int count() const;
    QString at(int index) const;

    //range handling
    void setMin(const QString& minCategory);
    QString min() const;
    void setMax(const QString& maxCategory);
    QString max() const;
    void setRange(const QString& minCategory, const QString& maxCategory);

Q_SIGNALS:
    void categoriesChanged();
	void minChanged(const QString &min);
	void maxChanged(const QString &max);
	void rangeChanged(const QString &min, const QString &max);

private:
    Q_DECLARE_PRIVATE(QCategoriesAxis)
    Q_DISABLE_COPY(QCategoriesAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCATEGORIESAXIS_H
