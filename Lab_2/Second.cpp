#include <windows.h>
#include <iostream>
#include <cmath>

DWORD t1 = 0, t2 = 0, t3 = 0, t4 = 0;

DWORD WINAPI Squaring1(void* tmp) {
    double data;
    DWORD n;
    HANDLE e1 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev1");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    HANDLE pipe_1 = CreateFileA("\\\\.\\pipe\\my_pipe1", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe_11 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe12", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(double), 2, 0, NULL);
    while (1) {
        WaitForSingleObject(e1, INFINITE);
        ReadFile(pipe_1, &data, sizeof(double), &n, NULL);
        std::cout << "ERROR: "<< GetLastError() << std::endl;
        std::cout << "First Cathet:" << data << std::endl;
        double x = 0;
        double temp;
        temp = data * data;
        WriteFile(pipe_11, &temp, sizeof(double), &n, NULL);
        TerminateThread(&t1, 0);
        CloseHandle(pipe_11);
        CloseHandle(pipe_1);
        SetEvent(e0);
    }
}

DWORD WINAPI Squaring2(void* tmp) {
    DWORD n;
    double data;
    HANDLE e2 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev2");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    HANDLE pipe_2 = CreateFileA("\\\\.\\pipe\\my_pipe2", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe_22 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe22", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 2 * sizeof(double), 2, 0, NULL);
    while (1) {
        WaitForSingleObject(e2, INFINITE);
        ReadFile(pipe_2, &data, sizeof(double), &n, NULL);
        std::cout << "ERROR: "<< GetLastError() << std::endl;
        std::cout << "Second Cathet:" << data << std::endl;
        double x = 0;
        double temp;
        temp = data * data;
        WriteFile(pipe_22, &temp, sizeof(double), &n, NULL);
        TerminateThread(&t2, 0);
        CloseHandle(pipe_22);
        CloseHandle(pipe_2);
        SetEvent(e0);
    }
}
DWORD WINAPI Adding(void* tmp) {
    DWORD n;
    double a, b;
    HANDLE e3 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev3");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    HANDLE pipe_11 = CreateFileA("\\\\.\\pipe\\my_pipe12", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe_22 = CreateFileA("\\\\.\\pipe\\my_pipe22", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe3 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe31", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(double), 2, 0, NULL);
    while (1) {
        WaitForSingleObject(e3, INFINITE);
        ReadFile(pipe_11, &a, sizeof(double), &n, NULL);
        std::cout << "ERROR: "<< GetLastError() << std::endl;
        ReadFile(pipe_22, &b, sizeof(double), &n, NULL);
        std::cout << "ERROR: "<< GetLastError() << std::endl;
        std::cout << "Addition of squares of cathets: " << a << " and " << b << std::endl;
        double res = a + b;
        WriteFile(pipe3, &res, sizeof(double), &n, NULL);
        TerminateThread(&t3, 0);
        CloseHandle(pipe3);
        CloseHandle(pipe_11);
        CloseHandle(pipe_22);
        SetEvent(e0);
    }
}

DWORD WINAPI Root(void* tmp) {
    DWORD n;
    HANDLE e4 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev4");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    HANDLE pipe3 = CreateFileA("\\\\.\\pipe\\my_pipe31", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    std::cout << "ERROR: "<< GetLastError() << std::endl;
    HANDLE pipe = CreateNamedPipeA("\\\\.\\pipe\\my_pipe4", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(double), 2, 0, NULL);
    double c;
    while (1) {
        WaitForSingleObject(e4, INFINITE);
        ReadFile(pipe3, &c, sizeof(double), &n, NULL);
        std::cout << "ERROR: "<< GetLastError() << std::endl;
        std::cout << "Get square of " << c << std::endl;
        double res = sqrt(c);
        WriteFile(pipe, &res, sizeof(double), &n, NULL);
        TerminateThread(&t4, 0);
        CloseHandle(pipe);
        CloseHandle(pipe3);
        SetEvent(e0);
    }
}

int main() {
    DWORD n;
    double a, b, res;

    HANDLE pipe1 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe1", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 2 * sizeof(double), 2, 0, NULL);
    HANDLE pipe2 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe2", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, 1, 2 * sizeof(double), 2, 0, NULL);

    HANDLE e0 = CreateEvent(NULL, FALSE, FALSE, "ev0"); // возвращение к main thread
    HANDLE e1 = CreateEvent(NULL, FALSE, FALSE, "ev1"); // разрешение выполнения thread mul
    HANDLE e2 = CreateEvent(NULL, FALSE, FALSE, "ev2"); // разрешение выполнения thread add
    HANDLE e3 = CreateEvent(NULL, FALSE, FALSE, "ev3"); // разрешение выполнения thread div
    HANDLE e4 = CreateEvent(NULL, FALSE, FALSE, "ev4"); // разрешение выполнения thread sqrt

    CreateThread(NULL, 0, Squaring1, NULL, 0, &t1);
    CreateThread(NULL, 0, Squaring2, NULL, 0, &t2);
    CreateThread(NULL, 0, Adding, NULL, 0, &t3);
    CreateThread(NULL, 0, Root, NULL, 0, &t4);

    std::cout << "Enter first cathet:";
    std::cin >> a;
    std::cout << "Enter second cathet:";
    std::cin >> b;

    WriteFile(pipe1, &a, sizeof(double), &n, NULL);
    WriteFile(pipe2, &b, sizeof(double), &n, NULL);

    HANDLE pipe = CreateFileA("\\\\.\\pipe\\my_pipe4", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    std::cout << "ERROR: "<< GetLastError() << std::endl;
    HANDLE pipe3 = CreateFileA("\\\\.\\pipe\\my_pipe31", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    std::cout << "ERROR: "<< GetLastError() << std::endl;
    HANDLE commands[4] = {e1, e2, e3, e4};

    for (int i = 0; i < 4; i++) {
        SetEvent(commands[i]); // Разрешить потоку выполнить операцию
        WaitForSingleObject(e0, INFINITE); // Ждать доклад
    }

    ReadFile(pipe, &res, sizeof(double), &n, NULL);
    std::cout << "Result: " << res << std::endl;
    CloseHandle(e0);
    CloseHandle(e1);
    CloseHandle(e2);
    CloseHandle(e3);
    CloseHandle(e4);
    CloseHandle(pipe3);
    CloseHandle(pipe);
    CloseHandle(pipe2);
    CloseHandle(pipe1);
    t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    return 0;
}
