#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using table_row = unordered_map<string, unordered_set<int>>;
using table = unordered_map<int, table_row>;

class Utils
{
public:
    Utils();
    static string TO_STRING(vector<int> v);
    static string TO_STRING(unordered_set<int> s);
};

#endif // UTILS_H
