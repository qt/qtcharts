/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QBARCATEGORYAXIS_H
#define QBARCATEGORYAXIS_H

#include <QtCharts/QAbstractAxis>

QT_CHARTS_BEGIN_NAMESPACE

class QBarCategoryAxisPrivate;

class QT_CHARTS_EXPORT QBarCategoryAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(QStringList categories READ categories WRITE setCategories NOTIFY categoriesChanged)
    Q_PROPERTY(QString min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(QString max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit QBarCategoryAxis(QObject *parent = 0);
    ~QBarCategoryAxis();

protected:
    QBarCategoryAxis(QBarCategoryAxisPrivate &d, QObject *parent = 0);

public:
    AxisType type() const;
    void append(const QStringList &categories);
    void append(const QString &category);
    void remove(const QString &category);
    void insert(int index, const QString &category);
    void replace(const QString &oldCategory, const QString &newCategory);
    Q_INVOKABLE void clear();
    void setCategories(const QStringList &categories);
    QStringList categories();
    int count() const;
    QString at(int index) const;

    //range handling
    void setMin(const QString &minCategory);
    QString min() const;
    void setMax(const QString &maxCategory);
    QString max() const;
    void setRange(const QString &minCategory, const QString &maxCategory);

Q_SIGNALS:
    void categoriesChanged();
    void minChanged(const QString &min);
    void maxChanged(const QString &max);
    void rangeChanged(const QString &min, const QString &max);
    void countChanged();

private:
    Q_DECLARE_PRIVATE(QBarCategoryAxis)
    Q_DISABLE_COPY(QBarCategoryAxis)
    friend class ChartBarCategoryAxisX;
    friend class ChartBarCategoryAxisY;
};

QT_CHARTS_END_NAMESPACE

#endif // QBARCATEGORYAXIS_H
