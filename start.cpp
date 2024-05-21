#include "test.cpp"

int main(int argc, char **argv) {
    Test test = Test();
    test.ReadArgs(argc, argv);
    test.ExecuteCommand();
}
