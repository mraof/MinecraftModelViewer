#include "oswin.h"
#include "globals.h"
#include "input.h"

extern int running;

namespace OS
{
    HWND os_window;
    HDC os_device_context;
    HGLRC os_render_context;
    LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
    {
        switch(msg)
        {
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
            case WM_KEYDOWN:
//                if(HIWORD(lParam) & KF_REPEAT) break; //No key repeat
//                else
                    keyPress(wParam);
                return 0;
            break;
        }

        return DefWindowProc(hWnd,msg,wParam,lParam);
    }

    int init()
    {
        WNDCLASSEX wclass;
        ZeroMemory(&wclass, sizeof(WNDCLASSEX));

        wclass.cbClsExtra = NULL;
        wclass.cbSize = sizeof(WNDCLASSEX);
        wclass.cbWndExtra = NULL;
        wclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wclass.hIcon = NULL;
        wclass.hInstance = GetModuleHandle(NULL);
        wclass.lpfnWndProc = (WNDPROC)WinProc;
        wclass.lpszClassName = WINDOW_CLASS;
        wclass.lpszMenuName = NULL;
        wclass.style = CS_OWNDC;

        RegisterClassEx(&wclass);

        os_window = CreateWindowEx(NULL, WINDOW_CLASS, WINDOW_TITLE,  WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WINDOW_STYLE,
                                    CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);

        ShowWindow(os_window, SW_SHOW);
        PIXELFORMATDESCRIPTOR pfg =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
            PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
            32,                        //Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                        //Number of bits for the depthbuffer
            8,                        //Number of bits for the stencilbuffer
            0,                        //Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0,
        };
        os_device_context = GetDC(os_window);
        int pixelFormat = ChoosePixelFormat(os_device_context, &pfg);
        SetPixelFormat(os_device_context, pixelFormat, &pfg);

        os_render_context = wglCreateContext(os_device_context);
        wglMakeCurrent(os_device_context, os_render_context);
    }
    void deinit()
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(os_render_context);
        ReleaseDC(os_window, os_device_context);
    }
    void refresh()
    {
        SwapBuffers(os_device_context);
        MSG _msg;
        while(PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
        {
            if(_msg.message == WM_QUIT)
            {
                running = false;
            }
            else
            {
                TranslateMessage(&_msg);
                DispatchMessage(&_msg);
            }
        }
    }
}
