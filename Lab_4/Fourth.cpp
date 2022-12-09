#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdlib>
#include <cstring>

Display *display;
Window window;
GC gc;

void mydraw() {
    auto red = 0xFF0000;
    auto blue = 0x0000FF;
    auto white = 0xFFFFFF;
    auto grey = 0xBEBEBE;
    auto yellow = 0xFFFF00;
    auto orange = 0xFF6600;

    XPoint up[3];
    up[0].x=350;up[0].y=150; up[1].x=400;up[1].y=50; up[2].x=450;up[2].y=150;
    XSetForeground(display, gc, red); XFillPolygon(display, window, gc, up, 3, Convex, CoordModeOrigin); // Нос ракеты

    XPoint left_wing[3];
    left_wing[0].x=300;left_wing[0].y=370; left_wing[1].x=350;left_wing[1].y=250; left_wing[2].x=350;left_wing[2].y=370;
    XSetForeground(display, gc, red); XFillPolygon(display, window, gc, left_wing, 3, Convex, CoordModeOrigin); // Левое крыло

    XPoint right_wing[3];
    right_wing[0].x=450;right_wing[0].y=250; right_wing[1].x=500;right_wing[1].y=370; right_wing[2].x=450;right_wing[2].y=370;
    XSetForeground(display, gc, red); XFillPolygon(display, window, gc, right_wing, 3, Convex, CoordModeOrigin); // Правое крыло

    XSetForeground(display, gc, grey); XFillRectangle(display, window, gc, 350, 150, 100, 250); // Корпус

    XSetForeground(display, gc, blue); XFillArc(display, window, gc, 375, 250, 50, 50, 0*64, 360*64); // Иллюминаторы
    XSetForeground(display, gc, blue); XFillArc(display, window, gc, 375, 325, 50, 50, 0*64, 360*64);

    XSetForeground(display, gc, white); XFillRectangle(display, window, gc, 370, 175, 60, 15); // Флаг России
    XSetForeground(display, gc, blue); XFillRectangle(display, window, gc, 370, 190, 60, 15);
    XSetForeground(display, gc, red); XFillRectangle(display, window, gc, 370, 205, 60, 15);

    XPoint left_turbine[3];
    left_turbine[0].x=350;left_turbine[0].y=450; left_turbine[1].x=375;left_turbine[1].y=400; left_turbine[2].x=400;left_turbine[2].y=450;
    XSetForeground(display, gc, red); XFillPolygon(display, window, gc, left_turbine, 3, Convex, CoordModeOrigin); // Левая турбина

    XPoint right_turbine[3];
    right_turbine[0].x=400;right_turbine[0].y=450; right_turbine[1].x=425;right_turbine[1].y=400; right_turbine[2].x=450;right_turbine[2].y=450;
    XSetForeground(display, gc, red); XFillPolygon(display, window, gc, right_turbine, 3, Convex, CoordModeOrigin); // Правая турбина

    XPoint left_fire[3];
    left_fire[0].x=355;left_fire[0].y=450; left_fire[1].x=375;left_fire[1].y=480; left_fire[2].x=395;left_fire[2].y=450;
    XSetForeground(display, gc, orange); XFillPolygon(display, window, gc, left_fire, 3, Convex, CoordModeOrigin); // Огонь

    XPoint right_fire[3];
    right_fire[0].x=405;right_fire[0].y=450; right_fire[1].x=425;right_fire[1].y=480; right_fire[2].x=445;right_fire[2].y=450;
    XSetForeground(display, gc, orange); XFillPolygon(display, window, gc, right_fire, 3, Convex, CoordModeOrigin);

    XPoint left_fire_y[3];
    left_fire_y[0].x=363;left_fire_y[0].y=450; left_fire_y[1].x=375;left_fire_y[1].y=475; left_fire_y[2].x=387;left_fire_y[2].y=450;
    XSetForeground(display, gc, yellow); XFillPolygon(display, window, gc, left_fire_y, 3, Convex, CoordModeOrigin); // Также огонь

    XPoint right_fire_y[3];
    right_fire_y[0].x=413;right_fire_y[0].y=450; right_fire_y[1].x=425;right_fire_y[1].y=475; right_fire_y[2].x=437;right_fire_y[2].y=450;
    XSetForeground(display, gc, yellow); XFillPolygon(display, window, gc, right_fire_y, 3, Convex, CoordModeOrigin);

    XSetForeground(display, gc, white); XFillArc(display, window, gc, 100, 100, 5, 5, 0*64, 360*64); // Звезды
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 123, 123, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 715, 85, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 500, 600, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 224, 433, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 535, 440, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 415, 545, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 300, 95, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 698, 612, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 175, 460, 5, 5, 0*64, 360*64);
    XSetForeground(display, gc, white); XFillArc(display, window, gc, 600, 333, 5, 5, 0*64, 360*64);

    XSetForeground(display, gc, yellow); XFillArc(display, window, gc, 625, 225, 75, 75, 0*64, 360*64); // Солнце

}


int main(void) {
    XEvent e; int s;
    if ((display = XOpenDisplay(getenv("DISPLAY"))) == NULL) exit(1);
    s = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, s),
                                 100, 100, 800, 600, 1, 0x000000, 0x000000);
    XSelectInput(display, window, ExposureMask|KeyPressMask|ButtonPressMask);
    XMapWindow(display, window);
    gc = XCreateGC(display, DefaultRootWindow(display), 0, 0);
    while (1) {
        XNextEvent(display, &e);
        if (e.type == Expose) mydraw();
        if ((e.type == KeyPress)&&(XLookupKeysym(&e.xkey,0)==XK_Escape)) break;
        if ((e.type == ButtonPress)&&(e.xbutton.x<10)&&(e.xbutton.y<10)) break;
    }
    XCloseDisplay(display);
}
