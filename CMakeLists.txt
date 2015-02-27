project(yandex_contest_invoker_compat_jni)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

cmake_minimum_required(VERSION 3.0)

find_package(BunsanCMake CONFIG REQUIRED)

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
)
target_include_directories(${PROJECT_NAME} PRIVATE jni_include)
bunsan_use_bunsan_package(${PROJECT_NAME} yandex_contest_invoker_compat_common
    yandex_contest_invoker_compat_common
)
find_package(JNI REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${JNI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${JAVA_JVM_LIBRARY})

bunsan_install_headers()
bunsan_install_targets(${PROJECT_NAME})
bunsan_install_project()

bunsan_include_tests()
