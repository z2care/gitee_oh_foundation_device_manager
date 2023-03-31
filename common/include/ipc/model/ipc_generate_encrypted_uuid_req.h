/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef OHOS_DM_IPC_GENERATE_ENCTRYPTED_UUID_REQ_H
#define OHOS_DM_IPC_GENERATE_ENCTRYPTED_UUID_REQ_H

#include "ipc_req.h"

namespace OHOS {
namespace DistributedHardware {
class IpcGenerateEncryptedUuidReq : public IpcReq {
    DECLARE_IPC_MODEL(IpcGenerateEncryptedUuidReq);

public:
    const std::string GetUuid() const
    {
        return uuid_;
    }

    void SetUuid(const std::string &uuid)
    {
        uuid_ = uuid;
    }
    const std::string GetAppId() const
    {
        return appId_;
    }

    void SetAppId(const std::string &appId)
    {
        appId_ = appId;
    }
private:
    std::string uuid_;
    std::string appId_;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DM_IPC_GENERATE_ENCTRYPTED_UUID_REQ_H
