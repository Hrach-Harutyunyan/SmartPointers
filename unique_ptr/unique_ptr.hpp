#ifndef __UNIQUE__PTR__HPP__
#define __UNIQUE__PTR__HPP__


template <class T>
class unique_ptr
{
public:
    unique_ptr();
    ~unique_ptr();
    explicit unique_ptr(T*);
    unique_ptr(unique_ptr &&) noexcept;

public:
    T& operator *() const;
    T* operator ->() const;
    explicit operator bool() const;
    unique_ptr& operator =(unique_ptr&&) noexcept;

public:
    T* get();
    void reset();
    void release();
    void swap(unique_ptr&) noexcept;

private:
    unique_ptr(const unique_ptr &) = delete;
    unique_ptr & operator =(const unique_ptr &) = delete;

private:
    T* ptr;
};

template <class T>
unique_ptr<T>::unique_ptr() : ptr(nullptr) {};


template <class T>
unique_ptr<T>::unique_ptr(T* pointer) : ptr(pointer) {
    pointer = nullptr;
} ;

template <class T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& rhs) noexcept : ptr(nullptr) {
    rhs.swap(*this);
};

template <class T>
unique_ptr<T>& unique_ptr<T>::operator = (unique_ptr<T>&& rhs) noexcept {
    this->swap(rhs);
    delete rhs.ptr;
    rhs.ptr = nullptr;
    return *this;
};

template <class T>
unique_ptr<T>::~unique_ptr() {
    if(!ptr){
        delete ptr;
    }
};

template <class T>
T& unique_ptr<T>::operator *() const {
    return *ptr;
};

template <class T>
T* unique_ptr<T>::operator ->() const {
    return ptr;
};

template <class T>
unique_ptr<T>::operator bool()  const  {
    return (ptr == nullptr? false:true);
};


template <class T>
void unique_ptr<T>::swap(unique_ptr<T>& other) noexcept {
    std::swap(ptr, other.ptr);
}

template <class T>
T* unique_ptr<T>::get() {
    return ptr;
}

template <class T>
void unique_ptr<T>::reset() {
    delete this->ptr;
    this->ptr = nullptr;
}

template <class T>
void unique_ptr<T>::release() {
    this->ptr = nullptr;
}

#endif