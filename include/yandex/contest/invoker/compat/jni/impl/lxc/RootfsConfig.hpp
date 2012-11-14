#pragma once

#include "yandex/contest/system/lxc/RootfsConfig.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace lxc{namespace rootfs_config
{
    LocalRef<jobject> create(const system::lxc::RootfsConfig &config);
}}}}}}}}
