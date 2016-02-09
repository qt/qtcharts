/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#ifndef DECLARATIVERENDERNODE_P_H
#define DECLARATIVERENDERNODE_P_H

#include <QtCharts/QChartGlobal>
#include <private/glxyseriesdata_p.h>
#include <QtQuick/QSGSimpleTextureNode>
#include <QtQuick/QQuickWindow>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOpenGLBuffer>

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
    int m_matrixUniformLoc;
    QOpenGLVertexArrayObject m_vao;
    QHash<const QAbstractSeries *, QOpenGLBuffer *> m_seriesBufferMap;
    bool m_renderNeeded;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVERENDERNODE_P_H
