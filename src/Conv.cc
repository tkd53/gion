/* Copyright (c) 2016 TKD53/Lime Project
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
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "config.hh"
#include "gion.hh"
#include "KkciIntStr.h"
#include "WordIntStr.h"
#include "picojson/picojson.h"

namespace gion {

Conv::Conv()
{
}

Conv::~Conv()
{
} 

int Conv::Open()
{
	int ret = GION_ERR;
	
	/* create socket */
	ret = CreateSock();
	if (ret == GION_ERR) {
		goto last;
	}
	
	/* dic create */
	/* 現状 WordIntStr.h を使用しているため辞書作成は行っていない */
	/* 規模が大きくなったら考える。。。 */
	
	ret = GION_OK;
last:
	return(ret);
}

void Conv::Close()
{
	close(fd);
}

int Conv::Convert(uint8_t *instr)
{
	int i = 0;
	int l = 0;
	int len = 0;
	int strsize = strlen((const char*)instr);
	std::stringstream ss;
	char rcvbuf[RECV_BUF_SIZE];
	
	/* JSON作成 */
	ss << "{\"command\":\"CONVERT\",\"kkciSequence\":[";
	while(i < strsize){
		/* UTF-8の文字コード1byte目から長さを判定 */
		if (instr[i] < 0x80)
			len = 1;
		else if(instr[i] < 0xE0)
			len = 2;
		else if(instr[i] < 0xF0)
			len = 3;
		else if(instr[i] < 0xF8)
			len = 4;
		else if(instr[i] < 0xFC)
			len = 5;
		else if(instr[i] < 0xFE)
			len = 6;
		else
			break;
		
		for (l = 0; l < KKCIINTSTR_SIZE; l++) {
			if (strncmp((const char*)(instr + i), (const char*)KkciIntStr[l], len) == 0) {
				ss << l;
				i += len;
				if (i != strsize)
					ss << ",";
				break;
			}
		}
	}
	ss << "]}";
	write(fd, ss.str().c_str(), RECV_BUF_SIZE);
	
	len = read(fd, rcvbuf, RECV_BUF_SIZE);
	if (len == 0) {
		perror("gion: receive");
		return(len);
	}
	
	picojson::value v;
	picojson::parse(v, rcvbuf);
	std::string err = picojson::get_last_error();
	if(!err.empty()) {
		perror("gion: json parse error");
		return(0);
	}
	picojson::object &obj = v.get<picojson::object>();
	picojson::array &kkci_seq = obj["kkciSequence"].get<picojson::array>();
	for (picojson::array::iterator it = kkci_seq.begin(); it != kkci_seq.end(); ++it) {
		picojson::object& tmpObject = it->get<picojson::object>();
		int tokenid = (int)tmpObject["token"].get<double>();
		convstr.append(WordIntStr[tokenid]);
	}
	
	return(len);
}

int Conv::CreateSock()
{
	struct sockaddr_un addr;
	int ret = GION_ERR;
	
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("gion: socket");
		goto last;
	}

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, GION_SOCKFD_PATH, strlen(GION_SOCKFD_PATH));
	
	if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0) {
		perror("gion: connect");
		goto last;
	}
	
	ret = GION_OK;
last:
	return(ret);
}

}

