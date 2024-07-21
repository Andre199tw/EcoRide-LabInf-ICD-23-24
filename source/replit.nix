{ pkgs }: {
	deps = [
   pkgs.llvmPackages_10.libllvm
   pkgs.gcc-unwrapped
   pkgs.llvmPackages_6.llvm
   pkgs.curlHTTP3
   pkgs.cjson
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
	env = { 
		LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [ pkgs.openssl_1_1.out ]; 
	};

}