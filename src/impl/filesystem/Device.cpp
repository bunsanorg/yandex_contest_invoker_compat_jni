#include "com_yandex_contest_invoker_impl_filesystem_Device.h"

#include "yandex/contest/invoker/compat/jni/impl/filesystem/Device.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/Enum.hpp"

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace
{
    CXXClass<filesystem::Device> deviceClass_;
    GlobalEnumClass<filesystem::DeviceType> deviceTypeClass_;
}

void Java_com_yandex_contest_invoker_impl_filesystem_Device_classInit(JNIEnv *env, jclass deviceClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    deviceClass_.assign(deviceClass, "impl");
    deviceTypeClass_.assign("com/yandex/contest/invoker/filesystem/IDevice$Type");
    YANDEX_JNI_METHOD_END_VOID(env)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace device
{
    LocalRef<jobject> create(const invoker::filesystem::Device &device)
    {
        return deviceClass_.setPointerCreate(device);
    }
}}}}}}}}

jobject Java_com_yandex_contest_invoker_impl_filesystem_Device_getType(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, deviceClass_, self)
    return deviceTypeClass_.newEnum(this_->type).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jint Java_com_yandex_contest_invoker_impl_filesystem_Device_getMajor(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, deviceClass_, self)
    return this_->major;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_filesystem_Device_getMinor(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, deviceClass_, self)
    return this_->minor;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
