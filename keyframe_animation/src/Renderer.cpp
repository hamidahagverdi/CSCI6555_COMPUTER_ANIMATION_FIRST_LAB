// src/Renderer.cpp
#include "Renderer.h"
#include "GlobalVariables.h"
#include "SplineMath.h"

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

// Silence macOS OpenGL deprecation warnings (optional)
#ifdef __APPLE__
  #ifndef GL_SILENCE_DEPRECATION
    #define GL_SILENCE_DEPRECATION
  #endif
#endif

// static members
float Renderer::t = 0.0f;
int   Renderer::pointIndex = 0;
std::string Renderer::spline = "Catmull-Rom Spline"; // or "B Spline"

static void enableLights() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat pos[4] = { 3.0f, 4.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    GLfloat white[4] = {1,1,1,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
}

void Renderer::init() {
    glClearColor(0.05f, 0.07f, 0.1f, 1.0f);
    enableLights();
}

void Renderer::reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);
}

void Renderer::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Quaternion interpolation (matches your JOGL intent)
    auto q   = Math::qInterpolation(spline, t, pointIndex);
    auto mat = q.toMatrix();     // column-major 4x4
    glLoadMatrixf(mat.data());

    glutSolidTeapot(2.0);

    glutSwapBuffers();
}

void Renderer::idle() {
    t += 0.01f;
    if (t >= 1.0f) {
        t = 0.0f;
        ++pointIndex;
        if (pointIndex + 3 >= Global::pointNum) pointIndex = 0;
    }
    glutPostRedisplay();
}
