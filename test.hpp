#include <map>
#include <string>

class Test {
 public:
    Test();
    void ReadArgs(int argc, char **argv);
    void ExecuteCommand();

 private:
    enum ErrorCode {
        ArgError,
        WrongFile,
    };
    std::map<std::string, std::string> args_;
    int word_count_ {0};
    uint32_t checksum_ {0};
    void PrintHelp();
    void CountWord();
    void CountChecksum();
};
