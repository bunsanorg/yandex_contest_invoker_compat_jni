#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/lxc/MountConfig.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace lxc{namespace mount_config
{
    LocalRef<jobject> create(const invoker::lxc::MountConfig &config);
}}}}}}}}
