#include "com_yandex_contest_invoker_impl_unistd_MountEntry.h"

#include <yandex/contest/invoker/compat/jni/impl/unistd/MountEntry.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::system::unistd::MountEntry;

namespace {
CxxClass<MountEntry> mountEntryClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_unistd_MountEntry_classInit(
    JNIEnv *env, jclass mountEntryClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  mountEntryClass_.assign(mountEntryClass, "impl");
  YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_unistd_MountEntry_finalize(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_FINALIZE(env, mountEntryClass_, self);
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace unistd {
namespace mount_entry {
LocalRef<jobject> create(const system::unistd::MountEntry &entry) {
  return mountEntryClass_.setPointerCreate(entry);
}
}  // namespace mount_entry
}  // namespace unistd
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex

void Java_com_yandex_contest_invoker_impl_unistd_MountEntry_create(
    JNIEnv *env, jobject self, jstring fsname, jstring dir, jstring type,
    jstring opts, jint freq, jint passno) {
  YANDEX_JNI_METHOD_BEGIN(env)
  MountEntry entry;
  entry.fsname = getStringUTF(fsname);
  entry.dir = getStringUTF(dir);
  entry.type = getStringUTF(type);
  entry.opts = getStringUTF(opts);
  entry.freq = freq;
  entry.passno = passno;
  mountEntryClass_.copyToPointer(self, entry);
  YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_unistd_MountEntry_proc(JNIEnv *env,
                                                                    jclass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  return impl::unistd::mount_entry::create(MountEntry::proc()).release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

/// Signature:
/// (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lcom/yandex/contest/invoker/impl/unistd/MountEntry;
jobject
Java_com_yandex_contest_invoker_impl_unistd_MountEntry_bind__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2(
    JNIEnv *env, jclass, jstring from, jstring to, jstring opts) {
  YANDEX_JNI_METHOD_BEGIN(env)
  return impl::unistd::mount_entry::create(
             MountEntry::bind(getStringUTF(from), getStringUTF(to),
                              getStringUTF(opts))).release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

/// Signature:
/// (Ljava/lang/String;Ljava/lang/String;)Lcom/yandex/contest/invoker/impl/unistd/MountEntry;
jobject
Java_com_yandex_contest_invoker_impl_unistd_MountEntry_bind__Ljava_lang_String_2Ljava_lang_String_2(
    JNIEnv *env, jclass, jstring from, jstring to) {
  YANDEX_JNI_METHOD_BEGIN(env)
  return impl::unistd::mount_entry::create(
             MountEntry::bind(getStringUTF(from), getStringUTF(to))).release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_unistd_MountEntry_bindRO(
    JNIEnv *env, jclass, jstring from, jstring to) {
  YANDEX_JNI_METHOD_BEGIN(env)
  return impl::unistd::mount_entry::create(
             MountEntry::bindRO(getStringUTF(from), getStringUTF(to)))
      .release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_unistd_MountEntry_fsname(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, mountEntryClass_, self)
  return newStringUTF(this_->fsname).release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_unistd_MountEntry_dir(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, mountEntryClass_, self)
  return newStringUTF(this_->dir).release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_unistd_MountEntry_type(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, mountEntryClass_, self)
  return newStringUTF(this_->type).release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_unistd_MountEntry_opts(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, mountEntryClass_, self)
  return newStringUTF(this_->opts).release();
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_MountEntry_freq(JNIEnv *env,
                                                                 jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, mountEntryClass_, self)
  return this_->freq;
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_MountEntry_passno(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, mountEntryClass_, self)
  return this_->passno;
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
