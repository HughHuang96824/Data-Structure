#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using std::string;
using std::vector;
using std::cin;

#define p 10000019
#define m 1000

struct Query {
    string type, name;
    int number;
};


vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}


int Hash(const Query& object, const int& a, const int& b){
    int number = (a * (long long)object.number + b) % p % m;
    return number;
}


void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}


vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    int a = rand() % (p - 1) + 1;
    int b = rand() % p;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<vector<Query>> contacts(m);
    
    for (size_t i = 0; i < queries.size(); ++i) {
        long long index = Hash(queries[i], a, b);
        if (queries[i].type == "add") {
            bool was_founded = false;
            for (size_t j = 0; j < contacts[index].size(); ++j) {
                if (contacts[index][j].number == queries[i].number) {
                    contacts[index][j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            }
            if (!was_founded)
                contacts[index].push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts[index].size(); ++j) {
                if (contacts[index][j].number == queries[i].number) {
                    contacts[index].erase(contacts[index].begin() + j);
                    break;
                }
            }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts[index].size(); ++j)
                if (contacts[index][j].number == queries[i].number) {
                    response = contacts[index][j].name;
                    break;
                }
            result.push_back(response);
        }
    }
    return result;
}



int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
