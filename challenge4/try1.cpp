#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <thread>
#include <vector>

using std::map;
using std::pair;
using std::set;
using std::vector;

using std::thread;

using std::cin;
using std::cout;
using std::endl;

class SharedPrinter {
  vector<std::atomic<int32_t>> progress;
  map<int32_t, std::vector<int32_t>> M;

  int32_t curr;
  int32_t print_period;
  int32_t next_notif;

  int32_t get_prog(int32_t index) const {
    int32_t value = progress[index];
    return value;
  }

public:
  SharedPrinter(int32_t thread_num, int32_t print_period = 1)
      : progress(thread_num), curr(0), print_period(print_period),
        next_notif(print_period) {
    for (int32_t i = 0; i < thread_num; ++i) {
      M[0].push_back(i);
    }
  }

  void run() {
    while (curr != INT32_MAX) {
      int32_t curr_min = M.cbegin()->first;
      if (curr_min > curr) {
        curr = curr_min;
        if (curr >= next_notif) {
          if (curr > INT32_MAX - print_period)
            next_notif = INT32_MAX;
          else {
            next_notif = curr + print_period;
          }
          cout << "All threads reached progress " << curr << endl;
        }
      }

      std::vector<int32_t> &helper = M.begin()->second;
      for (size_t i = 0; i < helper.size();) {
        int value = get_prog(helper[i]);
        if (value != curr) {
          // cout << "Thread " << helper[i] << " progress is now " << value <<
          // endl;
          M[value].push_back(helper[i]);
          if (i + 1 != helper.size()) {
            std::swap(helper[i], helper.back());
          }
          helper.pop_back();
          continue;
        }
        ++i;
      }
      if (helper.empty()) {
        M.erase(curr);
      }
    }
    cout << "All threads finished!" << endl;
  }

  void notify(int32_t thread, int32_t prog) { progress[thread] = prog; }
  void finish(int32_t thread) { progress[thread] = INT32_MAX; }
};

const int32_t number_of_threads = 4;
SharedPrinter sp(number_of_threads);

void f(int32_t thread_id) {

  for (int32_t i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    sp.notify(thread_id, i * i);
  }
  sp.finish(thread_id);
}

int main() {

  vector<thread> threads;
  for (int32_t i = 0; i < number_of_threads; ++i)
    threads.push_back(std::thread(f, i));
  sp.run();
  for (auto &th : threads)
    th.join();
  return 0;
}
