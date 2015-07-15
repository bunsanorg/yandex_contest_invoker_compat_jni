#include "com_yandex_contest_invoker_impl_process_ProcessResourceUsage.h"

#include <yandex/contest/invoker/compat/jni/impl/process/ResourceUsage.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace process = yandex::contest::invoker::process;

namespace {
CxxClass<process::ResourceUsage> resourceUsageClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_process_ProcessResourceUsage_classInit(
    JNIEnv *env, jclass resourceUsageClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  resourceUsageClass_.assign(resourceUsageClass, "impl");
  YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_ProcessResourceUsage_finalize(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_FINALIZE(env, resourceUsageClass_, self);
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace process {
namespace resource_usage {
LocalRef<jobject> create(const invoker::process::ResourceUsage &resourceUsage) {
  return resourceUsageClass_.setPointerCreate(resourceUsage);
}
}  // namespace resource_usage
}  // namespace process
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceUsage_getTimeUsageNanos(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceUsageClass_, self)
  return std::chrono::duration_cast<std::chrono::nanoseconds>(this_->timeUsage)
      .count();
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceUsage_getUserTimeUsageMillis(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceUsageClass_, self)
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             this_->userTimeUsage).count();
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceUsage_getSystemTimeUsageMillis(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceUsageClass_, self)
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             this_->systemTimeUsage).count();
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceUsage_getMemoryUsageBytes(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceUsageClass_, self)
  return this_->memoryUsageBytes;
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
