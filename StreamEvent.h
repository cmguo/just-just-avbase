// StreamEvent.h

#ifndef _JUST_AVBASE_STREAM_EVENT_H_
#define _JUST_AVBASE_STREAM_EVENT_H_

#include <util/event/Event.h>

namespace just
{
    namespace avbase
    {


        class StreamStatistic;

        class StreamEvent
            : public util::event::Event
        {
        public:
            StreamStatistic const & stat;

            StreamEvent(
                StreamStatistic const & stat)
                : stat(stat)
            {
            }

        private:
            StreamEvent(
                StreamEvent const & stat);

        };

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_DATA_EVENT_H_
