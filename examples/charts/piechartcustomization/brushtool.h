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
#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include <QtWidgets/QWidget>
#include <QtGui/QBrush>

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
QT_END_NAMESPACE

class BrushTool : public QWidget
{
    Q_OBJECT

public:
    explicit BrushTool(QString title, QWidget *parent = 0);
    void setBrush(QBrush brush);
    QBrush brush() const;
    QString name();
    static QString name(const QBrush &brush);

Q_SIGNALS:
    void changed();

public Q_SLOTS:
    void showColorDialog();
    void updateStyle();

private:
    QBrush m_brush;
    QPushButton *m_colorButton;
    QComboBox *m_styleCombo;
};

#endif // BRUSHTOOL_H
