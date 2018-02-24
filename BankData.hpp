/**
 * BankData.hpp
 * Name: Junjie Chen
 * Person number: 50200189
 *
 * Definition for the class BankData and the description of all methods are contained in here.
 * Feel free to add to this, but you must include at least the required methods.
 * You may not use any additional headers.
 */

#ifndef A3_BANKDATA_HPP
#define A3_BANKDATA_HPP

// Do not modify/add/remove includes in this file.
#include "Customer.hpp"
#include <vector>
#include <list>
#include <algorithm>

class BankData {
    // Create your variables to store customers and transaction information here.
    std::vector<Customer> customerList;

public:
    // You may want to add a constructor or other methods as well. The starting set is all that is required.

     ~BankData(){
         this->process_transactions();
     }
    /**
     * Add a customer to the stored customers if no customer with the same id is present.
     * Initialize the customer balance to the value provided.
     *
     * @param customer_id - id to assign the new customer.
     * @param balance - starting balance for the customer.
     * @return  true - if customer was successfully added.
     *         false - if the customer was previously added.
     */
    bool add_customer(const size_t& customer_id, const double& balance = 0);

    /**
     * Add a list of customers to the stored customers with the ids within this list.
     * You should initialize the customers with an account balance of 0.
     * All values in the list should be processed, even if a customer already exists.
     *
     * @param customer_list - list of customer ids to add.
     * @return  true - if all customers were successfully added.
     *         false - if some customer was previously added (including if there are duplicates in the list itself).
     */
    bool add_customer(const CSE250::dCustomerIDNode* customer_list);

    /**
     * Remove a customer from the stored customers.
     *
     * @param customer_id - id of customer to remove.
     * @return  true - if customer was successfully removed.
     *         false - if the customer was not present.
     */
    bool remove_customer(const size_t& customer_id);

    /**
     * Remove a list of customer to the stored customers with an account balance of 0.
     * All values in the list should be processed, even if an ID is for a customer that
     * was already removed or doesn't exist.
     *
     * @param customer_list - list of customer ids to remove.
     * @return  true - if all customers were successfully removed.
     *         false - if some customer was not removed (including if there are duplicates in the list itself).
     */
    bool remove_customer(const CSE250::dCustomerIDNode* customer_list);

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
    bool add_transaction(const size_t& customer_id, const size_t& timestamp, const double& amount);

    /**
     * Void the transaction with the specified customer id and timestamp
     * (i.e., remove it from the customer's transaction list).
     *
     * You may assume that each timestamp will be unique between each call to process transactions.
     *
     * @param customer_id - id of the customer the transaction is under.
     * @param timestamp - timestamp the transaction was created with.
     * @return  true - if the transaction was successfully added to the customer's account.
     *         false - if the customer didn't exist or there is no transaction with the given timestamp
     *                 for that customer.
     */
    bool void_transaction(const size_t& customer_id, const size_t& timestamp);

    /**
     * Process each transaction for each customer.
     * At the end, all transaction lists should be empty and account balances should reflect all changes
     * dictated by the respective lists of transactions.
     * Transactions should be processed in increasing order of timestamp (within the Customer's pending transactions).
     * Create a list of all customers that had overdrawn their account.
     * @return double linked list of all customer IDs that overdrew their account.
     */
    CSE250::dCustomerIDNode* process_transactions();

    /**
     * Process each transaction for a single customer.
     * Transactions should be processed in increasing timestamp order.
     * While processing the transactions, if the customer's balance becomes negative,
     * then the _overdrawn flag should be set to true.
     *
     * @param customer - customer object for which to process transactions.
     */
    void process_transactions(Customer& customer);

    /**
     * Tell whether or not a customer with the specified ID exists in the stored customer data.
     *
     * @param customer_id -  id of the customer requested.
     * @return  true - if the customer requested has a stored record.
     *         false - otherwise.
     */
    bool customer_exists(const size_t& customer_id) const;

    /**
     * Tell whether or not the ID belongs to a valid customer and
     * the timestamp belongs to a valid Transaction under that customer.
     *
     * @param customer_id -  id of the customer requested.
     * @param timestamp - timestamp the transaction was created with.
     * @return  true - if the customer requested has a stored record.
     *         false - otherwise.
     */
    bool transaction_exists(const size_t& customer_id, const size_t& timestamp) const;

    /**
     * Get access to the customer data associated with the requested ID.
     * You should assume that the ID belongs to a valid customer.
     * @param customer_id - id of the customer requested.
     * @return constant reference to the Customer object associated with the id.
     */
    const Customer& get_customer_data(const size_t& customer_id) const;

    /**
     * Get access to the transaction data associated with the requested ID and timestamp.
     * You should assume that the ID belongs to a valid customer and the timestamp belongs to a valid Transaction.
     * @param customer_id - id of the customer requested.
     * @param timestamp - timestamp the transaction was created with.
     * @return constant reference to the Transaction object associated with the id and timestamp.
     */
    const Transaction& get_customer_transaction(const size_t& customer_id, const size_t& timestamp) const;


};


#endif //A3_BANKDATA_HPP
