#include "widget.h"
#include <QApplication>
#include <QGLFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat   format;
    format.setVersion(4,4);
    format.setProfile(QGLFormat::CoreProfile);
    format.setDepthBufferSize(32);
    format.setRedBufferSize(32);
    format.setGreenBufferSize(32);
    format.setBlueBufferSize(32);
    format.setSampleBuffers(true);
    format.setDoubleBuffer(true);

    Widget w(format);
    w.show();

    return a.exec();
}
