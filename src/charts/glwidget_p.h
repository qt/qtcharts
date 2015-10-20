/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#ifndef QT_NO_OPENGL

#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtCore/QHash>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class QOpenGLBuffer;

QT_CHARTS_BEGIN_NAMESPACE

class GLXYSeriesDataManager;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(GLXYSeriesDataManager *xyDataManager, QWidget *parent = 0);
    ~GLWidget();

public Q_SLOTS:
    void cleanup();
    void cleanXYSeriesResources(const QXYSeries *series);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram *m_program;
    int m_shaderAttribLoc;
    int m_colorUniformLoc;
    int m_minUniformLoc;
    int m_deltaUniformLoc;
    int m_pointSizeUniformLoc;
    QOpenGLVertexArrayObject m_vao;

    QHash<const QAbstractSeries *, QOpenGLBuffer *> m_seriesBufferMap;
    GLXYSeriesDataManager *m_xyDataManager;
};

QT_CHARTS_END_NAMESPACE
#endif
#endif
