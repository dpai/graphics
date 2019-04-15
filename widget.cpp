#include "widget.h"
#include <iostream>


Widget::Widget(const QGLFormat &format, QWidget *parent)
    : QGLWidget(format, parent)
{
    windowwidth = 944;
    windowheight = 393;

}

Widget::~Widget()
{

}


void Widget::initializeGL()
{
    ///// Iniltialize Glew
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();

    if (error != GLEW_OK)
    {
        qWarning() << "Could not Initialize GLEW " ;
        return;
    }

    int glVersion[2] = {-1, -1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

    qWarning() << "Using OPENGL " << glVersion[0] <<  "." << glVersion[1] ;

    QGLFormat format = QGLWidget::format();

    if (!format.sampleBuffers())
    {
        qWarning() << "Cound not enable sample bufferes Check";
    }

    glClearColor(0.4f, 0.6f, 0.9f, 0.0f);

    shader = new Shader("C:\\Workspace\\Qt_Opengl\\GLWidget\\glwindow\\shader.vert",
                        "C:\\Workspace\\Qt_Opengl\\GLWidget\\glwindow\\shader.frag");

    projectionMatrix = glm::perspective(60.0f, (float)windowwidth/windowheight, 0.1f, 100.f);



    createSquare();

}

void Widget::createSquare()
{
    float *vertices = new float[18];
    float *colors = new float[18];

    vertices[0] = -0.5; vertices[1] = -0.5; vertices[2] = 0.0; // Bottom left corner
    colors[0] = 1.0; colors[1] = 1.0; colors[2] = 1.0; // Bottom left corner

    vertices[3] = -0.5; vertices[4] = 0.5; vertices[5] = 0.0; // Top left corner
    colors[3] = 1.0; colors[4] = 0.0; colors[5] = 0.0; // Top left corner

    vertices[6] = 0.5; vertices[7] = 0.5; vertices[8] = 0.0; // Top Right corner
    colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; // Top Right corner

    vertices[9] = 0.5; vertices[10] = -0.5; vertices[11] = 0.0; // Bottom right corner
    colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner

    vertices[12] = -0.5; vertices[13] = -0.5; vertices[14] = 0.0; // Bottom left corner
    colors[12] = 1.0; colors[13] = 1.0; colors[14] = 1.0; // Bottom left corner

    vertices[15] = 0.5; vertices[16] = 0.5; vertices[17] = 0.0; // Top Right corner
    colors[15] = 0.0; colors[16] = 1.0; colors[17] = 0.0; // Top Right corner

    glGenVertexArrays(1, &vaoID[0]);
    glBindVertexArray(vaoID[0]);

    glGenBuffers(2,&vboID[0]);

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);


    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint)3, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    delete [] vertices; // Delete our vertices from memory
    delete [] colors;
}

void Widget::resizeGL(int w, int h)
{
    windowwidth = w;
    windowheight = h;
}


void Widget::paintGL()
{
    qWarning() << "Inside Paint";
    qWarning() << windowwidth << "'" << windowheight ;
    glViewport(0,0, windowwidth, windowheight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    shader->bind();

    viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f));
    modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

    int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix");
    int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix");
    int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix");

    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

    glBindVertexArray(vaoID[0]);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    shader->unbind();

}
