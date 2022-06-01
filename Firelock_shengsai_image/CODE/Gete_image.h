
#ifndef CODE_GETE_IMAGE_H_
#define CODE_GETE_IMAGE_H_







#define Col               120           //图像宽度  范围1-752       RT102X RT105X RT106X 采集时列宽度必须为4的倍数
#define Row               60             //图像高度   范围1-480

#define black             0
#define white             1
extern uint8 Pixle[Row][Col];

void Get_Pixle(void);
#endif /* CODE_GETE_IMAGE_H_ */
