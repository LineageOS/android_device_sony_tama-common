/*
 * Copyright (C) 2018 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.light@2.0-service.sony_sdm845"

#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <utils/Errors.h>

#include "Light.h"

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::light::V2_0::ILight;
using android::hardware::light::V2_0::implementation::Light;

const static std::string kLcdBacklightPath = "/sys/class/backlight/panel0-backlight/brightness";
const static std::string kLcdMaxBacklightPath = "/sys/class/backlight/panel0-backlight/max_brightness";
const static std::string kRedLedPath = "/sys/class/leds/red/brightness";
const static std::string kGreenLedPath = "/sys/class/leds/green/brightness";
const static std::string kBlueLedPath = "/sys/class/leds/blue/brightness";
const static std::string kRedLutPwmPath = "/sys/class/leds/red/lut_pwm";
const static std::string kGreenLutPwmPath = "/sys/class/leds/green/lut_pwm";
const static std::string kBlueLutPwmPath = "/sys/class/leds/blue/lut_pwm";
const static std::string kRedPauseLoPath = "/sys/class/leds/red/pause_lo_multi";
const static std::string kGreenPauseLoPath = "/sys/class/leds/green/pause_lo_multi";
const static std::string kBluePauseLoPath = "/sys/class/leds/blue/pause_lo_multi";
const static std::string kRedPauseHiPath = "/sys/class/leds/red/pause_hi_multi";
const static std::string kGreenPauseHiPath = "/sys/class/leds/green/pause_hi_multi";
const static std::string kBluePauseHiPath = "/sys/class/leds/blue/pause_hi_multi";
const static std::string kRedStepDurationPath = "/sys/class/leds/red/step_duration";
const static std::string kGreenStepDurationPath = "/sys/class/leds/green/step_duration";
const static std::string kBlueStepDurationPath = "/sys/class/leds/blue/step_duration";
const static std::string kRgbBlinkPath = "/sys/class/leds/rgb/start_blink";
const static std::string kRgbSyncPath = "/sys/class/leds/rgb/sync_state";

int main() {
    uint32_t lcdMaxBrightness = 255;

    std::ofstream lcdBacklight(kLcdBacklightPath);
    if (!lcdBacklight) {
        LOG(ERROR) << "Failed to open " << kLcdBacklightPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ifstream lcdMaxBacklight(kLcdMaxBacklightPath);
    if (!lcdMaxBacklight) {
        LOG(ERROR) << "Failed to open " << kLcdMaxBacklightPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    } else {
        lcdMaxBacklight >> lcdMaxBrightness;
    }

    std::ofstream redLed(kRedLedPath);
    if (!redLed) {
        LOG(ERROR) << "Failed to open " << kRedLedPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream greenLed(kGreenLedPath);
    if (!greenLed) {
        LOG(ERROR) << "Failed to open " << kGreenLedPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream blueLed(kBlueLedPath);
    if (!blueLed) {
        LOG(ERROR) << "Failed to open " << kBlueLedPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream redLutPwm(kRedLutPwmPath);
    if (!redLutPwm) {
        LOG(ERROR) << "Failed to open " << kRedLutPwmPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream greenLutPwm(kGreenLutPwmPath);
    if (!greenLutPwm) {
        LOG(ERROR) << "Failed to open " << kGreenLutPwmPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream blueLutPwm(kBlueLutPwmPath);
    if (!blueLutPwm) {
        LOG(ERROR) << "Failed to open " << kBlueLutPwmPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream redPauseLo(kRedPauseLoPath);
    if (!redPauseLo) {
        LOG(ERROR) << "Failed to open " << kRedPauseLoPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream greenPauseLo(kGreenPauseLoPath);
    if (!greenPauseLo) {
        LOG(ERROR) << "Failed to open " << kGreenPauseLoPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream bluePauseLo(kBluePauseLoPath);
    if (!bluePauseLo) {
        LOG(ERROR) << "Failed to open " << kBluePauseLoPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream redPauseHi(kRedPauseHiPath);
    if (!redPauseHi) {
        LOG(ERROR) << "Failed to open " << kRedPauseHiPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream greenPauseHi(kGreenPauseHiPath);
    if (!greenPauseHi) {
        LOG(ERROR) << "Failed to open " << kGreenPauseHiPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream bluePauseHi(kBluePauseHiPath);
    if (!bluePauseHi) {
        LOG(ERROR) << "Failed to open " << kBluePauseHiPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream redStepDuration(kRedStepDurationPath);
    if (!redStepDuration) {
        LOG(ERROR) << "Failed to open " << kRedStepDurationPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream greenStepDuration(kGreenStepDurationPath);
    if (!greenStepDuration) {
        LOG(ERROR) << "Failed to open " << kGreenStepDurationPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream blueStepDuration(kBlueStepDurationPath);
    if (!blueStepDuration) {
        LOG(ERROR) << "Failed to open " << kBlueStepDurationPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream rgbBlink(kRgbBlinkPath);
    if (!rgbBlink) {
        LOG(ERROR) << "Failed to open " << kRgbBlinkPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ofstream rgbSync(kRgbSyncPath);
    if (!rgbSync) {
        LOG(ERROR) << "Failed to open " << kRgbSyncPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    android::sp<ILight> service = new Light(
            {std::move(lcdBacklight), lcdMaxBrightness},
            std::move(redLed), std::move(greenLed), std::move(blueLed),
            std::move(redLutPwm), std::move(greenLutPwm), std::move(blueLutPwm),
            std::move(redPauseLo), std::move(greenPauseLo), std::move(bluePauseLo),
            std::move(redPauseHi), std::move(greenPauseHi), std::move(bluePauseHi),
            std::move(redStepDuration), std::move(greenStepDuration), std::move(blueStepDuration),
            std::move(rgbBlink), std::move(rgbSync));

    configureRpcThreadpool(1, true);

    android::status_t status = service->registerAsService();

    if (status != android::OK) {
        LOG(ERROR) << "Cannot register Light HAL service";
        return 1;
    }

    LOG(INFO) << "Light HAL Ready.";
    joinRpcThreadpool();
    // Under normal cases, execution will not reach this line.
    LOG(ERROR) << "Light HAL failed to join thread pool.";
    return 1;
}
