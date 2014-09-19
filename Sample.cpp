// Sample.cpp

#include "ppbox/avbase/Common.h"
#include "ppbox/avbase/Sample.h"

#include <ppbox/data/base/MemoryLock.h>

namespace ppbox
{
    namespace avbase
    {

        Sample::Sample()
            : itrack(0)
            , flags(0)
            , time(0)
            , dts(0)
            , cts_delta(0)
            , duration(0)
            , size(0)
            , stream_info(NULL)
            , memory(NULL)
            , context(NULL)
        {
        }

        Sample::Sample(
            Sample const & s)
            : itrack(s.itrack)
            , flags(s.flags)
            , time(s.time)
            , dts(s.dts)
            , cts_delta(s.cts_delta)
            , duration(s.duration)
            , size(s.size)
            , stream_info(s.stream_info)
            , memory(s.memory)
            , context(s.context)
        {
            data.swap(const_cast<Sample &>(s).data);
            const_cast<Sample &>(s).memory = NULL;
        }

        Sample & Sample::operator=(
            Sample const & s)
        {
            assert(memory == NULL);

            itrack = s.itrack;
            flags = s.flags;
            time = s.time;
            dts = s.dts;
            cts_delta = s.cts_delta;
            duration = s.duration;
            size = s.size;
            stream_info = s.stream_info;
            memory = s.memory;
            context = s.context;
            data.swap(const_cast<Sample &>(s).data);

            const_cast<Sample &>(s).memory = NULL;

            return *this;
        }

        void Sample::append(
            Sample & s)
        {
            append(s.memory);
            s.memory = NULL;
        }

        void Sample::append(
            MemoryLock * mem)
        {
            if (memory == NULL) {
                memory = mem;
            } else if (mem) {
                mem->unlink();
                memory->join.insert(mem);
            }
        }

    } // namespace avbase
} // namespace ppbox
