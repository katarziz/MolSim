#fetch spdlog
include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)

set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "Use external fmt" FORCE)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

#Variable to set compile-time logging level.
#Can be set with the flag SPDLOG_ACTIVE_LEVEL
#possible options are:
# SPDLOG_LEVEL_OFF
# SPDLOG_LEVEL_CRITICAL
# SPDLOG_LEVEL_ERROR
# SPDLOG_LEVEL_WARN
# SPDLOG_LEVEL_INFO
# SPDLOG_LEVEL_DEBUG
# SPDLOG_LEVEL_TRACE
add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO)
