// Sample.h

#ifndef _PPBOX_AVBASE_SAMPLE_H_
#define _PPBOX_AVBASE_SAMPLE_H_

#include <boost/asio/buffer.hpp>

namespace ppbox
{
    namespace data
    {
        struct MemoryLock;
    }

    namespace avbase
    {

        using ppbox::data::MemoryLock;

        struct StreamInfo;

        struct Sample
        {
            enum FlagEnum
            {
                 f_sync = 1, 
                 f_discontinuity = 2,
                 f_config = 4, 
                 f_multiple = 0x10,
                 f_fragment = 0x20, 
                 f_frag_end = 0x40, 
                 f_frag_lost = 0x80, 
            };

            Sample();

            Sample(
                Sample const & s);

            Sample & operator=(
                Sample const & s);

            void append(
                Sample & s);

            void append(
                MemoryLock * mem);

            boost::uint32_t itrack;
            boost::uint32_t flags;
            boost::uint64_t time;
            boost::uint64_t dts;
            boost::uint32_t cts_delta;
            boost::uint32_t duration;
            boost::uint32_t size;
            StreamInfo const * stream_info;
            MemoryLock * memory; // 内存锁
            void const * context; // 处理上下文
            std::deque<boost::asio::const_buffer> data;
        };

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_SAMPLE_H_
