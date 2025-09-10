// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBARSET_H
#define QBARSET_H

#include <QtCharts/qchartglobal.h>
#include <QtGui/qpen.h>
#include <QtGui/qbrush.h>
#include <QtGui/qfont.h>
#include <QtCore/qobject.h>

QT_BEGIN_NAMESPACE
class QBarSetPrivate;

class Q_CHARTS_EXPORT QBarSet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(QBrush labelBrush READ labelBrush WRITE setLabelBrush NOTIFY labelBrushChanged)
    Q_PROPERTY(QFont labelFont READ labelFont WRITE setLabelFont NOTIFY labelFontChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor NOTIFY labelColorChanged)

public:
    explicit QBarSet(const QString label, QObject *parent = nullptr);
    virtual ~QBarSet();

    void setLabel(const QString label);
    QString label() const;

    void append(const qreal value);
    void append(const QList<qreal> &values);

    QBarSet &operator << (const qreal &value);

    void insert(const int index, const qreal value);
    void remove(const int index, const int count = 1);
    void replace(const int index, const qreal value);
    qreal at(const int index) const;
    qreal operator [](const int index) const;
    int count() const;
    qreal sum() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setLabelFont(const QFont &font);
    QFont labelFont() const;

    QColor color();
    void setColor(QColor color);

    QColor borderColor();
    void setBorderColor(QColor color);

    QColor labelColor();
    void setLabelColor(QColor color);

    QColor selectedColor() const;
    void setSelectedColor(const QColor &color);

    bool isBarSelected(int index) const;
    void selectBar(int index);
    void deselectBar(int index);
    void setBarSelected(int index, bool selected);
    void selectAllBars();
    void deselectAllBars();
    void selectBars(const QList<int> &indexes);
    void deselectBars(const QList<int> &indexes);
    void toggleSelection(const QList<int> &indexes);
    QList<int> selectedBars() const;

Q_SIGNALS:
    void clicked(int index);
    void hovered(bool status, int index);
    void pressed(int index);
    void released(int index);
    void doubleClicked(int index);
    void penChanged();
    void brushChanged();
    void labelChanged();
    void labelBrushChanged();
    void labelFontChanged();
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);
    void labelColorChanged(QColor color);
    Q_REVISION(6, 2) void selectedColorChanged(const QColor &color);

    void valuesAdded(int index, int count);
    void valuesRemoved(int index, int count);
    void valueChanged(int index);

    Q_REVISION(6, 2) void selectedBarsChanged(const QList<int> &indexes);

private:
    QScopedPointer<QBarSetPrivate> d_ptr;
    Q_DISABLE_COPY(QBarSet)
    friend class QAbstractBarSeries;
    friend class BarLegendMarker;
    friend class AbstractBarChartItem;
    friend class QAbstractBarSeriesPrivate;
    friend class StackedBarChartItem;
    friend class PercentBarChartItem;
    friend class BarChartItem;
    friend class HorizontalBarChartItem;
    friend class HorizontalStackedBarChartItem;
    friend class HorizontalPercentBarChartItem;
    friend class BoxPlotChartItem;
};

QT_END_NAMESPACE

#endif // QBARSET_H
