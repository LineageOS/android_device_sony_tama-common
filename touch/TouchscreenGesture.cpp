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

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"

#include <bitset>
#include <fstream>
#include <map>
#include <type_traits>
#include <vector>

namespace {
template <typename T>
std::enable_if_t<std::is_integral<T>::value, std::string> encode_binary(T i) {
    return std::bitset<sizeof(T) * 8>(i).to_string();
}
}  // anonymous namespace

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::string kGesturePath = "/proc/driver/gesture_type";

const std::map<int32_t, TouchscreenGesture::GestureInfo> TouchscreenGesture::kGestureInfoMap = {
    // clang-format off
    {0, {46, "Letter C"}},
    {1, {18, "Letter e"}},
    {2, {31, "Letter S"}},
    {3, {47, "Letter V"}},
    {4, {17, "Letter W"}},
    {5, {44, "Letter Z"}},
    // clang-format on
};

const uint8_t kKeyMaskGestureControl = 0x40;
const std::vector<uint8_t> kGestureMasks = {
    0x04,  // C gesture mask
    0x08,  // e gesture mask
    0x10,  // S gesture mask
    0x01,  // V gesture mask
    0x20,  // W gesture mask
    0x02,  // Z gesture mask
};

Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
    }
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(
    const ::vendor::lineage::touch::V1_0::Gesture& gesture, bool enabled) {
    uint8_t gestureMode;
    uint8_t mask = kGestureMasks[gesture.id];
    std::fstream file(kGesturePath);
    file >> gestureMode;
    if (enabled)
        gestureMode |= mask;
    else
        gestureMode &= ~mask;
    if (gestureMode != 0) gestureMode |= kKeyMaskGestureControl;
    // Strip first digit
    file << encode_binary(gestureMode).substr(1);
    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
