#ifndef __Kesong_RFID_PORT_H__
#define __Kesong_RFID_PORT_H__

#include<string>
using namespace std;

/*
 *���峣�����ƣ��Թ��ⲿ�ӿڵ���
 */
typedef unsigned __int8     INT8U;
typedef unsigned __int16    INT16U;
typedef unsigned __int32    INT32U;
typedef INT32U  RFID_18K6C_TAG_MEM_PERM;
typedef INT32U  RFID_18K6C_MEMORY_BANK;           

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#ifdef __Kesong_RFID_PORT
#define Kesong_RFID_PORT_API __declspec(dllexport)
#else
#define Kesong_RFID_PORT_API __declspec(dllimport)
#endif

/*
 *��0����rfid_reader_init���������豸���г�ʼ������ʼ���ɹ�����1�����򷵻�0��
 *reader_idû��ʹ�ã�������Ϊ�������Ա��������¸�������ͬ��
 * �����Ҫ���ƶ����д��������ͨ��reader_id���ƶ�Ӧ���豸���˴�Ĭ��Ϊ0��
 *���жԶ�д��������inventory��read��write�ȣ�֮ǰ�����ȳ�ʼ���豸��
 */
Kesong_RFID_PORT_API int rfid_reader_init(int reader_id);

/*
 *��0����rfid_reader_deinit���������豸����ж�عرգ�ж�سɹ�����1�����򷵻�0��
 *ж�سɹ��������Ҫ�ٴ�ʹ�ö�д���������rfid_reader_init��
 *ʹ�����д���󣬵��ô˺����Ա��ͷ���Դ��
 */
Kesong_RFID_PORT_API int rfid_reader_deinit(int reader_id);

/*
 *ִ��inventoryOnce��������ʾ��д����Χ��ǩ��Ϣ��EPC����ȫ���򲿷֣���ִ�гɹ����ر�ǩ�������򷵻�-1��
 *length����Ҫ��ʾ�ı�ǩ��Ϣ�ĳ��ȣ������32����ʱ��ǩ��Ϣȫ����ʾ��
 *buffer[][33]���ϲ���ó�����Ķ�ά�����Ա��沢��ʾEPC��Ϣ��Ĭ���г�Ϊ33��
 */
Kesong_RFID_PORT_API int rfid_reader_inventoryOnce(int reader_id,int length, char buffer[][33]);

/*
 *ִ��tag lock�������˴��̶�Ϊ��USER���������÷���Ȩ�ޣ����óɹ�����1�����򷵻�-1��
 *password������Ȩ��ʱ��������룬��������ʹ��writeTag����д��RESERVED���С�Access��Password�洢���У�
 *userpermission��ö�ٲ�������Ӧ����Ȩ�޵ȼ����ֱ�Ϊ��
 *RFID_18K6C_TAG_MEM_PERM_WRITEABLE                            ��0����д������������룩��
 *RFID_18K6C_TAG_MEM_PERM_ALWAYS_WRITEABLE             ��1�����ÿ�д����Ȩ���������ԣ������겻�ɻָ�����
 *RFID_18K6C_TAG_MEM_PERM_SECURED_WRITEABLE            ��2�������д����USER��д������ʱ��������룩��
 *RFID_18K6C_TAG_MEM_PERM_ALWAYS_NOT_WRITEABLE     ��3�����ò���д��ͬ�������겻�ɻָ�����
 *RFID_18K6C_TAG_MEM_PERM_NO_CHANGE                          ��4������Ȩ�޲��䣩��
 *�������ʱ����0,1,2...���ɣ�ע������1,3���ɻָ������������ǩ��Զ�޷�����USER�����ݣ�
 */
Kesong_RFID_PORT_API int rfid_reader_lock(int reader_id,const char* password,RFID_18K6C_TAG_MEM_PERM userpermission);

/*
 *��ȡ���д������ı�ǩ��Ϣ����ȡ�ɹ�����1�����򷵻�-1��
 *databuffer�ǵ��ó���������飬�������鳤��Ϊ1025��offset������ڴ洢��ƫ��������λ��16bit��count�Ƕ�ȡ���ݸ�������λ��16bit;
 *����USER���������ǡ�E29464F44532...��offset��Ϊ1��count��Ϊ2������������ݾ���64F44532��
 *bankchoice��ָ����ȡ�Ĵ洢������Ϊö�ٲ������ֱ�Ϊ��
 * RFID_18K6C_MEMORY_BANK_RESERVED                     ��0��RESERVED����
 * RFID_18K6C_MEMORY_BANK_EPC                                ��1��EPC����
 * RFID_18K6C_MEMORY_BANK_TID                                 ��2��TID����
 * RFID_18K6C_MEMORY_BANK_USER                              ��3��USER����
 */
Kesong_RFID_PORT_API int rfid_reader_readTag(int reader_id,char*databuffer,INT16U offset,INT16U count,RFID_18K6C_MEMORY_BANK bankchoice);

/*
 *�����д������ı�ǩд����Ϣ��д��ɹ�����1�����򷵻�-1��
 *data�ǽ�д���ǩ���ַ�����Ϣ��ע��Ӧ���ַ������ַ�����16�������ַ���
 *offset��count��bankchoiceͬrfid_reader_readTag�еĶ��壬ֻ����һ���Ƕ���һ����д�룻
 *����ñ�ǩ���÷���Ȩ�ޣ��˴����ø�������password�����û��Ȩ�ޣ�������Ĭ������Ϊ��00000000����
 */
Kesong_RFID_PORT_API int rfid_reader_writeTag(int reader_id,string data,INT16U offset,INT16U count,RFID_18K6C_MEMORY_BANK bankchoice,string password);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /*__Kesong_RFID_PORT_H__*/
