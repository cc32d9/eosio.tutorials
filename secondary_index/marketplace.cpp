#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>

using namespace eosio;

class marketplace : public eosio::contract {
public:
  marketplace( account_name self ):
    contract(self), _items(self, self)
  {}

  /// @abi table
  struct item
  {
    uint64_t       id;
    account_name   owner;
    uint64_t       product;
    int64_t        haveqty;

    auto primary_key()const { return id; }
    uint64_t get_owner()const { return owner; }
    uint64_t get_product()const { return product; }
  };

  typedef eosio::multi_index<N(item), item,
    indexed_by<N(owner), const_mem_fun<item, uint64_t, &item::get_owner>>,
    indexed_by<N(product), const_mem_fun<item, uint64_t, &item::get_product>>> items;

  /// @abi action
  void haveprod(account_name owner, uint64_t product, int64_t qty) {
    _additem(owner, product, qty);
  }

  /// @abi action
  void wantprod(account_name owner, uint64_t product, int64_t qty) {
    _additem(owner, product, qty * -1);
  }


  
private:
  items _items;

  void _additem(account_name owner, uint64_t product, int64_t haveqty)
  {
    require_auth( owner );

    auto prodidx = _items.get_index<N(product)>();
    auto proditr = prodidx.lower_bound(product);
    while( proditr != prodidx.end() && proditr->product == product ) {
      if( proditr->owner == owner ) {
        if( proditr->haveqty + haveqty == 0 ) {
          _items.erase(*proditr);
          return;
        }
        else {
          _items.modify( *proditr, owner, [&]( auto& i ) {
              i.haveqty += haveqty;
            });
          return;
        }
      }
      else {
        proditr++;
      }
    }

    // such item does not exist yet
    _items.emplace(owner, [&]( auto& i ) {
          i.id = _items.available_primary_key();
          i.owner = owner;
          i.product = product;
          i.haveqty = haveqty;
      });
  }
};
  
EOSIO_ABI( marketplace, (haveprod)(wantprod) )
