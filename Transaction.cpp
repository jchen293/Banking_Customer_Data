/**
 * Transaction.hpp
 * Name: Junjie Chen
 * Date: 10/22/2017
 *
 * This file contains the definition of the Transaction class.
 * Add any fields you wish, but do not change the name of or remove any
 * of the required fields that are provided by default.
 * You may not use any additional headers.
 */

#ifndef A3_TRANSACTION_HPP
#define A3_TRANSACTION_HPP

// Do not modify/add/remove includes in this file.
#include <vector>
#include <list>
#include <algorithm>


class Transaction {
private:
    /**
     * Default constructor with no parameters is made private so that no transactions are created without
     * providing a value for the _timestamp and a value for _tx_amt.
     */
    Transaction();

public:
    // Timestamp is equivalent to the number of transactions created between the time all transactions were last
    // processed and this Transaction was created.
    size_t _timestamp;

    // Value of the Transaction (positive: deposit, negative: withdrawal).
    double _tx_amt;

    /**
     * Constructor for transaction requires a time and amount to be provided.
     * As the members are const, you must provide these at construction as they cannot be changed later.
     *
     * @param time - the number of transactions prior to the creation of this transaction.
     * @param amount - the dollar value of the transaction (amount of money transferred)
     */
    Transaction(size_t time, double amount) : _timestamp(time), _tx_amt(amount) { }

    // Feel free to add more functionality here as needed.
};

namespace CSE250 {
    struct dTransactionNode;
}

struct CSE250::dTransactionNode {
    // Transaction stored within the node.
    Transaction _tx;

    // Pointer to previous node in list.
    dTransactionNode* _prev;

    // Pointer to next node in list.
    dTransactionNode* _next;

    /**
     * Constructor for a transaction node requires the default information to create a transaction.
     *
     * @param time - the number of transactions prior to the creation of this transaction.
     * @param amount - the dollar value of the transaction (amount of money transferred)
     */
    dTransactionNode(size_t time, double amount) : _tx(time, amount), _prev(nullptr), _next(nullptr) { }

private:
    /**
     * Default constructor with no parameters is made private so that no transactions are created without
     * providing a value for the _timestamp and a value for _tx_amt.
     * This is needed here as well because we don't want to create empty transactions.
     */
    dTransactionNode();
};


#endif //A3_TRANSACTION_HPP
