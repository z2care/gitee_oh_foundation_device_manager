/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "ipc_server_client_proxy.h"

#include "dm_constants.h"
#include "dm_log.h"
#include "ipc_cmd_register.h"
#include "ipc_def.h"
#include "ipc_types.h"

namespace OHOS {
namespace DistributedHardware {
int32_t IpcServerClientProxy::SendCmd(int32_t cmdCode, std::shared_ptr<IpcReq> req, std::shared_ptr<IpcRsp> rsp)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        LOGE("remote service null");
        return ERR_DM_POINT_NULL;
    }
    MessageParcel data;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGE("WriteInterfaceToken fail!");
        return ERR_DM_IPC_WRITE_FAILED;
    }
    MessageParcel reply;
    MessageOption option;
    if (IpcCmdRegister::GetInstance().SetRequest(cmdCode, req, data) != DM_OK) {
        return ERR_DM_IPC_SEND_REQUEST_FAILED;
    }
    if (remote->SendRequest((uint32_t)cmdCode, data, reply, option) != DM_OK) {
        LOGE("SendRequest fail, cmd:%d", cmdCode);
        return ERR_DM_IPC_SEND_REQUEST_FAILED;
    }
    return IpcCmdRegister::GetInstance().ReadResponse(cmdCode, reply, rsp);
}
} // namespace DistributedHardware
} // namespace OHOS