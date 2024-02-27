#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

namespace TKS
{
    template <typename T>
    class SmartPointer
    {
    private:
        T *m_ptr;

    public:
        SmartPointer(T *ptr = nullptr) : m_ptr(ptr) {}
        ~SmartPointer() { delete m_ptr; }

        // Copy constructor
        SmartPointer(SmartPointer &a)
        {
            m_ptr = a.m_ptr;
            a.m_ptr = nullptr;
        }

        // Assignment operator
        SmartPointer &operator=(SmartPointer &a)
        {
            if (&a == this)
                return *this;

            delete m_ptr;
            m_ptr = a.m_ptr;
            a.m_ptr = nullptr;
            return *this;
        }

        T &operator*() const { return *m_ptr; }
        T *operator->() const { return m_ptr; }

        bool isNull() const { return m_ptr == nullptr; }
    };
}

#endif
