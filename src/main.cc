#include <iostream>
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>

#include <unistd.h>

class NewVersionManager {
 public:
  NewVersionManager(boost::timed_mutex *mutex) : mutex_(mutex) {
    
  }

  void operator()() {
    boost::unique_lock<boost::timed_mutex> lock(*mutex_, boost::defer_lock_t());
    boost::posix_time::time_duration td = boost::posix_time::milliseconds(500);
    do {
      std::cout << "waiting for lock" << std::endl;
    } while (! lock.timed_lock<boost::posix_time::time_duration>(td));

    std::cout << "Finally got the lock" << std::endl;
    lock.unlock();
  }

 private:
  boost::timed_mutex *mutex_;
};

int main(int argc, char **argv) {
    boost::timed_mutex thread_blocker;
    boost::unique_lock<boost::timed_mutex> lock(thread_blocker);
    NewVersionManager nvm(&thread_blocker);
    boost::thread thrd(nvm);

    sleep(5);

    lock.unlock();
    thrd.join();
    return 0;
}
