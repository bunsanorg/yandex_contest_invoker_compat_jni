#pragma once

#include "yandex/contest/invoker/ControlProcessConfig.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace control_process_config
{
    LocalRef<jobject> create(const ControlProcessConfig &config);
}}}}}}}
