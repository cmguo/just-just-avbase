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
        class Object;

        template <
            typename ObjT
        >
        class ObjectHelper
        {
        public:
            typedef Object<ObjT> object_type;

            typedef typename ObjT::header_type header_type;

            typedef typename ObjT::i_archive_t i_archive_t;

            typedef typename ObjT::o_archive_t o_archive_t;

            typedef typename object_type::size_type size_type;

        public:
            ObjectHelper(
                i_archive_t & ar, 
                object_type & object)
                : ia_(&ar)
                , oa_(NULL)
                , object_(object)
                , beg_(ar.tellg())
                , data_beg_(0)
                , data_end_(0)
                , end_(0)
            {
            }

            ObjectHelper(
                o_archive_t & ar, 
                object_type const & object)
                : ia_(NULL)
                , oa_(&ar)
                , object_(const_cast<object_type &>(object))
                , beg_(ar.tellp())
                , data_beg_(0)
                , data_end_(0)
                , end_(0)
            {
            }

            ~ObjectHelper()
            {
                end_ = data_end_;
                header_type & header(object_);
                if (ia_) {
                    assert(!*ia_ || object_.is_cls_data() || header.data_size() == data_size());
                } else if (*oa_) {
                    if (header.data_size() != data_size() && object_.is_cls_meta()) {
                        header.data_size(data_size());
                        oa_->seekp(beg_);
                        (*oa_) << header;
                        oa_->seekp(end_);
                    }
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
                if (ia_) {
                    data_beg_ = ia_->tellg();
                    data_end_ = data_beg_ + (std::streamoff)header().data_size();
                    if (object_.is_cls_meta()) {
                        ia_->seekg(data_end_, std::ios::beg);
                        ia_->seekg(data_beg_, std::ios::beg);
                    }
                } else {
                    data_beg_ = oa_->tellp();
                }
            }

            void end_data()
            {
                if (ia_) {
                    data_end_ = ia_->tellg();
                } else {
                    data_end_ = oa_->tellp();
                }
            }

        public:
            object_type & object()
            {
                return object_;
            }

            header_type & header()
            {
                return object_;
            }

            size_type data_size() const
            {
                return (size_type)(data_end_ - data_beg_);
            }

            std::streampos data_end() const
            {
                return data_end_;
            }

        protected:
            i_archive_t * ia_;
            o_archive_t * oa_;
            object_type & object_;
            std::streampos beg_;
            std::streampos data_beg_;
            std::streampos data_end_;
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
