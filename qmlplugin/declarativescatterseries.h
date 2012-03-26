#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include "qchartglobal.h"
#include "declarativetablemodel.h"
#include "declarativexypoint.h"
#include <QDeclarativeItem>
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QScatterSeries;

class DeclarativeScatterSeries : public QDeclarativeItem//, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> data READ data)
    Q_PROPERTY(DeclarativeTableModel *model READ model WRITE setModel)
//    Q_PROPERTY(QObject *listModel READ listModel WRITE setListModel)
    Q_PROPERTY(int xColumn READ xColumn WRITE setXColumn)
    Q_PROPERTY(int yColumn READ yColumn WRITE setYColumn)

public:
    explicit DeclarativeScatterSeries(QDeclarativeItem *parent = 0);
    ~DeclarativeScatterSeries();

public: // from QDeclarativeParserStatus
    void componentComplete();

public:
    QDeclarativeListProperty<DeclarativeXyPoint> data();
    DeclarativeTableModel *model();
    void setModel(DeclarativeTableModel *model);
//QObject *listModel();
//void setListModel(QObject *model);
    int xColumn() { return m_xColumn; }
    void setXColumn(int xColumn);
    int yColumn() { return m_yColumn; }
    void setYColumn(int yColumn);

signals:

public slots:
    static void appendData(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                           DeclarativeXyPoint *element);

private slots:

public:
    QChart *m_chart; // not owned
    QScatterSeries *m_series; // not owned
    DeclarativeTableModel *m_model; // not owned
    QList<DeclarativeXyPoint *> m_data;
    int m_xColumn;
    int m_yColumn;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
