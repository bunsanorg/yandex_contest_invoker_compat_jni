#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <string>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    LocalRef<jstring> newStringUTF(const std::string &string);

    std::string getStringUTF(jstring string);
}}}}}
