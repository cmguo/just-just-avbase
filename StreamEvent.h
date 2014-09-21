// StreamEvent.h

#ifndef _PPBOX_AVBASE_STREAM_EVENT_H_
#define _PPBOX_AVBASE_STREAM_EVENT_H_

#include <util/event/Event.h>

namespace ppbox
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
} // namespace ppbox

#endif // _PPBOX_AVBASE_DATA_EVENT_H_
