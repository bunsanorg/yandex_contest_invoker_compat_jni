#pragma once

#include <yandex/contest/invoker/ProcessGroup.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace notification_stream
{
    LocalRef<jobject> create(const NotificationStream &notificationStream);
}}}}}}}
