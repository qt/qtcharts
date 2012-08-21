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

#ifndef PIESERIES_H
#define PIESERIES_H

#include <qabstractseries.h>
#include <QPieSlice>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSeriesPrivate;
//class QPieSlice;

class QTCOMMERCIALCHART_EXPORT QPieSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(qreal horizontalPosition READ horizontalPosition WRITE setHorizontalPosition)
    Q_PROPERTY(qreal verticalPosition READ verticalPosition WRITE setVerticalPosition)
    Q_PROPERTY(qreal size READ pieSize WRITE setPieSize)
    Q_PROPERTY(qreal startAngle READ pieStartAngle WRITE setPieStartAngle)
    Q_PROPERTY(qreal endAngle READ pieEndAngle WRITE setPieEndAngle)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(qreal sum READ sum NOTIFY sumChanged)
    Q_PROPERTY(qreal donutInnerSize READ donutInnerSize WRITE setDonutInnerSize)
    Q_PROPERTY(bool donut READ donut WRITE setDonut)

public:
    explicit QPieSeries(QObject *parent = 0);
    virtual ~QPieSeries();

    QAbstractSeries::SeriesType type() const;

    bool append(QPieSlice* slice);
    bool append(QList<QPieSlice*> slices);
    QPieSeries& operator << (QPieSlice* slice);
    QPieSlice* append(QString label, qreal value);

    bool insert(int index, QPieSlice* slice);

    bool remove(QPieSlice* slice);
    bool take(QPieSlice* slice);
    void clear();

    QList<QPieSlice*> slices() const;
    int count() const;

    bool isEmpty() const;

    qreal sum() const;

    void setDonut(bool donut = true);
    bool donut() const;

    void setDonutInnerSize(qreal innerSize);
    qreal donutInnerSize() const;

    void setHorizontalPosition(qreal relativePosition);
    qreal horizontalPosition() const;

    void setVerticalPosition(qreal relativePosition);
    qreal verticalPosition() const;

    void setPieSize(qreal relativeSize);
    qreal pieSize() const;

    void setPieStartAngle(qreal startAngle);
    qreal pieStartAngle() const;

    void setPieEndAngle(qreal endAngle);
    qreal pieEndAngle() const;

    void setLabelsVisible(bool visible = true);
    void setLabelsPosition(QPieSlice::LabelPosition position);

Q_SIGNALS:
    void added(QList<QPieSlice*> slices);
    void removed(QList<QPieSlice*> slices);
    void clicked(QPieSlice* slice);
    void hovered(QPieSlice* slice, bool state);
    void countChanged();
    void sumChanged();

private:
    Q_DECLARE_PRIVATE(QPieSeries)
    Q_DISABLE_COPY(QPieSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
