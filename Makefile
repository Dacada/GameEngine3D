.PHONY: all rel dbg clean veryclean

all: rel
rel:
	$(MAKE) -C Engine3D
	$(MAKE) -C Main

dbg:
	$(MAKE) -C Engine3D dbg
	$(MAKE) -C Main dbg

clean:
	$(MAKE) -C Engine3D cleanlib
	$(MAKE) -C Main clean

veryclean: clean
	$(MAKE) -C Engine3D clean
