#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

class BuildMenuLayer : public Layer
{
    using ProjectCreatedCallback = std::function<void()>;

public:
    BuildMenuLayer();
    ~BuildMenuLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

protected:
    void Close();

private:
    bool m_isOpen = true;
};

}
