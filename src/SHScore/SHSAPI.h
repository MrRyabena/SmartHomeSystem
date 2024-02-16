
namespace shs
{
    template <typename T>
    class API;
};

template <typename T>
class shs::API
{
public:
    T *object{};
    API(T *ptr = nullptr, int16_t ID = 0) : object(ptr), m_ID(ID) {}

    void setID(int16_t ID) { m_ID = ID; }
    int16_t getID() { return m_ID; }

    template <typename Tdata>
    virtual void handler(Tdata &data);

protected:
    int16_t m_ID{};
};
