#include "Core/LayerStack.hpp"
#include "Core/Application.hpp"

namespace WB
{

void Layer::SetContext(Application* app)
{
    m_context = app;
}

}
