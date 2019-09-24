#include "motion.h"

MPU6050 mpu;
Chrono motionTask;

void MotionService::begin() {

    pinMode(PIN_MPU_INT, INPUT);

    Wire.pins(PIN_MPU_SDA, PIN_MPU_SCL);

    mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G);

    mpu.setAccelPowerOnDelay(MPU6050_DELAY_3MS);

    mpu.setIntFreeFallEnabled(true);
    mpu.setIntZeroMotionEnabled(true);
    mpu.setIntMotionEnabled(true);

    mpu.setDHPFMode(MPU6050_DHPF_5HZ);

    mpu.setMotionDetectionThreshold(20);
    mpu.setMotionDetectionDuration(5);

    mpu.setZeroMotionDetectionThreshold(4);
    mpu.setZeroMotionDetectionDuration(2);
}

void MotionService::handle() {
    if(motionTask.hasPassed(MOTION_TASK_INTERVAL)) {
        motionTask.restart();
        Vector rawAccel = mpu.readRawAccel();
        Activites act = mpu.readActivites();
        if(act.isPosActivityOnY) {
            DenkoMessage msg("No suitable message found.", false, true);
            settingsService.nextMessage(msg);
            denko.drawMsg(msg);
        }
    }
}