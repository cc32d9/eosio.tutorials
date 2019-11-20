#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>

using namespace eosio;

class [[eosio::contract]] marketplace : public eosio::contract {
public:
  marketplace(name self, name code, datastream<const char*> ds):
    contract(self, code, ds), _items(self, self.value)
    {}

  
  struct [[eosio::table("items")]] item
  {
    uint64_t       id;
    name           owner;
    uint64_t       product;
    int64_t        haveqty;

    auto primary_key()const { return id; }
    uint64_t get_owner()const { return owner.value; }
    uint64_t get_product()const { return product; }
  };

  typedef eosio::multi_index<name("items"), item,
    indexed_by<name("owner"), const_mem_fun<item, uint64_t, &item::get_owner>>,
    indexed_by<name("product"), const_mem_fun<item, uint64_t, &item::get_product>>> items;

  [[eosio::action]]
  void haveprod(name owner, uint64_t product, int64_t qty) {
    _additem(owner, product, qty);
  }

  [[eosio::action]]
  void wantprod(name owner, uint64_t product, int64_t qty) {
    _additem(owner, product, qty * -1);
  }


  
private:
  items _items;

  void _additem(name owner, uint64_t product, int64_t haveqty)
  {
    require_auth(owner);

    auto prodidx = _items.get_index<name("product")>();
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
  
