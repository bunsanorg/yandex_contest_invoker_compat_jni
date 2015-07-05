#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/lxc/Config.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace lxc{namespace config
{
    LocalRef<jobject> create(const invoker::lxc::Config &config);
}}}}}}}}
