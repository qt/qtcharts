// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef PCCCUSTOMSLICE_H
#define PCCCUSTOMSLICE_H

#include <QPieSlice>

class PccCustomSlice : public QPieSlice
{
    Q_OBJECT
public:
    PccCustomSlice(const QString &label, qreal value);

public:
    QBrush originalBrush();

public slots:
    void showHighlight(bool show);

private:
    QBrush m_originalBrush;
};

#endif
