# gion
TKD53/Lime用クライアントライブラリ  

簡単な使い方は sample/sample.cc をご確認ください。 

## ビルド方法

Cmake を利用します。  

$ mkdir build  
$ cd build  
$ cmake ..  
$ make  

## サーバーとの接続方法

gion は TKD53/Limeサーバーと Unixドメインソケットで接続します。  
TKD53/Limeサーバー側は、 src/server/ 内で make を行い、 bin/unix_domain_socket を起動してください。  


