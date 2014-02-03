// ObjectHelper.h

#ifndef _PPBOX_AVBASE_OBJECT_OBJECT_HELPER_H_
#define _PPBOX_AVBASE_OBJECT_OBJECT_HELPER_H_

namespace ppbox
{
    namespace avbase
    {

        template <
            typename ObjT
        >
        class ObjectHelper
        {
        public:
            typedef typename ObjT::header_type header_type;

            typedef typename ObjT::i_archive_t i_archive_t;

            typedef typename ObjT::o_archive_t o_archive_t;

            typedef typename header_type::size_type size_type;

        public:
            ObjectHelper(
                i_archive_t & ar, 
                header_type & header)
                : ia_(&ar)
                , oa_(NULL)
                , header_(header)
                , beg_(ar.tellg())
                , data_beg_(0)
                , end_(0)
            {
            }

            ObjectHelper(
                o_archive_t & ar, 
                header_type const & header)
                : ia_(NULL)
                , oa_(&ar)
                , header_(const_cast<header_type &>(header))
                , beg_(ar.tellp())
                , data_beg_(0)
                , end_(0)
            {
            }

            ~ObjectHelper()
            {
                if (ia_) {
                    assert(!*ia_ || header_.data_size() == data_size());
                } else if (*oa_) {
                    header_.data_size(data_size());
                    std::streampos end = oa_->tellp();
                    oa_->seekp(beg_);
                    (*oa_) << header_;
                    oa_->seekp(end);
                }
            }

        public:
            void * context()
            {
                if (ia_)
                    return ia_->context();
                else
                    return oa_->context();
            }

        public:
            void begin_data()
            {
                if (ia_)
                    data_beg_ = ia_->tellg();
                else
                    data_beg_ = oa_->tellp();
            }

            void end_data()
            {
                if (ia_) {
                    end_ = ia_->tellg();
                } else {
                    end_ = oa_->tellp();
                }
            }

        public:
            header_type & header()
            {
                return header_;
            }

            size_type data_size() const
            {
                return (size_type)(end_ - data_beg_);
            }

            std::streampos data_end() const
            {
                return data_beg_ + (std::streamoff)header_.data_size();
            }

        protected:
            i_archive_t * ia_;
            o_archive_t * oa_;
            header_type & header_;
            std::streampos beg_;
            std::streampos data_beg_;
            std::streampos end_;
        };

        template <
            typename ObjT
        >
        class ObjectDataHelper
        {
        public:
            ObjectDataHelper(
                ObjectHelper<ObjT> & h)
                : h_(h)
            {
                h_.begin_data();
            }

            ~ObjectDataHelper()
            {
                h_.end_data();
            }

        private:
            ObjectHelper<ObjT> & h_;
        };

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_OBJECT_OBJECT_HELPER_H_
