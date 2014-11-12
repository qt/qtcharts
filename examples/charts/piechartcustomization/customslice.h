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
#ifndef CUSTOMSLICE_H
#define CUSTOMSLICE_H

#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

class CustomSlice : public QPieSlice
{
    Q_OBJECT

public:
    CustomSlice(QString label, qreal value);

public:
    QBrush originalBrush();

public Q_SLOTS:
    void showHighlight(bool show);

private:
    QBrush m_originalBrush;
};

#endif // CUSTOMSLICE_H
