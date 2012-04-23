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

#ifndef XYPOINTSMODEL_H
#define XYPOINTSMODEL_H

#include <QAbstractTableModel>
#include <QPointF>
#include <QStringList>
//#include <QColor>
#include <QHash>
#include <QRect>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomTableModel(QObject *parent = 0);

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    bool insertRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
    bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
    bool insertColumns ( int column, int count, const QModelIndex & parent = QModelIndex() );
    bool removeColumns ( int column, int count, const QModelIndex & parent = QModelIndex() );

    void addMapping(QString color, QRect area);
    void addMapping(QString color, int left, int top, int right, int bottom);
    void clearMapping() { m_mapping.clear(); }
    
    //signals:
    
    //public slots:
private:
    QList<QVector<qreal> * > m_data;
    QHash<QString, QRect> m_mapping;
    QList<QPointF> m_points;
    QStringList m_labels;    
    int m_columnCount;
    int m_rowCount;

    
};

#endif // XYPOINTSMODEL_H
