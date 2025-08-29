#include "Platform/Window/GLFW/GLFWInput.hpp"
#include <GLFW/glfw3.h>
#include "Core/Core.hpp"
#include "Core/Input/InputData.hpp"
#include "Core/Log/Log.hpp"
#include "glm/common.hpp"

namespace WB
{

void GLFWInput::BindWindow(const SharedPtr<Window> window)
{
    glfwSetKeyCallback(static_cast<GLFWwindow*>(window->GetNative()), GLFWInput::KeyCallback);
}

void GLFWInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Keycode keyCode = static_cast<Keycode>(key);
    Modifier modifier = static_cast<Modifier>(mods);
    InputData inputData{keyCode, modifier};

    for(const auto& callback : s_anyPressedInputCallbacks)
    {
        if (action == GLFW_PRESS) {
            callback(inputData);
        }
    }

    if(!m_currentInputTable)
    {
        return;
    }

    switch (action)
    {
        case GLFW_PRESS:
            if(m_currentInputTable->BindedPressedInputs.find(keyCode) != m_currentInputTable->BindedPressedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedPressedInputs.at(static_cast<Keycode>(key)))
                {
                    callback(inputData);
                }
            }
        break;

        case GLFW_REPEAT:
            if(m_currentInputTable->BindedRepeatedInputs.find(keyCode) != m_currentInputTable->BindedRepeatedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedRepeatedInputs.at(static_cast<Keycode>(key)))
                {
                    callback(inputData);
                }
            }
        break;

        case GLFW_RELEASE:
            if(m_currentInputTable->BindedReleasedInputs.find(keyCode) != m_currentInputTable->BindedReleasedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedReleasedInputs.at(static_cast<Keycode>(key)))
                {
                    callback(inputData);
                }
            }
        break;
    }
}

}
