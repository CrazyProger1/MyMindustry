//
// Created by crazy on 01.04.2022.
//

#include "../../include/managers/LoggingManager.h"


namespace engine {
    str getCurrentTime() {
        std::time_t t = std::time(nullptr);   // get time now
        std::tm *now = std::localtime(&t);
        return std::to_string(now->tm_year + 1900) +
               "-" + std::to_string(now->tm_mon) +
               "-" + std::to_string(now->tm_mday) +
               " " + std::to_string(now->tm_hour) +
               ":" + std::to_string(now->tm_min);
    }

    LoggingManager *LoggingManager::s_pSelf = nullptr;

    LoggingManager::LoggingManager() {
        m_logFile.open(m_strFileName, std::ios::app);
    }


    void LoggingManager::logInfo(const str &info, bool bindTime) {
        str strToLog;

        if (bindTime)
            strToLog = "INFO :" + getCurrentTime() + " : " + info;
        else
            strToLog = "INFO : " + info;

        if (m_bPrint)
            std::cout << strToLog << std::endl;

        if (m_bOutToFile) {
            m_logFile << strToLog << std::endl;
        }
    }

    void LoggingManager::logError(const str &error, bool bindTime) {
        str strToLog;
        if (bindTime)
            strToLog = "ERROR : " + getCurrentTime() + " : " + error;
        else
            strToLog = "ERROR : " + error;

        if (m_bPrint)
            std::cerr << strToLog << std::endl;

        if (m_bOutToFile) {
            m_logFile << strToLog << std::endl;
        }
    }

    void LoggingManager::clearLog() {
        m_logFile.close();

        std::ofstream lf;
        lf.open(m_strFileName);
        lf.close();

        m_logFile.open(m_strFileName, std::ios::app);

        logInfo("LOGS CLEARED");


    }

    void LoggingManager::setFileName(const str &fileName) {
        m_strFileName = fileName;
        m_logFile.open(m_strFileName, std::ios::app);
    }

    void LoggingManager::setPrintOut(bool print) {
        m_bPrint = print;
    }

    void LoggingManager::setOutToFile(bool out) {
        m_bOutToFile = out;
    }

    LoggingManager::~LoggingManager() {
        m_logFile.close();
    }

    bool LoggingManager::deleteInstance() {
        if (s_pSelf) {
            delete s_pSelf;
            s_pSelf = nullptr;
            return true;
        }
        return false;
    }

    LoggingManager *LoggingManager::getInstance() {
        if (!s_pSelf) {
            s_pSelf = new LoggingManager();
        }
        return s_pSelf;
    }







}