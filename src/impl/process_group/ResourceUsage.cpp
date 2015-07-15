#include "com_yandex_contest_invoker_impl_process_group_ProcessGroupResourceUsage.h"

#include <yandex/contest/invoker/compat/jni/impl/process_group/ResourceUsage.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::ProcessGroup;

namespace {
CxxClass<ProcessGroup::ResourceUsage> resourceUsageClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResourceUsage_classInit(
    JNIEnv *env, jclass resourceUsageClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  resourceUsageClass_.assign(resourceUsageClass, "impl");
  YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResourceUsage_finalize(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_FINALIZE(env, resourceUsageClass_, self);
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace process_group {
namespace resource_usage {
LocalRef<jobject> create(const ProcessGroup::ResourceUsage &resourceUsage) {
  return resourceUsageClass_.setPointerCreate(resourceUsage);
}
}  // namespace resource_usage
}  // namespace process_group
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
