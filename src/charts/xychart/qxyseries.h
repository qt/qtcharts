/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QXYSERIES_H
#define QXYSERIES_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QAbstractSeries>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QImage>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QXYSeriesPrivate;
class QXYModelMapper;

class Q_CHARTS_EXPORT QXYSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(bool pointsVisible READ pointsVisible WRITE setPointsVisible)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor selectedColor READ color WRITE setSelectedColor NOTIFY selectedColorChanged REVISION(6, 2))
    Q_PROPERTY(QString pointLabelsFormat READ pointLabelsFormat WRITE setPointLabelsFormat NOTIFY pointLabelsFormatChanged)
    Q_PROPERTY(bool pointLabelsVisible READ pointLabelsVisible WRITE setPointLabelsVisible NOTIFY pointLabelsVisibilityChanged)
    Q_PROPERTY(QFont pointLabelsFont READ pointLabelsFont WRITE setPointLabelsFont NOTIFY pointLabelsFontChanged)
    Q_PROPERTY(QColor pointLabelsColor READ pointLabelsColor WRITE setPointLabelsColor NOTIFY pointLabelsColorChanged)
    Q_PROPERTY(bool pointLabelsClipping READ pointLabelsClipping WRITE setPointLabelsClipping NOTIFY pointLabelsClippingChanged)
    Q_PROPERTY(bool bestFitLineVisible READ bestFitLineVisible WRITE setBestFitLineVisible NOTIFY bestFitLineVisibilityChanged REVISION(6, 2))
    Q_PROPERTY(QColor bestFitLineColor READ bestFitLineColor WRITE setBestFitLineColor NOTIFY bestFitLineColorChanged REVISION(6, 2))

protected:
    explicit QXYSeries(QXYSeriesPrivate &d, QObject *parent = nullptr);

public:
    enum class PointConfiguration {
        Color = 0,
        Size,
        Visibility,
        LabelVisibility
    };
    Q_ENUM(PointConfiguration)

public:
    ~QXYSeries();
    void append(qreal x, qreal y);
    void append(const QPointF &point);
    void append(const QList<QPointF> &points);
    void replace(qreal oldX, qreal oldY, qreal newX, qreal newY);
    void replace(const QPointF &oldPoint, const QPointF &newPoint);
    void replace(int index, qreal newX, qreal newY);
    void replace(int index, const QPointF &newPoint);
    void remove(qreal x, qreal y);
    void remove(const QPointF &point);
    void remove(int index);
    void removePoints(int index, int count);
    void insert(int index, const QPointF &point);
    void clear();

    int count() const;
    QList<QPointF> points() const;
#if QT_DEPRECATED_SINCE(6, 0)
    QT_DEPRECATED_X("Use points() instead")
    QList<QPointF> pointsVector() const;
#endif
    const QPointF &at(int index) const;

    QXYSeries &operator << (const QPointF &point);
    QXYSeries &operator << (const QList<QPointF> &points);

    virtual void setPen(const QPen &pen);
    QPen pen() const;

    virtual void setBrush(const QBrush &brush);
    QBrush brush() const;

    virtual void setColor(const QColor &color);
    virtual QColor color() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setPointsVisible(bool visible = true);
    bool pointsVisible() const;

    void setPointLabelsFormat(const QString &format);
    QString pointLabelsFormat() const;

    void setPointLabelsVisible(bool visible = true);
    bool pointLabelsVisible() const;

    void setPointLabelsFont(const QFont &font);
    QFont pointLabelsFont() const;

    void setPointLabelsColor(const QColor &color);
    QColor pointLabelsColor() const;

    void setPointLabelsClipping(bool enabled = true);
    bool pointLabelsClipping() const;

    void replace(const QList<QPointF> &points);

    bool isPointSelected(int index);
    void selectPoint(int index);
    void deselectPoint(int index);
    void setPointSelected(int index, bool selected);
    void selectAllPoints();
    void deselectAllPoints();
    void selectPoints(const QList<int> &indexes);
    void deselectPoints(const QList<int> &indexes);
    void toggleSelection(const QList<int> &indexes);
    QList<int> selectedPoints() const;

    void setLightMarker(const QImage &lightMarker);
    const QImage &lightMarker() const;

    void setSelectedLightMarker(const QImage &selectedLightMarker);
    const QImage &selectedLightMarker() const;

    void setMarkerSize(qreal size);
    qreal markerSize() const;

    void setBestFitLineVisible(bool visible = true);
    bool bestFitLineVisible() const;
    QPair<qreal, qreal> bestFitLineEquation(bool &ok) const;

    void setBestFitLinePen(const QPen &pen);
    QPen bestFitLinePen() const;
    void setBestFitLineColor(const QColor &color);
    QColor bestFitLineColor() const;

    void clearPointConfiguration(const int index);
    void clearPointConfiguration(const int index, const PointConfiguration key);
    void clearPointsConfiguration();
    void clearPointsConfiguration(const PointConfiguration key);
    void setPointConfiguration(const int index,
                               const QHash<PointConfiguration, QVariant> &configuration);
    void setPointConfiguration(const int index, const PointConfiguration key,
                               const QVariant &value);
    void setPointsConfiguration(
            const QHash<int, QHash<QXYSeries::PointConfiguration, QVariant>> &pointsConfiguration);
    QHash<PointConfiguration, QVariant> pointConfiguration(const int index) const;
    QHash<int, QHash<PointConfiguration, QVariant>> pointsConfiguration() const;

    void sizeBy(const QList<qreal> &sourceData, const qreal minSize, const qreal maxSize);
    void colorBy(const QList<qreal> &sourceData, const QLinearGradient &gradient = QLinearGradient());

Q_SIGNALS:
    void clicked(const QPointF &point);
    void hovered(const QPointF &point, bool state);
    void pressed(const QPointF &point);
    void released(const QPointF &point);
    void doubleClicked(const QPointF &point);
    void pointReplaced(int index);
    void pointRemoved(int index);
    void pointAdded(int index);
    void colorChanged(QColor color);
    Q_REVISION(6, 2) void selectedColorChanged(const QColor &color);
    void pointsReplaced();
    void pointLabelsFormatChanged(const QString &format);
    void pointLabelsVisibilityChanged(bool visible);
    void pointLabelsFontChanged(const QFont &font);
    void pointLabelsColorChanged(const QColor &color);
    void pointLabelsClippingChanged(bool clipping);
    void pointsRemoved(int index, int count);
    void penChanged(const QPen &pen);
    void selectedPointsChanged();
    Q_REVISION(6, 2) void lightMarkerChanged(const QImage &lightMarker);
    Q_REVISION(6, 2) void selectedLightMarkerChanged(const QImage &selectedLightMarker);
    Q_REVISION(6, 2) void bestFitLineVisibilityChanged(bool visible);
    Q_REVISION(6, 2) void bestFitLinePenChanged(const QPen &pen);
    Q_REVISION(6, 2) void bestFitLineColorChanged(const QColor &color);
    Q_REVISION(6, 2) void pointsConfigurationChanged(
            const QHash<int, QHash<PointConfiguration, QVariant>> &configuration);
    void markerSizeChanged(qreal size);

private:
    Q_DECLARE_PRIVATE(QXYSeries)
    Q_DISABLE_COPY(QXYSeries)
    friend class QXYLegendMarkerPrivate;
    friend class XYLegendMarker;
    friend class XYChart;
    friend class QColorAxisPrivate;
};

QT_END_NAMESPACE

#endif // QXYSERIES_H
