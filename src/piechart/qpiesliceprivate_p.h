#ifndef QPIESLICEPRIVATE_P_H
#define QPIESLICEPRIVATE_P_H

#include "qpieslice.h"
#include "pieslicedata_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieSlicePrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(QPieSlice)

public:
    QPieSlicePrivate(QPieSlice *parent)
        :QObject(parent),
        q_ptr(parent)
    {
        connect(this, SIGNAL(changed()), q_ptr, SIGNAL(changed()));
    }

    ~QPieSlicePrivate() {}

Q_SIGNALS:
    void changed();

public:
    friend class QPieSeriesPrivate;
    friend class ChartTheme;
    QPieSlice * const q_ptr;
    PieSliceData m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICEPRIVATE_P_H
