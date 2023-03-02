#include <windows.h>
#include <intsafe.h>
#include <cstdint>
#include <cstdio>
#include "logon.h"

HRESULT ParseCommandLineToStringArray(
    const WCHAR *pCommandLine,
    size_t unknown,
    wchar_t **pArgs,
    size_t *pNumArgs,
    wchar_t *pBuffer,
    size_t *pStrBufSize)
{
    size_t uVar1;
    bool bVar2;
    size_t numArgs;
    size_t strBufSize;
    size_t sVar3;
    size_t lVar4;
    int result;
    size_t uVar4;
    size_t uVar5;
    size_t uVar6;
    wchar_t chr;
    bool flag;

    chr = *pCommandLine;
    if (chr == L' ' || chr == L'\t')
    {
        return E_INVALIDARG;
    }
    uVar4 = 0;
    numArgs = 0;
    strBufSize = 0;
    if (chr != L'\0')
    {
        sVar3 = strBufSize;
        do
        {
            flag = false;
            uVar5 = 0;
            result = 0;
        LAB_1400014c4:
            lVar4 = 1;
            chr = pCommandLine[uVar4];
            uVar6 = uVar5;
            if (flag)
            {
                if (chr == L'\0')
                {
                    return E_INVALIDARG;
                }
                if (chr == L'\"')
                {
                    if ((pCommandLine + uVar4)[1] != L'\"')
                    {
                        flag = false;
                        goto LAB_1400015bc;
                    }
                    lVar4 = 2;
                }
            LAB_14000159c:
                if (pBuffer != nullptr)
                {
                    pBuffer[uVar5] = chr;
                }
                uVar6 = uVar5 + 1;
                if (uVar6 < uVar5)
                {
                    uVar6 = 0xffffffffffffffff;
                    result = INTSAFE_E_ARITHMETIC_OVERFLOW;
                }
                else
                {
                    result = 0;
                }
            LAB_1400015bc:
                if (result < 0)
                    goto LAB_140001510;
                uVar1 = lVar4 + uVar4;
                if (uVar1 < uVar4)
                {
                    if (uVar4 <= uVar1)
                    {
                        return 0;
                    }
                    return INTSAFE_E_ARITHMETIC_OVERFLOW;
                }
                bVar2 = uVar4 <= uVar1;
                uVar4 = uVar1;
                uVar5 = uVar6;
                result = INTSAFE_E_ARITHMETIC_OVERFLOW;
                if (bVar2)
                {
                    result = 0;
                }
                goto LAB_1400014c4;
            }
            if (L' ' < chr)
            {
                if (chr != L'\"')
                    goto LAB_14000159c;
                flag = true;
                goto LAB_1400015bc;
            }
            if ((chr != L' ' && chr != L'\0') && chr != L'\t')
                goto LAB_14000159c;
            if (pBuffer != nullptr)
            {
                pBuffer[uVar5] = L'\0';
            }
            uVar6 = uVar5 + 1;
            if (uVar6 < uVar5)
            {
                uVar6 = 0xffffffffffffffff;
                result = INTSAFE_E_ARITHMETIC_OVERFLOW;
            }
            else
            {
                result = 0;
            }
        LAB_140001510:
            if (result < 0)
            {
                return result;
            }
            if (pArgs != nullptr)
            {
                *pArgs = pBuffer;
                pArgs = pArgs + 1;
                pBuffer = pBuffer + uVar6;
            }
            strBufSize = uVar6 + sVar3;
            numArgs = numArgs + 1;
            if (strBufSize < sVar3)
            {
                return INTSAFE_E_ARITHMETIC_OVERFLOW;
            }
            flag = false;
            while (chr = pCommandLine[uVar4], chr == L' ' || chr == L'\t')
            {
                bVar2 = uVar4 + 1 < uVar4;
                flag = true;
                uVar4 = uVar4 + 1;
                if (bVar2)
                {
                    return INTSAFE_E_ARITHMETIC_OVERFLOW;
                }
            }
            sVar3 = strBufSize;
        } while (chr != L'\0');
        if (flag)
        {
            return E_INVALIDARG;
        }
    }
    *pNumArgs = numArgs;
    *pStrBufSize = strBufSize;
    return S_OK;
}

