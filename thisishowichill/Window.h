#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {

public:
    
   static enum enScreenMode {
        FullScreen  ,
        Windowed
    };

   static struct MouseState {
       int lastButton;
       int lastAction;
       bool hasNewClick = false;
   };

    Window(enScreenMode enVarScreenMode, const char* WindowName);



    void SwapBuffers();
    void LoadWindowBG();
    void StartWindow();
    void TerminateWindow();
    void GetEventsOnWindow();
    int OnMouseClick();

    //Getters
    bool isWindowActive();
    int getwidth();
    int getheight();
    
    GLFWwindow* get() {
        return __window;
    }

private:

    int width, height;


    GLFWwindow* __window;
    GLFWmonitor* __primaryMonitor;  
    const GLFWvidmode* __mode;
    bool __isWindowActive;
    enScreenMode WindowMode;
    const char* WindowName;

    
    void __init();
    void __setPrimaryMonitorSpecifications();
    void __setFullScreenWindowHints();
    bool __StartFullScreenWindow(const char* WindowName);
    void __setDefaultWindowBuffer();
    void __terminateWindow();
    void __UpdateIsWindowActive();

    //Coming feature to control speed by right/left click
 
    //static void __mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    //int getClickedButton();
};

