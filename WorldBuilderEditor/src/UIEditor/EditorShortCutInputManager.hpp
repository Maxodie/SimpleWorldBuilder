#pragma once

#include "WorldBuilder.hpp"

namespace WB {

enum Shortcut {
    Semicolon = 0
};

using ShortcutCallback = std::function<void()>;

class EditorShortcutInputManager {
private:
    std::unordered_map<Shortcut, ShortcutCallback> m_callbackMap;
    void CallShortcut(Shortcut);
    void InterpreteShortcut(Keycode keycode);

public:
    void BindShortcut(const ShortcutCallback&&, Shortcut);

    EditorShortcutInputManager();
    ~EditorShortcutInputManager();
};

}
