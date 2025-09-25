#pragma once
#include <string>

class Renderer {
public:
    static void init();
    static void reshape(int w, int h);
    static void display();
    static void idle();
private:
    static float t;              // ← defined in Renderer.cpp
    static int pointIndex;       // ← defined in Renderer.cpp
    static std::string spline;   // ← defined in Renderer.cpp
};
