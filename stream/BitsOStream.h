// BitsOStream.h

#ifndef _JUST_AVBASE_STREAM_BITS_O_STREAM_H_
#define _JUST_AVBASE_STREAM_BITS_O_STREAM_H_

#include "just/avbase/stream/BitsType.h"

#include <util/archive/StreamOArchive.h>

namespace just
{
    namespace avbase
    {

        template <
            typename _Elem = char, 
            typename _Traits = std::char_traits<_Elem>
        >
        class BitsOStream;

    } // namespace avbase
} // namespace just

namespace util
{
    namespace serialization
    {

        template<
            typename _Elem, 
            typename _Traits, 
            size_t n
        >
        struct is_primitive<just::avbase::BitsOStream<_Elem, _Traits>, just::avbase::I<n> >
            : boost::true_type
        {
        };

        template<
            typename _Elem, 
            typename _Traits, 
            size_t n
        >
        struct is_primitive<just::avbase::BitsOStream<_Elem, _Traits>, just::avbase::U<n> >
            : boost::true_type
        {
        };

        template<
            typename _Elem, 
            typename _Traits, 
            typename V
        >
        struct is_primitive<just::avbase::BitsOStream<_Elem, _Traits>, just::avbase::IV<V> >
            : boost::true_type
        {
        };

        template<
            typename _Elem, 
            typename _Traits, 
            typename V
        >
        struct is_primitive<just::avbase::BitsOStream<_Elem, _Traits>, just::avbase::UV<V> >
            : boost::true_type
        {
        };

        template<
            typename _Elem, 
            typename _Traits
        >
        struct is_primitive<just::avbase::BitsOStream<_Elem, _Traits>, just::avbase::SE>
            : boost::true_type
        {
        };

        template<
            typename _Elem, 
            typename _Traits
        >
        struct is_primitive<just::avbase::BitsOStream<_Elem, _Traits>, just::avbase::UE>
            : boost::true_type
        {
        };

        template<
            typename _Elem, 
            typename _Traits
        >
        struct is_primitive<just::avbase::BitsOStream<_Elem, _Traits>, just::avbase::P>
            : boost::true_type
        {
        };

    } // namespace serialization
} // namespace util

namespace just
{
    namespace avbase
    {

        template <
            typename _Elem, 
            typename _Traits
        >
        class BitsOStream
            : public util::archive::StreamOArchive<BitsOStream<_Elem, _Traits>, _Elem, _Traits>
        {
            friend class util::archive::StreamOArchive<BitsOStream<_Elem, _Traits>, _Elem, _Traits>;
        public:
            BitsOStream(
                std::basic_ostream<_Elem, _Traits> & os)
                : util::archive::StreamOArchive<BitsOStream<_Elem, _Traits>, _Elem, _Traits>(*os.rdbuf())
                , this_byte_(0)
                , size_this_byte_(8)
                , mask_this_byte_(0xff)
            {
            }

            BitsOStream(
                std::basic_streambuf<_Elem, _Traits> & buf)
                : util::archive::StreamOArchive<BitsOStream<_Elem, _Traits>, _Elem, _Traits>(buf)
                , this_byte_(0)
                , size_this_byte_(8)
                , mask_this_byte_(0xff)
            {
            }

        public:
            /// 从流中读出变量
            template<class T>
            void save(
                T const & t)
            {
                write_bits_flc(sizeof(T) * 8, t);
            }

            template<size_t N>
            void save(
                just::avbase::I<N> const & i)
            {
                boost::int32_t v = i;
                write_bits_flc(N, v);
            }

            template<size_t N>
            void save(
                just::avbase::U<N> const & u)
            {
                boost::uint32_t v = u;
                write_bits_flc(N, v);
            }

            template<typename V>
            void save(
                just::avbase::IV<V> const & i)
            {
                boost::uint32_t l = i();
                boost::int32_t v = i;
                write_bits_flc(l, v);
            }

            template<typename V>
            void save(
                just::avbase::UV<V> const & u)
            {
                boost::uint32_t l = u();
                boost::uint32_t v = u;
                write_bits_flc(l, v);
            }

            void save(
                just::avbase::SE const & se)
            {
                boost::uint32_t len = 0;
                boost::uint32_t v1 = 0;
                se.format(len, v1);
                write_bits_vlc(len, v1);
            }

            void save(
                just::avbase::UE const & ue)
            {
                boost::uint32_t len = 0;
                boost::uint32_t v1 = 0;
                ue.format(len, v1);
                write_bits_vlc(len, v1);
            }

            void save(
                just::avbase::P const & p)
            {
                if (size_this_byte_ == 0)
                    next_byte();
                p.data(1 << (size_this_byte_ - 1));
                p.size(size_this_byte_);
                this_byte_ |= 1 << (size_this_byte_ - 1);
                size_this_byte_ = 0;
                mask_this_byte_ = 0;
                next_byte();
            }

            using util::archive::StreamOArchive<BitsOStream<_Elem, _Traits>, _Elem, _Traits>::save;

            bool byte_aligned()
            {
                return size_this_byte_ == 8;
            }

        private:
            void write_bits_flc(
                boost::uint32_t l, 
                boost::uint32_t v)
            {
                //std::cout << "write_bits_flc beg: this_byte = " << (size_t)this_byte_ << ", size_this_byte = " << size_this_byte_ << ", l = " << l << ", v = " << v << std::endl;
                if (this->state()) {
                    return;
                }
                while (l >= size_this_byte_) {
                    this_byte_ |= ((v >> (l - size_this_byte_)) & mask_this_byte_);
                    l -= size_this_byte_;
                    next_byte();
                    if (this->state()) {
                        return;
                    }
                }
                if (l) {
                    this_byte_ |= ((v << (size_this_byte_ - l)) & mask_this_byte_);
                    size_this_byte_ -= l;
                    mask_this_byte_ >>= l;
                }
                //std::cout << "write_bits_flc end: this_byte = " << (size_t)this_byte_ << ", size_this_byte = " << size_this_byte_ << std::endl;
            }

            void write_bits_vlc(
                boost::uint32_t l, 
                boost::uint32_t v)
            {
                //std::cout << "write_bits_vlc beg: this_byte = " << (size_t)this_byte_ << ", size_this_byte = " << size_this_byte_ << ", l = " << l << ", v = " << v << std::endl;
                write_bits_flc(l + 1, 1);
                write_bits_flc(l, v);
                //std::cout << "write_bits_vlc end: this_byte = " << (size_t)this_byte_ << ", size_this_byte = " << size_this_byte_ << std::endl;
            }
            
            void next_byte()
            {
                this->save_binary(&this_byte_, 1);
                if (this->state())
                    return;
                //std::cout << "next_byte: this_byte = " << (size_t)this_byte_ << std::endl;
                size_this_byte_ = 8;
                mask_this_byte_ = 0xff;
                this_byte_ = 0;
            }
            
        private:
            _Elem this_byte_;
            boost::uint32_t size_this_byte_;
            boost::uint32_t mask_this_byte_;
        };

    } // namespace avbase
} // namespace just

#endif // _JUST_AVBASE_STREAM_BITS_O_STREAM_H_
