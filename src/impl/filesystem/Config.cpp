#include "com_yandex_contest_invoker_impl_filesystem_FilesystemConfig.h"

#include "yandex/contest/invoker/compat/jni/impl/filesystem/Config.hpp"
#include "yandex/contest/invoker/compat/jni/impl/filesystem/RegularFile.hpp"
#include "yandex/contest/invoker/compat/jni/impl/filesystem/Device.hpp"
#include "yandex/contest/invoker/compat/jni/impl/filesystem/Directory.hpp"
#include "yandex/contest/invoker/compat/jni/impl/filesystem/SymLink.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/Collection.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

#include <boost/variant/static_visitor.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace
{
    CXXClass<filesystem::Config> configClass_;
}

void Java_com_yandex_contest_invoker_impl_filesystem_FilesystemConfig_classInit(
    JNIEnv *env, jclass configClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    configClass_.assign(configClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_filesystem_FilesystemConfig_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, configClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace config
{
    LocalRef<jobject> create(const invoker::filesystem::Config &config)
    {
        return configClass_.setPointerCreate(config);
    }
}}}}}}}}

void Java_com_yandex_contest_invoker_impl_filesystem_FilesystemConfig_create(
    JNIEnv *env, jobject self, jobject filesystemConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    configClass_.copyToPointer(self, config::load<filesystem::Config>(filesystemConfig));
    YANDEX_JNI_METHOD_END_VOID(env)
}

namespace
{
    // note: boost::apply_visitor does not support move semantics
    class CreateFileVisitor: public boost::static_visitor<void>
    {
    public:
        explicit CreateFileVisitor(LocalRef<jobject> &createFile):
            createFile_(createFile) {}

        void operator()(const filesystem::RegularFile &regularFile) const
        {
            createFile_ = impl::filesystem::regular_file::create(regularFile);
        }

        void operator()(const filesystem::Device &device) const
        {
            createFile_ = impl::filesystem::device::create(device);
        }

        void operator()(const filesystem::Directory &directory) const
        {
            createFile_ = impl::filesystem::directory::create(directory);
        }

        void operator()(const filesystem::SymLink &symLink) const
        {
            createFile_ = impl::filesystem::sym_link::create(symLink);
        }

    private:
        LocalRef<jobject> &createFile_;
    };

    struct CreateArchive
    {
        CreateArchive &operator&(const filesystem::CreateFile::Variant &createFileVariant)
        {
            boost::apply_visitor(CreateFileVisitor(createFile), createFileVariant);
            return *this;
        }

        LocalRef<jobject> createFile;
    };

    LocalRef<jobject> createFileCreate(const filesystem::CreateFile &createFile)
    {
        CreateArchive ar;
        // FIXME boost::serialization::access should be used
        const_cast<filesystem::CreateFile &>(createFile).serialize(ar, 0);
        return std::move(ar.createFile);
    }
}

jobject Java_com_yandex_contest_invoker_impl_filesystem_FilesystemConfig_getCreateFiles(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    return newArrayList(this_->createFiles, createFileCreate).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
