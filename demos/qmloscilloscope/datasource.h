/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QAbstractSeries>

class QDeclarativeView;

QTCOMMERCIALCHART_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QDeclarativeView *appViewer, QObject *parent = 0);

signals:

public slots:
    void generateData(int type, int rowCount, int colCount);
    void update(QAbstractSeries *series);
    void setAntialiasing(bool enabled);

private:
    QDeclarativeView *m_appViewer;
    QList<QList<QPointF> > m_data;
    int m_index;
};

#endif // DATASOURCE_H
