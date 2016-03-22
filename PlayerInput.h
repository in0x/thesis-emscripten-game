#ifndef PLAYERINPUTS_HPP_INCLUDED
#define PLAYERINPUTS_HPP_INCLUDED

enum class Action
{
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    ShootUp,
    ShootDown,
    ShootLeft,
    ShootRight
};

// Lets us hash the enum class
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif // PLAYERINPUTS_HPP_INCLUDED
