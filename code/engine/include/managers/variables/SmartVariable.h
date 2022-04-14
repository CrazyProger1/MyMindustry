//
// Created by crazy on 14.04.2022.
//

#ifndef MYMINDUSTRY_SMARTVARIABLE_H
#define MYMINDUSTRY_SMARTVARIABLE_H

#include <memory>
#include "../../types.h"

namespace engine {
    struct SmartVariable {
    private:
    public:
        [[nodiscard]] virtual bool isChanged() { return false; };

        virtual void update() {};

//        virtual str &getStrValue(){return (str &) "hello";};

//        virtual void *getValue() {};
    };

    typedef std::shared_ptr<SmartVariable> SmartVariablePtr;
}


#endif //MYMINDUSTRY_SMARTVARIABLE_H
