// ************************************************************************** //
//                                                                            //
//                Account.hpp for GlobalBanksters United                //
//                Created on  : Thu Nov 20 19:43:15 1989                      //
//                Last update : Wed Jan 04 14:54:06 1992                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //


#pragma once
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

// ************************************************************************** //
//                               Account Class                                //
// ************************************************************************** //

class Account {


public:

	typedef Account		t;

	static int	getNbAccounts( void );          // Return _nbAccounts
	static int	getTotalAmount( void );         // Return _totalAmount
	static int	getNbDeposits( void );          // Return _totalNbDeposits
	static int	getNbWithdrawals( void );       // Return _totalNbWithdrawals
	static void	displayAccountsInfos( void );   // Etat de tous les comptes ???

	Account( int initial_deposit );             // Init un compte avec _amount = initial_deposit && _nbDeposits = 0
	~Account( void );

	void	makeDeposit( int deposit );         // Ajout deposit a _amount et incremente _nbDeposits
	bool	makeWithdrawal( int withdrawal );   // Retire withdrawal a _amount et incremente _nbWithdrawals
	int		checkAmount( void ) const;          // Return _amount
	void	displayStatus( void ) const;        // Etat du compte ???


private:

	static int	_nbAccounts;                    // Nombres total de comptes
	static int	_totalAmount;                   // Total de thunes generale
	static int	_totalNbDeposits;               // Nombres de depos generale
	static int	_totalNbWithdrawals;            // Nombres de retrait generale

	static void	_displayTimestamp( void );      // Date [YYYYMMDD_HHMMSS]

	int				_accountIndex;              // Id du compte
	int				_amount;                    // Totale de thunes du compte
	int				_nbDeposits;                // Nombres de depot
	int				_nbWithdrawals;             // Nombres de retrait

	Account( void );

};



// ************************************************************************** //
// vim: set ts=4 sw=4 tw=80 noexpandtab:                                      //
// -*- indent-tabs-mode:t;                                                   -*-
// -*- mode: c++-mode;                                                       -*-
// -*- fill-column: 75; comment-column: 75;                                  -*-
// ************************************************************************** //


#endif /* __ACCOUNT_H__ */
