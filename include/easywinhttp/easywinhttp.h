#pragma once

#include <string>
#include <memory>
#include <type_traits>

#include <windows.h>
#include <winhttp.h>

namespace easywinhttp {

typedef std::remove_pointer<HINTERNET>::type internet;
typedef std::shared_ptr<internet> internet_ptr;

class WinHttpObject {
public:
    WinHttpObject();
    WinHttpObject(WinHttpObject&& other);

public:
    operator HINTERNET() const;
    WinHttpObject& operator=(WinHttpObject&& other);

public:
    void setOption(DWORD option, LPVOID buffer, DWORD bufferLength);

protected:
    internet_ptr handle_;
};

class WinHttpChildObject : public WinHttpObject {
public:
    WinHttpChildObject() = default;
    WinHttpChildObject(HINTERNET parentHandle);
    WinHttpChildObject(WinHttpChildObject&& other);

public:
    WinHttpChildObject& operator=(WinHttpChildObject&& other);

protected:
    internet_ptr parent_;
};

class WinHttp : public WinHttpObject {
public:
    WinHttp() = default;
    WinHttp(const std::wstring& userAgent);
    WinHttp(WinHttp&& other);

public:
    WinHttp& operator=(WinHttp&& other);
};



}

