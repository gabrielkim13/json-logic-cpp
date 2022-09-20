#include <execution>
#include <vector>
int main() {
  std::vector<int> v = { 1, 2, 3 };
  int sum = 0;
  std::for_each(std::execution::seq, std::begin(v), std::end(v), [&](int i) {
    sum += i*i;
  });
}

