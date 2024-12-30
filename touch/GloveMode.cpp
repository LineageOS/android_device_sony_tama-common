/*
 * Copyright (C) 2021-2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "GloveModeService"

#include "GloveMode.h"

#include <android-base/properties.h>
#include <android-base/strings.h>
#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::string kGloveModePath = "/sys/devices/common_touch/touch/glove_mode";

Return<bool> GloveMode::isEnabled() {
    std::ifstream file(kGloveModePath);
    bool enabled;

    file >> enabled;

    return enabled;
}

Return<bool> GloveMode::setEnabled(bool enabled) {
    std::ofstream file(kGloveModePath);

    file << enabled << std::flush;

    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
