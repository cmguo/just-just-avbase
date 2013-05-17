// StreamInfo.h

#ifndef _PPBOX_AVBASE_STREAM_INFO_H_
#define _PPBOX_AVBASE_STREAM_INFO_H_

namespace ppbox
{
    namespace avbase
    {

        struct VideoInfo
        {
            boost::uint32_t width;
            boost::uint32_t height;
            boost::uint32_t frame_rate;
        };

        struct AudioInfo
        {
            boost::uint32_t channel_count;
            boost::uint32_t sample_size;
            boost::uint32_t sample_rate;
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
            void const * context;
        };

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_STREAM_INFO_H_
