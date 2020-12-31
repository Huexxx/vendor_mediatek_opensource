/*
 * Copyright (C) 2016 The Android Open Source Project
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

#ifndef VENDOR_MEDIATEK_HARDWARE_AUDIO_MTKPRIMARYDEVICE_H
#define VENDOR_MEDIATEK_HARDWARE_AUDIO_MTKPRIMARYDEVICE_H

#include <vendor/mediatek/hardware/audio/5.1/IAudioParameterChangedCallback.h>
#include <vendor/mediatek/hardware/audio/5.1/IMTKPrimaryDevice.h>
#include <vendor/mediatek/hardware/audio/5.1/IMTKPrimaryDeviceCallback.h>
#include <hidl/Status.h>

#include <hidl/MQDescriptor.h>

#include "Device.h"

namespace vendor {
namespace mediatek {
namespace hardware {
namespace audio {
namespace V5_1 {
namespace implementation {

using ::android::sp;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using namespace ::android::hardware::audio::common::V5_0;
using namespace ::android::hardware::audio::V5_0;
using ::android::hardware::audio::common::V5_0::implementation::AudioInputFlagBitfield;
using ::android::hardware::audio::common::V5_0::implementation::AudioOutputFlagBitfield;

using ::vendor::mediatek::hardware::audio::V5_1::IAudioParameterChangedCallback;
using ::vendor::mediatek::hardware::audio::V5_1::IMTKPrimaryDevice;
using ::vendor::mediatek::hardware::audio::V5_1::IMTKPrimaryDeviceCallback;

struct MTKPrimaryDevice : public IMTKPrimaryDevice {
    explicit MTKPrimaryDevice(audio_hw_device_mtk_t *device);

    // Methods from ::android::hardware::audio::V5_0::IDevice follow.
    Return<Result> initCheck()  override;
    Return<Result> setMasterVolume(float volume)  override;
    Return<void> getMasterVolume(getMasterVolume_cb _hidl_cb)  override;
    Return<Result> setMicMute(bool mute)  override;
    Return<void> getMicMute(getMicMute_cb _hidl_cb)  override;
    Return<Result> setMasterMute(bool mute)  override;
    Return<void> getMasterMute(getMasterMute_cb _hidl_cb)  override;
    Return<void> getInputBufferSize(const AudioConfig &config,
                                    getInputBufferSize_cb _hidl_cb)  override;
    Return<void> openOutputStream(int32_t ioHandle, const DeviceAddress& device,
                                  const AudioConfig& config, AudioOutputFlagBitfield flags,
                                  const SourceMetadata& sourceMetadata,
                                  openOutputStream_cb _hidl_cb) override;

    Return<void> openInputStream(int32_t ioHandle, const DeviceAddress& device,
                                 const AudioConfig& config, AudioInputFlagBitfield flags,
                                 AudioSource source, openInputStream_cb _hidl_cb);
    Return<void> openInputStream(int32_t ioHandle, const DeviceAddress& device,
                                 const AudioConfig& config, AudioInputFlagBitfield flags,
                                 const SinkMetadata& sinkMetadata,
                                 openInputStream_cb _hidl_cb) override;

    Return<bool> supportsAudioPatches()  override;
    Return<void> createAudioPatch(const hidl_vec<AudioPortConfig>& sources,
        const hidl_vec<AudioPortConfig> &sinks,
        createAudioPatch_cb _hidl_cb)  override;
    Return<Result> releaseAudioPatch(int32_t patch)  override;
    Return<void> getAudioPort(const AudioPort &port, getAudioPort_cb _hidl_cb)  override;
    Return<Result> setAudioPortConfig(const AudioPortConfig &config)  override;

    Return<Result> setScreenState(bool turnedOn)  override;

    Return<void> getHwAvSync(getHwAvSync_cb _hidl_cb) override;
    Return<void> getParameters(const hidl_vec<ParameterValue>& context,
                               const hidl_vec<hidl_string>& keys,
                               getParameters_cb _hidl_cb) override;
    Return<Result> setParameters(const hidl_vec<ParameterValue>& context,
                                 const hidl_vec<ParameterValue>& parameters) override;
    Return<void> getMicrophones(getMicrophones_cb _hidl_cb) override;
    Return<Result> setConnectedState(const DeviceAddress& address, bool connected) override;

    Return<void> debug(const hidl_handle& fd, const hidl_vec<hidl_string>& options) override;

    // Methods from ::android::hardware::audio::V5_0::IPrimaryDevice follow.
    Return<Result> setVoiceVolume(float volume)  override;
    Return<Result> setMode(AudioMode mode)  override;
    Return<void> getBtScoNrecEnabled(getBtScoNrecEnabled_cb _hidl_cb)  override;
    Return<Result> setBtScoNrecEnabled(bool enabled)  override;
    Return<void> getBtScoWidebandEnabled(getBtScoWidebandEnabled_cb _hidl_cb)  override;
    Return<Result> setBtScoWidebandEnabled(bool enabled)  override;
    Return<void> getTtyMode(getTtyMode_cb _hidl_cb)  override;
    Return<Result> setTtyMode(IPrimaryDevice::TtyMode mode)  override;
    Return<void> getHacEnabled(getHacEnabled_cb _hidl_cb)  override;
    Return<Result> setHacEnabled(bool enabled)  override;

    Return<Result> setBtScoHeadsetDebugName(const hidl_string& name) override;
    Return<void> getBtHfpEnabled(getBtHfpEnabled_cb _hidl_cb) override;
    Return<Result> setBtHfpEnabled(bool enabled) override;
    Return<Result> setBtHfpSampleRate(uint32_t sampleRateHz) override;
    Return<Result> setBtHfpVolume(float volume) override;
    Return<Result> updateRotation(IPrimaryDevice::Rotation rotation) override;

private:
    sp<android::hardware::audio::V5_0::implementation::Device> mDevice;
    // Methods from ::vendor::mediatek::hardware::audio::V5_1::IMTKPrimaryDevice follow.
    Return<Result> setupParametersCallback(const sp<IMTKPrimaryDeviceCallback> &callback);
    Return<Result> setAudioParameterChangedCallback(const sp<IAudioParameterChangedCallback> &callback);
    Return<Result> clearAudioParameterChangedCallback();

    virtual ~MTKPrimaryDevice();
};

}  // namespace implementation
}  // namespace V5_1
}  // namespace audio
}  // namespace hardware
}  // namespace mediatek
}  // namespace vendor

#endif  // VENDOR_MEDIATEK_HARDWARE_AUDIO_MTKPRIMARYDEVICE_H
