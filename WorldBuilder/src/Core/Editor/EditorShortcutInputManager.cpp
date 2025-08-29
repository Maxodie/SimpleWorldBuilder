#include "Core/Editor/EditorShortCutInputManager.hpp"
#include "Core/Core.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Input/Keycode.hpp"

namespace WB {

EditorShortcutInputManager::EditorShortcutInputManager() {
    Input::AddAnyInputCallback(WB_BIND_FUN1(EditorShortcutInputManager::InterpreteShortcut));
}

EditorShortcutInputManager::~EditorShortcutInputManager() {
}

void EditorShortcutInputManager::BindShortcut(const ShortcutCallback&& callback, Shortcut shortcut) {
    m_callbackMap[shortcut] = callback;
}

void EditorShortcutInputManager::CallShortcut(Shortcut shortcut) {
    m_callbackMap[shortcut]();
}

void EditorShortcutInputManager::InterpreteShortcut(InputData inputData) {
    switch (inputData.keycode) {
        case Keycode::WB_KEY_SEMICOL:
            if  (inputData.modifier == Modifier::WB_MOD_SHIFT) {
                CallShortcut(Shortcut::Semicolon);
            }
        break;

        default:
        break;
    }
}

}
