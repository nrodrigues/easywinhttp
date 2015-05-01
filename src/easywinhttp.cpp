#include <easywinhttp/easywinhttp.h>

#include "errorutils.h"

using namespace easywinhttp;

WinHttpObject::WinHttpObject()
    : handle_()
{
}

WinHttpObject::WinHttpObject(WinHttpObject&& other)
    : handle_(other.handle_.get(), WinHttpCloseHandle)
{
    other.handle_ = nullptr;
}

WinHttpObject::operator HINTERNET() const
{
    return handle_.get();
}

WinHttpObject& WinHttpObject::operator=(WinHttpObject&& other)
{
    if (this != other) {
        handle_.reset(other.handle_.get(), WinHttpCloseHandle);
        other.handle_ = nullptr;
    }

    return *this;
}

void WinHttpObject::setOption(DWORD option, LPVOID buffer, DWORD bufferLength)
{
    if (!WinHttpSetOption(*this, option, buffer, bufferLength)) {
        errorutils::throwError(GetLastError());
    }
}


// WinHttp
WinHttp::WinHttp(const std::wstring& userAgent)
    : WinHttpObject()
{
    HINTERNET handle = WinHttpOpen(userAgent.c_str(), WINHTTP_ACCESS_TYPE_NO_PROXY,
                                   WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    if (handle == NULL) {
        errorutils::throwError(GetLastError());
    }

    handle_.reset(handle, WinHttpCloseHandle);
}

WinHttp& WinHttp::operator=(WinHttp&& other)
{
    if (this != other) {
        WinHttpObject::operator=(other);
    }

    return *this;
}
