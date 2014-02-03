// ObjectBase.cpp

#include "ppbox/avbase/Common.h"
#include "ppbox/avbase/object/ObjectBase.h"

namespace ppbox
{
    namespace avbase
    {

        ObjectBase::ObjectBase()
            : def_(NULL)
        {
        }

        ObjectBase::~ObjectBase()
        {
            reset();
        }

        ObjectBase::ObjectBase(
            ObjectBase const & r)
            : def_(r.def_)
        {
            if (def_) {
                def_->copy(this, &r);
            }
        }

        ObjectBase & ObjectBase::operator=(
            ObjectBase const & r)
        {
            reset();
            def_ = r.def_;
            if (def_) {
                def_->copy(this, &r);
            }
            return *this;
        }

        void ObjectBase::load(
            void * ar)
        {
            def_->load(this, ar);
        }

        void ObjectBase::save(
            void * ar) const
        {
            def_->save(this, ar);
        }

        void ObjectBase::reset()
        {
            if (!empty()) {
                def_->destroy(this);
                def_ = NULL;
            }
        }

        void ObjectBase::reset(
            ObjectDefine const * def)
        {
            if (!empty()) {
                def_->destroy(this);
            }
            def->construct(this);
            def_ = def;
        }

        bool ObjectBase::empty() const
        {
            return def_ == NULL;
        }

    } // namespace avbase
} // namespace ppbox
