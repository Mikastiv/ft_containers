template <class _NodePtr>
void
__tree_balance_after_insert(_NodePtr __root, _NodePtr __x) _NOEXCEPT
{
    __x->__is_black_ = __x == __root;
    while (__x != __root && !__x->__parent_unsafe()->__is_black_)
    {
        // __x->__parent_ != __root because __x->__parent_->__is_black == false
        if (_VSTD::__tree_is_left_child(__x->__parent_unsafe()))
        {
            _NodePtr __y = __x->__parent_unsafe()->__parent_unsafe()->__right_;
            if (__y != nullptr && !__y->__is_black_)
            {
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = __x == __root;
                __y->__is_black_ = true;
            }
            else
            {
                if (!_VSTD::__tree_is_left_child(__x))
                {
                    __x = __x->__parent_unsafe();
                    _VSTD::__tree_left_rotate(__x);
                }
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = false;
                _VSTD::__tree_right_rotate(__x);
                break;
            }
        }
        else
        {
            _NodePtr __y = __x->__parent_unsafe()->__parent_->__left_;
            if (__y != nullptr && !__y->__is_black_)
            {
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = __x == __root;
                __y->__is_black_ = true;
            }
            else
            {
                if (_VSTD::__tree_is_left_child(__x))
                {
                    __x = __x->__parent_unsafe();
                    _VSTD::__tree_right_rotate(__x);
                }
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = false;
                _VSTD::__tree_left_rotate(__x);
                break;
            }
        }
    }
}

template <class _NodePtr>
void
__tree_left_rotate(_NodePtr __x) _NOEXCEPT
{
    _NodePtr __y = __x->__right_;
    __x->__right_ = __y->__left_;
    if (__x->__right_ != nullptr)
        __x->__right_->__set_parent(__x);
    __y->__parent_ = __x->__parent_;
    if (_VSTD::__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_unsafe()->__right_ = __y;
    __y->__left_ = __x;
    __x->__set_parent(__y);
}

// Effects:  Makes __x->__left_ the subtree root with __x as its right child
//           while preserving in-order order.
// Precondition:  __x->__left_ != nullptr
template <class _NodePtr>
void
__tree_right_rotate(_NodePtr __x) _NOEXCEPT
{
    _NodePtr __y = __x->__left_;
    __x->__left_ = __y->__right_;
    if (__x->__left_ != nullptr)
        __x->__left_->__set_parent(__x);
    __y->__parent_ = __x->__parent_;
    if (_VSTD::__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_unsafe()->__right_ = __y;
    __y->__right_ = __x;
    __x->__set_parent(__y);
}
