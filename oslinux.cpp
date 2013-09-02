#include "oslinux.h"
#include "input.h"
#include <GL/glx.h>
#include <sys/time.h>


namespace OS
{
    Display                 *dpy;
    Window                  root;
    GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    XVisualInfo             *vi;
    Colormap                cmap;
    XSetWindowAttributes    swa;
    Window                  win;
    GLXContext              glc;
    XWindowAttributes       gwa;
    XEvent                  xev;

    int init()
    {
        dpy = XOpenDisplay(NULL);
        root = DefaultRootWindow(dpy);
        vi = glXChooseVisual(dpy, 0, att);
        cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask;
        win = XCreateWindow(dpy, root, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
        XMapWindow(dpy, win);
        XStoreName(dpy, win, "X11 version");
        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
    }
    void refresh()
    {
        glXSwapBuffers(dpy, win);
        XEvent msg;
        XEvent next;
        while(XPending(dpy) > 0)
        {
            XNextEvent(dpy, &msg);
            switch(msg.type)
            {
            case KeyPress:
                keyPress(XLookupKeysym(&msg.xkey, 0));
                break;
            }

        }
    }
    void deinit()
    {
        glXMakeCurrent(dpy, None, NULL);
        XCloseDisplay(dpy);
    }
    unsigned long getTime()
    {
        struct timeval tv;
        gettimeofday(&tv, 0);
        return (unsigned long)((tv.tv_sec * 1000 + tv.tv_usec / 1000));
    }

}
