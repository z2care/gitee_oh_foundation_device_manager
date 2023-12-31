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

#ifndef OHOS_MOCK_IPC_CLIENT_PROXY_H
#define OHOS_MOCK_IPC_CLIENT_PROXY_H

#include <gmock/gmock.h>
#include <refbase.h>

#include "ipc_client_proxy.h"

namespace OHOS {
namespace DistributedHardware {
class MockIpcClientProxy : public IpcClientProxy, public RefBase {
public:
    MOCK_METHOD1(Init, int32_t(const std::string &pkgName));
    MOCK_METHOD1(UnInit, int32_t(const std::string &pkgName));
    MOCK_METHOD3(SendRequest, int32_t(int32_t cmdCode, std::shared_ptr<IpcReq> req, std::shared_ptr<IpcRsp> rsp));
    MOCK_METHOD0(OnDmServiceDied, int32_t());
};
} // namespace DistributedHardware
} // namespace OHOS

#endif // OHOS_MOCK_IPC_CLIENT_PROXY_H
