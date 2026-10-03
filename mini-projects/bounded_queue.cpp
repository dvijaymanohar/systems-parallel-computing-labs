// Build: g++ -O2 -std=c++20 -pthread mini-projects/bounded_queue.cpp -o bounded_queue
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

class BoundedQueue{
    std::deque<int>q; std::size_t cap; bool done=false;
    std::mutex m; std::condition_variable not_empty,not_full;
public:
    explicit BoundedQueue(std::size_t c):cap(c){}
    void push(int v){std::unique_lock lk(m);not_full.wait(lk,[&]{return q.size()<cap;});q.push_back(v);not_empty.notify_one();}
    bool pop(int&v){std::unique_lock lk(m);not_empty.wait(lk,[&]{return done||!q.empty();});if(q.empty())return false;v=q.front();q.pop_front();not_full.notify_one();return true;}
    void close(){std::lock_guard lk(m);done=true;not_empty.notify_all();}
};
int main(){
    BoundedQueue q(64); long long sum=0; std::mutex sm;
    std::thread producer([&]{for(int i=1;i<=100000;++i)q.push(i);q.close();});
    std::vector<std::thread> workers;
    for(int t=0;t<4;++t)workers.emplace_back([&]{int v;long long local=0;while(q.pop(v))local+=v;std::lock_guard g(sm);sum+=local;});
    producer.join(); for(auto&w:workers)w.join();
    long long expected=100000ll*100001/2;
    std::cout<<"sum="<<sum<<" expected="<<expected<<"\n";
    return sum==expected?0:2;
}
