#pragma once
#ifndef INCLUDE_GUARD_MOTION_H
#define INCLUDE_GUARD_MOTION_H

#include "config.h"
#include "denko.h"
#include "settings.h"
#include <Chrono.h>
#include <MPU6050.h>
#include <Wire.h>

#define MOTION_TASK_INTERVAL 100 // 100ms

extern MPU6050 mpu;
extern SettingsService settingsService;
extern Denko denko;

namespace MotionService {
void begin();
void handle();
} // namespace MotionService

#endif // INCLUDE_GUARD_MOTION_H
