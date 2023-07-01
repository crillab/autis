# ---- In-source guard ----

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(
      FATAL_ERROR
      "In-source builds are not supported. "
      "Please read the BUILDING document before trying to build this project. "
      "You may need to delete 'CMakeCache.txt' and 'CMakeFiles/' first."
  )
endif()

option(COMPILE_GMP "If this option is enabled, Universe will be compiled with the GMP library for handling large numbers. When off BigInteger is an alias for long long. " Off)
