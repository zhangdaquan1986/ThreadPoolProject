・ThreadPoolProjectプロジェクトの概要
	C++で実装されたスレッドプールのサンプルプログラムです。
 
・ビルド実行方法
	・Linux
		ThreadPoolProjectに移動
		mkdir -p build
		cd build
		cmake ..
		make
		./ThreadPoolProject
	・Windows
		ThreadPoolProjectに移動
		mkdir build 
		cd build
		cmake .. -G "MinGW Makefiles"
		mingw32-make
		ThreadPoolProject.exe

