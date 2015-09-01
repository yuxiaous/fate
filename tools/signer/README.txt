MAC签名工具使用流程（命令行界面）

使用方法：

1.在MAC OS中打开“终端”（实用工具(shift+command+U)==>终端）
2.进入签名工具目录下，通过perl命令行及参数完成对apk包的签名，参数解析如下：

example: perl signer-mac.pl -k test.keystore -p1 12341234 -a test.keystore -p2 12341234 -s ./apk_unsign -d ./apk_sign

-k  : keystore的路径
-p1 : storepass密码
-a  : 签名文件的别名
-p2 : keystore密码
-s  : 待签名apk的路径 或 待签名apk所在目录（支持对该目录下所有apk批量签名）
-d  : 生成的签名后的目录
