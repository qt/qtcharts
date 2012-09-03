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

#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QAbstractSeries>
#include <QModelIndex>

class QStandardItemModel;
class QItemSelectionModel;


QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QChart;
class QXYSeries;
class QAbstractBarSeries;
class QPieSeries;
class QAreaSeries;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

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
