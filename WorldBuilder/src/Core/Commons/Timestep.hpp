#pragma once
#include "Core/Core.hpp"
#include <chrono>

namespace WB
{

class Timestep
{
public:
    Timestep() = default;
    Timestep(int64_t time);

    ~Timestep() = default;

    [nodiscard] WB_INLINE int64_t GetMilliseconds() const { return m_time; }
    [nodiscard] WB_INLINE double GetSeconds() const { return static_cast<double>(m_time) / 1000; }

    WB_INLINE void ReadTime()
    {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        m_time = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
    }

    Timestep operator-()
    {
        return Timestep(-m_time);
    }

    Timestep operator-(const Timestep& b)
    {
        return Timestep(m_time - b.m_time);
    }

private:
    int64_t m_time;
};

}
