#pragma once

#include "Core/Core.hpp"
#include "Core/Input/Input.hpp"

namespace WB {

enum Shortcut {
    Semicolon = 0
};

using ShortcutCallback = std::function<void()>;

class EditorShortcutInputManager {
private:
    std::unordered_map<Shortcut, ShortcutCallback> m_callbackMap;
    void CallShortcut(Shortcut);
    void InterpreteShortcut(InputData);

public:
    void BindShortcut(const ShortcutCallback&&, Shortcut);

    EditorShortcutInputManager();
    ~EditorShortcutInputManager();
};

}
