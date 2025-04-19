#include "Platform/Window/GLFW/GLFWInput.hpp"
#include <GLFW/glfw3.h>

namespace WB
{


void GLFWInput::BindWindow(const SharedPtr<Window> window)
{
    glfwSetKeyCallback(static_cast<GLFWwindow*>(window->GetNative()), GLFWInput::KeyCallback);
}

void GLFWInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(!m_currentInputTable)
    {
        return;
    }

    switch (action)
    {
        case GLFW_PRESS:
            if(m_currentInputTable->BindedPressedInputs.find(static_cast<Keycode>(key)) != m_currentInputTable->BindedPressedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedPressedInputs.at(static_cast<Keycode>(key)))
                {
                    callback();
                }
            }

            if(m_currentInputTable->BindedRepeatedInputs.find(static_cast<Keycode>(key)) != m_currentInputTable->BindedRepeatedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedRepeatedInputs.at(static_cast<Keycode>(key)))
                {
                    callback();

                }
            }
        break;
        case GLFW_REPEAT:
            if(m_currentInputTable->BindedRepeatedInputs.find(static_cast<Keycode>(key)) != m_currentInputTable->BindedRepeatedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedRepeatedInputs.at(static_cast<Keycode>(key)))
                {
                    callback();
                }
            }
        break;
        case GLFW_RELEASE:
            if(m_currentInputTable->BindedReleasedInputs.find(static_cast<Keycode>(key)) != m_currentInputTable->BindedReleasedInputs.end())
            {
                for(const InputCallback& callback : m_currentInputTable->BindedReleasedInputs.at(static_cast<Keycode>(key)))
                {
                    callback();
                }
            }
        break;
    }
}

}
