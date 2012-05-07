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

#ifndef CHARTTABLEMODEL_H
#define CHARTTABLEMODEL_H

#include "qchartglobal.h"
#include <QAbstractTableModel>
#include <QHash>
#include <QRect>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT ChartTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount)

public:
    explicit ChartTableModel(QObject *parent = 0);

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    void insertRow(int row, const QModelIndex &parent = QModelIndex());
    /*Q_INVOKABLE*/ //bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
    Q_INVOKABLE bool removeRow (int row, const QModelIndex &parent = QModelIndex());

private:
    QList<QVector<QVariant> * > m_data;
    int m_columnCount;
    int m_rowCount;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTTABLEMODEL_H
