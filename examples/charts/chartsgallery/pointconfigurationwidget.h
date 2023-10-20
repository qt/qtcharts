// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef POINTCONFIGURATIONWIDGET_H
#define POINTCONFIGURATIONWIDGET_H

#include "contentwidget.h"

#include <QXYSeries>

QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QCheckBox)

typedef QHash<QXYSeries::PointConfiguration, QVariant> PointConfigurations;

class PointConfigurationWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit PointConfigurationWidget(QWidget *parent = nullptr);

private:
    QXYSeries *m_series = nullptr;

    QMetaObject::Connection m_selectInitialPointConnection;
    int m_selectedPointIndex = -1;
    PointConfigurations m_selectedPointConfig;

    QLineEdit *m_selectedPointIndexLineEdit = nullptr;
    QComboBox *m_colorCombobox = nullptr;
    QComboBox *m_sizeCombobox = nullptr;
    QCheckBox *m_labelVisibilityCheckbox = nullptr;
    QLineEdit *m_customLabelLineEdit = nullptr;
};

#endif
