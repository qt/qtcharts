/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef ENGINE_H
#define ENGINE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCore/QModelIndex>

class QStandardItemModel;
class QItemSelectionModel;


QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QXYSeries;
class QAbstractBarSeries;
class QPieSeries;
class QAreaSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

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
