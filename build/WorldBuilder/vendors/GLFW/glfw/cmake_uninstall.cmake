
if (NOT EXISTS "E:/_prog/C++/Engine/SimpleWorldBuilder/SimpleWorldBuilder/build/WorldBuilder/vendors/GLFW/glfw/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"E:/_prog/C++/Engine/SimpleWorldBuilder/SimpleWorldBuilder/build/WorldBuilder/vendors/GLFW/glfw/install_manifest.txt\"")
endif()

file(READ "E:/_prog/C++/Engine/SimpleWorldBuilder/SimpleWorldBuilder/build/WorldBuilder/vendors/GLFW/glfw/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("C:/cmake-3.31.0-rc2-windows-x86_64/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("C:/cmake-3.31.0-rc2-windows-x86_64/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

