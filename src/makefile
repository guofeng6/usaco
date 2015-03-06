SRC = $(shell ls *.cc)
DIR = $(HOME)/usaco_out
OUT = $(addprefix $(DIR)/, $(SRC:.cc=.out))
EXE = $(addprefix $(DIR)/, $(SRC:.cc=.exe))

all: $(DIR) $(OUT) 
exe: $(EXE)

$(DIR)/%.out:%.in $(DIR)/%.exe
	@if [ -f $@ ]; then rm $@; fi
	@time $(@:.out=.exe) 2>&1
	@mv  $(<:.in=.out) $(DIR) 
	@cat $< | head -50 && echo "..."
	@echo "==>"
	@cat $@ && echo ""

$(DIR)/%.exe:%.cc
	g++ -std=gnu++0x $< -o $@ 

$(DIR):
	install -d $(DIR) 

clean:
	rm -r $(DIR)
