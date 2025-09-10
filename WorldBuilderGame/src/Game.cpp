#include "WorldBuilder.hpp"

class GameLayer : public WB::Layer
{
public:
    virtual void Update() override
    {

    }
    virtual void UpdateGUI() override
    {

    }
    virtual void OnAttach() override
    {

    }
    virtual void OnDetach() override
    {

    }
};

extern void OnAppStarted(WB::Application& app)
{
    app.AddLayer<GameLayer>();
}
