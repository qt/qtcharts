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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACTAXIS_P_H
#define QABSTRACTAXIS_P_H

#include "qabstractaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class ChartAxis;
class Domain;
class ChartDataSet;

class QTCOMMERCIALCHART_AUTOTEST_EXPORT QAbstractAxisPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstractAxisPrivate(QAbstractAxis *q);
    ~QAbstractAxisPrivate();

public:

    virtual ChartAxis* createGraphics(ChartPresenter* presenter) = 0;
    virtual void intializeDomain(Domain* domain) = 0;

    void emitUpdated();
    void setDirty(bool dirty);
    bool isDirty(){ return m_dirty; }
    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const { return m_orientation; }

    virtual void setMin(const QVariant &min) = 0;
    virtual qreal min() = 0;

    virtual void setMax(const QVariant &max) = 0;
    virtual qreal max() = 0;

    virtual int count() const = 0;

    virtual void setRange(const QVariant &min, const QVariant &max) = 0;

public Q_SLOTS:
    virtual void handleDomainUpdated() = 0;

Q_SIGNALS:
    void updated();

protected:
    QAbstractAxis *q_ptr;
    Qt::Orientation m_orientation;
    ChartDataSet *m_dataset;

private:
    bool m_visible;

    bool m_arrowVisible;
    QPen m_axisPen;
    QBrush m_axisBrush;

    bool m_gridLineVisible;
    QPen m_gridLinePen;

    bool m_labelsVisible;
    QPen m_labelsPen;
    QBrush m_labelsBrush;
    QFont m_labelsFont;
    int m_labelsAngle;

    bool m_shadesVisible;
    QPen m_shadesPen;
    QBrush m_shadesBrush;
    qreal m_shadesOpacity;

    bool m_dirty;

    friend class QAbstractAxis;
    friend class ChartDataSet;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
