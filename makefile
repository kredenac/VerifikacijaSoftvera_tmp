src_dir = ./src/rtc
build_dir = ./src/build-rtc-Release

.PHONY: all run clean

all:
	rm -rf $(build_dir)
	mkdir $(build_dir)
	qmake -o $(build_dir)/ $(src_dir)/rtc.pro
	make -C $(build_dir)

run:
	cd $(build_dir) && ./rtc

clean:
	rm -rf $(build_dir)

