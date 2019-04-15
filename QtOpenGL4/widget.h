#ifndef WIDGET_H
#define WIDGET_H

#include <GL/glew.h>
#include <GL/wglew.h>

#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    Widget(const QGLFormat& format, QWidget *parent = 0);
    ~Widget();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:

    void createSquare();

    Shader *shader;

    int windowwidth;
    int windowheight;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 modelMatrix;

    unsigned int vaoID[1];

    unsigned int vboID[2];


};

#endif // WIDGET_H
