#include "hdd_writer.h"

#include <cstdio>
#include <cstdint>

namespace {
  constexpr size_t kSectorSize = 512;
  
  // Minimum size of disk for bochs to understand it is 16MiB = 2^23
  constexpr size_t kMinDiskSize = (2 << 23);
}

HddWriter::HddWriter(const std::string& output_file,
                     const std::string& boot16_input,
                     const std::string& boot32_input,
                     const std::string& kernel_input)
  : output_file_(nullptr),
    boot16_source_(boot16_input),
    boot32_source_(boot32_input),
    kernel_start_(kernel_input) {
  output_file_ = std::fopen(output_file.c_str(), "w");
}

HddWriter::~HddWriter() {
  std::fclose(output_file_);
}

void HddWriter::Write() {
  FILE* boot16 = fopen(boot16_source_.c_str(), "r");
  FILE* boot32 = fopen(boot32_source_.c_str(), "r");
  if (boot16 == nullptr) {
    //fprintf(stderr, "error opening %s\n", boot16_source_.c_str());
    perror(boot16_source_.c_str());
    return;
  }
  else if (boot32 == nullptr) {
    //fprintf(stderr, "error opening %s\n", boot32_source_.c_str());
    perror(boot32_source_.c_str());
    return;
  }

  // Make the initial size of the buffer one sector, to hold the 16 bit boot
  // loader
  std::vector<uint8_t> buffer(kSectorSize);


  // Read boot16.bin into buffer
  ReadFile(boot16, &buffer);

  WriteBuffer(buffer);
  buffer.clear();

  // The next 7 sectors are for the 32 bit boot loader
  // padded with 0s
  buffer.resize(kSectorSize * 7, 0);

  // Read boot32.bin into buffer
  ReadFile(boot32, &buffer);

  WriteBuffer(buffer);
  buffer.clear();

  buffer.clear();

  // Pad the rest of the disk with 0s
  buffer.resize(kMinDiskSize - (kSectorSize * 9) - kernel_size, 0);
  WriteBuffer(buffer);

  // TODO: Get kernel size, resize buffer, read kernel into buffer, write buffer
  printf("%s: hard drive file written\n", __func__);
}

void HddWriter::ReadFile(FILE* f, std::vector<uint8_t>* buffer) const {
  fread(buffer->data(), buffer->size(), 1, f);
}

void HddWriter::WriteBuffer(const std::vector<uint8_t>& buffer) const {

  fwrite(buffer.data(), buffer.size(), 1, output_file_);

  return;
}
