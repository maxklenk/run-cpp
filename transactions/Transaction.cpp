
#include "Transaction.h"

#include <iostream>

namespace MI {
    Transaction::Transaction(const std::string &name)
            : m_name{name} {
    }


    const std::string &Transaction::name() const {
        return m_name;
    }


    void Transaction::process(const std::string &operation) {
        onBeforeProcess(operation);

        std::cout << "TA '" << m_name << "': " << operation;

        onAfterProcess(operation);
    }


    void Transaction::onBeforeProcess(const std::string &operation) {
    }


    void Transaction::onAfterProcess(const std::string &operation) {
    }


    LoggedTransaction::LoggedTransaction(const std::string &name) : Transaction(name) {
    }

    void LoggedTransaction::onBeforeProcess(const std::string &operation) {
        std::cout << "[logged] ";
    }


    void LoggedTransaction::onAfterProcess(const std::string &operation) {
        std::cout << " [/logged]";
    }


    SecuredTransaction::SecuredTransaction(const std::string &name) : Transaction(name) {
    }

    void SecuredTransaction::onBeforeProcess(const std::string &operation) {
        std::cout << "[secured] ";
    }


    void SecuredTransaction::onAfterProcess(const std::string &operation) {
        std::cout << " [/secured]";
    }


    LoggedSecureTransaction::LoggedSecureTransaction(const std::string &name) : Transaction(name),
                                                                                LoggedTransaction(name),
                                                                                SecuredTransaction(name) {
    }

    void LoggedSecureTransaction::onBeforeProcess(const std::string &operation) {
        LoggedTransaction::onBeforeProcess(operation);
        SecuredTransaction::onBeforeProcess(operation);
    }


    void LoggedSecureTransaction::onAfterProcess(const std::string &operation) {
        SecuredTransaction::onAfterProcess(operation);
        LoggedTransaction::onAfterProcess(operation);
    }
}

namespace nonMI {
    Transaction::Transaction(const std::string &name)
            : m_name{name} {
    }


    const std::string &Transaction::name() const {
        return m_name;
    }


    void Transaction::process(const std::string &operation) {
        onBeforeProcess(operation);

        std::cout << "TA '" << m_name << "': " << operation;

        onAfterProcess(operation);
    }


    void Transaction::onBeforeProcess(const std::string &operation) {
    }


    void Transaction::onAfterProcess(const std::string &operation) {
    }
}