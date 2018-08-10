```
cleos -u http://rpc.eoswatch.info:9000 system newaccount --transfer --stake-net "100.0000 SYS" --stake-cpu "100.0000 SYS" --buy-ram-kbytes 500 eosio marketplace1 EOS8C9tb8QQhZet6WWcYFCWDKHYfjC3W59ugHCD63s7LLDQx6JsNK EOS8C9tb8QQhZet6WWcYFCWDKHYfjC3W59ugHCD63s7LLDQx6JsNK


make
cleos -u http://rpc.eoswatch.info:9000 set contract marketplace1 . marketplace.wasm marketplace.abi 

cleos -u http://rpc.eoswatch.info:9000 push action marketplace1 wantprod '["tsttoken11", 111, 10]' -p tsttoken11
cleos -u http://rpc.eoswatch.info:9000 push action marketplace1 haveprod '["tsttoken11", 111, 15]' -p tsttoken11

cleos -u http://rpc.eoswatch.info:9000 push action marketplace1 haveprod '["tsttoken12", 111, 15]' -p tsttoken12

cleos -u http://rpc.eoswatch.info:9000 get table marketplace1 marketplace1 item
```


