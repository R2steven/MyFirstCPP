
#include <string>
#include <iostream>



    int lengthOfLongestSubstring(std::string s) {
        std::string seen = "";
        int length = 0;
        int sublength = 0;
        
        for (auto itr = s.begin(); itr < s.end(); itr++) {
            int index = seen.find(*itr);
            if(index != -1) {
                sublength -= index;
                seen.erase(0,index + 1);
                seen+=*itr;
            }
            else {
                seen+=*itr;
                sublength++;
            }
            length = std::max(length,sublength);
        }
        return length;
    }

    int main() {
        std::string s = "pwwkew";
        std::cout << lengthOfLongestSubstring(s);
    }
