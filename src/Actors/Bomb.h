#pragma once
#include "Actor.h"
#include "../Commons/Shader.h"

class Bomb : public Actor {
public:
    Bomb(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t* state) override;

};
