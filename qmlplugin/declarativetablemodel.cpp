#include "declarativetablemodel.h"
#include <QDebug>

DeclarativeTableModel::DeclarativeTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int DeclarativeTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return 5;
}

int DeclarativeTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

QVariant DeclarativeTableModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
    return QString("headerData");
}

QVariant DeclarativeTableModel::data(const QModelIndex &index, int /*role*/) const
{
//    return QString("data") + QString::number(index.row()) + QString::number(index.column());
    QObject *element = this->findChild<QObject*>("ListElement");
    if (element)
        qDebug() << "property: " << element->property("time");
//    element->setProperty("time", "0.1");
    return index.row() + index.column();
}

bool DeclarativeTableModel::setData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
    return true;
}

Qt::ItemFlags DeclarativeTableModel::flags(const QModelIndex &/*index*/) const
{
    return 0;
}

bool DeclarativeTableModel::insertRows(int /*row*/, int /*count*/, const QModelIndex &/*parent*/)
{
    return true;
}

bool DeclarativeTableModel::removeRows(int /*row*/, int /*count*/, const QModelIndex &/*parent*/)
{
    return true;
}
