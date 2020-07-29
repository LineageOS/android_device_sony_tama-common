/*
 * Copyright (C) 2019 The LineageOS Project
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

#define LOG_TAG "GloveModeService"

#include "GloveMode.h"

#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::string kGloveModePath = "/proc/driver/glove";

Return<bool> GloveMode::isEnabled() {
    std::ifstream file(kGloveModePath);
    std::string line;
    while (getline(file, line)) {
        if (line == "Glove Mode: On") return true;
    }
    return false;
}

Return<bool> GloveMode::setEnabled(bool enabled) {
    std::ofstream file(kGloveModePath);
    file << (enabled ? "1" : "0");
    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
