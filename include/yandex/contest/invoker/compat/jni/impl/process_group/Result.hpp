#pragma once

#include <yandex/contest/invoker/process_group/Result.hpp>
#include <yandex/contest/invoker/ProcessGroup.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_group{namespace result
{
    LocalRef<jobject> create(const ProcessGroup::Result &result);
}}}}}}}}
