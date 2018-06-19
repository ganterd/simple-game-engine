#ifndef SGE_TIME
#define SGE_TIME

#include <chrono>

namespace SGE
{
    class Time
    {
    friend class Scene;
    public:
        typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
        static double getDelta(){ return mTickDelta; };

    private:

        static TimePoint mCurrentSystemTime;
        static TimePoint mLastSystemTime;
        static TimePoint mGameStartTime;

        static double mCurrentGameTime;
        static double mTickDelta;

        static TimePoint now()
        {
            return std::chrono::system_clock::now();
        }

        static double duration(TimePoint from, TimePoint to)
        {
            return std::chrono::duration<double>(to - from).count();
        }

        static void init()
        {
            mGameStartTime = now();
            mLastSystemTime = mGameStartTime;
            mCurrentSystemTime = mGameStartTime;
            mCurrentGameTime = 0.0;
            mTickDelta = 0.0;
        }

        static void tick()
        {
            mCurrentSystemTime = now();
            mCurrentGameTime = duration(mGameStartTime, mCurrentSystemTime);
            mTickDelta = duration(mLastSystemTime, mCurrentSystemTime);
            mLastSystemTime = mCurrentSystemTime;
        }
    };
}

#endif /* end of include guard: SGE_TIME */
