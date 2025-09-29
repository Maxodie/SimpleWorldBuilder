#pragma once

#include <algorithm>
#include <typeindex>
#include <utility>
#include <regex>
#include <ostream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <chrono>
#include <array>
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <map>
#include <functional>
#include <assert.h>

#include "Core/Log/Log.hpp"

#define WB_INLINE inline

#include "Core/Utils/FileSystem.hpp"
#include "Commons/Timestep.hpp"

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
#   define WB_CORE_ASSERT(exp, msg)
#   define WB_CLIENT_ASSERT(exp, msg)
#endif


#define WB_DELETE(ptr) if(!(ptr)) {} else {delete(ptr);}

#define WB_BIND_FUN0(fun) std::bind(&fun, this)
#define WB_BIND_FUN1(fun) std::bind(&fun, this, std::placeholders::_1)
#define WB_BIND_FUN2(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2)
#define WB_BIND_FUN3(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define WB_BIND_FUN4(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define WB_BIND_FUN5(fun) std::bind(&fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

#define WB_BIND_OTHER_FUN0(fun, instance) std::bind(&fun, instance)
#define WB_BIND_OTHER_FUN1(fun, instance) std::bind(&fun, instance, std::placeholders::_1)
#define WB_BIND_OTHER_FUN2(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2)
#define WB_BIND_OTHER_FUN3(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define WB_BIND_OTHER_FUN4(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define WB_BIND_OTHER_FUN5(fun, instance) std::bind(&fun, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

#define BIT(x) 1 << x

using TypeID = std::type_index;
using TypeIDptr = uintptr_t;

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

template<typename T>
using WeakPtr = std::weak_ptr<T>;

template<typename T>
TypeIDptr GetTypeIDptr()
{
    return reinterpret_cast<uintptr_t>(&typeid(T));
}

template<typename T>
TypeID GetTypeID()
{
    return typeid(T);
}
