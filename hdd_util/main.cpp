#include "hdd_writer.h"

#include <cstdlib>
#include <cstdio>
#include <unistd.h>

void usage(const std::string& prog) {
  fprintf(stderr, "usage: %s -o <output_file> <boot16> <boot32> <kernel>\n", prog.c_str());
  return;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    usage(std::string(argv[0]));
    return EXIT_FAILURE;
  }

  int opt;
  std::string output_file;
  std::vector<std::string> input_files;
  while ((opt = getopt(argc, argv, "vo:")) != -1) {
    switch(opt) {
      case 'o':
        if(optarg) output_file = optarg;
        break;
      default:
        fprintf(stderr, "invalid argument\n");
        usage(std::string(argv[0]));
        return EXIT_FAILURE;
    }
  }

  for (size_t i = optind; i < argc; i++) {
    input_files.push_back(std::string(argv[i]));
  }

  if (input_files.size() != 3) {
    fprintf(stderr, "incorrect number of input files\n");
    return EXIT_FAILURE;
  }

  HddWriter hdd_writer(output_file, input_files[0], input_files[1], input_files[2]);
  hdd_writer.Write();
  return EXIT_SUCCESS;
}
