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

#ifndef QCATEGORYAXIS_H
#define QCATEGORYAXIS_H

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE

class QCategoryAxisPrivate;

class QT_CHARTS_EXPORT QCategoryAxis : public QValueAxis
{
    Q_OBJECT
    Q_PROPERTY(qreal startValue READ startValue WRITE setStartValue)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QStringList categoriesLabels READ categoriesLabels)

public:
    explicit QCategoryAxis(QObject *parent = 0);
    ~QCategoryAxis();

protected:
    QCategoryAxis(QCategoryAxisPrivate &d, QObject *parent = 0);

public:
    AxisType type() const;

    void append(const QString &label, qreal categoryEndValue);
    void remove(const QString &label);
    void replaceLabel(const QString &oldLabel, const QString &newLabel);

    qreal startValue(const QString &categoryLabel = QString()) const;
    void setStartValue(qreal min);

    qreal endValue(const QString &categoryLabel) const;

    QStringList categoriesLabels();
    int count() const;

Q_SIGNALS:
    void categoriesChanged();

private:
    Q_DECLARE_PRIVATE(QCategoryAxis)
    Q_DISABLE_COPY(QCategoryAxis)
};

QT_CHARTS_END_NAMESPACE

#endif // QCATEGORYAXIS_H
