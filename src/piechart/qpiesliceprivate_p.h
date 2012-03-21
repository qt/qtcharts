#ifndef QPIESLICEPRIVATE_P_H
#define QPIESLICEPRIVATE_P_H

#include "qpieslice.h"
#include "pieslicedata_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieSlicePrivate
{
    Q_DECLARE_PUBLIC(QPieSlice)

public:
    QPieSlicePrivate(QPieSlice *parent):q_ptr(parent) {}
    ~QPieSlicePrivate() {}

    QPieSlice * const q_ptr;

    PieSliceData m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICEPRIVATE_P_H
