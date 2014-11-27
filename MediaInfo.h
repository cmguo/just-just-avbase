// MediaInfo.h

#ifndef _JUST_AVBASE_MEDIA_INFO_H_
#define _JUST_AVBASE_MEDIA_INFO_H_

namespace just 
{
    namespace avformat
    {
        class Format;
    }

    namespace avbase 
    {

        static boost::uint64_t const invalid_size = boost::uint64_t(-1);

        struct MediaBasicInfo
        {
            MediaBasicInfo()
                : type(vod)
                , flags(0)
            {
            }

            enum TypeEnum
            {
                vod, 
                live, 
            };

            enum FlagEnum
            {
                f_seekable      = 1, 
                f_pauseable     = 2, 
                f_is_live       = 4, 

                f_extend        = 0xf00, 
                f_segment       = 0x100, 
                f_packet        = 0x200, 
            };

            TypeEnum type;
            boost::uint32_t flags;
            std::string format_type;
        };

        struct MediaInfo
            : MediaBasicInfo
        {
            MediaInfo()
                : file_size(invalid_size)
                , duration(invalid_size)
                , head_size(0)
                , bitrate(0)
                , start_time(0)
                , delay(0)
                , current(0)
                , shift(0)
                , format(NULL)
            {
            }

            boost::uint64_t file_size;
            boost::uint64_t duration;
            boost::uint32_t head_size;  // ͷ����С���������жϴ򿪳ɹ���Ҫ��������
            boost::uint32_t bitrate;    // ƽ��������

            // live only
            time_t start_time;          // ��ʱ����˵�ʱ���
            boost::uint32_t delay;      // �����Ӻ󳤶ȣ������current
            boost::uint64_t current;    // ��ǰʱ�̣������������Ч�������������ֳ���Ҫ����delay����
            boost::uint64_t shift;      // �ܹ�ʱ�Ƶĳ��ȣ������current

            // description
            std::string name;
            std::string format_data;
            just::avformat::Format * format;
        }; 

    } // namespace avbase
} // namespace just

#endif//_JUST_AVBASE_MEDIA_INFO_H_
