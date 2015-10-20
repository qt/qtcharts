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
