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

#ifndef OHOS_DM_SOFUBUS_ADAPTER_CRYPTO_H
#define OHOS_DM_SOFUBUS_ADAPTER_CRYPTO_H

#include <string>

namespace OHOS {
namespace DistributedHardware {
class DmSoftbusAdapterCrypto {
public:
    static int32_t GetUdidHash(const std::string &udid, unsigned char *udidHash);
};
}; // namespace DistributedHardware
}; // namespace OHOS
#endif // OHOS_DM_SOFUBUS_ADAPTER_CRYPTO_H