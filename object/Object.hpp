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
            : ObjectBase()
            , header_type(r)
            , data_(buf_)
        {
            // default copy constructor will copy member "data_", which is not expected to 
            ObjectBase::operator =(r);
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
            std::streampos data_beg = ia.tellg();
            std::streampos data_end = 
                data_beg + (std::streamoff)header_type::data_size();
            typename ObjT::data_helper_t hlp2(hlp);
            ObjectDefine const * def = find_obj(header_type::id());
            if (def) {
                if (def->cls != ObjectDefine::cls_data) {
                    ia.seekg(data_end, std::ios::beg);
                    if (!ia)
                        return;
                    ia.seekg(data_beg, std::ios::beg);
                }
                ObjectBase::reset(def);
                ObjectBase::load(&ia);
                assert(!ia || def->cls == ObjectDefine::cls_data || ia.tellg() == data_end);
            } else {
                reserve((size_t)header_type::data_size());
                ia >> framework::container::make_array(data_, (size_t)header_type::data_size());
                //LOG_DEBUG("[load] unknown box type: " << ctx->path);
            }
        }

        template <typename ObjT>
        void Object<ObjT>::save(
            typename ObjT::o_archive_t & oa) const
        {
            typename ObjT::helper_t hlp(oa, *this);
            oa << (header_type const &)(*this);
            typename ObjT::data_helper_t hlp2(hlp);
            ObjectBase::save(&oa);
        }

        template <typename ObjT>
        typename Object<ObjT>::raw_data_t Object<ObjT>::raw_data() const
        {
            return raw_data_t(data_, data_ == buf_ ? sizeof(buf_) : data_size_);
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
