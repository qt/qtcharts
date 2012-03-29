#ifndef DECLARATIVEPIESERIES_H
#define DECLARATIVEPIESERIES_H

#include "qchartglobal.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativePieSeries : public QPieSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QDeclarativeListProperty<QPieSlice> slices READ slices)

public:
    explicit DeclarativePieSeries(QObject *parent = 0);
    QDeclarativeListProperty<QPieSlice> slices();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    static void appendSlice(QDeclarativeListProperty<QPieSlice> *list,
                            QPieSlice *element);

private:
    QChart *m_chart;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
