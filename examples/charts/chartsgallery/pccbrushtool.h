// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef PCCBRUSHTOOL_H
#define PCCBRUSHTOOL_H

#include <QBrush>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QPushButton)

class PccBrushTool : public QWidget
{
    Q_OBJECT

public:
    explicit PccBrushTool(const QString &title, QWidget *parent = nullptr);
    void setBrush(const QBrush &brush);
    QBrush brush() const;
    QString name() const;
    static QString name(const QBrush &brush);

signals:
    void changed();

public slots:
    void showColorDialog();
    void updateStyle();

private:
    QBrush m_brush;
    QPushButton *m_colorButton = nullptr;
    QComboBox *m_styleCombo = nullptr;
};

#endif
