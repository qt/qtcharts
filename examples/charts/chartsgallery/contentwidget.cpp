// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "contentwidget.h"

#include <QChart>
#include <QChartView>
#include <QFont>
#include <QLabel>
#include <QVBoxLayout>

ContentWidget::ContentWidget(QWidget *parent)
    : QWidget(parent)
{
}

void ContentWidget::load()
{
    if (m_loaded || layout())
        return;

    if (!doLoad()) {
        auto errorLabel = new QLabel(this);
        auto errorLayout = new QVBoxLayout(this);
        errorLabel->setText(tr("Error loading the example:\n%1").arg(m_loadError));
        QFont font = errorLabel->font();
        font.setPointSize(20);
        errorLabel->setFont(font);
        errorLabel->setAlignment(Qt::AlignCenter);
        errorLayout->addWidget(errorLabel);
        setLayout(errorLayout);
    }

    m_loaded = true;
}

bool ContentWidget::doLoad()
{
    // Most examples do their initialization in constructor.
    // Only those that can fail and show error message need to reimplement this method.
    return true;
}

void ContentWidget::resizeEvent(QResizeEvent *)
{
    if (m_defaultChartView)
        m_defaultChartView->resize(size());
}

// Most examples are simple and need only basic chart view widget, so provide it in this base class
// to avoid duplicating code
void ContentWidget::createDefaultChartView(QChart *chart)
{
    m_defaultChartView = new QChartView(chart, this);
    m_defaultChartView->setRenderHint(QPainter::Antialiasing);
}

void ContentWidget::setDefaultChartView(QChartView *view)
{
    m_defaultChartView = view;
    m_defaultChartView->setRenderHint(QPainter::Antialiasing);
}
