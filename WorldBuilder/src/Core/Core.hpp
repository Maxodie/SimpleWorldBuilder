#pragma once

#include <utility>
#include <ostream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <chrono>
#include <time.h>
#include <array>
#include <cstdint>
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <functional>
#include <assert.h>

#include "Core/Log/Log.hpp"

#ifdef WB_ASSERT
#   define WB_CORE_ASSERT(exp, msg)\
do\
{\
if(!(exp))\
{assert(0); CORE_LOG_ERROR(msg)}\
}while(0)

#   define WB_CLIENT_ASSERT(exp, msg)\
do\
{\
if(!(exp))\
{assert(0); CLIENT_LOG_ERROR(msg)}\
}while(0)
#else
#   define WB_ASSERT(exp, msg)
#   define WB_CLIENT_ASSERT(exp, msg)
#endif

#define WB_INLINE inline

#define WB_DELETE(ptr) if(!(ptr)) {} else {delete(ptr);}

using TypeID = uintptr_t;

template<typename T>
uintptr_t GetTypeID()
{
    return reinterpret_cast<uintptr_t>(&typeid(T));
}
