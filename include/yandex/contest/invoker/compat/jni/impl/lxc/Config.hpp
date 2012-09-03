#pragma once

#include "yandex/contest/system/lxc/Config.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace lxc{namespace config
{
    LocalRef<jobject> create(const system::lxc::Config &config);
}}}}}}}}