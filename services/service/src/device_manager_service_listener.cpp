/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "device_manager_service_listener.h"

#include "device_manager_ipc_interface_code.h"
#include "dm_anonymous.h"
#include "dm_constants.h"
#include "dm_log.h"
#include "dm_crypto.h"
#include "ipc_notify_auth_result_req.h"
#include "ipc_notify_credential_req.h"
#include "ipc_notify_device_found_req.h"
#include "ipc_notify_device_state_req.h"
#include "ipc_notify_discover_result_req.h"
#include "ipc_notify_publish_result_req.h"
#include "ipc_notify_verify_auth_result_req.h"

namespace OHOS {
namespace DistributedHardware {
std::mutex DeviceManagerServiceListener::dmListenerMapLock_;
std::mutex DeviceManagerServiceListener::udidHashMapLock_;
std::map<std::string, std::string> DeviceManagerServiceListener::dmListenerMap_ = {};
std::map<std::string, std::string> DeviceManagerServiceListener::udidHashMap_ = {};

void DeviceManagerServiceListener::OnDeviceStateChange(const std::string &pkgName, const DmDeviceState &state,
                                                       const DmDeviceInfo &info)
{
    LOGI("OnDeviceStateChange, state = %d", state);
    std::shared_ptr<IpcNotifyDeviceStateReq> pReq = std::make_shared<IpcNotifyDeviceStateReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetDeviceState(state);
    pReq->SetDeviceInfo(info);
    if (pkgName == std::string(DM_PKG_NAME)) {
        ipcServerListener_.SendAll(SERVER_DEVICE_STATE_NOTIFY, pReq, pRsp);
    } else {
        ipcServerListener_.SendRequest(SERVER_DEVICE_STATE_NOTIFY, pReq, pRsp);
    }
}

void DeviceManagerServiceListener::OnDeviceFound(const std::string &pkgName, uint16_t subscribeId,
                                                 const DmDeviceInfo &info)
{
    std::shared_ptr<IpcNotifyDeviceFoundReq> pReq = std::make_shared<IpcNotifyDeviceFoundReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetSubscribeId(subscribeId);
    pReq->SetDeviceInfo(info);
    ipcServerListener_.SendRequest(SERVER_DEVICE_FOUND, pReq, pRsp);
}

void DeviceManagerServiceListener::OnDiscoveryFailed(const std::string &pkgName, uint16_t subscribeId,
                                                     int32_t failedReason)
{
    LOGI("DeviceManagerServiceListener::OnDiscoveryFailed");
    std::shared_ptr<IpcNotifyDiscoverResultReq> pReq = std::make_shared<IpcNotifyDiscoverResultReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetSubscribeId(subscribeId);
    pReq->SetResult(failedReason);
    ipcServerListener_.SendRequest(SERVER_DISCOVER_FINISH, pReq, pRsp);
}

void DeviceManagerServiceListener::OnDiscoverySuccess(const std::string &pkgName, int32_t subscribeId)
{
    LOGI("DeviceManagerServiceListener::OnDiscoverySuccess");
    std::shared_ptr<IpcNotifyDiscoverResultReq> pReq = std::make_shared<IpcNotifyDiscoverResultReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetSubscribeId((uint16_t)subscribeId);
    pReq->SetResult(DM_OK);
    ipcServerListener_.SendRequest(SERVER_DISCOVER_FINISH, pReq, pRsp);
}

void DeviceManagerServiceListener::OnPublishResult(const std::string &pkgName, int32_t publishId, int32_t publishResult)
{
    LOGI("DeviceManagerServiceListener::OnPublishResult : %d", publishResult);
    std::shared_ptr<IpcNotifyPublishResultReq> pReq = std::make_shared<IpcNotifyPublishResultReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetPublishId(publishId);
    pReq->SetResult(publishResult);
    ipcServerListener_.SendRequest(SERVER_PUBLISH_FINISH, pReq, pRsp);
}

void DeviceManagerServiceListener::OnAuthResult(const std::string &pkgName, const std::string &deviceId,
                                                const std::string &token, int32_t status, int32_t reason)
{
    std::shared_ptr<IpcNotifyAuthResultReq> pReq = std::make_shared<IpcNotifyAuthResultReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetDeviceId(deviceId);
    pReq->SetToken(token);
    pReq->SetStatus(status);
    pReq->SetReason(reason);
    ipcServerListener_.SendRequest(SERVER_AUTH_RESULT, pReq, pRsp);
}

void DeviceManagerServiceListener::OnVerifyAuthResult(const std::string &pkgName, const std::string &deviceId,
                                                      int32_t resultCode, const std::string &flag)
{
    std::shared_ptr<IpcNotifyVerifyAuthResultReq> pReq = std::make_shared<IpcNotifyVerifyAuthResultReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetDeviceId(deviceId);
    pReq->SetResult(resultCode);
    ipcServerListener_.SendAll(SERVER_VERIFY_AUTH_RESULT, pReq, pRsp);
}

void DeviceManagerServiceListener::OnUiCall(std::string &pkgName, std::string &paramJson)
{
    LOGI("OnUiCall in");
    std::shared_ptr<IpcNotifyDMFAResultReq> pReq = std::make_shared<IpcNotifyDMFAResultReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetJsonParam(paramJson);
    ipcServerListener_.SendRequest(SERVER_DEVICE_FA_NOTIFY, pReq, pRsp);
}

void DeviceManagerServiceListener::OnCredentialResult(const std::string &pkgName, int32_t action,
    const std::string &resultInfo)
{
    LOGI("call OnCredentialResult for %s, action %d", pkgName.c_str(), action);
    std::shared_ptr<IpcNotifyCredentialReq> pReq = std::make_shared<IpcNotifyCredentialReq>();
    std::shared_ptr<IpcRsp> pRsp = std::make_shared<IpcRsp>();

    pReq->SetPkgName(pkgName);
    pReq->SetCredentialAction(action);
    pReq->SetCredentialResult(resultInfo);
    ipcServerListener_.SendRequest(SERVER_CREDENTIAL_RESULT, pReq, pRsp);
}

void DeviceManagerServiceListener::RegisterDmListener(const std::string &pkgName, const std::string &appId)
{
    std::lock_guard<std::mutex> autoLock(dmListenerMapLock_);
    dmListenerMap_[pkgName] = appId;
}

void DeviceManagerServiceListener::UnRegisterDmListener(const std::string &pkgName)
{
    std::lock_guard<std::mutex> autoLock(dmListenerMapLock_);
    dmListenerMap_.erase(pkgName);
}

void DeviceManagerServiceListener::DeleteDeviceIdFromMap(const std::string &deviceId)
{
    std::lock_guard<std::mutex> lock(udidHashMapLock_);
    auto iter = udidHashMap_.find(deviceId);
    if (iter == udidHashMap_.end()) {
        return;
    }
    udidHashMap_.erase(deviceId);
}
void DeviceManagerServiceListener::SetUdidHashMap(const std::string &udidHash, const std::string &deviceId)
{
    std::lock_guard<std::mutex> lock(udidHashMapLock_);
    udidHashMap_[deviceId] = udidHash;
}

std::string DeviceManagerServiceListener::GetDeviceId(const std::string &udidHash)
{
    std::lock_guard<std::mutex> lock(udidHashMapLock_);
    for (auto iter = udidHashMap_.begin(); iter != udidHashMap_.end(); iter++) {
        if (udidHash == iter->second) {
            return iter->first;
        }
    }
    return "";
}

std::string DeviceManagerServiceListener::GetUdidHash(const std::string &deviceId)
{
    std::lock_guard<std::mutex> lock(udidHashMapLock_);
    return udidHashMap_.count(deviceId) > 0 ?  udidHashMap_[deviceId] : "";
}

std::string DeviceManagerServiceListener::GetAppId(const std::string &pkgName)
{
    std::lock_guard<std::mutex> autoLock(dmListenerMapLock_);
    return dmListenerMap_.count(pkgName) > 0 ? dmListenerMap_[pkgName] : "";
}

std::string DeviceManagerServiceListener::CalcDeviceId(const std::string &pkgName, const std::string &udidHash)
{
    std::string appId = GetAppId(pkgName);
    LOGI("CalcDeviceId, appId : %s, udidHash : %s.", GetAnonyString(appId).c_str(), GetAnonyString(udidHash).c_str());
    if (appId.empty()) {
        return udidHash;
    }
    std::string deviceId = GetDeviceId(udidHash);
    if (deviceId.empty()) {
        deviceId = Crypto::Sha256(appId + udidHash);
        SetUdidHashMap(udidHash, deviceId);
        return deviceId;
    }
    return deviceId;
}
} // namespace DistributedHardware
} // namespace OHOS
