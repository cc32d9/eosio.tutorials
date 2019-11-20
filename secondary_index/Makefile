CONTRACT=marketplace

all: $(CONTRACT).wasm



%.wasm: %.cpp
	eosio-cpp $<


clean:
	rm -f $(CONTRACT).abi $(CONTRACT).wasm
