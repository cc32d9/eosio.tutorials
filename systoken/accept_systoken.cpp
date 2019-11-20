#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio.system/eosio.system.hpp>

using namespace eosio;

using std::string;
using std::to_string;

class [[eosio::contract]] accept_systoken: public eosio::contract {
 public:
  accept_systoken(name self, name code, datastream<const char*> ds):
    contract(self, code, ds)
    {}
  
  [[eosio::on_notify("*::transfer")]]
    void transfer_handler (name from, name to, asset quantity, string memo) {
    
    if(to == _self) {
      const name sys_token_contract = eosiosystem::system_contract::token_account;
      const symbol sys_token_symbol = eosiosystem::system_contract::get_core_symbol();
      
      const extended_asset payment(quantity, name{get_first_receiver()});

      check(payment.contract == sys_token_contract, "System token contract expected");
      check(payment.quantity.symbol == sys_token_symbol, "System token symbol expected");
    }
  }

  // CDT dispatcher needs at least one action */
  [[eosio::action]] void donothing() {}
  
};

  
