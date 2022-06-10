// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QMultiHash>
#include <QtCore/QRect>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomTableModel(QObject *parent = 0);
    virtual ~CustomTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }

private:
    QList<QList<qreal> *> m_data;
    QMultiHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;
};

#endif // CUSTOMTABLEMODEL_H
