#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: 2024 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)
from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

blob_fixups: blob_fixups_user_type = {
    (
        'system_ext/etc/permissions/com.qualcomm.qti.imscmservice-V2.0-java.xml',
        'system_ext/etc/permissions/com.qualcomm.qti.imscmservice-V2.1-java.xml',
        'system_ext/etc/permissions/com.qualcomm.qti.imscmservice-V2.2-java.xml',
        'system_ext/etc/permissions/qcrilhook.xml',
        'system_ext/etc/permissions/telephonyservice.xml'
    ): blob_fixup()
        .regex_replace('/product/framework/', '/system_ext/framework/'),
    'system_ext/lib64/lib-imsvideocodec.so': blob_fixup()
        .add_needed('libgui_shim.so'),
    'vendor/bin/pm-service': blob_fixup()
        .add_needed('libutils-v33.so'),
    'vendor/bin/sony-modem-switcher': blob_fixup()
        .binary_regex_replace(b'/oem/modem-config/(.*)/modem.conf', b'/vendor/modemconf/\\1/modem.conf')
        .binary_regex_replace(b'/oem/modem-config/modem.conf', b'/vendor/modemconf/modem.conf')
        .binary_regex_replace(b'persist.radio.multisim.config', b'vendor.radio.multisim.config\x00')
        .binary_regex_replace(b'persist.somc.cust.modem(0|1)\x00', b'persist.vendor.somc.sim\\1\x00'),
    'vendor/etc/init/init.sony-modem-switcher.rc': blob_fixup()
        .regex_replace('/system/bin/sony-modem-switcher', '/vendor/bin/sony-modem-switcher')
        .regex_replace('persist.somc.cust.modem(0|1)', 'persist.vendor.somc.sim\\1'),
}  # fmt: skip

module = ExtractUtilsModule(
    'tama-common',
    'sony',
    blob_fixups=blob_fixups,
)

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
