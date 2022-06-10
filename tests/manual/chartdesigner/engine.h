// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef ENGINE_H
#define ENGINE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCore/QModelIndex>

class QStandardItemModel;
class QItemSelectionModel;


QT_BEGIN_NAMESPACE
class QChart;
class QXYSeries;
class QAbstractBarSeries;
class QPieSeries;
class QAreaSeries;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
   ~Engine();

    int modelCount() { return m_count; }
    QStandardItemModel *model() const { return m_model; }
    QItemSelectionModel *selectionModel() const { return m_selection; }
    QChart* chart() const { return m_chart; }
    void clearModels();
    QList<QAbstractSeries*> addSeries(QAbstractSeries::SeriesType type);
    void removeSeries(QAbstractSeries* series);
    bool save(const QString &filename) const;
    bool load(const QString &filename);
signals:
    void selected();

private:
    void createModels();
    void setupXYSeries(QXYSeries *xyseries, const QList<int>& columns, int column, int minRow, int maxRow);
    void setupBarSeries(QAbstractBarSeries *series, const QList<int>& columns, int minRow, int maxRow);
    void setupPieSeries(QPieSeries *pie, const QList<int>& columns, int minRow, int maxRow);
    void setupAreaSeries(QAreaSeries *series, const QList<int>& columns, int minRow, int maxRow);

private:
    int m_count;
    QChart *m_chart;
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;
    QMap<QAbstractSeries*, QList<QModelIndex> > m_seriesModelIndex;
};

#endif /* ENGINE_H */
