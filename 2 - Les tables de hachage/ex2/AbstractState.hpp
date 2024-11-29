#ifndef ABSTRACTSTATE_HPP
#define ABSTRACTSTATE_HPP

class AbstractState {
public:
    virtual ~AbstractState() = default;
    virtual void action() const = 0; 
};

#endif // ABSTRACTSTATE_HPP
