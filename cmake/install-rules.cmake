if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/crillab-autis-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package crillab-autis)

install(
    DIRECTORY
    include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT crillab-autis_Development
)

install(
    TARGETS crillab-autis_crillab-autis
    EXPORT crillab-autisTargets
    RUNTIME #
    COMPONENT crillab-autis_Runtime
    LIBRARY #
    COMPONENT crillab-autis_Runtime
    NAMELINK_COMPONENT crillab-autis_Development
    ARCHIVE #
    COMPONENT crillab-autis_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

if (VCPKG_TARGET_TRIPLET)
# Allow package maintainers to freely override the path for the configs
set(
    crillab-universe_INSTALL_CMAKEDIR "${CMAKE_INSTALL_PREFIX}/share/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
else ()
set(
    crillab-universe_INSTALL_CMAKEDIR "${CMAKE_INSTALL_INCLUDEDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
endif()
mark_as_advanced(crillab-autis_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${crillab-autis_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT crillab-autis_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${crillab-autis_INSTALL_CMAKEDIR}"
    COMPONENT crillab-autis_Development
)

install(
    EXPORT crillab-autisTargets
    NAMESPACE crillab-autis::
    DESTINATION "${crillab-autis_INSTALL_CMAKEDIR}"
    COMPONENT crillab-autis_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
