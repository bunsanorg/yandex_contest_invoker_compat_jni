project(yandex_contest_invoker_compat_jni)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

cmake_minimum_required(VERSION 2.8)

include(BunsanCommon)

bunsan_use_boost(system filesystem serialization program_options)

# JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
bunsan_use(${JAVA_JVM_LIBRARY})

# JNI generated headers
include_directories(jni_include)

bunsan_use(
    yandex_contest_common
    yandex_contest_system
    yandex_contest_invoker
    yandex_contest_invoker_flowctl_game
    yandex_contest_invoker_compat_common
)

bunsan_add_shared_library(${PROJECT_NAME}
    src/Context.cpp
    src/ContextJVM.cpp
    src/ContextThread.cpp
    src/String.cpp
    src/CxxClass.cpp
    src/Collection.cpp
    src/NotNull.cpp

    src/impl/PackageInit.cpp
    src/impl/Container.cpp
    src/impl/Filesystem.cpp
    src/impl/ProcessGroup.cpp
    src/impl/Process.cpp
    src/impl/Stream.cpp
    src/impl/Pipe.cpp
    src/impl/Log.cpp
    src/impl/File.cpp
    src/impl/FdAlias.cpp
    src/impl/ContainerConfig.cpp
    src/impl/ControlProcessConfig.cpp
    src/impl/process/Result.cpp
    src/impl/process/ResourceUsage.cpp
    src/impl/process/ResourceLimits.cpp
    src/impl/process/DefaultSettings.cpp
    src/impl/process_group/Result.cpp
    src/impl/process_group/ResourceUsage.cpp
    src/impl/process_group/ResourceLimits.cpp
    src/impl/process_group/DefaultSettings.cpp
    src/impl/lxc/Config.cpp
    src/impl/lxc/MountConfig.cpp
    src/impl/lxc/RootfsConfig.cpp
    src/impl/filesystem/Config.cpp
    src/impl/filesystem/File.cpp
    src/impl/filesystem/Directory.cpp
    src/impl/filesystem/Device.cpp
    src/impl/filesystem/RegularFile.cpp
    src/impl/filesystem/SymLink.cpp
    src/impl/filesystem/Fifo.cpp
    src/impl/unistd/MountEntry.cpp
    src/impl/unistd/FileStatus.cpp
    src/impl/unistd/access/Id.cpp

    src/flowctl/game/impl/Configurator.cpp
)

bunsan_install_headers()
bunsan_install_targets(${PROJECT_NAME})

bunsan_include_tests()
