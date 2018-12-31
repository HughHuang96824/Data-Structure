#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();

      long loop = data_.size() / 2 - 1;
    for (long i = loop; i >= 0; i--)
    {
        long j = i;
        long child1 = 2*j+1;
        long child2 = 2*j+2;
        while (child1 < data_.size())
        {
            if (child2 < data_.size())
            {
                long min = data_[child1] < data_[child2]? child1:child2;
                if (data_[min] < data_[j])
                {
                    swap(data_[min], data_[j]);
                    swaps_.push_back(make_pair(min, j));
                    j = min; child1 = 2*j+1; child2 = 2*j+2;
                }
                else break;
            }
            else if (data_[child1] < data_[j])
            {
                swap(data_[child1], data_[j]);
                swaps_.push_back(make_pair(child1, j));
                j = child1; child1 = 2*j+1; child2 = 2*j+2;
            }
            else break;
        }
    }

  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
