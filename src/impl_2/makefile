all:
	@mkdir -p build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=True -S . -B build && cmake --build build && cd build && ./jenkins_traub_impl_2

	# Create soft link to compile_commands.json if it not exist in project dir
	@if [ -L compile_commands.json ] ; then printf "compile_commands.json exists"; else echo "Creating symlink compile_commands.json"; ln -s build/compile_commands.json .; fi

