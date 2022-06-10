// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef PENWIDGET_H
#define PENWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QPen>

class QComboBox;
class QSpinBox;

class PenWidget : public QWidget
{
public:
    explicit PenWidget(QWidget* parent = 0);
    ~PenWidget();

    QPen pen() const { return m_pen; }
private:
    void createContent();
    void createLayout();

private:
    QPen m_pen;
    QComboBox *m_colorComboBox;
    QComboBox *m_lineStyleComboBox;
    QSpinBox *m_widthSpinBox;
};

#endif /* PENWIDGET_H */
