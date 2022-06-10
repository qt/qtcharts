// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef GLWIDGET_H
#define GLWIDGET_H

#ifndef QT_NO_OPENGL

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QOpenGLFunctions>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLFramebufferObject>
#include <QtCore/QHash>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QChart>
#include <QtCore/private/qglobal_p.h>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

QT_BEGIN_NAMESPACE

class GLXYSeriesDataManager;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(GLXYSeriesDataManager *xyDataManager, QChart *chart, QGraphicsView *parent = 0);
    ~GLWidget();

    bool needsReset() const;

public Q_SLOTS:
    void cleanup();
    void cleanXYSeriesResources(const QXYSeries *series);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QXYSeries *findSeriesAtEvent(QMouseEvent *event);
    void render(bool selection);
    void recreateSelectionFbo();
    QXYSeries *chartSeries(const QXYSeries *cSeries);

    QOpenGLShaderProgram *m_program;
    int m_shaderAttribLoc;
    int m_colorUniformLoc;
    int m_minUniformLoc;
    int m_deltaUniformLoc;
    int m_pointSizeUniformLoc;
    int m_matrixUniformLoc;
    QOpenGLVertexArrayObject m_vao;

    QHash<const QAbstractSeries *, QOpenGLBuffer *> m_seriesBufferMap;
    GLXYSeriesDataManager *m_xyDataManager;
    bool m_antiAlias;
    QGraphicsView *m_view;
    QOpenGLFramebufferObject *m_selectionFbo;
    QSize m_fboSize;
    QList<const QXYSeries *> m_selectionList;
    QChart *m_chart;
    bool m_recreateSelectionFbo;
    bool m_selectionRenderNeeded;
    QPoint m_mousePressPos;
    bool m_mousePressed;
    QXYSeries *m_lastPressSeries;
    QXYSeries *m_lastHoverSeries;
};

QT_END_NAMESPACE
#endif
#endif
