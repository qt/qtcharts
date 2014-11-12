/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
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

#ifndef POLARCHARTLOGVALUEAXISANGULAR_P_H
#define POLARCHARTLOGVALUEAXISANGULAR_P_H

#include <private/polarchartaxisangular_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QLogValueAxis;

class PolarChartLogValueAxisAngular : public PolarChartAxisAngular
{
    Q_OBJECT
public:
    PolarChartLogValueAxisAngular(QLogValueAxis *axis, QGraphicsItem *item);
    ~PolarChartLogValueAxisAngular();

protected:
    virtual QVector<qreal> calculateLayout() const;
    virtual void createAxisLabels(const QVector<qreal> &layout);

private Q_SLOTS:
    void handleBaseChanged(qreal base);
    void handleLabelFormatChanged(const QString &format);
};

QT_CHARTS_END_NAMESPACE

#endif // POLARCHARTLOGVALUEAXISANGULAR_P_H
