MACǩ������ʹ�����̣������н��棩

ʹ�÷�����

1.��MAC OS�д򿪡��նˡ���ʵ�ù���(shift+command+U)==>�նˣ�
2.����ǩ������Ŀ¼�£�ͨ��perl�����м�������ɶ�apk����ǩ���������������£�

example: perl signer-mac.pl -k test.keystore -p1 12341234 -a test.keystore -p2 12341234 -s ./apk_unsign -d ./apk_sign

-k  : keystore��·��
-p1 : storepass����
-a  : ǩ���ļ��ı���
-p2 : keystore����
-s  : ��ǩ��apk��·�� �� ��ǩ��apk����Ŀ¼��֧�ֶԸ�Ŀ¼������apk����ǩ����
-d  : ���ɵ�ǩ�����Ŀ¼
