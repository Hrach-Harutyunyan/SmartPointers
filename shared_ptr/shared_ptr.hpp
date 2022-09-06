#ifndef __SHARED__PTR__HPP__
#define __SHARED__PTR__HPP__

template <typename T>
class Shared_ptr
{
public:
    explicit Shared_ptr(T* ptr = nullptr);
    Shared_ptr(const Shared_ptr<T>&);
    ~Shared_ptr();

public:
    std::size_t use_count() const { return m_counter->get(); }
    T* get() const { return _m_ptr; }
    T& operator*() const { return *_m_ptr; }
    T* operator->() const { return _m_ptr; }

    void swap(Shared_ptr& s) {
        using std::swap;
        swap(this->_m_ptr, s._m_ptr);
        swap(this->m_counter, s.m_counter);
    }
    void reset() {
        if(this->m_counter->get() == 1) {
            delete this->_m_ptr;
        }
        this->_m_ptr = nullptr;
        this->m_counter->set(0); 
    }
    
public:
    friend std::ostream& operator <<(std::ostream& os, const Shared_ptr<T>& sh_ptr) {
            os << "Address pointed : " << sh_ptr.get() << std::endl;
            os << *(sh_ptr.m_counter) << std::endl;
        return os;
    }

private:
    class Counter
    {
    public:
        Counter () : _m_counter{} { }
        ~Counter () { }

    public:
        void reset() { _m_counter = 0; }
        std::size_t get() const { return _m_counter; }
        void set(std::size_t n) { _m_counter = n; }
        void operator++() { _m_counter++; }
        void operator--() { _m_counter--; }
        void operator++(int) { _m_counter++; }
        void operator--(int) { _m_counter--; }
        friend std::ostream& operator<<(std::ostream& os, const Counter& counter) {
            os << "Counter Value : " << counter._m_counter << std::endl;
            return os;
        }

    private:
        Counter (const Counter&) = delete;
        Counter& operator = (const Counter&) = delete;

    private:
        std::size_t _m_counter;
    };

private:
    T* _m_ptr;
    Counter* m_counter;
};

template <typename T>
Shared_ptr<T>::Shared_ptr(T* capture_ptr) : _m_ptr{capture_ptr}, m_counter{new Counter()} {
    if (capture_ptr) {
        (*m_counter)++;
    }
}

template <typename T>
Shared_ptr<T>::Shared_ptr(const Shared_ptr<T>& other) : _m_ptr{other._m_ptr}, m_counter {other.m_counter} {
    (*m_counter)++;
}

template <typename T>
Shared_ptr<T>::~Shared_ptr() {
    (*m_counter)--;
    if (m_counter->get() == 0) {
        delete m_counter;
        delete _m_ptr;
    }
}

#endif