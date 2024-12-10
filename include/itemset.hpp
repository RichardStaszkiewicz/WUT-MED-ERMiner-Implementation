#ifndef ITEMSET
#define ITEMSET

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <stdexcept>

class Itemset : public std::set<int> {
private:
    // Map to store occurrences: key = sequence ID, value = pair(first, last)
    std::map<int, std::pair<int, int>> occurrences;

public:
    // Constructor
    Itemset(const std::vector<int>& elements, const std::map<int, std::pair<int, int>>& initOccurrences = {})
        : std::set<int>(elements.begin(), elements.end()), occurrences(initOccurrences) {}

    // Custom hash function
    std::size_t hash() const {
        std::vector<int> sorted_elements(this->begin(), this->end());
        std::sort(sorted_elements.begin(), sorted_elements.end());
        std::size_t h = 0;
        for (int elem : sorted_elements) {
            h ^= std::hash<int>()(elem) + 0x9e3779b9 + (h << 6) + (h >> 2); // Standard hash combine
        }
        return h;
    }

    // Compute occurrences for the entire itemset
    void computeOccurrences(const std::vector<std::vector<int>>& sdb);

    // Update occurrences with an additional item
    std::map<int, std::pair<int, int>> updateOccurrences(int item, const std::vector<std::vector<int>>& sdb);

    // Print occurrences (for debugging)
    void printOccurrences() const {
        for (const auto& [sid, range] : occurrences) {
            std::cout << "Sequence " << sid << ": [" << range.first << ", " << range.second << "]\n";
        }
    }

    std::map<int, std::pair<int, int>> getOccurrences();

};

#endif
