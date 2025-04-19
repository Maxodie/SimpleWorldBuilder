#include "Core/Input/Input.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Window/Window.hpp"
#include "Platform/Window/GLFW/GLFWInput.hpp"

namespace WB
{

SharedPtr<Input> Input::s_instance = nullptr;
const InputTable* Input::m_currentInputTable = nullptr;

void InputTable::BindInput(Keycode keycode, InputState state, const InputCallback&& callback)
{
    switch(state)
    {
        case InputState::PRESSED:
            BindedPressedInputs[keycode].push_back(std::move(callback));
        break;
        case InputState::REPEATED:
            BindedRepeatedInputs[keycode].push_back(std::move(callback));
            break;
        case InputState::RELEASED:
            BindedReleasedInputs[keycode].push_back(std::move(callback));
        break;
        default:
            CORE_LOG_ERROR("Unknown input state %d", state);
        break;
    }
}

SharedPtr<Input> Input::Create()
{
    switch(Window::GetAPI())
    {
        case Window::API::GLFW:
            return s_instance = MakeShared<GLFWInput>();
        break;
        case Window::API::None:
            CORE_LOG_ERROR("window api %d is None", Window::GetAPI());
        break;
        default:
            CORE_LOG_ERROR("Unknown window api %d", Window::GetAPI());
        break;
    }

    return nullptr;
}

}
