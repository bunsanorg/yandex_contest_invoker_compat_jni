#pragma once

#include <yandex/contest/invoker/filesystem/Directory.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace directory
{
    LocalRef<jobject> create(const invoker::filesystem::Directory &directory);
}}}}}}}}
