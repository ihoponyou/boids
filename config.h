#pragma once

#define TITLE "boids"

#define SCREEN_SIDE_LENGTH 700
#define FRAMES_PER_SECOND 60
constexpr auto OPTIMAL_FRAME_DELAY = 1000 / FRAMES_PER_SECOND;

#define INITIAL_BIRDS 100
#define BIRD_SIDE_LENGTH 10
#define NEIGHBOR_RADIUS 50
#define MAX_ACCELERATION_FORCE 2
#define MAX_SPEED 2

constexpr float SEPARATION_FACTOR = 1.0f;
constexpr float ALIGNMENT_FACTOR = 1.0f;
constexpr float COHESION_FACTOR = 1.0f;