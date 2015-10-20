/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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

