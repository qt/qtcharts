#ifndef QPIESERIESPRIVATE_P_H
#define QPIESERIESPRIVATE_P_H

#include "qpieseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieSeriesPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(QPieSeries)

public:
    QPieSeriesPrivate(QPieSeries *parent);
    ~QPieSeriesPrivate();

    void updateDerivativeData();

public Q_SLOTS:
    void sliceChanged();
    void sliceClicked(Qt::MouseButtons buttons);
    void sliceHoverEnter();
    void sliceHoverLeave();
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);

public:
    QPieSeries * const q_ptr;

    QList<QPieSlice*> m_slices;
    qreal m_pieRelativeHorPos;
    qreal m_pieRelativeVerPos;
    qreal m_pieRelativeSize;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_total;

    // model map
    int m_mapValues;
    int m_mapLabels;
    Qt::Orientation m_mapOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESERIESPRIVATE_P_H
