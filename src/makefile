hugs: *.c *.h
	gcc hugs.c edit.c observe.c builtin.c compiler.c errors.c evaluator.c ffi.c goal.c input.c machdep.c machine.c module.c opts.c output.c plugin.c script.c static.c storage.c strutil.c subst.c type.c server.c version.c  -lm -ldl -lreadline -o hugs

runhugs: *.c *.h
	gcc -O3 hugs.c edit.c observe.c builtin.c compiler.c errors.c evaluator.c ffi.c goal.c input.c machdep.c machine.c module.c opts.c output.c plugin.c script.c static.c storage.c strutil.c subst.c type.c server.c version.c  -lm -ldl -lreadline -o runhugs
