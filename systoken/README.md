# System token lookup

This simple contract looks up the system token symbol and it only
accepts transfers in system currency.

The code uses `eosio.system.hpp` from `eosio.contracts` repository.

Building:

```
cd ~/build
git clone https://github.com/EOSIO/eosio.contracts.git

git clone https://github.com/cc32d9/eosio.tutorials.git
cd eosio.tutorials/systoken
eosio-cpp -I ~/build/eosio.contracts/contracts/eosio.system/include accept_systoken.cpp
```



