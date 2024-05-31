all: comp run

pv:  comp_pv run_pv

pa: comp_pa run_pa

pt : comp_pt run_pt

comp:
	gcc ./src_Code/index.c -o main

run:
	./main

comp_pv:
	gcc ./src_Code/view_p.c -o view_p

run_pv:
	./view_p.exe

comp_pa:
	gcc ./src_Code/about.c -o about

run_pa:
	./about.exe

comp_pt:
	gcc ./src_Code/testcase.c -o ./src_Code/testcase

run_pt:
	./src_Code/testcase
