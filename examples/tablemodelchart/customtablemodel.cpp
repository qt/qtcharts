#include "customtablemodel.h"
#include <QVector>
#include <QTime>

CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    //    m_points.append(QPointF(10, 50));
    //    m_labels.append("Apples");
    //    m_points.append(QPointF(60, 70));
    //    m_labels.append("Oranges");
    //    m_points.append(QPointF(110, 50));
    //    m_labels.append("Bananas");
    //    m_points.append(QPointF(140, 40));
    //    m_labels.append("Lemons");
    //    m_points.append(QPointF(200, 150));
    //    m_labels.append("Plums");
    //    m_points.append(QPointF(225, 75));
    //    m_labels.append("Pearls");

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    // m_data
    for (int i = 0; i < 6; i++)
    {
        QVector<qreal>* dataVec = new QVector<qreal>(6);
        QVector<QColor>* colorVec = new QVector<QColor>(6);
        for (int k = 0; k < dataVec->size(); k++)
        {
            if (k%2 == 0)
                dataVec->replace(k, i * 50 + qrand()%20);
            else
                dataVec->replace(k, qrand()%100);
            colorVec->replace(k, QColor(Qt::white));
        }
        m_data.append(dataVec);
        m_labels.append(QString("Row: %1").arg((i + 1)));
        m_rowsColors.append(colorVec);
    }
}

int CustomTableModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    //    return m_points.count();
    return m_data.count();
}

int CustomTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    //    return 3;
    return 6;
}

QVariant CustomTableModel::headerData (int section, Qt::Orientation orientation, int role ) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch(section)
        {
        //        case 0:
        //            return "x";
        //        case 1:
        //            return "y";
        //        case 2:
        case 6:
            return "Fruit";
        default:
            if (section%2 == 0)
                return "x";
            else
                return "y";
            //            return "What?";
        }
    }
    else
        return QString("%1").arg(section + 1);
}

QVariant CustomTableModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        //        case 0:
        //            return m_points[index.row()].x();
        //        case 1:
        //            return m_points[index.row()].y();
        //        case 2:
        case 6:
            return m_labels[index.row()];
        default:
            return m_data[index.row()]->at(index.column());
            break;
        }
    }
    else if (role == Qt::EditRole)
    {
        switch(index.column())
        {
        //        case 0:
        //            return m_points[index.row()].x();
        //        case 1:
        //            return m_points[index.row()].y();
        //        case 2:
        case 6:
            return m_labels[index.row()];
        default:
            return m_data[index.row()]->at(index.column());
            break;
        }
    }
    else if (role == Qt::BackgroundRole)
        {
            return m_rowsColors[index.row()]->at(index.column());
        }
    return QVariant();
}

bool CustomTableModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        switch(index.column())
        {
        //        case 0:
        //            m_points[index.row()].setX(value.toDouble());
        //            break;
        //        case 1:
        //            m_points[index.row()].setY(value.toDouble());
        //            break;
        //        case 2:
        case 6:
            m_labels.replace(index.row(), value.toString());
            break;
        default:
            m_data[index.row()]->replace(index.column(), value.toDouble());
            break;
            //            return false;
        }
        emit dataChanged(index, index);
        return true;
    }
    else if (role == Qt::BackgroundRole)
        {
            m_rowsColors[index.row()]->replace(index.column(), value.value<QColor>());
            return true;
        }
    return false;
}

Qt::ItemFlags CustomTableModel::flags ( const QModelIndex & index ) const
{
    //    if (!index.isValid())
    //                return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CustomTableModel::insertRows ( int row, int count, const QModelIndex & parent)
{
    Q_UNUSED(parent)

    if (row < 0)
        row = 0;
    beginInsertRows(QModelIndex(), row /*dataTable.count()*/, row + count - 1);
    for (int i = row; i < row + count; i++)
    {
        //        m_points.insert(row, QPointF(10,20));
        QVector<qreal>* dataVec = new QVector<qreal>(6);        
        QVector<QColor>* colorVec = new QVector<QColor>(6);
        for (int k = 0; k < dataVec->size(); k++)
        {
            if (k%2 == 0)
                //                dataVec->replace(k, i * 50 + qrand()%20);
            {
                int difference = 0;
                if (i < m_data.size())
                {
                    if (i - 1 >= 0)
                    {
                        difference = (int)((qAbs(m_data[i]->at(k) - m_data[row - 1]->at(k)))/count);
                        dataVec->replace(k, m_data[i - 1]->at(k) + qrand()%qMax(1, difference));
                    }
                    else
                        dataVec->replace(k, qrand()%40 + 10);
                }
                else
                {
                    if (i - 1 >= 0)
                    {
                        dataVec->replace(k, m_data[i - 1]->at(k) + qrand()%40 + 10);
                    }
                    else
                    {
                        dataVec->replace(k, qrand()%40 + 10);
                    }
                }
            }
            else
                dataVec->replace(k, qrand()%100);
            colorVec->replace(k, QColor(Qt::white));
        }
        m_data.insert(i, dataVec);
        m_labels.insert(i,(QString("Row: %1").arg(i + 1)));
        m_rowsColors.insert(i, colorVec);
    }
    endInsertRows();
    return true;
}

bool CustomTableModel::removeRows ( int row, int count, const QModelIndex & parent)
{
    if (row > this->rowCount() - 1)
        return false;
    if (row < 0)
        row = 0;
    if (row + count > rowCount())
        return false;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++)
    {
        //        m_points.removeAt(row);
        QVector<qreal>* item = m_data.at(row);
        m_data.removeAt(row);
        delete item;
        m_labels.removeAt(row);
    }
    endRemoveRows();
    return true;
}
