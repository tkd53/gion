#!/bin/sh
KkciIntStrfilename=$1
tblfilename=$2
linenum=`wc -l ${KkciIntStrfilename} | awk '{ print $1 }'`

echo "/* Copyright (c) 2016 Masahiko HASHIMOTO
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
" > ${tblfilename}

echo "#ifndef KKCIINTSTR_H" >> ${tblfilename}
echo "#define KKCIINTSTR_H" >> ${tblfilename}
echo "" >> ${tblfilename}

echo "#define KKCIINTSTR_SIZE (${linenum})" >> ${tblfilename}
echo "" >> ${tblfilename}

echo "const char KkciIntStr[KKCIINTSTR_SIZE][8] {" >> ${tblfilename}

while read line ; do
  echo "  {\"${line}\"}," >> ${tblfilename}
done < ${KkciIntStrfilename} 

echo "};" >> ${tblfilename}
echo "" >> ${tblfilename}

echo "#endif /* KKCIINTSTR_H */" >> ${tblfilename}
