// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QChart)
QT_FORWARD_DECLARE_CLASS(QChartView)

class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = nullptr);

    void load();

protected:
    virtual bool doLoad();
    void resizeEvent(QResizeEvent *) override;
    void createDefaultChartView(QChart *chart);
    QChartView *defaultChartView() const { return m_defaultChartView; }
    void setDefaultChartView(QChartView *view);

    QString m_loadError;

private:
    QChartView *m_defaultChartView = nullptr;
    bool m_loaded = false;
};

#endif
