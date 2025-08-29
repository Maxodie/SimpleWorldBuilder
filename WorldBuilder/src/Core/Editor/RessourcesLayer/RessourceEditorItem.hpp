#pragma once

namespace WB
{

class RessourceEditorItem
{
    virtual void Draw();
    virtual void Open();
};

class RessourceEditorFile : public RessourceEditorItem
{
    virtual void Draw() override;
};

class RessourceEditorFolder : public RessourceEditorItem
{
    virtual void Draw() override;
};

}
