#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

long long PolyHash(const string& subtext, const long long& x, const long long& p) {
    long long sum = 0;
    for (int i = 0; i < subtext.length(); i++)
        sum += ((char)subtext[i] * (long long)pow(x, i)) % p;
    //std::cout << sum << std::endl;
    return (sum % p + p) % p;
}


std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    size_t hash_len = t.length() - s.length() + 1;
    std::vector<int> occurrences;
    std::vector<long long> hash(hash_len);
    int p = 100097;
    int x = 1;

    long long pattern_hash = PolyHash(input.pattern, x, p);
    hash[hash.size()-1] = PolyHash(t.substr(hash_len - 1, s.length()), x, p);
    
    long long y = 1;
    for (int i = 1; i <= s.length(); i++)
        y = (y * x) % p;
    
    for (long i = hash_len - 2; i >=0; i--)
        hash[i] = (((x * hash[i + 1]) % p + t[i] % p - (y * t[i + s.length()]) % p) % p + p) % p;

    for (int i = 0; i < hash.size(); i++) {
        if (hash[i] == pattern_hash){
            if (s == t.substr(i, s.length()))
                occurrences.push_back(i);
        }
    }
    return occurrences;
}



int main() {
    //std::cout << "enter: \n";
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
