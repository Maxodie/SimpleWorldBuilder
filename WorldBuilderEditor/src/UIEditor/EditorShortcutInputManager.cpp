#include "UIEditor/EditorShortCutInputManager.hpp"
#include "WorldBuilder.hpp"

namespace WB {

EditorShortcutInputManager::EditorShortcutInputManager() {
    Input::AddAnyInputCallback(WB_BIND_FUN1(EditorShortcutInputManager::InterpreteShortcut));
}

EditorShortcutInputManager::~EditorShortcutInputManager() {
}

void Caca() {
    std::cout << "caca" << std::endl;
}

void EditorShortcutInputManager::BindShortcut(const ShortcutCallback&& callback, Shortcut shortcut) {
    m_callbackMap[shortcut] = callback;
}

void EditorShortcutInputManager::CallShortcut(Shortcut shortcut) {
    m_callbackMap[shortcut]();
}

void EditorShortcutInputManager::InterpreteShortcut(Keycode keycode) {
    switch (keycode) {
        case Keycode::WB_KEY_SEMICOL:
            CallShortcut(Shortcut::Semicolon);
        break;

        default:
        break;
    }
}

}
