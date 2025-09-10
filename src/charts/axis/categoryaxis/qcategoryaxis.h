// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QCATEGORYAXIS_H
#define QCATEGORYAXIS_H

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE

class QCategoryAxisPrivate;

class Q_CHARTS_EXPORT QCategoryAxis : public QValueAxis
{
    Q_OBJECT
    Q_PROPERTY(qreal startValue READ startValue WRITE setStartValue)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QStringList categoriesLabels READ categoriesLabels)
    Q_PROPERTY(AxisLabelsPosition labelsPosition READ labelsPosition WRITE setLabelsPosition NOTIFY labelsPositionChanged)
    Q_ENUMS(AxisLabelsPosition)

public:

    enum AxisLabelsPosition {
        AxisLabelsPositionCenter = 0x0,
        AxisLabelsPositionOnValue = 0x1
    };

    explicit QCategoryAxis(QObject *parent = nullptr);
    ~QCategoryAxis();

protected:
    QCategoryAxis(QCategoryAxisPrivate &d, QObject *parent = nullptr);

public:
    AxisType type() const override;

    void append(const QString &label, qreal categoryEndValue);
    void remove(const QString &label);
    void replaceLabel(const QString &oldLabel, const QString &newLabel);

    qreal startValue(const QString &categoryLabel = QString()) const;
    void setStartValue(qreal min);

    qreal endValue(const QString &categoryLabel) const;

    QStringList categoriesLabels();
    int count() const;

    QCategoryAxis::AxisLabelsPosition labelsPosition() const;
    void setLabelsPosition(QCategoryAxis::AxisLabelsPosition position);

Q_SIGNALS:
    void categoriesChanged();
    void labelsPositionChanged(QCategoryAxis::AxisLabelsPosition position);

private:
    Q_DECLARE_PRIVATE(QCategoryAxis)
    Q_DISABLE_COPY(QCategoryAxis)
};

QT_END_NAMESPACE

#endif // QCATEGORYAXIS_H
