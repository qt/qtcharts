/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef DECLARATIVERENDERNODE_P_H
#define DECLARATIVERENDERNODE_P_H

#include <QtCharts/QChartGlobal>
#include <private/glxyseriesdata_p.h>
#include <QtQuick/QSGSimpleTextureNode>
#include <QtQuick/QQuickWindow>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLFunctions>

class QOpenGLFramebufferObject;
class QOpenGLBuffer;

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativeRenderNode : public QObject, public QSGSimpleTextureNode, QOpenGLFunctions
{
    Q_OBJECT
public:
    DeclarativeRenderNode(QQuickWindow *window);
    ~DeclarativeRenderNode();

    void initGL();
    QSize textureSize() const { return m_textureSize; }
    void setTextureSize(const QSize &size);
    void setSeriesData(bool mapDirty, const GLXYDataMap &dataMap);

public Q_SLOTS:
    void render();

private:
    void renderGL();
    void recreateFBO();
    void cleanXYSeriesResources(const QXYSeries *series);

    QSGTexture *m_texture;
    QQuickWindow *m_window;
    QQuickWindow::CreateTextureOptions m_textureOptions;
    QSize m_textureSize;
    bool m_recreateFbo;
    GLXYDataMap m_xyDataMap;
    QOpenGLFramebufferObject *m_fbo;
    QOpenGLShaderProgram *m_program;
    int m_shaderAttribLoc;
    int m_colorUniformLoc;
    int m_minUniformLoc;
    int m_deltaUniformLoc;
    int m_pointSizeUniformLoc;
    QOpenGLVertexArrayObject m_vao;
    QHash<const QAbstractSeries *, QOpenGLBuffer *> m_seriesBufferMap;
    bool m_renderNeeded;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVERENDERNODE_P_H
