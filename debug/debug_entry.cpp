#include <iostream>

class __DebugEntry__ {
  private:
    const char* mpfile;
    int32_t mline;
    const char* mpfunc;
    int64_t mEnterTime;

  public:
    inline __DebugEntry__(const char* __file, int32_t __line, const char* __func):
    mpfile(__file), mline(__line), mpfunc(__func), mEnterTime(0) {
            std::cout << "TID:" << static_cast<int32_t>(syscall(__NR_gettid)) << " ";
            std::cout << "." <<  strrchr(mpfile, '/') << ":" << mline << ":\tLeave " << mpfunc << std::endl;
    }

    inline void timeDiff(int32_t diffLine) {
    }

    inline ~__DebugEntry__() {
        std::cout << "TID:" << static_cast<int32_t>(syscall(__NR_gettid)) << " ";
        std::cout << "." <<  strrchr(mpfile, '/') << ":" << mline << ":\tLeave " << mpfunc << std::endl;
    }
};

#define LOGENTRY(args...) __DebugEntry__ __debug_entry__(__FILE__, __LINE__, __FUNCTION__);

int main(int argc, char **argv) {
    LOGENTRY();

    return 0;
}