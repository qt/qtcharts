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
#ifndef PENTOOL_H
#define PENTOOL_H

#include <QtWidgets/QWidget>
#include <QtGui/QPen>

QT_BEGIN_NAMESPACE
class QPushButton;
class QDoubleSpinBox;
class QComboBox;
QT_END_NAMESPACE

class PenTool : public QWidget
{
    Q_OBJECT

public:
    explicit PenTool(QString title, QWidget *parent = 0);
    void setPen(const QPen &pen);
    QPen pen() const;
    QString name();
    static QString name(const QPen &pen);

Q_SIGNALS:
    void changed();

public Q_SLOTS:
    void showColorDialog();
    void updateWidth(double width);
    void updateStyle(int style);
    void updateCapStyle(int index);
    void updateJoinStyle(int index);

private:
    QPen m_pen;
    QPushButton *m_colorButton;
    QDoubleSpinBox *m_widthSpinBox;
    QComboBox *m_styleCombo;
    QComboBox *m_capStyleCombo;
    QComboBox *m_joinStyleCombo;
};

#endif // PENTOOL_H
