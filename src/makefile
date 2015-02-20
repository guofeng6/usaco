SRC = $(shell ls *.cc)
DIR = $(HOME)/usaco_out
OUT = $(addprefix $(DIR)/, $(SRC:.cc=.out))
EXE = $(addprefix $(DIR)/, $(SRC:.cc=.exe))

all: $(DIR) $(OUT) 
exe: $(EXE)

$(DIR)/%.out:%.in $(DIR)/%.exe
	$(@:.out=.exe)
	@mv  $(<:.in=.out) $(DIR) 
	@cat $< && echo "===>"
	@cat $@ && echo ""

$(DIR)/%.exe:%.cc
	g++ $< -o $@ 

$(DIR):
	install -d $(DIR) 

clean:
	rm -r $(DIR)
