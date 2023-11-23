// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtQml/qqmlregistration.h>
#include <private/glxyseriesdata_p.h>
#include <private/declarativechartglobal_p.h>
#include <private/declarativeabstractrendernode_p.h>

#include <QtCore/QtGlobal>
#include <QtQuick/QQuickItem>
#include <QtWidgets/QGraphicsScene>

#include <QtCharts/QChart>
#include <QtCore/QLocale>
#include <QQmlComponent>

Q_MOC_INCLUDE(<QtCharts/qlegend.h>)
Q_MOC_INCLUDE("declarativemargins_p.h")

QT_BEGIN_NAMESPACE

class DeclarativeMargins;
class Domain;
class DeclarativeAxes;

class Q_CHARTSQML_EXPORT DeclarativeChart : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme)
    Q_PROPERTY(Animation animationOptions READ animationOptions WRITE setAnimationOptions)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged REVISION(2, 1))
    Q_PROPERTY(QEasingCurve animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve NOTIFY animationEasingCurveChanged REVISION(2, 1))
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
    Q_PROPERTY(QLegend *legend READ legend CONSTANT)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool dropShadowEnabled READ dropShadowEnabled WRITE setDropShadowEnabled NOTIFY dropShadowEnabledChanged)
    Q_PROPERTY(qreal backgroundRoundness READ backgroundRoundness WRITE setBackgroundRoundness NOTIFY backgroundRoundnessChanged REVISION(1, 3))
    Q_PROPERTY(DeclarativeMargins *margins READ margins NOTIFY marginsChanged REVISION(1, 2))
    Q_PROPERTY(QRectF plotArea READ plotArea WRITE setPlotArea NOTIFY plotAreaChanged REVISION(1, 1))
    Q_PROPERTY(QColor plotAreaColor READ plotAreaColor WRITE setPlotAreaColor NOTIFY plotAreaColorChanged REVISION(1, 3))
    Q_PROPERTY(QQmlListProperty<QAbstractAxis> axes READ axes REVISION(1, 2))
    Q_PROPERTY(bool localizeNumbers READ localizeNumbers WRITE setLocalizeNumbers NOTIFY localizeNumbersChanged REVISION(2, 0))
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale NOTIFY localeChanged REVISION(2, 0))
    Q_ENUMS(Animation)
    Q_ENUMS(Theme)
    Q_ENUMS(SeriesType)
    QML_NAMED_ELEMENT(ChartView)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    // duplicating enums from QChart to make the QML api namings 1-to-1 with the C++ api
    enum Theme {
        ChartThemeLight = 0,
        ChartThemeBlueCerulean,
        ChartThemeDark,
        ChartThemeBrownSand,
        ChartThemeBlueNcs,
        ChartThemeHighContrast,
        ChartThemeBlueIcy,
        ChartThemeQt
    };

    enum Animation {
        NoAnimation = 0x0,
        GridAxisAnimations = 0x1,
        SeriesAnimations = 0x2,
        AllAnimations = 0x3
    };

    enum SeriesType {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline,
        SeriesTypeHorizontalBar,
        SeriesTypeHorizontalStackedBar,
        SeriesTypeHorizontalPercentBar,
        SeriesTypeBoxPlot,
        SeriesTypeCandlestick
    };

public:
    DeclarativeChart(QQuickItem *parent = 0);
    ~DeclarativeChart();

public: // From parent classes
    void childEvent(QChildEvent *event) override;
    void componentComplete() override;
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private Q_SLOTS:
    void handleAntialiasingChanged(bool enable);
    void sceneChanged(const QList<QRectF> &region);
    void renderScene();

public:
    void setTheme(DeclarativeChart::Theme theme);
    DeclarativeChart::Theme theme();
    void setAnimationOptions(DeclarativeChart::Animation animations);
    DeclarativeChart::Animation animationOptions();
    void setAnimationDuration(int msecs);
    int animationDuration() const;
    void setAnimationEasingCurve(const QEasingCurve &curve);
    QEasingCurve animationEasingCurve() const;
    void setTitle(QString title);
    QString title();
    QLegend *legend();
    QFont titleFont() const;
    void setTitleFont(const QFont &font);
    void setTitleColor(QColor color);
    QColor titleColor();
    void setBackgroundColor(QColor color);
    QColor backgroundColor();
    void setPlotAreaColor(QColor color);
    QColor plotAreaColor();
    void setLocalizeNumbers(bool localize);
    bool localizeNumbers() const;
    void setLocale(const QLocale &locale);
    QLocale locale() const;

    int count();
    void setDropShadowEnabled(bool enabled);
    bool dropShadowEnabled();
    qreal backgroundRoundness() const;
    void setBackgroundRoundness(qreal diameter);

    // Margins & plotArea
    DeclarativeMargins *margins() { return m_margins; }
    QRectF plotArea() { return m_chart->plotArea(); }
    void setPlotArea(const QRectF &rect);

    // Axis handling
    QAbstractAxis *defaultAxis(Qt::Orientation orientation, QAbstractSeries *series);
    void initializeAxes(QAbstractSeries *series);
    void doInitializeAxes(QAbstractSeries *series, DeclarativeAxes *axes);
    QQmlListProperty<QAbstractAxis> axes();
    static void axesAppendFunc(QQmlListProperty<QAbstractAxis> *list, QAbstractAxis *element);
    static qsizetype axesCountFunc(QQmlListProperty<QAbstractAxis> *list);
    static QAbstractAxis *axesAtFunc(QQmlListProperty<QAbstractAxis> *list, qsizetype index);
    static void axesClearFunc(QQmlListProperty<QAbstractAxis> *list);

