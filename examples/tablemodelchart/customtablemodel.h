#ifndef XYPOINTSMODEL_H
#define XYPOINTSMODEL_H

#include <QAbstractTableModel>
#include <QPointF>
#include <QStringList>

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
    
    //signals:
    
    //public slots:
private:
    QList<QPointF> m_points;
    QStringList m_labels;

    
};

#endif // XYPOINTSMODEL_H
