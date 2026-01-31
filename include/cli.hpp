#pragma once

/*

This just defines a struct CommandLineArguments, Takes in source path and out path.
I imagine we will use this struct to store args when calling the main function
in this is the Source path and the Out path

very similar to gcc in.cpp -o out.asm

*/


#include <unistd.h>

#include <iostream>

struct CommandLineArguments {
  std::string compile_source_path;
  std::string compile_output_path;
};

CommandLineArguments ParseCommandLineArgs(int argc, char **argv);
