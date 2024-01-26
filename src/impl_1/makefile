
all:
	@printf "${Purple}\nExecuting jenkins_traub_impl_1 in Debug type ...${NC}\n"
	mkdir -p build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=True -DCMAKE_BUILD_TYPE=Debug .. && make && echo "\n\n" && ./jenkins_traub_impl_1

	# Create soft link to compile_commands.json if it not exist in project dir
	@if [ -L compile_commands.json ] ; then printf "compile_commands.json exists"; else echo "Creating symlink compile_commands.json"; ln -s build/compile_commands.json .; fi

