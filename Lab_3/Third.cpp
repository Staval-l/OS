// Ракета в космосе

#include <windows.h>

void MyDraw(HWND h) {
    HDC dc = GetDC(h); // получить контекст

    HBRUSH b_red = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH b_blue = CreateSolidBrush(RGB(0, 0, 255));
    HBRUSH b_white = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH b_black = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH b_grey = CreateSolidBrush(RGB(190, 190, 190));
    HBRUSH b_yellow = CreateSolidBrush(RGB(255, 255, 0));
    HBRUSH b_orange = CreateSolidBrush(RGB(255, 102, 0));
    HBRUSH b_dark_grey = CreateSolidBrush(RGB(128, 128, 128));

    POINT pt_up[3] = { {350, 150}, {400, 50}, {450, 150} }; // Нос ракеты
    SelectObject(dc, b_red); Polygon(dc, pt_up, 3);

    POINT pt_left_wing[3] = { {300, 370}, {350, 250}, {350, 370} }; // Левое крыло
    SelectObject(dc, b_red); Polygon(dc, pt_left_wing, 3);

    POINT pt_right_wing[3] = { {450, 250}, {500, 370}, {450, 370} }; // Правое крыло
    SelectObject(dc, b_red); Polygon(dc, pt_right_wing, 3);

    SelectObject(dc, b_grey); Rectangle(dc, 350, 150, 450, 400); // Корпус

    SelectObject(dc, b_blue); Ellipse(dc, 375, 250, 425, 300); // Иллюминаторы
    SelectObject(dc, b_blue); Ellipse(dc, 375, 325, 425, 375);

    SelectObject(dc, b_white); Rectangle(dc, 370, 175, 430, 190); // Флаг России
    SelectObject(dc, b_blue); Rectangle(dc, 370, 190, 430, 205);
    SelectObject(dc, b_red); Rectangle(dc, 370, 205, 430, 220);

    POINT pt_left_turbine[3] = { {350, 450}, {375, 400}, {400, 450} }; // Левая турбина
    SelectObject(dc, b_red); Polygon(dc, pt_left_turbine, 3);
    POINT pt_right_turbine[3] = { {400, 450}, {425, 400}, {450, 450} }; // Правая турбина
    SelectObject(dc, b_red); Polygon(dc, pt_right_turbine, 3);

    POINT pt_left_fire[3] = { {355, 450}, {375, 480}, {395, 450} }; // Огонь
    SelectObject(dc, b_orange); Polygon(dc, pt_left_fire, 3);
    POINT pt_right_fire[3] = { {405, 450}, {425, 480}, {445, 450} };
    SelectObject(dc, b_orange); Polygon(dc, pt_right_fire, 3);

    POINT pt_left_fire_y[3] = { {363, 450}, {375, 475}, {387, 450} }; // Тоже огонь
    SelectObject(dc, b_yellow); Polygon(dc, pt_left_fire_y, 3);
    POINT pt_right_fire_y[3] = { {413, 450}, {425, 475}, {437, 450} };
    SelectObject(dc, b_yellow); Polygon(dc, pt_right_fire_y, 3);

    SelectObject(dc, b_white); Ellipse(dc, 100, 100, 105, 105); // Звезды
    Ellipse(dc, 123, 123, 128, 128); Ellipse(dc, 715, 85, 720, 90);
    Ellipse(dc, 500, 600, 505, 605); Ellipse(dc, 224, 433, 229, 438);
    Ellipse(dc, 535, 440, 540, 445); Ellipse(dc, 415, 545, 420, 550);
    Ellipse(dc, 300, 95, 305, 100); Ellipse(dc, 698, 612, 703, 617);
    Ellipse(dc, 175, 460, 180, 465); Ellipse(dc, 600, 333, 605, 338);

    SelectObject(dc, b_yellow); Ellipse(dc, 625, 225, 700, 300); // Солнце

    DeleteObject(b_red); DeleteObject(b_blue); // удалить кисти
    DeleteObject(b_white); DeleteObject(b_black); // удалить кисти
    DeleteObject(b_grey); DeleteObject(b_yellow);
    DeleteObject(b_orange); DeleteObject(b_dark_grey);

    ReleaseDC(h, dc); DeleteDC(dc); // освободить контекст
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        //case WM_PAINT:
        //    MyDraw(hwnd);
        //     break;
        case WM_KEYDOWN:
            if (wparam == VK_ESCAPE) PostQuitMessage(0);
            break;
        case WM_LBUTTONDOWN:
            if ((LOWORD(lparam) < 20) && (LOWORD(lparam) < 20)) PostQuitMessage(0);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    MSG msg; // сообщение
    WNDCLASS w; // класс окна
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    w.lpszClassName = reinterpret_cast<LPCSTR>(LPCWSTR("My Class"));
    RegisterClass(&w);
    HWND hwnd = CreateWindow(reinterpret_cast<LPCSTR>(LPCWSTR("My Class")),
                             reinterpret_cast<LPCSTR>(LPCWSTR("Chernyi")),
                             WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
                             NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MyDraw(hwnd);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); DispatchMessage(&msg);
    }
    return msg.wParam;
}