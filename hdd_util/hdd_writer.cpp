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
  FILE* kernel = fopen(kernel_start_.c_str(), "r");
  if (boot16 == nullptr) {
    perror(boot16_source_.c_str());
    return;
  }
  else if (boot32 == nullptr) {
    perror(boot32_source_.c_str());
    return;
  }
  else if (kernel == nullptr) {
    perror(kernel_start_.c_str());
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

  // The kernel size is the first 4 bytes of the sector following the 32 bit
  // boot loader. Get that number and resize buffer to read in the kernel
  uint32_t kernel_size = GetKernelSize(kernel);

  buffer.resize(kSectorSize);
  buffer[0] = static_cast<uint8_t>(kernel_size & 0xFF);
  buffer[1] = static_cast<uint8_t>((kernel_size >> 8) & 0xFF);
  buffer[2] = static_cast<uint8_t>((kernel_size >> 16) & 0xFF);
  buffer[3] = static_cast<uint8_t>((kernel_size >> 24) & 0xFF);

  WriteBuffer(buffer);
  buffer.clear();
  buffer.resize(kernel_size, 0);

  // Read kernel.bin into buffer
  ReadFile(kernel, &buffer);

  // write kernel to hdd file
  WriteBuffer(buffer);
  buffer.clear();

  // Pad the rest of the disk with 0s
  buffer.resize(kMinDiskSize - (kSectorSize * 9) - kernel_size, 0);
  WriteBuffer(buffer);

  printf("%s: hard drive file written\n", __func__);
}

void HddWriter::ReadFile(FILE* f, std::vector<uint8_t>* buffer) const {
  fread(buffer->data(), buffer->size(), 1, f);
}

void HddWriter::WriteBuffer(const std::vector<uint8_t>& buffer) const {
  fwrite(buffer.data(), buffer.size(), 1, output_file_);
  return;
}

uint32_t HddWriter::GetKernelSize(FILE* kernel_file) const {
  uint32_t size;
  fseek(kernel_file, 0, SEEK_END);
  size = ftell(kernel_file);
  rewind(kernel_file);
  printf("%s: kernel size is: %d\n", __func__, size);
  return size;
}
