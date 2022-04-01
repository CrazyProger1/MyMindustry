//
// Created by crazy on 01.04.2022.
//

#ifndef MYMINDUSTRY_LOGGINGMANAGER_H
#define MYMINDUSTRY_LOGGINGMANAGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include "../types.h"

namespace engine {
    class LoggingManager {
    private:
        bool m_bOutToFile = true;
        bool m_bPrint = false;
        str m_strFileName = "log.txt";
        std::ofstream m_logFile;

    protected:
        static LoggingManager *s_pSelf;

        LoggingManager();

        virtual ~LoggingManager();

    public:
        static LoggingManager *getInstance();

        static bool deleteInstance();

        void logInfo(const str &info, bool bindTime = true);

        void logError(const str &error, bool bindTime = true);

        void clearLog();

        void setFileName(const str &fileName);

        void setPrintOut(bool print);

        void setOutToFile(bool out);
    };

}


#endif //MYMINDUSTRY_LOGGINGMANAGER_H
