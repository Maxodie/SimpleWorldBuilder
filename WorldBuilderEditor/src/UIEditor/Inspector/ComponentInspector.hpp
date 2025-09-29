#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

class InfoComponentInspector
{
public:
    static void Show(InfoComponent& info);
};

class TransformComponentInspector
{
public:
    static void Show(TransformComponent& tr);
};

class ModelComponentInspector
{
public:
    static void Show(ModelComponent& model, Application& context);
};

}
