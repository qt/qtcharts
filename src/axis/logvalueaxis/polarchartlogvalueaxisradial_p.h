/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
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
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef POLARCHARTLOGVALUEAXISRADIAL_P_H
#define POLARCHARTLOGVALUEAXISRADIAL_P_H

#include "polarchartaxisradial_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLogValueAxis;

class PolarChartLogValueAxisRadial : public PolarChartAxisRadial
{
    Q_OBJECT
public:
    PolarChartLogValueAxisRadial(QLogValueAxis *axis, QGraphicsItem *item);
    ~PolarChartLogValueAxisRadial();

protected:
    virtual QVector<qreal> calculateLayout() const;
    virtual void createAxisLabels(const QVector<qreal> &layout);

private Q_SLOTS:
    void handleBaseChanged(qreal base);
    void handleLabelFormatChanged(const QString &format);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // POLARCHARTLOGVALUEAXISRADIAL_P_H
