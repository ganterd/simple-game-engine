#include <sge/time/time.hpp>

SGE::Time::TimePoint SGE::Time::mCurrentSystemTime;
SGE::Time::TimePoint SGE::Time::mLastSystemTime;
SGE::Time::TimePoint SGE::Time::mGameStartTime;

double SGE::Time::mTickDelta;
double SGE::Time::mCurrentGameTime;
