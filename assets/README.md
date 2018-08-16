# Assets representation

```
make
cleos -u http://rpc.eoswatch.info:9000 set contract tsttoken11 . assets.wasm assets.abi 
cleos -u http://rpc.eoswatch.info:9000 push action tsttoken11 init '[]' -p tsttoken11
cleos -u http://rpc.eoswatch.info:9000 push action tsttoken11 init '[]' -p tsttoken11

cleos -u http://rpc.eoswatch.info:9000 get table tsttoken11 tsttoken11 items
{
  "rows": [{
      "id": 0,
      "amounta": "110150.6328 TESTA",
      "contracta": "testtokena",
      "amountb": {
        "quantity": "110150.6328 TESTB",
        "contract": "testtokenb"
      }
    },{
      "id": 1,
      "amounta": "110151.1328 TESTA",
      "contracta": "testtokena",
      "amountb": {
        "quantity": "110151.1328 TESTB",
        "contract": "testtokenb"
      }
    }
  ],
  "more": false
}

```