# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Saul\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.6693.114\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Saul\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.6693.114\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Saul\Projects\LX\LimpChimp-CS-GO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio

# Include any dependencies generated for this target.
include CMakeFiles\LimpChimp_CS_GO.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\LimpChimp_CS_GO.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\LimpChimp_CS_GO.dir\flags.make

CMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.obj: CMakeFiles\LimpChimp_CS_GO.dir\flags.make
CMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.obj: ..\LimpChimp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LimpChimp_CS_GO.dir/LimpChimp.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.obj /FdCMakeFiles\LimpChimp_CS_GO.dir\ /FS -c C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\LimpChimp.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LimpChimp_CS_GO.dir/LimpChimp.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\LimpChimp.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LimpChimp_CS_GO.dir/LimpChimp.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.s /c C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\LimpChimp.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.obj: CMakeFiles\LimpChimp_CS_GO.dir\flags.make
CMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.obj: ..\Hooks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LimpChimp_CS_GO.dir/Hooks.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.obj /FdCMakeFiles\LimpChimp_CS_GO.dir\ /FS -c C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\Hooks.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LimpChimp_CS_GO.dir/Hooks.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\Hooks.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LimpChimp_CS_GO.dir/Hooks.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.s /c C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\Hooks.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.obj: CMakeFiles\LimpChimp_CS_GO.dir\flags.make
CMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.obj: ..\process\process.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LimpChimp_CS_GO.dir/process/process.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.obj /FdCMakeFiles\LimpChimp_CS_GO.dir\ /FS -c C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\process\process.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LimpChimp_CS_GO.dir/process/process.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\process\process.cpp
<<

CMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LimpChimp_CS_GO.dir/process/process.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.s /c C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\process\process.cpp
<<

# Object files for target LimpChimp_CS_GO
LimpChimp_CS_GO_OBJECTS = \
"CMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.obj" \
"CMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.obj" \
"CMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.obj"

# External object files for target LimpChimp_CS_GO
LimpChimp_CS_GO_EXTERNAL_OBJECTS =

LimpChimp_CS_GO.dll: CMakeFiles\LimpChimp_CS_GO.dir\LimpChimp.cpp.obj
LimpChimp_CS_GO.dll: CMakeFiles\LimpChimp_CS_GO.dir\Hooks.cpp.obj
LimpChimp_CS_GO.dll: CMakeFiles\LimpChimp_CS_GO.dir\process\process.cpp.obj
LimpChimp_CS_GO.dll: CMakeFiles\LimpChimp_CS_GO.dir\build.make
LimpChimp_CS_GO.dll: CMakeFiles\LimpChimp_CS_GO.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library LimpChimp_CS_GO.dll"
	C:\Users\Saul\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.6693.114\bin\cmake\win\bin\cmake.exe -E vs_link_dll --intdir=CMakeFiles\LimpChimp_CS_GO.dir --rc=C:\PROGRA~2\WINDOW~4\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WINDOW~4\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\LimpChimp_CS_GO.dir\objects1.rsp @<<
 /out:LimpChimp_CS_GO.dll /implib:LimpChimp_CS_GO.lib /pdb:C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio\LimpChimp_CS_GO.pdb /dll /version:0.0 /machine:X86 /debug /INCREMENTAL  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib  
<<

# Rule to build all files generated by this target.
CMakeFiles\LimpChimp_CS_GO.dir\build: LimpChimp_CS_GO.dll

.PHONY : CMakeFiles\LimpChimp_CS_GO.dir\build

CMakeFiles\LimpChimp_CS_GO.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LimpChimp_CS_GO.dir\cmake_clean.cmake
.PHONY : CMakeFiles\LimpChimp_CS_GO.dir\clean

CMakeFiles\LimpChimp_CS_GO.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Saul\Projects\LX\LimpChimp-CS-GO C:\Users\Saul\Projects\LX\LimpChimp-CS-GO C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio C:\Users\Saul\Projects\LX\LimpChimp-CS-GO\cmake-build-debug-visual-studio\CMakeFiles\LimpChimp_CS_GO.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\LimpChimp_CS_GO.dir\depend

