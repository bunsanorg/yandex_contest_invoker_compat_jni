#include "com_yandex_contest_invoker_flowctl_game_impl_Configurator.h"

#include "yandex/contest/invoker/flowctl/game/Configurator.hpp"

#include "yandex/contest/invoker/compat/ContainerContext.hpp"
#include "yandex/contest/invoker/compat/ProcessGroupContext.hpp"
#include "yandex/contest/invoker/compat/ProcessContext.hpp"

#include "yandex/contest/invoker/compat/jni/CxxClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"
#include "yandex/contest/invoker/compat/jni/Enum.hpp"
#include "yandex/contest/invoker/compat/jni/Collection.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::ContainerPointer;
using yandex::contest::invoker::ProcessGroupPointer;
using yandex::contest::invoker::ProcessPointer;
using yandex::contest::invoker::compat::ContainerContext;
using yandex::contest::invoker::compat::ContainerContextPointer;
using yandex::contest::invoker::compat::ProcessGroupHandle;
using yandex::contest::invoker::compat::ProcessHandle;
using yandex::contest::invoker::flowctl::game::Configurator;
using yandex::contest::invoker::flowctl::game::BrokerImpl;

namespace
{
    CxxClass<ContainerContextPointer> containerClass_;
    CxxClass<ProcessGroupHandle> processGroupClass_;
    CxxClass<ProcessHandle> processClass_;
    GlobalJClass configClass_;
    jmethodID getContainerId_, getProcessGroupId_, getBrokerId_,
              getKillerId_, getJudgeId_, getSolutionsId_;
}

void Java_com_yandex_contest_invoker_flowctl_game_impl_Configurator_classInit(
    JNIEnv *env, jclass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerClass_.assign("com/yandex/contest/invoker/impl/Container", "impl");
    processGroupClass_.assign("com/yandex/contest/invoker/impl/ProcessGroup", "impl");
    processClass_.assign("com/yandex/contest/invoker/impl/Process", "impl");
    configClass_.assign("com/yandex/contest/invoker/flowctl/game/IConfig");
    getContainerId_ =
        configClass_.getMethodId("getContainer",
                                 "()Lcom/yandex/contest/invoker/impl/Container;");
    getProcessGroupId_ =
        configClass_.getMethodId("getProcessGroup",
                                 "()Lcom/yandex/contest/invoker/impl/ProcessGroup;");
    getBrokerId_ =
        configClass_.getMethodId("getBroker",
                                 "()Lcom/yandex/contest/invoker/impl/Process;");
    getKillerId_ =
        configClass_.getMethodId("getKiller",
                                 "()Lcom/yandex/contest/invoker/impl/Process;");
    getJudgeId_ =
        configClass_.getMethodId("getJudge",
                                 "()Lcom/yandex/contest/invoker/impl/Process;");
    getSolutionsId_ =
        configClass_.getMethodId("getSolutions",
                                 "()Ljava/util/List;");
    YANDEX_JNI_METHOD_END_VOID(env)
}

namespace
{
    template <typename Class>
    typename Class::Type::ChildContext::MemberPointer loadFromContext(
        const Class &clazz, jobject jobj)
    {
        // note: precondition MemberPointer is specialization of boost::intrusive_ptr
        return typename Class::Type::ChildContext::MemberPointer(
            &clazz.getReference(jobj).member());
    }

    Configurator loadConfigurator(jobject config)
    {
        const Context::Handle ctx = Context::getContext();
        Configurator cfg = config::load<Configurator>(config);

        LocalRef<jobject> container(ctx->env()->CallObjectMethod(config, getContainerId_));
        cfg.container = ContainerPointer(&containerClass_.getReference(container.get())->member());

        LocalRef<jobject> processGroup(ctx->env()->CallObjectMethod(config, getProcessGroupId_));
        cfg.processGroup = loadFromContext(processGroupClass_, processGroup.get());

        LocalRef<jobject> broker(ctx->env()->CallObjectMethod(config, getBrokerId_));
        cfg.broker = loadFromContext(processClass_, broker.get());

        LocalRef<jobject> killer(ctx->env()->CallObjectMethod(config, getKillerId_));
        cfg.killer = loadFromContext(processClass_, killer.get());

        LocalRef<jobject> judge(ctx->env()->CallObjectMethod(config, getJudgeId_));
        cfg.judge = loadFromContext(processClass_, judge.get());

        LocalRef<jobject> solutions(ctx->env()->CallObjectMethod(config, getSolutionsId_));
        getIterable(solutions.get(),
            [&cfg](jobject jobj)
            {
                cfg.solutions.push_back(loadFromContext(processClass_, jobj));
            });

        return cfg;
    }
}

void Java_com_yandex_contest_invoker_flowctl_game_impl_Configurator_configure__Lcom_yandex_contest_invoker_flowctl_game_IConfig_2Ljava_lang_String_2Ljava_lang_String_2(
    JNIEnv *env, jclass, jobject config, jstring brokerConfig, jstring killerConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    Configurator cfg = loadConfigurator(config);
    cfg.configure(getStringUTF(brokerConfig), getStringUTF(killerConfig));
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_flowctl_game_impl_Configurator_configure__Lcom_yandex_contest_invoker_flowctl_game_IConfig_2(
    JNIEnv *env, jclass, jobject config)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    Configurator cfg = loadConfigurator(config);
    cfg.configure();
    YANDEX_JNI_METHOD_END_VOID(env)
}

