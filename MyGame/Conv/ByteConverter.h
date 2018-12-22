#pragma once
#include<cmath>

class ByteConverter{
public:
	//先頭を下位バイトとしたbyte配列をintに変換する(byte配列の先頭と配列サイズを受け取る)
	static int Byte_to_Int(unsigned char* data,int size) {
		int result = 0;
		for (int i = 0; i < size; i++) {
			result += (int)data[i] * (int)std::pow(256,i);
		}
		return result;
	}
	//指定バイト数の最大値を返す
	static int ByteMaxSize(int size) {
		return (int)std::pow(256, size);
	}
	//指定バイト計算結果値をマイナス値に変換する(計算対象値とその値の元byte数を受け取る)
	static int ReverseNumber(int i,int size) {
		return -(ByteMaxSize(size) - i);
	}
};
