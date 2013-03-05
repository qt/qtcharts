/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef VERTICALAXIS_P_H_
#define VERTICALAXIS_P_H_

#include "chartaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class VerticalAxis : public ChartAxis
{
public:
    VerticalAxis(QAbstractAxis *axis, QGraphicsItem* item = 0, bool intervalAxis = false);
    ~VerticalAxis();
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
protected:
    void updateGeometry();

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* VERTICALAXIS_P_H_ */
