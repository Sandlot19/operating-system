// Hard Drive utility
// Jacob Rutherford
#include <string>
#include <vector>

class HddWriter {
  public:
    HddWriter(const std::string& output_file,
              const std::string& boot16_input,
              const std::string& boot32_input,
              const std::string& kernel_input);
    ~HddWriter();
    void Write();
  private:
    void WriteBuffer(const std::vector<uint8_t>& buffer) const;
    void ReadFile(FILE* f, std::vector<uint8_t>* buffer) const;
    FILE* output_file_;
    const std::string boot16_source_;
    const std::string boot32_source_;
    const std::string kernel_start_;
};
