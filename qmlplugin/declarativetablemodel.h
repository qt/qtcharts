#ifndef DECLARATIVETABLEMODEL_H
#define DECLARATIVETABLEMODEL_H

#include <QAbstractTableModel>

class DeclarativeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DeclarativeTableModel(QObject *parent = 0);

public:
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    bool insertRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
    bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );

signals:
    
public slots:
    
};

#endif // DECLARATIVETABLEMODEL_H
