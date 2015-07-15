#include "com_yandex_contest_invoker_impl_process_ProcessResourceLimits.h"

#include <yandex/contest/invoker/compat/jni/impl/process/ResourceLimits.hpp>

#include <yandex/contest/invoker/compat/jni/config/load.hpp>
#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::Process;

namespace {
CxxClass<Process::ResourceLimits> resourceLimitsClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_classInit(
    JNIEnv *env, jclass resourceLimitsClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  resourceLimitsClass_.assign(resourceLimitsClass, "impl");
  YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_finalize(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_FINALIZE(env, resourceLimitsClass_, self)
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace process {
namespace resource_limits {
LocalRef<jobject> create(const Process::ResourceLimits &resourceLimits) {
  return resourceLimitsClass_.setPointerCreate(resourceLimits);
}
}  // namespace resource_limits
}  // namespace process
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex

void Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_create(
    JNIEnv *env, jobject self, jobject resourceLimits) {
  YANDEX_JNI_METHOD_BEGIN(env)
  resourceLimitsClass_.copyToPointer(
      self, config::load<Process::ResourceLimits>(resourceLimits));
  YANDEX_JNI_METHOD_END_VOID(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_getTimeLimitNanos(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceLimitsClass_, self)
  return std::chrono::duration_cast<std::chrono::nanoseconds>(this_->timeLimit)
      .count();
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_getUserTimeLimitMillis(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceLimitsClass_, self)
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             this_->userTimeLimit).count();
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_getSystemTimeLimitMillis(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceLimitsClass_, self)
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             this_->systemTimeLimit).count();
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_getMemoryLimitBytes(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceLimitsClass_, self)
  return this_->memoryLimitBytes;
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_getOutputLimitBytes(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceLimitsClass_, self)
  return this_->outputLimitBytes;
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_ProcessResourceLimits_getNumberOfProcesses(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceLimitsClass_, self)
  return this_->numberOfProcesses;
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
