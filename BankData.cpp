/**
 * BankData.cpp
 * Name: Junjie Chen
 * Person number: 50200189
 *
 * All definitions of functions for the class BankData and the description of all methods are contained in here.
 * Feel free to add more function definitions to this, but you must include at least the required methods.
 * You may not use any additional headers.
 */

// Do not modify/add/remove includes in this file.
#include "BankData.hpp"

using namespace std;
/**
 * Add a customer to the stored customers if no customer with the same id is present.
 * Initialize the customer balance to the value provided.
 *
 * @param customer_id - id to assign the new customer.
 * @param balance - starting balance for the customer.
 * @return  true - if customer was successfully added.
 *         false - if the customer was previously added.
 */
bool BankData::add_customer(const size_t &customer_id, const double &balance) {
    if (customer_exists(customer_id)) {
        return false;
    } else {
        customerList.push_back(Customer(customer_id, balance));
        return true;
    }
}

/**
 * Add a list of customers to the stored customers with the ids within this list.
 * You should initialize the customers with an account balance of 0.
 * All values in the list should be processed, even if a customer already exists.
 *
 * @param customer_list - list of customer ids to add.
 * @return  true - if all customers were successfully added.
 *         false - if some customer was previously added (including if there are duplicates in the list itself).
 */
bool BankData::add_customer(const CSE250::dCustomerIDNode *customer_list) {
    bool flag = true;
    size_t i;
    auto *temp = customer_list;
    while (temp != nullptr) {
        for (i = 0; i < customerList.size(); ++i)
            if (customerList[i]._customer_id == temp->_customer_id)
                break;
        if (i == customerList.size()) {
            customerList.push_back(Customer(temp->_customer_id, 0));
        } else {
            flag = false;
        }
//        auto *t = temp;
        temp = temp->_next;
        //    delete t;
    }
    //delete temp;
    return flag; // TODO: Change this return value.
}

/**
 * Remove a customer from the stored customers.
 *
 * @param customer_id - id of customer to remove.
 * @return  true - if customer was successfully removed.
 *         false - if the customer was not present.
 */
bool BankData::remove_customer(const size_t &customer_id) {
    auto temp = customerList.begin();
    for (int i = 0; i < customerList.size(); ++i) {
        if (customerList.at(i)._customer_id == customer_id) {
            this->process_transactions(customerList.at(i));
            customerList.erase(temp);
            return true;
        }
        temp = temp + 1;
    }
    return false; // TODO: Change this return value.
}

/**
 * Remove a list of customer to the stored customers with an account balance of 0.
 * All values in the list should be processed, even if an ID is for a customer that
 * was already removed or doesn't exist.
 *
 * @param customer_list - list of customer ids to remove.
 * @return  true - if all customers were successfully removed.
 *         false - if some customer was not removed (including if there are duplicates in the list itself).
 */
bool BankData::remove_customer(const CSE250::dCustomerIDNode *customer_list) {
    auto *temp = customer_list;
    bool flag = true;
    bool flag_delete;
    while (temp != nullptr) {
        flag_delete = false;
        if (customerList.empty()) {
            return false;
        }
        for (int i = 0; i < customerList.size(); ++i)
            if (customerList.at(i)._customer_id == temp->_customer_id) {
                flag_delete = this->remove_customer(temp->_customer_id);
            }
        if (!flag_delete) {
            flag = false;
        }
        temp = temp->_next;
    }
    return flag;
}

/**
 * Add a transaction for to the transaction list for the specified customer.
 *
 * You may assume that each timestamp will be unique between each call to process transactions.
 * You may not assume that the timestamps will be given in any particular order.
 *
 * @param customer_id - id of the customer to add the transaction under.
 * @param timestamp - timestamp the transaction should be created with.
 * @param amount - amount the transaction will change their account balance
 * @return  true - if the transaction was successfully added to the customer's account.
 *         false - if the customer didn't exist.
 */
bool BankData::add_transaction(const size_t &customer_id, const size_t &timestamp, const double &amount) {
    if (!this->customer_exists(customer_id))
        return false;
    bool flag = false;
    auto *temp = new CSE250::dTransactionNode(timestamp, amount);
    for (size_t i = 0; i < customerList.size(); ++i) {
        if (customerList.at(i)._customer_id == customer_id) {
            if (customerList[i]._pending_txs == nullptr) {
                customerList[i]._pending_txs = temp;
                return true;
            }
            CSE250::dTransactionNode *t = customerList[i]._pending_txs, *p = nullptr;
            if (customerList[i]._pending_txs->_tx._timestamp > timestamp) {
                temp->_next = customerList[i]._pending_txs;
                customerList[i]._pending_txs->_prev = temp;
                customerList[i]._pending_txs = temp;
                return true;
            }
            while (t != nullptr&&t->_tx._timestamp < timestamp) {
                p = t;
                t = t->_next;
            }
            if (t == nullptr) {
                p->_next = temp;
                temp->_prev = p;
                return true;
            }
            else {
                p->_next = temp;
                temp->_next = t;
                temp->_prev = p;
                t->_prev = temp;
                return true;
            }
        }
    }
    return flag;
}


/**
 * Void the transaction with the specified customer id and timestamp
 * (i.e., remove it from the customer's transaction list).
 *
 * You may assume that each timestamp will be unique between each call to process transactions.
 *
 * @param customer_id - id of the customer the transaction is under.
 * @param timestamp - timestamp the transaction was created with.
 * @return  true - if the transaction was successfully removed to the customer's account.
 *         false - if the customer didn't exist or there is no transaction with the given timestamp
 *                 for that customer.
 */
