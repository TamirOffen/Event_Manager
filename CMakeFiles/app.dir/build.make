# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager"

# Include any dependencies generated for this target.
include CMakeFiles/app.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app.dir/flags.make

CMakeFiles/app.dir/main.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/app.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/main.c.o -c "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/main.c"

CMakeFiles/app.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/main.c" > CMakeFiles/app.dir/main.c.i

CMakeFiles/app.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/main.c" -o CMakeFiles/app.dir/main.c.s

CMakeFiles/app.dir/member.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/member.c.o: member.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/app.dir/member.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/member.c.o -c "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/member.c"

CMakeFiles/app.dir/member.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/member.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/member.c" > CMakeFiles/app.dir/member.c.i

CMakeFiles/app.dir/member.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/member.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/member.c" -o CMakeFiles/app.dir/member.c.s

CMakeFiles/app.dir/event.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/event.c.o: event.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/app.dir/event.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/event.c.o -c "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/event.c"

CMakeFiles/app.dir/event.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/event.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/event.c" > CMakeFiles/app.dir/event.c.i

CMakeFiles/app.dir/event.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/event.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/event.c" -o CMakeFiles/app.dir/event.c.s

CMakeFiles/app.dir/date.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/date.c.o: date.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/app.dir/date.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/date.c.o -c "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/date.c"

CMakeFiles/app.dir/date.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/date.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/date.c" > CMakeFiles/app.dir/date.c.i

CMakeFiles/app.dir/date.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/date.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/date.c" -o CMakeFiles/app.dir/date.c.s

CMakeFiles/app.dir/event_manager.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/event_manager.c.o: event_manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/app.dir/event_manager.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/event_manager.c.o -c "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/event_manager.c"

CMakeFiles/app.dir/event_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/event_manager.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/event_manager.c" > CMakeFiles/app.dir/event_manager.c.i

CMakeFiles/app.dir/event_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/event_manager.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/event_manager.c" -o CMakeFiles/app.dir/event_manager.c.s

CMakeFiles/app.dir/priority_queue.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/priority_queue.c.o: priority_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/app.dir/priority_queue.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/priority_queue.c.o -c "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/priority_queue.c"

CMakeFiles/app.dir/priority_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/priority_queue.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/priority_queue.c" > CMakeFiles/app.dir/priority_queue.c.i

CMakeFiles/app.dir/priority_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/priority_queue.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/priority_queue.c" -o CMakeFiles/app.dir/priority_queue.c.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/main.c.o" \
"CMakeFiles/app.dir/member.c.o" \
"CMakeFiles/app.dir/event.c.o" \
"CMakeFiles/app.dir/date.c.o" \
"CMakeFiles/app.dir/event_manager.c.o" \
"CMakeFiles/app.dir/priority_queue.c.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

app: CMakeFiles/app.dir/main.c.o
app: CMakeFiles/app.dir/member.c.o
app: CMakeFiles/app.dir/event.c.o
app: CMakeFiles/app.dir/date.c.o
app: CMakeFiles/app.dir/event_manager.c.o
app: CMakeFiles/app.dir/priority_queue.c.o
app: CMakeFiles/app.dir/build.make
app: CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app.dir/build: app

.PHONY : CMakeFiles/app.dir/build

CMakeFiles/app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app.dir/clean

CMakeFiles/app.dir/depend:
	cd "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager" "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager" "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager" "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager" "/Users/tamiroffen/Documents/Winter 2020 - Sem 2/Matam/HW/hw1/Event_Manager/CMakeFiles/app.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/app.dir/depend

