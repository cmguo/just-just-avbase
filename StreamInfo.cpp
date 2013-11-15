// StreamInfo.cpp

#include "ppbox/avbase/Common.h"
#include "ppbox/avbase/StreamInfo.h"
#include "ppbox/avbase/StreamType.h"

namespace ppbox
{
    namespace avbase
    {

        StreamInfoBase::StreamInfoBase()
            : type(StreamType::NONE)
            , sub_type(0)
            , time_scale(0)
            , bitrate(0)
            , start_time(0)
            , duration(0)
        {
        }

        static boost::uint32_t common_divisor(
            boost::uint32_t scale_in, 
            boost::uint32_t scale_out)
        {
            if (scale_in == 0 || scale_out == 0)
                return 1;
            while (scale_in != scale_out) {
                if (scale_in > scale_out) {
                    scale_in -= scale_in / scale_out * scale_out;
                    if (scale_in == 0)
                        return scale_out;
                } else {
                    scale_out -= scale_out / scale_in * scale_in;
                    if (scale_out == 0)
                        return scale_in;
                }
            }
            return scale_in;
        }

        void VideoInfo::frame_rate(
            boost::uint32_t n, 
            boost::uint32_t d)
        {
            boost::uint32_t c = common_divisor(n, d);
            frame_rate_num = n / c;
            frame_rate_den = d / c;
        }

        StreamInfo::StreamInfo()
            : format_type(0)
            , context(NULL)
        {
            memset(&video_format, 0, sizeof(audio_format));
        }

    } // namespace avbase
} // namespace ppbox
