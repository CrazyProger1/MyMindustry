//
// Created by crazy on 14.04.2022.
//

#include "../../../include/managers/variables/SmartStr.h"
#include "iostream"

namespace engine {

    void SmartStr::setValue(const str &value) {
        m_sValue = value;
        m_bIsChanged = true;
    }

    bool SmartStr::isChanged() {
        m_bFunctionChangedCalled = true;
        return m_bIsChanged;
    }

    void SmartStr::update() {
        if (m_bFunctionChangedCalled && m_bIsChanged) {
            m_bIsChanged = false;

        }
        m_bFunctionChangedCalled = false;

    }

    str &SmartStr::getValue() {
        return m_sValue;
    }
}