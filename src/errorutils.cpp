#include "errorutils.h"

#include <string>
#include <stdexcept>

#include <windows.h>
#include <winhttp.h>

using namespace easywinhttp;

void errorutils::throwError(DWORD error) {
    LPSTR message = NULL;
    DWORD cchars = 0;

    cchars = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message, 0, NULL);

    // if no message found try from winhttp

    if (cchars == 0 && error > WINHTTP_ERROR_BASE) {
        cchars = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,
                                GetModuleHandle(L"winhttp.dll"), error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message, 0, NULL);
    }

    if (cchars > 0) {
        std::string errorMessage(message, cchars);
        LocalFree(message);

        throw std::runtime_error(errorMessage);
    }
    else {
        throw std::runtime_error("unknown error " + std::to_string(error));
    }

}
