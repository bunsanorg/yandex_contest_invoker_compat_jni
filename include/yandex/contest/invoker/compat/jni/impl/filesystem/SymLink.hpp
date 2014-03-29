#pragma once

#include <yandex/contest/invoker/filesystem/SymLink.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace sym_link
{
    LocalRef<jobject> create(const invoker::filesystem::SymLink &symLink);
}}}}}}}}
