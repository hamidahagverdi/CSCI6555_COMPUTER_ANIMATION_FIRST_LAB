#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include "Renderer.h"
#include "GlobalVariables.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Global::WIDTH, Global::HEIGHT);
    glutCreateWindow("Key-Framing (C++/OpenGL)");

    Renderer::init();
    glutDisplayFunc([](){ Renderer::display(); });
    glutReshapeFunc([](int w,int h){ Renderer::reshape(w,h); });
    glutIdleFunc([](){ Renderer::idle(); });

    glutMainLoop();
    return 0;
}
