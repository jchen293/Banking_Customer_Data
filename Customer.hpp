/**
 * Customer.hpp
 * Name: Junjie Chen
 * Person number: 50200189
 *
 * This file contains the definition of the Customer class.
 * Add any fields you wish, but do not change the name of or remove any
 * of the required fields that are provided by default.
 * You may not use any additional headers.
 */

#ifndef A3_CUSTOMER_HPP
#define A3_CUSTOMER_HPP

// Do not modify/add/remove includes in this file.
#include "Transaction.hpp"
#include <vector>
#include <list>
#include <algorithm>

class Customer {
private:
    /**
     * Default constructor with no parameters is made private so that no transactions are created without
     * providing a value for the _customer_id.
     */

    Customer();

public:
    // Used to store the customer ID.
    size_t _customer_id;

    // Used to store the customer's account balance.
    double _account_balance;

    // List of pending transactions.
    CSE250::dTransactionNode* _pending_txs;

    // Flag to determine if account was overdrawn.
    bool _overdrawn;

    /**
     * Constructor for Customer requires a customer id to be provided.
     * By default, if no starting balance is given, the customer is created with a starting balance of 0.
     * As the member variable _cust_id is const, you must provide this at construction as it cannot be changed later.
     *
     * @param id - the unique customer id number assigned to this customer.
     * @param starting_balance - the dollar amount to start the account at.
     */
    Customer(const size_t& id, const double& starting_balance = 0) : _customer_id(id), _account_balance(starting_balance),
                                                                     _pending_txs(nullptr), _overdrawn(false) { }

    // Feel free to add more functionality here as needed.
};

namespace CSE250 {
    struct dCustomerIDNode;
}

struct CSE250::dCustomerIDNode {
    // Transaction stored within the node.
    const size_t _customer_id;

    // Pointer to previous node in list.
    dCustomerIDNode* _prev;

    // Pointer to next node in list.
    dCustomerIDNode* _next;

    /**
     * Constructor for a transaction node requires the default information to create a transaction.
     *
     * @param id - the id of a customer of interest.
     */
    dCustomerIDNode(const size_t& id) : _customer_id(id), _prev(nullptr), _next(nullptr) { }

private:
    /**
     * Default constructor with no parameters is made private so that no node is created without
     * providing a value for the _customer_id. This avoids accidentally creating a node without
     * providing a specific id.
     */
    dCustomerIDNode();
};

#endif //A3_CUSTOMER_HPP
