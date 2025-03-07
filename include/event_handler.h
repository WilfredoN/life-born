#pragma once

#define BANG_DURATION 2.0f
#define BANG_EFFECT 20.0f

#include "raylib.h"
#include <entity.h>
#include <iostream>
#include <cmath>

bool SingularityMouseLeftButtonPressed(Vector2 mousePosition,
                                       Singularity &singularity);
void SingularityResize(Singularity &singularity, float size);
void BigBangExplosion(Singularity &singularity, float deltaTime);
bool IsBigBangActive();
