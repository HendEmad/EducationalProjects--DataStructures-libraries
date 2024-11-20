
template <typename T>
class IDataStructure {
public:
    virtual bool empty() = 0;
    virtual void clear() = 0;
    virtual void display() const = 0;
    virtual void process(const std::function<void(T&)>& func) = 0;
    virtual ~IDataStructure();   
};