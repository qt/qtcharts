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

