// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
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
