/* Copyright (c) 2016 Masahiko HASHIMOTO
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include <iostream>
#include "gion.hh"

using namespace gion;


void output(Conv *convobj, char *instr)
{
	const char *retstr;
	
	retstr = convobj->Convert(instr);
	if (retstr != NULL)
		std::cout << retstr << std::endl;
	else
		std::cout << "Conv Faild!!" << std::endl;
}


int main(int argc, char *argv[])
{
	Conv conv;
	char instr[1024];
	
	// gionlib Open
	conv.Open();
	
	if (argc == 1) {
		while(1) {
			// 入力待ち
			std::cout << "> ";
			std::cin >> instr;		
			if (instr[0] == 'q')
				break;
			
			// 入力されたひらがなを変換
			output(&conv, instr);
		}
	}
	else {
		// 引数のひらがなを変換
		output(&conv, instr);
	}

	// gionlib close
	conv.Close();

	return(0);
}
