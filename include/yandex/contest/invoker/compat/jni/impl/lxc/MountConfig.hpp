#pragma once

#include <yandex/contest/system/lxc/MountConfig.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace lxc{namespace mount_config
{
    LocalRef<jobject> create(const system::lxc::MountConfig &config);
}}}}}}}}