bool BankData::void_transaction(const size_t &customer_id, const size_t &timestamp) {
    if (!this->customer_exists(customer_id))
        return false;
    for (size_t i = 0; i < customerList.size(); i++)
    {
        if (customerList[i]._customer_id == customer_id)
        {
            if (customerList[i]._pending_txs == nullptr) {
                return false;
            }
            if (customerList[i]._pending_txs->_tx._timestamp == timestamp) {
                if (customerList[i]._pending_txs->_next == nullptr) {
                    delete customerList[i]._pending_txs;
                    customerList[i]._pending_txs = nullptr;
                    return true;
                }
                else {
                    auto *t = customerList[i]._pending_txs;
                    customerList[i]._pending_txs = t->_next;
                    delete t;
                    return true;
                }
            }
            else {
                auto* t1 = customerList[i]._pending_txs, *t2 = customerList[i]._pending_txs;
                while (t1 != nullptr&&t1->_tx._timestamp != timestamp)
                {
                    t2 = t1;
                    t1 = t2->_next;
                }
                if (t1 != nullptr) {
                    t2->_next = t1->_next;
                    if (t1->_next != nullptr)
                        t1->_next->_prev = t2;
                    delete t1;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Process each transaction for each customer.
 * At the end, all transaction lists should be empty and account balances should reflect all changes
 * dictated by the respective lists of transactions.
 * Transactions should be processed in increasing order of timestamp (within the Customer's pending transactions).
 * Create a list of all customers that had overdrawn their account.
 * @return double linked list of all customer IDs that overdrew their account.
 */
CSE250::dCustomerIDNode *BankData::process_transactions() {
    CSE250::dCustomerIDNode *h = nullptr;
    for (size_t i = 0; i < customerList.size(); ++i) {
         this->process_transactions(customerList[i]);
        if (customerList[i]._overdrawn) {
            if (h == nullptr)
                h = new CSE250::dCustomerIDNode(customerList[i]._customer_id);
            else {
                auto *p = new CSE250::dCustomerIDNode(customerList[i]._customer_id);
                p->_next = h->_next;
                p->_prev = h;
                h->_next = p;
            }
        }
    }
    return h; // TODO: Change this return value.
}


/**
 * Process each transaction for a single customer.
 * Transactions should be processed in increasing timestamp order.
 * While processing the transactions, if the customer's balance becomes negative,
 * then the _overdrawn flag should be set to true.
 *
 * @param customer - customer object for which to process transactions.
 */
void BankData::process_transactions(Customer &customer) {
    CSE250::dTransactionNode *temp = nullptr;
    if (customer._pending_txs == nullptr) {
        return;
    }
    while (customer._pending_txs->_next != nullptr) {
        temp = customer._pending_txs;
        customer._pending_txs = temp->_next;
        customer._account_balance += temp->_tx._tx_amt;
        if (customer._account_balance < 0) {
            customer._overdrawn = true;
        }
        delete temp;
    }
    customer._account_balance += customer._pending_txs->_tx._tx_amt;
    if (customer._account_balance < 0) {
        customer._overdrawn = true;
    }
    delete customer._pending_txs;
    customer._pending_txs = nullptr;
}

/**
 * Tell whether or not a customer with the specified ID exists in the stored customer data.
 *
 * @param customer_id -  id of the customer requested.
 * @return  true - if the customer requested has a stored record.
 *         false - otherwise.
 */
bool BankData::customer_exists(const size_t &customer_id) const {

    for (size_t i = 0; i < customerList.size(); i++) {
        if (customerList[i]._customer_id == customer_id) {
            return true;
        }
    }
    return false;
}


/**
 * Tell whether or not the ID belongs to a valid customer and
 * the timestamp belongs to a valid Transaction under that customer.
 *
 * @param customer_id -  id of the customer requested.
 * @param timestamp - timestamp the transaction was created with.
 * @return  true - if the customer requested has a stored record.
 *         false - otherwise.
 */


bool BankData::transaction_exists(const size_t &customer_id, const size_t &timestamp) const {

    for (size_t i = 0; i < customerList.size(); i++) {
        if (customerList.at(i)._customer_id == customer_id) {
            if (customerList[i]._pending_txs == nullptr) {
                return false;
            } else {
                auto *p = customerList[i]._pending_txs;
                while (p != nullptr && p->_tx._timestamp != timestamp)
                    p = p->_next;
                if (p != nullptr) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false; // TODO: Change this return value.
}
/***********************************************************************************************/
/* The following definitions cannot be completed until you decide how you will store your data.*/
/***********************************************************************************************/

/**
 * Get access to the customer data associated with the requested ID.
 * You should assume that the ID belongs to a valid customer.
 * @param customer_id - id of the customer requested.
 * @return constant reference to the Customer object associated with the id.
 */
const Customer &BankData::get_customer_data(const size_t &customer_id) const {
    // TODO: Finish this function.
    size_t i;
    for (i = 0; i < customerList.size(); ++i) {
        if (customerList[i]._customer_id == customer_id) {
            return customerList[i];
        }
    }
    return customerList[i];
}

/**
 * Get access to the transaction data associated with the requested ID and timestamp.
 * You should assume that the ID belongs to a valid customer and the timestamp belongs to a valid Transaction.
 * @param customer_id - id of the customer requested.
 * @param timestamp - timestamp the transaction was created with.
 * @return constant reference to the Transaction object associated with the id and timestamp.
 */
const Transaction &BankData::get_customer_transaction(const size_t &customer_id, const size_t &timestamp) const {
    // TODO: Finish this function.
    size_t i;
    CSE250::dTransactionNode *temp = nullptr;
    for (i = 0; i < customerList.size(); i++) {
        if (customerList[i]._customer_id == customer_id) {
            temp = customerList[i]._pending_txs;
            while (temp != nullptr && temp->_tx._timestamp != timestamp)
                temp = temp->_next;
            break;
        }
    }
    return temp->_tx;
}
