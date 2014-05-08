/***************************************************************************/
// ������ϴ�豸������
// ģ�飺����ͷ�ļ�
// �ļ���parameter.h
// ���ߣ������D
// �汾��V0.02
// ���ڣ�2013��11��8��
// ���ܣ�����ͷ�ļ�
// оƬ��STC12C5A60S2
// ���룺Keil uVision3 V3.90
/***************************************************************************/

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

/***************************************************************************/
// ��������
/***************************************************************************/
enum RunMode {AutoMode, ManualMode}; //����ģʽ 0�Զ�ģʽ 1�ֶ�ģʽ

enum DisplayMode {MainDisplayMode, Setting, SettingSaved, PowerOffing, PowerOffed, PowerOnChecking}; //��ʾģʽ 0������ 1���� 2���óɹ�  3�°�����ڹػ�  4�°���ػ����  5������λģʽ

enum CisternStatus {Empty, InCounting, Ready}; //��״̬ 0���� 1���ڼ�ʱ 2����

enum ManipulatorStatus {Stop, GoEntrance, GoOutfall, GoUp, GoDown}; //��е��״̬  0ֹͣ 1�����ڷ���  2�����ڷ���  3����  4����

enum ManipulatorPosition {Top, Center,  Bottom}; //��е״̬(��ֱ����)  0�Ϸ� 1�м�λ��  2�·�

enum DrivingDirect {DStop, DGoEntrance, DGoOutfall}; //�г��˶����� 	0ֹͣ 1�����ڷ���  2�����ڷ��� 

struct Cistern  //�۽ṹ��
{
	enum CisternStatus cisternStatus;  //��״̬
	unsigned int settingTime;   //�۽�������ʱ��
	unsigned int currentTime;	//�۵�ǰ����ʱ��
	unsigned int perSettingTime;	//��������ʱ�䣨����ҳ��δ����ֵ��
	unsigned char isCurrentlSetting; //��ǰ�Ƿ�Ϊ����״̬ 0��������״̬  1������״̬
};

struct Manipulator //��е�۽ṹ��
{
	enum ManipulatorStatus manipulaterStatus; //��е��״̬
	enum ManipulatorPosition manipulatorPosition;
	unsigned char currentPosition; 	//��ǰλ�ã�x�ۣ� 
									//0������ 
									//1������һ�Ų�֮��
									//2��һ�Ų�
									//3��һ�Ų۶��Ų�֮��
									//4�����Ų�
									//5�����Ų����Ų�֮��
									//6�����Ų�
									//7�����Ų��ĺŲ�֮��
									//8���ĺŲ�
									//9���ĺŲ���Ų�֮��
									//10����Ų�
									//11����Ų����Ų�֮��
									//12�����Ų�
									//13�����Ų۳���֮��
									//14������
};

/***************************************************************************/
// ��������
/***************************************************************************/
extern void parameter_init();
extern unsigned char parameter_save();

extern enum RunMode runMode;
extern enum DisplayMode displayMode;
extern enum DrivingDirect drivingDirect; 
extern struct Cistern cistern[8];
extern struct Manipulator manipulator; 

extern unsigned char displayFlag;  //ˢ����ʾ��־λ  0��ˢ�� 1ˢ����ҳ�� 2ˢ�»�е�۶���ˢ��  3��λҺ������ʼ����ʾ
extern unsigned char MotorSpeedFlag;  //���ٱ�־λ	 0�����ٶ� 1������� 2�������
extern unsigned char TargetCisternNumber; //��е������Ŀ���λ

#endif