HRESULT ParseCommandLineToStringArrayLocalAlloc(
    const WCHAR *pCommandLine,
    size_t unknown,
    LPCWSTR **pArgs,
    size_t *pNumArgs)
{
    HRESULT result;
    size_t sizeArgs;
    size_t strBufSizeBytes;
    uint8_t *buffer;
    size_t numArgs = 0;
    size_t strBufSize = 0;
    size_t totalBufSize;

    *pArgs = nullptr;
    *pNumArgs = 0;

    result = ParseCommandLineToStringArray(pCommandLine, unknown, nullptr, &numArgs, nullptr, &strBufSize);
    if (result < 0)
    {
        return result;
    }

    result = SizeTMult(numArgs, 8, &sizeArgs);
    if (FAILED(result))
        return result;

    result = SizeTMult(strBufSize, 2, &strBufSizeBytes);
    if (FAILED(result))
        return result;

    result = SizeTAdd(sizeArgs, strBufSizeBytes, &totalBufSize);
    if (FAILED(result))
        return result;

    buffer = (uint8_t *)LocalAlloc(0, totalBufSize);
    if (!buffer)
    {
        result = E_OUTOFMEMORY;
        return result;
    }

    result = ParseCommandLineToStringArray(pCommandLine,
                                           unknown,
                                           reinterpret_cast<wchar_t **>(buffer),
                                           &numArgs,
                                           reinterpret_cast<wchar_t *>(&buffer[sizeArgs]),
                                           &strBufSize);
    if (FAILED(result))
    {
        LocalFree(buffer);
        return result;
    }

    *pNumArgs = numArgs;
    *pArgs = (LPCWSTR *)buffer;

    return result;
}

const GUID CLSID_LogonUIController = {0x0bdc6fc7, 0x83e3, 0x46a4, {0xbf, 0xa0, 0x1b, 0xc1, 0x4d, 0xbf, 0x8b, 0x38}};
const IID IID_ILogonController = {0xe76c5d5b, 0x7ad9, 0x4496, {0x9e, 0xfd, 0xdf, 0xa0, 0x8e, 0xc7, 0x00, 0xbb}};

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    HANDLE currentProcess = GetCurrentProcess();
    SetPriorityClass(currentProcess, HIGH_PRIORITY_CLASS);

    if (CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE) < 0)
    {
        return 1;
    }

    unsigned long testclientprocessid = 0;
    unsigned long flags = 0;
    unsigned long state0 = 0;
    unsigned long state1 = 0;

    LPCWSTR *args;
    size_t numArgs;

    if (*lpCmdLine && SUCCEEDED(ParseCommandLineToStringArrayLocalAlloc(lpCmdLine, 6, &args, &numArgs)))
    {

#define COMPARE_ARG(str, out)                                           \
    for (size_t i = 0; i < numArgs; i++)                                \
    {                                                                   \
        const wchar_t *pStr = args[i];                                  \
        size_t len = -1ull;                                             \
        do                                                              \
            ++len;                                                      \
        while (pStr[len]);                                              \
        if (len >= ((sizeof(str) / sizeof(wchar_t)) - 1) &&             \
            !wcsncmp(str, pStr, ((sizeof(str) / sizeof(wchar_t)) - 1))) \
        {                                                               \
            const wchar_t *chr = wcschr(pStr, L':');                    \
            if (chr && chr[1])                                          \
            {                                                           \
                out = wcstoul(&chr[1], nullptr, 16);                    \
                break;                                                  \
            }                                                           \
        }                                                               \
    }

        COMPARE_ARG(L"/testclientprocessid:", testclientprocessid);
        COMPARE_ARG(L"/flags:", flags);
        COMPARE_ARG(L"/state0:", state0);
        COMPARE_ARG(L"/state1:", state1);

        LocalFree(args);
    }

    ILogonController *pLogonController;

    if (SUCCEEDED(CoCreateInstance(CLSID_LogonUIController,
                                   nullptr,
                                   CLSCTX_INPROC_SERVER,
                                   IID_ILogonController,
                                   (LPVOID *)&pLogonController)))
    {
        pLogonController->DoModal(flags, testclientprocessid, state0, state1);
        pLogonController->Release();

        CoUninitialize();
        return 0;
    }
    else
    {
        CoUninitialize();
        return 1;
    }
}
