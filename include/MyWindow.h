#pragma once

#include "Macros.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MyWindow
{
public:
	MyWindow(int width,int height, const char* windowText)
	{
	    mWindow = glfwCreateWindow(width, height, windowText, NULL, NULL);
	    glfwSetWindowUserPointer(mWindow, this);
	    glfwSetKeyCallback(mWindow, onKey);
	}

	~MyWindow()
	{
	    glfwDestroyWindow(mWindow);
	}

    // virtual in case you want to override it in child class
    virtual void onKey(int key, int scancode, int actions, int mods)
    {
        // ... do whatever you want here
    }

private:
    GLFWwindow* mWindow;

    static void onKey(GLFWwindow* window, int key, int scancode, int actions, int mods)
    {
        MyWindow* obj = glfwGetWindowUserPointer(window);
        obj->onKey(key, scancode, actions, mods);
    }
};