#pragma once

#include "yandex/contest/invoker/ProcessDefaultSettings.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_default_settings
{
    LocalRef<jobject> create(const ProcessDefaultSettings &processDefaultSettings);
}}}}}}}
