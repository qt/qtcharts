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

#ifndef DECLARATIVEOPENGLRENDERNODE_P_H
#define DECLARATIVEOPENGLRENDERNODE_P_H

#include <private/declarativeabstractrendernode_p.h>

#include <QtCharts/QChartGlobal>
#include <private/glxyseriesdata_p.h>
#include <QtQuick/QSGImageNode>
#include <QtQuick/QQuickWindow>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLFunctions>
#include <QtOpenGL/QOpenGLFramebufferObject>
#include <QtOpenGL/QOpenGLBuffer>

QT_BEGIN_NAMESPACE

class DeclarativeOpenGLRenderNode : public QObject, public DeclarativeAbstractRenderNode, QOpenGLFunctions
{
    Q_OBJECT
public:
    DeclarativeOpenGLRenderNode(QQuickWindow *window);
    ~DeclarativeOpenGLRenderNode();

    void initGL();
    QSize textureSize() const override { return m_textureSize; }
    void setTextureSize(const QSize &size) override;

    void setSeriesData(bool mapDirty, const GLXYDataMap &dataMap) override;
    void setRect(const QRectF &rect) override;
    void setAntialiasing(bool enable) override;
    void addMouseEvents(const QList<QMouseEvent *> &events) override;
    void takeMouseEventResponses(QList<MouseEventResponse> &responses) override;

public Q_SLOTS:
    void render();

private:
    void renderGL(bool selection);
    void renderSelection();
    void renderVisual();
    void recreateFBO();
    void cleanXYSeriesResources(const QXYSeries *series);
    void handleMouseEvents();
    const QXYSeries *findSeriesAtEvent(QMouseEvent *event);

    QSGTexture *m_texture;
    QSGImageNode *m_imageNode;
    QQuickWindow *m_window;
    QQuickWindow::CreateTextureOptions m_textureOptions;
    QSize m_textureSize;
    bool m_recreateFbo;
    GLXYDataMap m_xyDataMap;
    QOpenGLFramebufferObject *m_fbo;
    QOpenGLFramebufferObject *m_resolvedFbo;
    QOpenGLFramebufferObject *m_selectionFbo;
    QOpenGLShaderProgram *m_program;
    int m_shaderAttribLoc;
    int m_colorUniformLoc;
    int m_minUniformLoc;
    int m_deltaUniformLoc;
    int m_pointSizeUniformLoc;
    int m_matrixUniformLoc;
    QOpenGLVertexArrayObject m_vao;
    QHash<const QAbstractSeries *, QOpenGLBuffer *> m_seriesBufferMap;
    bool m_renderNeeded;
    QRectF m_rect;
    bool m_antialiasing;
    QList<QMouseEvent *> m_mouseEvents;
    QList<MouseEventResponse> m_mouseEventResponses;
    bool m_selectionRenderNeeded;
    QList<const QXYSeries *> m_selectionList;
    QPoint m_mousePressPos;
    bool m_mousePressed;
    const QXYSeries *m_lastPressSeries;
    const QXYSeries *m_lastHoverSeries;
};

QT_END_NAMESPACE

#endif // DECLARATIVEOPENGLRENDERNODE_P_H
