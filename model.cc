#include <cstdlib>
#include <regex>
#include <string>

//
int main(int argc, char* argv[])
{
    std::string filename { argv[1] };
    std::regex r { R"((.+)\.(cpp|cxx|cc)$)" };
    std::smatch m;
    std::regex_match(filename, m, r);
    std::string target { std::string(m[1]) + ".class" };
    std::string command { std::string("clang++ -Xclang -fdump-record-layouts -fsyntax-only ") + std::string(m[0]) + std::string(" > ") + target };
    system(command.c_str());
    return 0;
}