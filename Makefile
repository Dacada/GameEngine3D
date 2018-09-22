.PHONY: all rel dbg prf clean veryclean

all: rel
rel:
	$(MAKE) -C Engine3D
	$(MAKE) -C Main

dbg:
	$(MAKE) -C Engine3D dbg
	$(MAKE) -C Main dbg

prf:
	$(MAKE) -C Engine3D prf
	$(MAKE) -C Main prf

clean:
	$(MAKE) -C Engine3D cleanlib
	$(MAKE) -C Main clean

veryclean: clean
	$(MAKE) -C Engine3D clean
	rm -f gmon.out
