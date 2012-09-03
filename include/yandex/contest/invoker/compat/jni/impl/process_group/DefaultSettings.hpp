#pragma once

#include "yandex/contest/invoker/process_group/DefaultSettings.hpp"
#include "yandex/contest/invoker/ProcessGroup.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_group{namespace default_settings
{
    LocalRef<jobject> create(const ProcessGroup::DefaultSettings &defaultSettings);
}}}}}}}}