public:
    Q_INVOKABLE QAbstractSeries *series(int index);
    Q_INVOKABLE QAbstractSeries *series(QString seriesName);
    Q_INVOKABLE QAbstractSeries *createSeries(int type, QString name = QString(),
                                              QAbstractAxis *axisX = 0, QAbstractAxis *axisY = 0);
    Q_INVOKABLE void removeSeries(QAbstractSeries *series);
    Q_INVOKABLE void removeAllSeries() { m_chart->removeAllSeries(); }
    Q_INVOKABLE void setAxisX(QAbstractAxis *axis, QAbstractSeries *series = 0);
    Q_INVOKABLE void setAxisY(QAbstractAxis *axis, QAbstractSeries *series = 0);
    Q_INVOKABLE QAbstractAxis *axisX(QAbstractSeries *series = 0);
    Q_INVOKABLE QAbstractAxis *axisY(QAbstractSeries *series = 0);
    Q_INVOKABLE void zoom(qreal factor);
    Q_REVISION(2, 1) Q_INVOKABLE void zoomIn();
    Q_REVISION(2, 1) Q_INVOKABLE void zoomIn(const QRectF &rectangle);
    Q_REVISION(2, 1) Q_INVOKABLE void zoomOut();
    Q_REVISION(2, 1) Q_INVOKABLE void zoomReset();
    Q_REVISION(2, 1) Q_INVOKABLE bool isZoomed();
    Q_INVOKABLE void scrollLeft(qreal pixels);
    Q_INVOKABLE void scrollRight(qreal pixels);
    Q_INVOKABLE void scrollUp(qreal pixels);
    Q_INVOKABLE void scrollDown(qreal pixels);
    Q_REVISION(2, 1) Q_INVOKABLE QPointF mapToValue(const QPointF &position,
                                                 QAbstractSeries *series = 0);
    Q_REVISION(2, 1) Q_INVOKABLE QPointF mapToPosition(const QPointF &value,
                                                    QAbstractSeries *series = 0);


Q_SIGNALS:
    void axisLabelsChanged();
    void titleColorChanged(QColor color);
    void backgroundColorChanged();
    void dropShadowEnabledChanged(bool enabled);
    Q_REVISION(1, 2) void marginsChanged();
    void plotAreaChanged(QRectF plotArea);
    void seriesAdded(QAbstractSeries *series);
    void seriesRemoved(QAbstractSeries *series);
    Q_REVISION(1, 3) void plotAreaColorChanged();
    Q_REVISION(1, 3) void backgroundRoundnessChanged(qreal diameter);
    Q_REVISION(2, 0) void localizeNumbersChanged();
    Q_REVISION(2, 0) void localeChanged();
    Q_REVISION(2, 1) void animationDurationChanged(int msecs);
    Q_REVISION(2, 1) void animationEasingCurveChanged(QEasingCurve curve);
    void needRender();
    void pendingRenderNodeMouseEventResponses();

private Q_SLOTS:
    void changeMargins(int top, int bottom, int left, int right);
    void handleAxisXSet(QAbstractAxis *axis);
    void handleAxisYSet(QAbstractAxis *axis);
    void handleAxisXTopSet(QAbstractAxis *axis);
    void handleAxisYRightSet(QAbstractAxis *axis);
    void handleSeriesAdded(QAbstractSeries *series);
    void handlePendingRenderNodeMouseEventResponses();

protected:
    explicit DeclarativeChart(QChart::ChartType type, QQuickItem *parent);

private:
    void initChart(QChart::ChartType type);
    void seriesAxisAttachHelper(QAbstractSeries *series, QAbstractAxis *axis,
                                Qt::Orientations orientation, Qt::Alignment alignment);
    void findMinMaxForSeries(QAbstractSeries *series,Qt::Orientations orientation,
                             qreal &min, qreal &max);
    void queueRendererMouseEvent(QMouseEvent *event);

    // Extending QChart with DeclarativeChart is not possible because QObject does not support
    // multi inheritance, so we now have a QChart as a member instead
    QChart *m_chart;
    QGraphicsScene *m_scene;
    QPointF m_mousePressScenePoint;
    QPoint m_mousePressScreenPoint;
    QPointF m_lastMouseMoveScenePoint;
    QPoint m_lastMouseMoveScreenPoint;
    Qt::MouseButton m_mousePressButton;
    Qt::MouseButtons m_mousePressButtons;
    QImage *m_sceneImage;
    bool m_sceneImageDirty;
    bool m_updatePending;
    Qt::HANDLE m_paintThreadId;
    Qt::HANDLE m_guiThreadId;
    DeclarativeMargins *m_margins;
    GLXYSeriesDataManager *m_glXYDataManager;
    bool m_sceneImageNeedsClear;
    QList<QMouseEvent *> m_pendingRenderNodeMouseEvents;
    QList<MouseEventResponse> m_pendingRenderNodeMouseEventResponses;
    QRectF m_adjustedPlotArea;
};

QT_END_NAMESPACE

#endif // DECLARATIVECHART_H
