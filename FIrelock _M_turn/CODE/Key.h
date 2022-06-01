#ifndef __KEY_H__
#define __KEY_H__


//�����Ƕ��尴����ʱ�䣬��λΪ �� 10ms���ж�ʱ�䣩
#define KEY_DOWN_TIME           1       //����ȷ�ϰ���ʱ��
#define KEY_HOLD_TIME           9     //����holdȷ��ʱ�䣬���253��������Ҫ�޸� keytime ������
                                        //�������һֱ����ȥ����ÿ�� KEY_HOLD_TIME - KEY_DOWN_TIME ʱ��ᷢ��һ�� KEY_HOLD ��Ϣ

//���尴����ϢFIFO��С
#define KEY_MSG_FIFO_SIZE       20      //��� 255��������Ҫ�޸�key_msg_front/key_msg_rear����


//�����˿ڵ�ö��
typedef enum
{
    KEY_U,  //��
    KEY_D,  //��
    KEY_L,  //��
    KEY_R,  //��
    KEY_P,  //����
    KEY_1,  //1
    KEY_MAX,
} KEY_e;


//key״̬ö�ٶ���
typedef enum
{
    KEY_DOWN  =   0,         //��������ʱ��Ӧ��ƽ
    KEY_UP    =   1,         //��������ʱ��Ӧ��ƽ

    KEY_HOLD,               //��������(���ڶ�ʱ����ɨ��)

} KEY_STATUS_e;


//������Ϣ�ṹ��
typedef struct
{
    KEY_e           key;        //�������
    KEY_STATUS_e    status;     //����״̬
} KEY_MSG_t;


extern void            key_init(KEY_e key);            // KEY��ʼ������(key С�� KEY_MAX ʱ��ʼ�� ��Ӧ�˿ڣ������ʼ��ȫ���˿�)
extern KEY_STATUS_e    key_get(KEY_e key);             //���key״̬��������ʱ������
extern KEY_STATUS_e    key_check(KEY_e key);           //���key״̬������ʱ������

//��ʱɨ�谴��
extern uint8   get_key_msg(KEY_MSG_t *keymsg);         //��ȡ������Ϣ������1��ʾ�а�����Ϣ��0Ϊ�ް�����Ϣ
extern void    key_IRQHandler(void);                   //��Ҫ��ʱɨ����жϷ���������ʱʱ��Ϊ10ms��

uint8 key_scan(void);
#endif  //_KEY_H__
