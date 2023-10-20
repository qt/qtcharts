// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "pccpentool.h"

#include <QColorDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QPushButton>

PccPenTool::PccPenTool(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(title);
    setWindowFlags(Qt::Tool);

    m_colorButton = new QPushButton(this);

    m_widthSpinBox = new QDoubleSpinBox(this);

    m_styleCombo = new QComboBox(this);
    m_styleCombo->addItem("NoPen");
    m_styleCombo->addItem("SolidLine");
    m_styleCombo->addItem("DashLine");
    m_styleCombo->addItem("DotLine");
    m_styleCombo->addItem("DashDotLine");
    m_styleCombo->addItem("DashDotDotLine");

    m_capStyleCombo = new QComboBox(this);
    m_capStyleCombo->addItem("FlatCap", Qt::FlatCap);
    m_capStyleCombo->addItem("SquareCap", Qt::SquareCap);
    m_capStyleCombo->addItem("RoundCap", Qt::RoundCap);

    m_joinStyleCombo = new QComboBox(this);
    m_joinStyleCombo->addItem("MiterJoin", Qt::MiterJoin);
    m_joinStyleCombo->addItem("BevelJoin", Qt::BevelJoin);
    m_joinStyleCombo->addItem("RoundJoin", Qt::RoundJoin);
    m_joinStyleCombo->addItem("SvgMiterJoin", Qt::SvgMiterJoin);

    auto layout = new QFormLayout;
    layout->addRow("Color", m_colorButton);
    layout->addRow("Width", m_widthSpinBox);
    layout->addRow("Style", m_styleCombo);
    layout->addRow("Cap style", m_capStyleCombo);
    layout->addRow("Join style", m_joinStyleCombo);
    setLayout(layout);

    // Use old style connect on some signals because the signal is overloaded
    connect(m_colorButton, &QPushButton::clicked, this, &PccPenTool::showColorDialog);
    connect(m_widthSpinBox, &QDoubleSpinBox::valueChanged, this, &PccPenTool::updateWidth);
    connect(m_styleCombo, &QComboBox::currentIndexChanged, this, &PccPenTool::updateStyle);
    connect(m_capStyleCombo, &QComboBox::currentIndexChanged, this, &PccPenTool::updateCapStyle);
    connect(m_joinStyleCombo, &QComboBox::currentIndexChanged, this, &PccPenTool::updateJoinStyle);
}

void PccPenTool::setPen(const QPen &pen)
{
    m_pen = pen;
    m_colorButton->setText(m_pen.color().name());
    m_widthSpinBox->setValue(m_pen.widthF());
    m_styleCombo->setCurrentIndex(m_pen.style()); // index matches the enum
    m_capStyleCombo->setCurrentIndex(m_capStyleCombo->findData(m_pen.capStyle()));
    m_joinStyleCombo->setCurrentIndex(m_joinStyleCombo->findData(m_pen.joinStyle()));
}

QPen PccPenTool::pen() const
{
    return m_pen;
}

QString PccPenTool::name() const
{
    return name(m_pen);
}

QString PccPenTool::name(const QPen &pen)
{
    return pen.color().name() + ":" + QString::number(pen.widthF());
}

void PccPenTool::showColorDialog()
{
    QColorDialog dialog(m_pen.color());
    dialog.show();
    dialog.exec();
    m_pen.setColor(dialog.selectedColor());
    m_colorButton->setText(m_pen.color().name());
    emit changed();
}

void PccPenTool::updateWidth(double width)
{
    if (!qFuzzyCompare((qreal) width, m_pen.widthF())) {
        m_pen.setWidthF(width);
        emit changed();
    }
}

void PccPenTool::updateStyle(int style)
{
    if (m_pen.style() != style) {
        m_pen.setStyle((Qt::PenStyle) style);
        emit changed();
    }
}

void PccPenTool::updateCapStyle(int index)
{
    Qt::PenCapStyle capStyle = (Qt::PenCapStyle) m_capStyleCombo->itemData(index).toInt();
    if (m_pen.capStyle() != capStyle) {
        m_pen.setCapStyle(capStyle);
        emit changed();
    }
}

void PccPenTool::updateJoinStyle(int index)
{
    Qt::PenJoinStyle joinStyle = (Qt::PenJoinStyle) m_joinStyleCombo->itemData(index).toInt();
    if (m_pen.joinStyle() != joinStyle) {
        m_pen.setJoinStyle(joinStyle);
        emit changed();
    }
}
