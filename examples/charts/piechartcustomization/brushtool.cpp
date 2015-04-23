/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/
#include "brushtool.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QColorDialog>

BrushTool::BrushTool(QString title, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(title);
    setWindowFlags(Qt::Tool);

    m_colorButton = new QPushButton();
    m_styleCombo = new QComboBox();
    m_styleCombo->addItem("Nobrush", (int) Qt::NoBrush);
    m_styleCombo->addItem("Solidpattern", (int) Qt::SolidPattern);
    m_styleCombo->addItem("Dense1pattern", (int) Qt::Dense1Pattern);
    m_styleCombo->addItem("Dense2attern", (int) Qt::Dense2Pattern);
    m_styleCombo->addItem("Dense3Pattern", (int) Qt::Dense3Pattern);
    m_styleCombo->addItem("Dense4Pattern", (int) Qt::Dense4Pattern);
    m_styleCombo->addItem("Dense5Pattern", (int) Qt::Dense5Pattern);
    m_styleCombo->addItem("Dense6Pattern", (int) Qt::Dense6Pattern);
    m_styleCombo->addItem("Dense7Pattern", (int) Qt::Dense7Pattern);
    m_styleCombo->addItem("HorPattern", (int) Qt::HorPattern);
    m_styleCombo->addItem("VerPattern", (int) Qt::VerPattern);
    m_styleCombo->addItem("CrossPattern", (int) Qt::CrossPattern);
    m_styleCombo->addItem("BDiagPattern", (int) Qt::BDiagPattern);
    m_styleCombo->addItem("FDiagPattern", (int) Qt::FDiagPattern);
    m_styleCombo->addItem("DiagCrossPattern", (int) Qt::DiagCrossPattern);

    QFormLayout *layout = new QFormLayout();
    layout->addRow("Color", m_colorButton);
    layout->addRow("Style", m_styleCombo);
    setLayout(layout);

    connect(m_colorButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));
    connect(m_styleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStyle()));
}

void BrushTool::setBrush(QBrush brush)
{
    m_brush = brush;
    m_colorButton->setText(m_brush.color().name());
    m_styleCombo->setCurrentIndex(m_brush.style()); // index matches the enum
}

QBrush BrushTool::brush() const
{
    return m_brush;
}

QString BrushTool::name()
{
    return name(m_brush);
}

QString BrushTool::name(const QBrush &brush)
{
    return brush.color().name();
}

void BrushTool::showColorDialog()
{
    QColorDialog dialog(m_brush.color());
    dialog.show();
    dialog.exec();
    m_brush.setColor(dialog.selectedColor());
    m_colorButton->setText(m_brush.color().name());
    emit changed();
}

void BrushTool::updateStyle()
{
    Qt::BrushStyle style = (Qt::BrushStyle) m_styleCombo->itemData(m_styleCombo->currentIndex()).toInt();
    if (m_brush.style() != style) {
        m_brush.setStyle(style);
        emit changed();
    }
}

#include "moc_brushtool.cpp"
