#include "Scene.h"
#include "../Game.h"

Scene::Scene(class Game *game)
: mGame(game)
{}

Scene::~Scene()
{}

void Scene::Start()
{}

void Scene::Update(float deltaTime)
{}

void Scene::ProcessInput(const Uint8 *state, float deltaTime)
{}

std::string const Scene::GetSceneName()
{
    return "";
}
