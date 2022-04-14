//
// Created by crazy on 14.04.2022.
//

#ifndef MYMINDUSTRY_SMARTSTR_H
#define MYMINDUSTRY_SMARTSTR_H

#include "../../types.h"
#include "./SmartVariable.h"

namespace engine {
    struct SmartStr : public SmartVariable {
    private:
        str m_sValue;
        bool m_bIsChanged = false;
        bool m_bFunctionChangedCalled = false;
    public:
        void setValue(const str &value);

        str &getValue();

        [[nodiscard]] bool isChanged() override;

        void update() override;
    };

    typedef std::shared_ptr<SmartStr> SmartStrPtr;
}


#endif //MYMINDUSTRY_SMARTSTR_H
