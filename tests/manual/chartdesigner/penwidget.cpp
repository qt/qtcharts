// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "penwidget.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>

PenWidget::PenWidget(QWidget *parent):QWidget(parent),
m_colorComboBox(0),
m_lineStyleComboBox(0),
m_widthSpinBox(0)
{
    createContent();
    createLayout();
    setFixedSize(minimumSizeHint());
}

PenWidget::~PenWidget()
{

}

void PenWidget::createContent()
{
    m_colorComboBox = new QComboBox(this);
    m_lineStyleComboBox = new QComboBox(this);
    m_widthSpinBox = new QSpinBox(this);
}

void PenWidget::createLayout()
{
    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("Color"), m_colorComboBox);
    layout->addRow(tr("Style"), m_lineStyleComboBox);
    layout->addRow(tr("Width"), m_widthSpinBox);
    setLayout(layout);
}

