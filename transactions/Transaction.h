
#pragma once

#include <vector>
#include <string>

namespace MI
{
    class Transaction
    {
    public:
        explicit Transaction(const std::string &name);

        virtual ~Transaction() = default;

        const std::string &name() const;

        void process(const std::string &operation);


    protected:
        virtual void onBeforeProcess(const std::string &operation);

        virtual void onAfterProcess(const std::string &operation);


    private:
        std::string m_name;
    };


    class LoggedTransaction : public virtual Transaction
    {
    public:
        explicit LoggedTransaction(const std::string &name);

    protected:
        virtual void onBeforeProcess(const std::string &operation);

        virtual void onAfterProcess(const std::string &operation);
    };


    class SecuredTransaction : public virtual Transaction
    {
    public:
        explicit SecuredTransaction(const std::string &name);

    protected:
        virtual void onBeforeProcess(const std::string &operation);

        virtual void onAfterProcess(const std::string &operation);
    };

    class LoggedSecureTransaction : public virtual LoggedTransaction, public virtual SecuredTransaction
    {
    public:
        explicit LoggedSecureTransaction(const std::string &name);

        using LoggedTransaction::process;

    protected:
        virtual void onBeforeProcess(const std::string &operation);

        virtual void onAfterProcess(const std::string &operation);
    };
}


namespace nonMI
{

    class Hook
    {
    public:
        Hook() {}

        virtual ~Hook() = default;

        virtual void onBeforeProcess(const std::string &operation) = 0;

        virtual void onAfterProcess(const std::string &operation) = 0;
    };

    class LoggerHook : public Hook
    {
    public:
        LoggerHook() {}

        virtual ~LoggerHook() = default;

        virtual void onBeforeProcess(const std::string &operation) override;

        virtual void onAfterProcess(const std::string &operation) override;

    };

    class SecureHook : public Hook
    {
    public:
        SecureHook() {}

        virtual ~SecureHook() = default;

        virtual void onBeforeProcess(const std::string &operation) override;

        virtual void onAfterProcess(const std::string &operation) override;
    };


    class Transaction
    {
    public:
        explicit Transaction(const std::string &name);

        virtual ~Transaction() = default;

        const std::string &name() const;

        void process(const std::string &operation);

        void addHook(Hook *hook);


    protected:
        virtual void onBeforeProcess(const std::string &operation);

        virtual void onAfterProcess(const std::string &operation);


    private:
        std::string m_name;
        std::vector<Hook *> hooks;
    };
}