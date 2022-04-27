/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVEPIESERIES_H
#define DECLARATIVEPIESERIES_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <private/declarativechartglobal_p.h>

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlParserStatus>

QT_BEGIN_NAMESPACE

class Q_QMLCHARTS_PRIVATE_EXPORT DeclarativePieSlice : public QPieSlice
{
    Q_OBJECT
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged)
    QML_NAMED_ELEMENT(PieSlice)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativePieSlice(QObject *parent = 0);
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);

Q_SIGNALS:
    void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleBrushChanged();

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

class DeclarativePieSeries : public QPieSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(PieSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativePieSeries(QQuickItem *parent = 0);
    QQmlListProperty<QObject> seriesChildren();
    Q_INVOKABLE QPieSlice *at(int index);
    Q_INVOKABLE QPieSlice *find(QString label);
    Q_INVOKABLE DeclarativePieSlice *append(QString label, qreal value);
    Q_INVOKABLE bool remove(QPieSlice *slice);
    Q_INVOKABLE void clear();

public:
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void sliceAdded(QPieSlice *slice);
    void sliceRemoved(QPieSlice *slice);

public Q_SLOTS:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);
    void handleAdded(const QList<QPieSlice *> &slices);
    void handleRemoved(const QList<QPieSlice *> &slices);
};

QT_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
