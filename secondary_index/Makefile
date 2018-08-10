CONTRACT=marketplace

all: $(CONTRACT).wast $(CONTRACT).abi



%.wast: %.cpp
	eosiocpp -o $@ $<

%.abi: %.cpp
	eosiocpp -g $@ $<

clean:
	rm -f $(CONTRACT).abi $(CONTRACT).wast $(CONTRACT).wasm
