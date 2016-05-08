#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "console_color.h"

using namespace std;
using int_set = unordered_set<int>;
//using int_set = set<int>;
using fa_table_row = unordered_map<string, int_set>;
using fa_table = unordered_map<int, fa_table_row>;

class Utils
{
public:
    Utils();
    static string TO_STRING(vector<int> v);
    static string TO_STRING(int_set s);
};

#endif // UTILS_H
