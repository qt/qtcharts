// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>

QT_BEGIN_NAMESPACE
class QCandlestickSet;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CustomTableModel(QObject *parent = nullptr);
    virtual ~CustomTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    void addRow(QCandlestickSet *set);
    void clearRows();

    void addMapping(QString color, QRect area);
    void clearMapping();

private:
    QStringList m_categories;
    QList<QList<qreal> *> m_data;
    QMultiHash<QString, QRect> m_mapping;
};

#endif // CUSTOMTABLEMODEL_H
