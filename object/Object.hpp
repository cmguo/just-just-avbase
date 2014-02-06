// Object.hpp

#ifndef _PPBOX_AVBASE_OBJECT_OBJECT_HPP_
#define _PPBOX_AVBASE_OBJECT_OBJECT_HPP_

#include "ppbox/avbase/object/Object.h"
#include "ppbox/avbase/object/ObjectTraits.h"

#include <util/serialization/Array.h>

namespace ppbox
{
    namespace avbase
    {

        template <
            typename ObjT
        >
        std::map<typename Object<ObjT>::id_type, ObjectDefine const *> & Object<ObjT>::obj_defs()
        {
            static std::map<typename Object<ObjT>::id_type, ObjectDefine const *> smap;
            return smap;
        }

        template <typename ObjT>
        Object<ObjT>::Object()
            : data_(buf_)
        {
        }

        template <typename ObjT>
        Object<ObjT>::Object(
            id_type id)
            : data_(buf_)
        {
            reset(id);
        }

        template <typename ObjT>
        Object<ObjT>::Object(
            Object const & r)
            : header_type(r)
            , ObjectBase()
            , data_(buf_)
        {
            // default copy constructor will copy member "data_", which is not expected to 
            if (r.ObjectBase::empty()) {
                // copy raw data
                reserve((size_t)header_type::data_size());
                memcpy(data_, r.data_, (size_t)header_type::data_size());
            } else {
                ObjectBase::operator =(r);
            }
        }

        template <typename ObjT>
        template <typename T>
        Object<ObjT>::Object(
            T const & t, 
            typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type *)
            : data_(buf_)
        {
            reset(t);
        }

        template <typename ObjT>
        template <typename T>
        T & Object<ObjT>::get(
            typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type *)
        {
            if (!is<T>()) {
                ObjectBase::reset(&T::obj_def);
                header_type::id(T::static_id);
            }
            return as<T>();
        }

        template <typename ObjT>
        void Object<ObjT>::reset(
            id_type id)
        {
            ObjectBase::reset(find_obj(id));
            header_type::id(id);
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::reset(
            T const & t, 
            typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type *)
        {
            reset();
            header_type::id(T::static_id);
            def_ = &T::obj_def;
            assert(sizeof(T) <= sizeof(data_));
            new (data_) T(t);
        }

        template <typename ObjT>
        template <typename T>
        bool Object<ObjT>::is(
            typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type *) const
        {
            return def_ == &T::obj_def;
        }

        template <typename ObjT>
        template <typename T>
        T const & Object<ObjT>::as(
            typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type *) const
        {
            assert(is<T>());
            return *(T const *)data_;
        }

        template <typename ObjT>
        template <typename T>
        T & Object<ObjT>::as(
            typename boost::enable_if<boost::is_base_of<ObjectDataBase, T> >::type *)
        {
            assert(is<T>());
            return *(T *)data_;
        }

        template <typename ObjT>
        void Object<ObjT>::reset()
        {
            ObjectBase::reset();
            (header_type &)(*this) = header_type();
        }

        template <typename ObjT>
        void Object<ObjT>::load(
            typename ObjT::i_archive_t & ia)
        {
            typename ObjT::helper_t hlp(ia, *this);
            ia >> (header_type &)(*this);
            if (!ia)
                return;
            ObjectBase::reset(find_obj(header_type::id()));
            typename ObjT::data_helper_t hlp2(hlp);
            if (!ia)
                return;
            if (ObjectBase::empty()) {
                reserve((size_t)header_type::data_size());
                ia >> framework::container::make_array(data_, (size_t)header_type::data_size());
                //LOG_DEBUG("[load] unknown box type: " << ctx->path);
            } else {
                ObjectBase::load(&ia);
            }
        }

        template <typename ObjT>
        void Object<ObjT>::save(
            typename ObjT::o_archive_t & oa) const
        {
            typename ObjT::helper_t hlp(oa, *this);
            oa << (header_type const &)(*this);
            if (!oa)
                return;
            typename ObjT::data_helper_t hlp2(hlp);
            if (!oa)
                return;
            if (ObjectBase::empty()) {
                oa << framework::container::make_array(data_, (size_t)header_type::data_size());
            } else {
                ObjectBase::save(&oa);
            }
        }

        template <typename ObjT>
        typename Object<ObjT>::raw_data_t Object<ObjT>::raw_data() const
        {
            return raw_data_t(data_, (size_t)header_type::data_size());
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::reg_obj(
            ObjectDefine & def)
        {
            assert(&def == &T::obj_def);
            def.construct = &s_construct<T>;
            def.copy = &s_copy<T>;
            def.load = &s_load<T>;
            def.save = &s_save<T>;
            def.destroy = &s_destroy<T>;
            obj_defs()[T::static_id] = &def;
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::reg_obj(
            id_type id, 
            ObjectDefine & def)
        {
            assert(&def == &T::obj_def);
            def.construct = &s_construct<T>;
            def.copy = &s_copy<T>;
            def.load = &s_load<T>;
            def.save = &s_save<T>;
            def.destroy = &s_destroy<T>;
            obj_defs()[id] = &def;
        }

        template <typename ObjT>
        void Object<ObjT>::reserve(
            size_t size)
        {
            if (size <= ObjT::max_size) {
                return;
            }
            if (data_ == buf_) {
                data_ = new boost::uint8_t[size];
                data_size_ = size;
            } else if (data_size_ < size) {
                delete [] data_;
                data_ = new boost::uint8_t[size];
                data_size_ = size;
            }
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::s_construct(
            ObjectBase * mb)
        {
            Object * m = static_cast<Object *>(mb);
            m->reserve(sizeof(T));
            new (m->data_) T;
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::s_copy(
            ObjectBase * mb, 
            ObjectBase const * mbr)
        {
            Object * m = static_cast<Object *>(mb);
            Object const * mr = static_cast<Object const *>(mbr);
            m->reserve(sizeof(T));
            new (m->data_) T(mr->as<T>());
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::s_load(
            ObjectBase * mb, 
            void * ar)
        {
            Object * m = static_cast<Object *>(mb);
            typename ObjT::i_archive_t * ia = 
                reinterpret_cast<typename ObjT::i_archive_t *>(ar);
            (*ia) >> m->as<T>();
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::s_save(
            ObjectBase const * mb, 
            void * ar)
        {
            Object const * m = static_cast<Object const *>(mb);
            typename ObjT::o_archive_t * oa = 
                reinterpret_cast<typename ObjT::o_archive_t *>(ar);
            (*oa) << m->as<T>();
        }

        template <typename ObjT>
        template <typename T>
        void Object<ObjT>::s_destroy(
            ObjectBase * mb)
        {
            Object * m = static_cast<Object *>(mb);
            ((T *)m->data_)->~T();
        }

    } // namespace avbase
} // namespace ppbox

#endif // _PPBOX_AVBASE_OBJECT_OBJECT_HPP_
