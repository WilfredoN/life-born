#pragma once

#include "raylib.h"
#include <entity.h>
#include <cmath>

bool SingularityMouseLeftButtonPressed(Vector2 mousePosition,
                                       Singularity &singularity);
void SingularityResize(Singularity &singularity, float rotation);
