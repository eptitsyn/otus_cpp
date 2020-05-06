//#include "bayan.hpp"
#include "file.hpp"
#include "hash.hpp"

#include <boost/filesystem.hpp>
#include <iostream>
#include <unordered_set>

namespace fs = boost::filesystem;

int main()
{
    // dups.SetScanDirs({"./test_data"});
    // dups.Run();
    int hbs = 100;
    auto p1 = fs::path("./aaa.txt");
    auto p2 = fs::path("./bbb.txt");
    CRC32Hasher hasher;

    File f1(fs::weakly_canonical(p1), fs::file_size(p1), hbs, &hasher);
    File f2(fs::weakly_canonical(p2), fs::file_size(p2), hbs, &hasher);
    bool result = f1.EqualByHashTo(f2);
    std::cout << result << std::endl;
    return 0;
}