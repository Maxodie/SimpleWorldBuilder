#pragma once
#include "Core/Core.hpp"
#include "Core/Window/Window.hpp"
#include "Core/Input/InputData.hpp"

enum class InputState
{
    PRESSED, REPEATED, RELEASED
};

namespace WB
{
using InputCallback = std::function<void(InputData)>;

struct InputTable
{
    std::unordered_map<Keycode, std::vector<InputCallback>> BindedPressedInputs;
    std::unordered_map<Keycode, std::vector<InputCallback>> BindedRepeatedInputs;
    std::unordered_map<Keycode, std::vector<InputCallback>> BindedReleasedInputs;

    void BindInput(Keycode keyCode, InputState state, const InputCallback&& callback);
};

class Input
{
public:

public:
    Input() = default;
    virtual ~Input() = default;

    virtual void BindWindow(const SharedPtr<Window> window) = 0;

    static WB_INLINE void SetInputTable(InputTable& inputTable)
    {
        m_currentInputTable = &inputTable;
    }

    static WB_INLINE void AddAnyInputCallback(const InputCallback&& callback)
    {
        s_anyPressedInputCallbacks.emplace_back(std::move(callback));
    }

    static SharedPtr<Input> Create();

protected:
    static const InputTable* m_currentInputTable;
    static std::vector<InputCallback> s_anyPressedInputCallbacks;

private:
    static SharedPtr<Input> s_instance;
};

}
