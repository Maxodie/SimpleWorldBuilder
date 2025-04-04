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
{CORE_LOG_ERROR(msg); assert(0);}\
}while(0)

#   define WB_CLIENT_ASSERT(exp, msg)\
do\
{\
if(!(exp))\
{assert(0); CLIENT_LOG_ERROR(msg);}\
}while(0)
#else
#   define WB_ASSERT(exp, msg)
#   define WB_CLIENT_ASSERT(exp, msg)
#endif

#define WB_INLINE inline

#define WB_DELETE(ptr) if(!(ptr)) {} else {delete(ptr);}
#define WB_BIND_FUN(fun) std::bind(&fun, this, std::placeholders::_1)

using TypeID = uintptr_t;

namespace WB
{
template<typename T>
using UniquePtr = std::unique_ptr<T>;
template<typename T, typename... TArgs>
constexpr UniquePtr<T> MakeUnique(TArgs&&... args)
{
    return std::make_unique<T>(std::forward<TArgs>(args)...);
}

template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T, typename... TArgs>
constexpr SharedPtr<T> MakeShared(TArgs&&... args)
{
    return std::make_shared<T>(std::forward<TArgs>(args)...);
}

}

template<typename T>
uintptr_t GetTypeID()
{
    return reinterpret_cast<uintptr_t>(&typeid(T));
}
