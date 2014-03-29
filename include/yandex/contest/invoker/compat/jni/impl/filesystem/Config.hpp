#pragma once

#include <yandex/contest/invoker/filesystem/Config.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace config
{
    LocalRef<jobject> create(const invoker::filesystem::Config &config);
}}}}}}}}
