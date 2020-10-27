#ifndef ZOMBIEGAME_TEMPLATES_H
#define ZOMBIEGAME_TEMPLATES_H

template<class BaseType, class SubType>
BaseType* GenericObjectCreationFunction() { return new SubType; }

template<class BaseClass, class IdType>
class GenericObjectFactory
{
    typedef BaseClass *(*ObjectCreationFunction)();

    std::map <IdType, ObjectCreationFunction> m_CreationFunctions;

public:
    template<class SubClass>
    bool Register(IdType id)
    {
        auto findIt = m_CreationFunctions.find(id);
        if(findIt == m_CreationFunctions.end())
        {
            m_CreationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;
            return true;
        }

        return false;
    }

    BaseClass* Create(IdType id)
    {
        auto findIt = m_CreationFunctions.find(id);
        if(findIt != m_CreationFunctions.end())
        {
            ObjectCreationFunction pFunc = findIt->second;
            return pFunc();
        }

        return nullptr;
    }
};

template <class Type>
std::shared_ptr<Type> MakeStrongPtr(std::weak_ptr<Type> pWeakPtr)
{
    if(!pWeakPtr.expired())
        return std::shared_ptr<Type>(pWeakPtr);
    else
        return std::shared_ptr<Type>();
}

#endif //ZOMBIEGAME_TEMPLATES_H
