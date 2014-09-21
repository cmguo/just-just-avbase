// StreamInfo.h

#ifndef _PPBOX_AVBASE_STREAM_INFO_H_
#define _PPBOX_AVBASE_STREAM_INFO_H_

namespace ppbox
{
    namespace avcodec
    {
        class Codec;
    }

    namespace avbase
    {

        struct VideoInfo
        {
            boost::uint32_t width;
            boost::uint32_t height;
            boost::uint32_t frame_rate_num;
            boost::uint32_t frame_rate_den;

            boost::uint32_t frame_rate() const
            {
                return frame_rate_den == 0 ? 0 : frame_rate_num / frame_rate_den;
            }

            void frame_rate(
                boost::uint32_t f)
            {
                frame_rate_num = f;
                frame_rate_den = 1;
            }

            void frame_rate(
                boost::uint32_t n, 
                boost::uint32_t d);
        };

        struct AudioInfo
        {
            boost::uint32_t channel_count;
            boost::uint32_t sample_size;
            boost::uint32_t sample_rate;
            boost::uint32_t block_align;
            boost::uint32_t sample_per_frame;
        };

        struct StreamInfoBase
        {
            StreamInfoBase();

            union {
                boost::uint32_t type;
                char type_char[4];
            };
            union {
                boost::uint32_t sub_type;
                char sub_type_char[4];
            };
            boost::uint32_t index;
            boost::uint32_t time_scale;
            boost::uint32_t bitrate;
            boost::uint64_t start_time;
            boost::uint64_t duration;
        };

        struct StreamInfo
            : StreamInfoBase
        {
            StreamInfo();

            boost::uint32_t format_type;             // 格式说明的类型
            union {
                VideoInfo video_format;
                AudioInfo audio_format;
            };
            std::vector<boost::uint8_t> format_data; // 格式说明的内容
            ppbox::avcodec::Codec * codec;
            void const * context;
        };

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_STREAM_INFO_H_
