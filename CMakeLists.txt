project(yandex_contest_invoker_compat_jni)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

cmake_minimum_required(VERSION 2.8)

include(YandexContestCommon)

# BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system filesystem serialization unit_test_framework program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND libraries ${Boost_LIBRARIES})

# JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# JNI generated headers
include_directories(jni_include)

# yandex_contest_*
list(APPEND libraries
    yandex_contest_common
    yandex_contest_system
    yandex_contest_invoker
    yandex_contest_invoker_flowctl_game
    yandex_contest_invoker_compat_common
)

# Local
include_directories(include)

# Targets
add_library(${PROJECT_NAME} SHARED
    src/Context.cpp
    src/ContextJVM.cpp
    src/ContextThread.cpp
    src/String.cpp
    src/CXXClass.cpp
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
    src/impl/FDAlias.cpp
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
    src/impl/filesystem/Config.cpp
    src/impl/filesystem/File.cpp
    src/impl/filesystem/Directory.cpp
    src/impl/filesystem/Device.cpp
    src/impl/filesystem/RegularFile.cpp
    src/impl/filesystem/SymLink.cpp
    src/impl/filesystem/FIFO.cpp
    src/impl/unistd/MountEntry.cpp
    src/impl/unistd/FileStatus.cpp
    src/impl/unistd/access/Id.cpp

    src/flowctl/game/impl/Configurator.cpp
)
target_link_libraries(${PROJECT_NAME} ${libraries} ${JAVA_JVM_LIBRARY})

# Installation
install(DIRECTORY include DESTINATION .)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

yandex_contest_tests()
