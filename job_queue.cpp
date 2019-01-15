#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
      //cout <<"enter: \n";
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

    
    bool TakeJob(vector<long long> &time, vector<int> &worker, int index1, int index2) {
        return (time[index1] < time[index2] ||
                (time[index1] == time[index2] && worker[index1] < worker[index2]));
    }
    
    int SiftDown(vector<long long> &time, vector<int> &worker, int index){
        int left = (index<<1) + 1;
        int right = (index<<1) + 2;
        
        if (left >= worker.size())
            return 0;
        
        if (right >= worker.size())
        {
            if (TakeJob(time, worker, left, index))
            {
                std::swap(time[left], time[index]);
                std::swap(worker[left], worker[index]);
            }
            
            return 0;
        }
        else
        {
            int min = TakeJob(time, worker, left, right)? left:right;
            
            if (TakeJob(time, worker, min, index)) {
                std::swap(time[min], time[index]);
                std::swap(worker[min], worker[index]);
                return SiftDown(time, worker, min);
            }
            else return 0;
        }
    }
    
    
    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        vector<long long> next_free_time(num_workers_, 0);
        vector<int> workers(num_workers_);
        for (int i = 0; i < num_workers_; i++)
            workers[i] = i;
        
        for (int i = 0; i < jobs_.size(); i++) {
            assigned_workers_[i] = workers[0];
            start_times_[i] = next_free_time[0];
            next_free_time[0] += jobs_[i];
            SiftDown(next_free_time, workers, 0);
        }
    }


 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
