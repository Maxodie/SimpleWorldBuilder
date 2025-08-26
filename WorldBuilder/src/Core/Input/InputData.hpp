#pragma once

#include "Core/Input/Input.hpp"
#include "Core/Input/Keycode.hpp"
#include "Core/Core.hpp"

namespace WB {
struct InputData {
    Keycode keycode;
    Modifer modifier;
};
}
