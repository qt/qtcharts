// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef PCCPENTOOL_H
#define PCCPENTOOL_H

#include <QPen>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QComboBox);
QT_FORWARD_DECLARE_CLASS(QDoubleSpinBox);
QT_FORWARD_DECLARE_CLASS(QPushButton);

class PccPenTool : public QWidget
{
    Q_OBJECT
public:
    explicit PccPenTool(const QString &title, QWidget *parent = nullptr);
    void setPen(const QPen &pen);
    QPen pen() const;
    QString name() const;
    static QString name(const QPen &pen);

signals:
    void changed();

public slots:
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

#endif
