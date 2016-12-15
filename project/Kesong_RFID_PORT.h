#ifndef __Kesong_RFID_PORT_H__
#define __Kesong_RFID_PORT_H__

#include<string>
using namespace std;

/*
 *定义常量名称，以供外部接口调用
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
 *将0传给rfid_reader_init函数，对设备进行初始化，初始化成功返回1，否则返回0；
 *reader_id没有使用，但是作为参数予以保留，以下各函数皆同；
 * 如果需要控制多个读写器，可以通过reader_id控制对应的设备，此处默认为0；
 *所有对读写器操作（inventory、read、write等）之前必须先初始化设备。
 */
Kesong_RFID_PORT_API int rfid_reader_init(int reader_id);

/*
 *将0传给rfid_reader_deinit函数，对设备进行卸载关闭，卸载成功返回1，否则返回0；
 *卸载成功后，如果需要再次使用读写器，则调用rfid_reader_init；
 *使用完读写器后，调用此函数以便释放资源。
 */
Kesong_RFID_PORT_API int rfid_reader_deinit(int reader_id);

/*
 *执行inventoryOnce操作，显示读写器周围标签信息（EPC区的全部或部分），执行成功返回标签数，否则返回-1；
 *length是需要显示的标签信息的长度，最大是32，此时标签信息全部显示；
 *buffer[][33]是上层调用程序传入的二维数组以保存并显示EPC信息，默认列长为33；
 */
Kesong_RFID_PORT_API int rfid_reader_inventoryOnce(int reader_id,int length, char buffer[][33]);

/*
 *执行tag lock操作，此处固定为对USER区数据设置访问权限，设置成功返回1，否则返回-1；
 *password是设置权限时所需的密码，密码事先使用writeTag函数写入RESERVED区中“Access”Password存储区中；
 *userpermission是枚举参量，对应设置权限等级，分别为：
 *RFID_18K6C_TAG_MEM_PERM_WRITEABLE                            （0，可写，无需访问密码）；
 *RFID_18K6C_TAG_MEM_PERM_ALWAYS_WRITEABLE             （1，永久可写，此权限是永久性，设置完不可恢复）；
 *RFID_18K6C_TAG_MEM_PERM_SECURED_WRITEABLE            （2，口令可写，对USER区写入数据时需访问密码）；
 *RFID_18K6C_TAG_MEM_PERM_ALWAYS_NOT_WRITEABLE     （3，永久不可写，同样设置完不可恢复）；
 *RFID_18K6C_TAG_MEM_PERM_NO_CHANGE                          （4，保持权限不变）；
 *程序调用时输入0,1,2...即可，注意慎用1,3不可恢复操作，否则标签永远无法更新USER区数据；
 */
Kesong_RFID_PORT_API int rfid_reader_lock(int reader_id,const char* password,RFID_18K6C_TAG_MEM_PERM userpermission);

/*
 *读取离读写器最近的标签信息，读取成功返回1，否则返回-1；
 *databuffer是调用程序传入的数组，建议数组长度为1025，offset是相对于存储区偏移量，单位是16bit，count是读取数据个数，单位是16bit;
 *例如USER区的数据是“E29464F44532...”offset设为1，count设为2，则读出的数据就是64F44532；
 *bankchoice是指定读取的存储区，此为枚举参量，分别为：
 * RFID_18K6C_MEMORY_BANK_RESERVED                     （0，RESERVED区）
 * RFID_18K6C_MEMORY_BANK_EPC                                （1，EPC区）
 * RFID_18K6C_MEMORY_BANK_TID                                 （2，TID区）
 * RFID_18K6C_MEMORY_BANK_USER                              （3，USER区）
 */
Kesong_RFID_PORT_API int rfid_reader_readTag(int reader_id,char*databuffer,INT16U offset,INT16U count,RFID_18K6C_MEMORY_BANK bankchoice);

/*
 *向离读写器最近的标签写入信息，写入成功返回1，否则返回-1；
 *data是将写入标签的字符串信息，注意应该字符串中字符都是16进制数字符；
 *offset，count，bankchoice同rfid_reader_readTag中的定义，只不过一个是读出一个是写入；
 *如果该标签设置访问权限，此处还得附加密码password，如果没有权限，密码请默认设置为“00000000”；
 */
Kesong_RFID_PORT_API int rfid_reader_writeTag(int reader_id,string data,INT16U offset,INT16U count,RFID_18K6C_MEMORY_BANK bankchoice,string password);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /*__Kesong_RFID_PORT_H__*/
