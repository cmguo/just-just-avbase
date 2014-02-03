// Object.h

#ifndef _PPBOX_AVBASE_OBJECT_OBJECT_H_
#define _PPBOX_AVBASE_OBJECT_OBJECT_H_

#include "ppbox/avbase/object/ObjectBase.h"

#include <util/serialization/Serialization.h>
#include <util/serialization/SplitMember.h>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace ppbox
{
    namespace avbase
    {

        struct ObjectDataBase {};

        template <
            typename ObjT
        >
        class Object
            : public ObjectBase
            , public ObjT::header_type
        {
        public:
            typedef typename ObjT::header_type header_type;
            typedef typename header_type::id_type id_type;

        public:
            Object();

            Object(
                Object const & r);

            Object(
                id_type id);

            template <typename T>
            Object(
                T const & t, 
                typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type * = 0);

        public:
            template <typename T>
            T & get(
                typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type * = 0);

            void reset(
                id_type id);

            template <typename T>
            void reset(
                T const & t, 
                typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type * = 0);

            template <typename T>
            bool is(
                typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type * = 0) const;

            template <typename T>
            T const & as(
                typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type * = 0) const;

            template <typename T>
            T & as(
                typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type * = 0);

            void reset();

        public:
            SERIALIZATION_SPLIT_MEMBER();

            void load(
                typename ObjT::i_archive_t & ia);

            void save(
                typename ObjT::o_archive_t & oa) const;

            typedef framework::container::Array<boost::uint8_t const> raw_data_t;

            raw_data_t raw_data() const;

        public:
            template <typename T>
            static void reg_obj(
                ObjectDefine & def);

            template <typename T>
            static void reg_obj(
                id_type id, 
                ObjectDefine & def);

            static ObjectDefine const * find_obj(
                id_type id)
            {
                return obj_defs()[id];
            }

        private:
            void reserve(
                size_t size);

        private:
            template <typename T>
            static void s_construct(
                ObjectBase *);

            template <typename T>
            static void s_copy(
                ObjectBase *, 
                ObjectBase const *);

            template <typename T>
            static void s_load(
                ObjectBase *, 
                void *);

            template <typename T>
            static void s_save(
                ObjectBase const *, 
                void *);

            template <typename T>
            static void s_destroy(
                ObjectBase *);

        private:
            static std::map<id_type, ObjectDefine const *> & obj_defs();

        private:
            union {
                size_t data_size_;
                boost::uint64_t _u64;
                boost::uint8_t buf_[ObjT::max_size];
            };
            boost::uint8_t * data_;
        };

        template <
            typename ObjT, 
            typename T
        >
        struct ObjectDefineT
            : ObjectDefine
        {
            ObjectDefineT(
                ClassEnum cls = T::static_cls)
                : ObjectDefine(cls)
            {
                Object<ObjT>::template reg_obj<T>(*this);
            }
        };

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_OBJECT_OBJECT_H_
