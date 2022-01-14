GENERATES = range *.log *.out

range: range.c
	gcc -O0 -g $< -o $@

test: test_1 test_2


test_%: gdb_scenario_%.out
	cmp $< $@

gdb_scenario_1.out: gdb_scenario_1 range
	cgdb -x $< ./range
	cat gdb_scenario_1.log | grep "@@@" | sed -E "s/@@@(.*)/\1/" > $@

gdb_scenario_2.out: gdb_scenario_2 range
	cgdb -x $< ./range
	cat gdb_scenario_2.log | grep "@@@" | sed -E "s/@@@(.*)/\1/" > $@

clean:
	rm -f $(GENERATES)