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

#ifndef OHOS_DM_IPC_NOTIFY_PUBLISH_RESULT_REQ_H
#define OHOS_DM_IPC_NOTIFY_PUBLISH_RESULT_REQ_H

#include "ipc_req.h"

namespace OHOS {
namespace DistributedHardware {
class IpcNotifyPublishResultReq : public IpcReq {
    DECLARE_IPC_MODEL(IpcNotifyPublishResultReq);

public:
    /**
     * @tc.name: IpcNotifyPublishResultReq::GetPublishId
     * @tc.desc: Get PublishId of the Ipc Notify Publish Result Request
     * @tc.type: FUNC
     */
    int32_t GetPublishId() const
    {
        return publishId_;
    }

    /**
     * @tc.name: IpcNotifyPublishResultReq::SetPublishId
     * @tc.desc: Set PublishId of the Ipc Notify Publish Result Request
     * @tc.type: FUNC
     */
    void SetPublishId(int32_t publishId)
    {
        publishId_ = publishId;
    }

    /**
     * @tc.name: IpcNotifyPublishResultReq::GetResult
     * @tc.desc: Get Result of the Ipc Notify Publish Result Request
     * @tc.type: FUNC
     */
    int32_t GetResult() const
    {
        return result_;
    }

    /**
     * @tc.name: IpcNotifyPublishResultReq::SetResult
     * @tc.desc: Set Result of the Ipc Notify Publish Result Request
     * @tc.type: FUNC
     */
    void SetResult(int32_t result)
    {
        result_ = result;
    }

private:
    int32_t publishId_ = 0;
    int32_t result_ = 0;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DM_IPC_NOTIFY_PUBLISH_RESULT_REQ_H
