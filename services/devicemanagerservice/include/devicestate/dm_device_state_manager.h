/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_DM_DEVICE_STATE_MANAGER_H
#define OHOS_DM_DEVICE_STATE_MANAGER_H

#include "device_manager_service_listener.h"
#include "dm_adapter_manager.h"
#include "softbus_connector.h"

namespace OHOS {
namespace DistributedHardware {
class DmDeviceStateManager final : public ISoftbusStateCallback,
                                   public std::enable_shared_from_this<DmDeviceStateManager> {
public:
    DmDeviceStateManager(std::shared_ptr<SoftbusConnector> softbusConnector,
                         std::shared_ptr<DeviceManagerServiceListener> listener);
    ~DmDeviceStateManager();
    void OnDeviceOnline(const std::string &pkgName, const DmDeviceInfo &info);
    void OnDeviceOffline(const std::string &pkgName, const DmDeviceInfo &info);
    void OnDeviceChanged(const std::string &pkgName, const DmDeviceInfo &info);
    void OnDeviceReady(const std::string &pkgName, const DmDeviceInfo &info);
    void OnProfileReady(const std::string &pkgName, const std::string deviceId);
    int32_t RegisterSoftbusStateCallback();

private:
    std::shared_ptr<SoftbusConnector> softbusConnector_;
    std::shared_ptr<DmAdapterManager> adapterMgr_;
    std::shared_ptr<DeviceManagerServiceListener> listener_;
    std::map<std::string, DmDeviceState> deviceStateMap_;
    std::map<std::string, DmDeviceInfo> remoteDeviceInfos_;
    std::string profileSoName_;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DM_DEVICE_STATE_MANAGER_H