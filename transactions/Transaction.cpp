
#include "Transaction.h"

#include <iostream>


Transaction::Transaction(const std::string & name)
: m_name{ name }
{
}


const std::string & Transaction::name() const
{
    return m_name;
}


void Transaction::process(const std::string & operation)
{
    onBeforeProcess(operation);

    std::cout << "TA '" << m_name << "': " << operation;

    onAfterProcess(operation);
}


void Transaction::onBeforeProcess(const std::string & operation)
{
}


void Transaction::onAfterProcess(const std::string & operation)
{
}
