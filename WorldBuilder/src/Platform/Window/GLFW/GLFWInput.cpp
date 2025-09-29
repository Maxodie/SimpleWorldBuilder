#include "Platform/Window/GLFW/GLFWInput.hpp"
#include <GLFW/glfw3.h>
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"

namespace WB
{

void GLFWInput::BindWindow(const SharedPtr<Window> window)
{
    glfwSetKeyCallback(static_cast<GLFWwindow*>(window->GetNative()), GLFWInput::KeyCallback);
}

void GLFWInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Keycode wbKey = static_cast<Keycode>(key);
    CORE_LOG_DEBUG("GLFWInput.cpp mods : %d", mods);
    for(const auto& callback : s_anyPressedInputCallbacks)
    {
        if (action == GLFW_PRESS) {
            callback(wbKey);
        }
    }

    if(!m_currentInputTable)
    {
        return;
    }

    switch (action)
    {
        case GLFW_PRESS:
            if(m_currentInputTable->BindedPressedInputs.find(wbKey) != m_currentInputTable->BindedPressedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedPressedInputs.at(static_cast<Keycode>(key)))
                {
                    callback(wbKey);
                }
            }
        break;

        case GLFW_REPEAT:
            if(m_currentInputTable->BindedRepeatedInputs.find(wbKey) != m_currentInputTable->BindedRepeatedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedRepeatedInputs.at(static_cast<Keycode>(key)))
                {
                    callback(wbKey);
                }
            }
        break;

        case GLFW_RELEASE:
            if(m_currentInputTable->BindedReleasedInputs.find(wbKey) != m_currentInputTable->BindedReleasedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedReleasedInputs.at(static_cast<Keycode>(key)))
                {
                    callback(wbKey);
                }
            }
        break;
    }
}

}
