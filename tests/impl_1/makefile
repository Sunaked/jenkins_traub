all:
	@mkdir -p build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=True .. && make -j && ctest -V
	# Create soft link to compile_commands.json if it not exist in project dir
	@if [ -L compile_commands.json ] ; then printf "compile_commands.json exists"; else echo "Creating symlink compile_commands.json"; ln -s build/compile_commands.json .; fi


clean:
	$(MAKE) clean -C build/
