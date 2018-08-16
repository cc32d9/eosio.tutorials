#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/multi_index.hpp>

using namespace eosio;

class assets : public eosio::contract {
public:
  assets( account_name self ):
    contract(self), _items(self, self)
  {}

  /// @abi table items
  struct item
  {
    uint64_t       id;
    asset          amounta;
    account_name   contracta;
    extended_asset amountb;

    auto primary_key()const { return id; }
  };

  typedef eosio::multi_index<N(items), item> items;

  /// @abi action
  void init() {
    _items.emplace(_self, [&]( auto& i ) {
        i.id = _items.available_primary_key();
        i.amounta = asset(1000*now(), S(4,TESTA));
        i.contracta = N(testtokena);
        i.amountb = extended_asset(asset(1000*now(), S(4,TESTB)), N(testtokenb));
      });
  }
  
  
private:
  items _items;

};
  
EOSIO_ABI( assets, (init) )
