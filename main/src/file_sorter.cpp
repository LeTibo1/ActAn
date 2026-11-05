#include "file_sorter.h"
#include <iostream>
#include <cctype>

static bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

static char lower(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

// Return values:
// 0 = str1 comes before str2
// 1 = str1 comes after str2
// 2 = both are equal (case-insensitive)
int isFile1GreaterFile2(const std::string& str1, const std::string& str2) {
    size_t p1 = 0, p2 = 0;

    while (p1 < str1.size() && p2 < str2.size()) {
        if (isDigit(str1[p1]) && isDigit(str2[p2])) {
            // Find the end of the whole digit sequence in both strings
            size_t s1 = p1, s2 = p2;
            while (p1 < str1.size() && isDigit(str1[p1])) p1++;
            while (p2 < str2.size() && isDigit(str2[p2])) p2++;

            // Skip leading zeros
            while (s1 < p1 && str1[s1] == '0') s1++;
            while (s2 < p2 && str2[s2] == '0') s2++;

            std::string n1 = str1.substr(s1, p1 - s1);
            std::string n2 = str2.substr(s2, p2 - s2);

            // Longer number is larger; with equal length, compare as text
            if (n1.size() != n2.size()) return n1.size() > n2.size();
            if (n1 != n2) return n1 > n2;
            continue;  // Numbers are equal, continue after the digits
        }

        // At least one character is not a digit: compare case-insensitively
        char c1 = lower(str1[p1]);
        char c2 = lower(str2[p2]);
        if (c1 != c2) return c1 > c2;
        p1++;
        p2++;
    }

    // One string is a prefix of the other: the longer one comes after
    if (p1 < str1.size()) return 1;  // str1 has remaining characters
    if (p2 < str2.size()) return 0;  // str2 has remaining characters
    return 2;                        // both fully equal (case-insensitive)
}

void sortFiles(StringList& files) {
	for (auto i = 1; i < files.size(); i++) {
		auto file = files[i];
		for (auto j = i - 1; j >= 0; j--) {
			auto res = isFile1GreaterFile2(file, files[j]);
			if (res == 2) {
				std::cerr << "Error: Two files in the same directory have the same name:\n"
						  << "file1: " << file << "\n"
						  << "file2: " << files[j] << "\n"
          				  << "Make sure file names do not differ only in letter case.\n";
				std::exit(1);
			}
			if (res) {
				break;
			} else {
				files[j + 1] = files[j];
				files[j] = file;
			}
		}
	}
}
