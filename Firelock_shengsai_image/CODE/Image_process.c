
#include "FIRELOCK.h"


//存左右中边线数组 1-118
int leftline[Row];
int midline[Row];
int rightline[Row];
//存储标志 2可信 1不一定可信 0丢线
uint8 leftlineflag[Row];
uint8 rightlineflag[Row];
//截止行 55-0
uint8 endline=0;

uint8 endline_chu_hang_min=60;

//真实赛道宽度
uint8 track_width[Row]={
                        0X05 ,0X06 ,0X07 ,0X08 ,0X09 ,0X0A ,0X0B ,0X0C ,0X0D ,0X0E ,
                        0X11 ,0X13 ,0X14 ,0X16 ,0X18 ,0X1A ,0X1C ,0X1E ,0X20 ,0X21 ,
                        0X24 ,0X26 ,0X27 ,0X29 ,0X2B ,0X2D ,0X2F ,0X30 ,0X32 ,0X34 ,
                        0X36 ,0X38 ,0X3A ,0X3C ,0X3D ,0X3F ,0X41 ,0X44 ,0X46 ,0X48 ,
                        0X4A ,0X4B ,0X4D ,0X4F ,0X51 ,0X53 ,0X55 ,0X57 ,0X5A ,0X5A ,
                        0X5D ,0X5F ,0X61 ,0X62 ,0X64 ,0X66 ,0X67 ,0X69 ,0X6B ,0X6B
                        };



//0X12, 0X12, 0X13, 0X14, 0X15, 0X16, 0X17, 0X18, 0X19, 0X1A,
//0X1B, 0X1E, 0X1F, 0X21, 0X29, 0X26, 0X26, 0X28, 0X2A, 0X2C,
//0X2E, 0X30, 0X32, 0X34, 0X36, 0X38, 0X3A, 0X3C, 0X3E, 0X40,
//0X41, 0X43, 0X45, 0X47, 0X49, 0X4B, 0X4D, 0X4E, 0X50, 0X52,
//0X54, 0X56, 0X57, 0X59, 0X5B, 0X5D, 0X5F, 0X61, 0X63, 0X65,
//0X67, 0X69, 0X6B, 0X6D, 0X6F, 0X70, 0X71, 0X72, 0X74, 0X74,

//0X0E, 0X0F, 0X10, 0X11, 0X12, 0X13, 0X14, 0X16, 0X18, 0X1A
//,0X1C, 0X1E, 0X20, 0X22, 0X24, 0X27, 0X28, 0X2A, 0X2C, 0X2E
//,0X30, 0X31, 0X32, 0X34, 0X36, 0X38, 0X3A, 0X3B, 0X3D, 0X3F
//,0X41, 0X43, 0X45, 0X47, 0X49, 0X4B, 0X4D, 0X4F, 0X51, 0X53
//,0X55, 0X57, 0X59, 0X5A, 0X5B, 0X5D, 0X5F, 0X61, 0X63, 0X65
//,0X67, 0X69, 0X6B, 0X6D, 0X6F, 0X70, 0X72, 0X73, 0X75, 0X75

//0X14,0X16,0X18,0X1A,0X1B,0X1D,0X1E,0X20,0X21,0X24
//,0X25,0X27,0X29,0X2B,0X2D,0X2E,0X30,0X32,0X34,0X37
//,0X38,0X3B,0X3C,0X3E,0X3F,0X41,0X43,0X45,0X47,0X48
//,0X4A,0X4B,0X4D,0X4F,0X50,0X52,0X54,0X56,0X58,0X5A
//,0X5B,0X5C,0X5E,0X60,0X62,0X64,0X66,0X67,0X69,0X6B
//,0X6D,0X6F,0X71,0X73,0X73,0X74,0X75,0X75,0X75,0X75


uint8 ramp_cnt=0;
uint8 rampflag=0;
uint8 ramp_time=0;
int ramp_B_L=0,ramp_B_R=0;


#define ramptime 50

//拟合的赛道宽度
#define Width_P_W_L 1.35  //1.2
#define Width_P_W_R  1.35  //1.2
#define Width_P_Z  1//1
#define Width_P_R_L  1.5  //1.25
#define Width_P_R_R  1.5//1.25

int scratch_allfind=0;
uint8 scratchflag=0;

uint8 start_coner=0;
uint8 sanchaflag=0;
uint8 xuanzhuan=0;
uint8 ruku_hang=0;

uint8 BlackEndMR      = 0;
uint8 BlackEndML      = 0;
uint8 BlackEndLL      = 0;
uint8 BlackEndRR      = 0;
uint8 BlackEndL       = 0;
uint8 BlackEndM       = 0;
uint8 BlackEndR       = 0;
uint8 BlackEndMaxMax  = 0;
uint8 BlackEndMax     = 0;
uint8 DropRow         = 0;

extern int SZ_xie_L_Flag;
extern int SZ_xie_R_Flag;
extern uint8 sancha_en;
extern uint8 EB;
uint8 stop_flag=0;
uint8 Go_L_or_R=0;
extern uint8 cross_en;
uint8 endflag=0;
uint8 end_count=0;
uint8 endend_cnt=0;



//第一行图像寻线
//起跑线与其他图像寻线方式区别
void get_route_one(uint8 hang,uint8 start)
{
  //清零
  for(uint8 hang=0;hang<Row;hang++)
  {
    leftline[hang]=0;
    rightline[hang]=Col-1;
    leftlineflag[hang]=0;
    rightlineflag[hang]=0;
    midline[hang]=Col/2;
  }
  endline=0;
  //检测本行起跑线标志位
  int baihei=0;
  for(uint8 lie=0;lie<Col-1;lie++)
  {
    if(Pixle[hang][lie]==white&&Pixle[hang][lie+1]==black)
      baihei++;
  }
  //起跑线寻线
  if(baihei>3)
  {
    if(Pixle[hang][5]==white)
    {
      //向左找
      for(uint8 lie=5;lie>=1;lie--)
      {
        if(Pixle[hang][lie]==white&&Pixle[hang][lie-1]==black)
        {
            leftline[hang]=lie;
            leftlineflag[hang]=1;
            break;
        }
      }
    }
    else
    {
      //向右找
      for(uint8 lie=5;lie<=Col-2;lie++)
      {
        if(Pixle[hang][lie]==black&&Pixle[hang][lie+1]==white)
        {
            leftline[hang]=lie;
            leftlineflag[hang]=1;
            break;
        }
      }
    }
    //如果没找到，直接给定值
    if(leftlineflag[hang]==0)
    {
      leftline[hang]=1;
      leftlineflag[hang]=1;
    }
    //右边线
    if(Pixle[hang][Col-5]==white)
    {
      //向右找
      for(uint8 lie=Col-5;lie<=Col-2;lie++)
      {
        if(Pixle[hang][lie]==white&&Pixle[hang][lie+1]==black)
        {
            rightline[hang]=lie;
            rightlineflag[hang]=2;
            break;
        }
      }
    }
    else
    {
      //向左找
      for(uint8 lie=Col-5;lie>=1;lie--)
      {
        if(Pixle[hang][lie]==black&&Pixle[hang][lie-1]==white)
        {
            rightline[hang]=lie;
            rightlineflag[hang]=1;
            break;
        }
      }
    }
    //如果没找到，直接给定值
    if(rightlineflag[hang]==0)
    {
      rightline[hang]=Col-2;
      rightlineflag[hang]=2;
    }
  }
  else
  {
    //左边线
    if(Pixle[hang][start]==white)
    {
      //向左找
      for(uint8 lie=start;lie>=1;lie--)
      {
        if(Pixle[hang][lie]==white&&Pixle[hang][lie-1]==black)
        {
            leftline[hang]=lie;
            leftlineflag[hang]=2;
            break;
        }
      }
    }
    else
    {
      //向右找
      for(uint8 lie=start;lie<=Col-2;lie++)
      {
        if(Pixle[hang][lie]==black&&Pixle[hang][lie+1]==white)
        {
            leftline[hang]=lie;
            leftlineflag[hang]=1;
            break;
        }
      }
    }
    //如果没找到，直接给定值
    if(leftlineflag[hang]==0)
    {
      leftline[hang]=1;
      leftlineflag[hang]=2;
    }
    //右边线
    if(Pixle[hang][start]==white)
    {
      //向右找
      for(uint8 lie=start;lie<=Col-2;lie++)
      {
        if(Pixle[hang][lie]==white&&Pixle[hang][lie+1]==black)
        {
            rightline[hang]=lie;
            rightlineflag[hang]=2;
            break;
        }
      }
    }
    else
    {
      //向左找
      for(uint8 lie=start;lie>=1;lie--)
      {
        if(Pixle[hang][lie]==black&&Pixle[hang][lie-1]==white)
        {
            rightline[hang]=lie;
            rightlineflag[hang]=1;
            break;
        }
      }
    }
    //如果没找到，直接给定值
    if(rightlineflag[hang]==0)
    {
      rightline[hang]=Col-2;
      rightlineflag[hang]=2;
    }
    //如果左右边线都不绝对可信
    if(rightlineflag[hang]==1&&leftlineflag[hang]==1)
    {
      leftline[hang]=1;
      rightline[hang]=Col-2;
    }
    leftlineflag[hang]=1;
    rightlineflag[hang]=1;
  }
}
//跟踪寻线
void get_route_all(void)
{
  //初始化
  int Lstart=0,L_max=0,L_min=0;
  int Rstart=0,R_max=0,R_min=0;
  int range=10;
  for(uint8 hang=Row-2;hang>0;hang--)
  {
    //左边线
    //确定搜线范围
    //根据上一行确定本行寻线点
    if(leftlineflag[hang+1]==0)
    {
      L_max=Col-1;
      L_min=0;
      Lstart=Col*1/2-10;
    }
    else
    {
      L_max=leftline[hang+1]+range;
      L_min=leftline[hang+1]-range;
      Lstart=leftline[hang+1];
      if(L_max>Col-1)
        L_max=Col-1;
      if(L_min<0)
        L_min=0;
    }
    //左边线
    if(Pixle[hang][Lstart]==black)
    {
      //向右找
      for(uint8 lie=Lstart;lie<L_max;lie++)
      {
        if(Pixle[hang][lie]==black&&Pixle[hang][lie+1]==white)
        {
            leftline[hang]=lie;
            leftlineflag[hang]=1;
            break;
        }
      }
      //如果还没找到说明丢线
      if(leftlineflag[hang]==0)
      {
        leftline[hang]=Col-2;
      //  leftlineflag[hang]=0;
      }
    }
    else
    {
      //向左找
      for(uint8 lie=Lstart;lie>L_min;lie--)
      {
        if(Pixle[hang][lie]==white&&Pixle[hang][lie-1]==black)
        {
            leftline[hang]=lie;
            leftlineflag[hang]=1;
            break;
        }
      }
      //如果还没找到说明丢线
      if(leftlineflag[hang]==0)
      {
        leftline[hang]=1;
       // leftlineflag[hang]=0;
      }
    }


    //右边线
    //确定寻线范围
    if(rightlineflag[hang+1]==0)
    {
      Rstart=Col*1/2+10;
      R_max=Col-1;
      R_min=0;
    }
    else
    {
      Rstart=rightline[hang+1];
      R_max=rightline[hang+1]+range;
      R_min=rightline[hang+1]-range;
      if(R_max>Col-1)
        R_max=Col-1;
      if(R_min<0)
        R_min=0;
    }
    //右边线
    if(Pixle[hang][Rstart]==black)
    {
      //向左找
      for(uint8 lie=Rstart;lie>R_min;lie--)
      {
        if(Pixle[hang][lie]==black&&Pixle[hang][lie-1]==white)
        {
          rightline[hang]=lie;
          rightlineflag[hang]=1;
          break;
        }
      }
      //如果还没找到
      if(rightlineflag[hang]==0)
      {
        rightline[hang]=1;
       // rightlineflag[hang]=0;
      }
    }
    else
    {
      //向右找
      for(uint8 lie=Rstart;lie<R_max;lie++)
      {
        if(Pixle[hang][lie]==white&&Pixle[hang][lie+1]==black)
        {
          rightline[hang]=lie;
          rightlineflag[hang]=1;
          break;
        }
      }
      //如果还没找到
      if(rightlineflag[hang]==0)
      {
        rightline[hang]=Col-2;
       // rightlineflag[hang]=0;

      }
    //  oled_printf_int32(10,3,rightlineflag[40],3);
      if(rightline[hang]>=117) //这里有一个BUG没有解决，当右线没有找到时rightline应该是0，但是不知道为什么仍然是1，所以强制置零
      {
          rightlineflag[hang]=0;

      }
      if(leftline[hang]<=2)
      {
          leftlineflag[hang]=0;

      }
   //   oled_printf_int32(10,4,rightlineflag[40],3);
    }
  }



  //车最远一行按上一行补
  leftline[0]=leftline[1];
  leftlineflag[0]=leftlineflag[1];
  rightline[0]=rightline[1];
  rightlineflag[0]=rightlineflag[1];
}
//寻截止行
void get_route_endline(void)
{
  //截止行的判断需要消除折点，这里不破坏原来左右线数组
  int left_line[Row],right_line[Row];

  //复制
  for(uint8 hang=Row-1;hang>0;hang--)
  {
    left_line[hang]=leftline[hang];
    right_line[hang]=rightline[hang];
  }
  //消折点（突变点）
  for(uint8 hang=Row-3;hang>0;hang--)
  {
    int temp=0;
    //左
    if((left_line[hang+1]-left_line[hang])>0)
    {
        temp=left_line[hang+1];
        left_line[hang+1]=left_line[hang];
        left_line[hang]=temp;
    }
    //右
    if((right_line[hang]-right_line[hang+1])>0)
    {
        temp=right_line[hang+1];
        right_line[hang+1]=right_line[hang];
        right_line[hang]=temp;
    }
  }
  endline=DropRow;
  //截止行判断
  for(uint8 hang=Row-5;hang>endline;hang--)
  {
    //隔离赛道外的边线
    if((right_line[hang-1]<left_line[hang])
       ||(left_line[hang-1]>right_line[hang]))
    {
        endline=hang;
        break;
    }
  }

  if(DropRow<10&&BlackEndM>50)
    endline=DropRow;

  if(endline>48)    endline=48;

}
//拟合中线
void get_route_midline(void)
{

//    if(scratchflag == 1)
//      {
//        //右丢左不丢
//        for(uint8 hang=Row-1;hang<endline;hang++)
//        {
//            if((leftlineflag[hang]!=0)&&(rightlineflag[hang]==0))
//              {
//                leftline[hang]=rightline[hang]-Width_P_W_L*track_width[hang];
//
//              }
//        }
////          ruku_hang=30;
////          for(uint8 hang=Row-1;hang<5;hang--)
////          {
////              if(rightlineflag[hang]==0)
////              {
////                  ruku_hang=hang;break;
////              }
////          }
////          rightline[ruku_hang-10]=Col-1;
////          rightlineflag[ruku_hang-10]=1;
////          leftline[ruku_hang-10]=Col-10;
////          leftlineflag[ruku_hang-10]=1;
////          connect(ruku_hang+10, ruku_hang-10, leftline);
//
//
//      }

//    if(SZ_xie_L_Flag&&SZ_xie_R_Flag&&SZ_xie_L>20&&SZ_xie_R>20)
//    {
//        for(uint8 hang=(int)(SZ_xie_L+SZ_xie_R)+10;hang>endline-5;hang--)
//        {
//            leftline[hang]=1;leftlineflag[hang]=1;
//            rightline[hang]=Col-1;rightlineflag[hang]=1;
//        }
//    }
//    if(chu_cross_flag)
//    {
//        for(uint8 hang=endline+5;hang<endline-5;hang--)
//        {
//            leftline[hang]=1;leftlineflag[hang]=1;
//            rightline[hang]=Col-1;rightlineflag[hang]=1;
//        }
//    }

//    if(sanchaflag|chu_cross_flag)
//    {
//        for(uint8 hang=endline+5;hang>endline-5;hang--)
//            {
//                leftlineflag[hang]=0;
//                leftline[hang]=1;
//                rightlineflag[hang]=0;
//                rightline[hang]=Col-1;
//            }
//    }

    uint8 which_line;
    if(start_flag==0)
    {
        which_line=endline_chu_hang_min;

    }
    else {
        which_line=endline;
    }
    for(uint8 hang=55;hang>which_line;hang--)
    {
//      if(!SZ_xie_point&&!ru_cross_flag&&!chu_cross_flag&&!xie_cross_flag)
    if(!cross_en)
      {
       //   直道补线
              if(BlackEndM>=47)
              {
                //左丢又不丢
                if((leftlineflag[hang]==0)&&(rightlineflag[hang]!=0))
                {
                  leftline[hang]=rightline[hang]-Width_P_Z*track_width[hang]-5;

                }
                //右丢左不丢
                else if((leftlineflag[hang]!=0)&&(rightlineflag[hang]==0))
                {
                  rightline[hang]=leftline[hang]+Width_P_Z*track_width[hang]+5;

                }
              //  全丢
                else  if((leftlineflag[hang]==0)&&(rightlineflag[hang]==0))
                  {
                    rightline[hang]=Col-2;
                    leftline[hang]=1;

                  }
                  //全不丢
                }
                else if(ringflag==4||ringflag==3)
                {
                  //左丢又不丢
                  if((leftlineflag[hang]==0)&&(rightlineflag[hang]!=0))
                  {
                     leftline[hang]=rightline[hang]-Width_P_R_R*track_width[hang];
                  }
                  //右丢左不丢
                  else if((leftlineflag[hang]!=0)&&(rightlineflag[hang]==0))
                  {
                    rightline[hang]=leftline[hang]+Width_P_R_R*track_width[hang];

                  }
               //   全丢
                  else if((leftlineflag[hang]==0)&&(rightlineflag[hang]==0))
                  {
                    rightline[hang]=Col-2;
                    leftline[hang]=1;

                  }

                }
                else
                {
                  //左丢又不丢
                  if((leftlineflag[hang]==0)&&(rightlineflag[hang]!=0))
                  {
                     leftline[hang]=rightline[hang]-Width_P_W_L*track_width[hang];
                  }
                  //右丢左不丢
                  else if((leftlineflag[hang]!=0)&&(rightlineflag[hang]==0))
                  {
                    rightline[hang]=leftline[hang]+Width_P_W_R*track_width[hang];

                  }
                   //全
                  else if((leftlineflag[hang]==0)&&(rightlineflag[hang]==0))
                  {
                    rightline[hang]=Col-2;
                    leftline[hang]=1;

                  }
                }
      }



//     if(chu_cross_flag==1&&rightlineflag[hang]==0)
//     {
//         if(rightline[hang]-leftline[hang]<10)
//         {
//             leftlineflag[hang]=0;
//             leftline[hang]=1;
//         }
//     }


    midline[hang]=(leftline[hang]+rightline[hang])/2;
  }
//  oled_printf_int32(10,0,rightline[40],3);
//  oled_printf_int32(10,1,rightlineflag[40],3);
//  oled_printf_int32(50,0,midline[40],3);
//  oled_printf_int32(90,0,leftline[40],3);
//  oled_printf_int32(90,1,Width_P_W_R*track_width[40],3);
}

//取最大值
int max(int a,int b)
{
  return a>b?a:b;
}
//提取图像的特征
//选取几列，从图像底部往上扫描
void GetBlackEndParam(void)//获取黑线截止行
{

  unsigned char LEndFlag  = 0;//标志位
  unsigned char MEndFlag  = 0;
  unsigned char REndFlag  = 0;
  unsigned char MREndFlag = 0;
  unsigned char MLEndFlag = 0;
  unsigned char LLEndFlag = 0;
  unsigned char RREndFlag = 0;

  int i=0;

  BlackEndMR=0;//清零
  BlackEndML=0;
  BlackEndLL=0;
  BlackEndRR=0;
  BlackEndL=0;
  BlackEndM=0;
  BlackEndR=0;

  for (i=Row-1;i>0;i--)
  {
    if(Pixle[i][60] == white && !MEndFlag )//
        {
        BlackEndM++;//中黑线截至行
        }
    else if(i > 1 && Pixle[i-1][60] == black && Pixle[i-2][Col/2] == black)//连续两行是黑色
        {
        MEndFlag = 1;
        }
    if(Pixle[i][30] == white && !LEndFlag )
        {
        BlackEndL++;//左黑线截至行
        }
    else if(i > 1 && Pixle[i-1][30] == black && Pixle[i-2][Col/4] == black)
        {
        LEndFlag = 1;
        }
    if(Pixle[i][90] == white && !REndFlag )
        {
        BlackEndR++;//右黑线截至行
    }
    else if(i > 1 && Pixle[i-1][90] == black && Pixle[i-2][Col*3/4] == black)
        {
        REndFlag = 1;
        }
    if(Pixle[i][45] == white && !MLEndFlag )
        {
        BlackEndML++;
        }
    else if(i > 1 && Pixle[i-1][45] == black && Pixle[i-2][45] == black)
        {
        MLEndFlag = 1;
        }
    if(Pixle[i][75] == white && !MREndFlag )
        {
        BlackEndMR++;
        }
    else if(i > 1 && Pixle[i-1][75] == black && Pixle[i-2][75] == black)
        {
        MREndFlag = 1;
    }
        if(Pixle[i][5] == white && !LLEndFlag )
        {
        BlackEndLL++;
    }
    else if(i > 1 && Pixle[i-1][5] == black && Pixle[i-2][5] == black)
        {
        LLEndFlag = 1;
    }
        if(Pixle[i][115] == white && !RREndFlag )
        {
        BlackEndRR++;
    }
    else if(i > 1 && Pixle[i-1][115] == black && Pixle[i-2][115] == black)
        {
        RREndFlag = 1;
    }
   }

//  if(BlackEndM<15) BlackEndM=15;

        BlackEndMax =max(BlackEndL,BlackEndM);//取大值
        BlackEndMax =max(BlackEndMax,BlackEndR);
        BlackEndMaxMax =max(BlackEndMax,BlackEndMR);
        BlackEndMaxMax =max(BlackEndMaxMax,BlackEndML);
        BlackEndMaxMax =max(BlackEndMaxMax,BlackEndLL);
        BlackEndMaxMax =max(BlackEndMaxMax,BlackEndRR);
        if(BlackEndMaxMax>60)
        {
            BlackEndMaxMax=58;
        }
        DropRow=60-BlackEndMaxMax;//封顶的行数

        if(DropRow>=55) DropRow=55;

        if(DropRow<=6) DropRow=6;

        /*******初始判断，冲出赛道停车******/
//         if(BlackEndMaxMax < 15)
//         {
//             ALL_flag=241;
//         }
//         else if(BlackEndMaxMax>=15&&!sancha_en&&!EB&&ALL_flag!=11)
//             ALL_flag=0;

         if(ALL_flag==10)   EB=0;

 }


void scratch_line(void)
{
    uint8 scratch_cnt;
  //起跑线跳变检测
//  for(uint8 hang=ring_xie_L;hang>DropRow+2;hang--)
//  {
//
//    if(Pixle[hang][leftline[ring_xie_L]/2]==black&&Pixle[hang-1][leftline[ring_xie_L]/2]==white)
//      ring_tiaobian++;
//    if(Pixle[hang][leftline[ring_xie_L]/2]==white&&Pixle[hang-1][leftline[ring_xie_L]/2]==black)
//      ring_tiaobian++;
//  }
  for(uint8 hang=55;hang>Pro_scratch(endline+26);hang--)//Pro_scratch(endline+24)//endline+20//斑马线只出现在直道，直道endline<10;在endline基础上加一个偏差值
  {
    scratch_cnt=0;
    for(uint8 lie=leftline[hang];lie<Col-20;lie++)
    {
        if(Pixle[hang][lie]==black&&Pixle[hang][lie+1]==white)
            scratch_cnt++;
        if(Pixle[hang][lie]==white&&Pixle[hang][lie+1]==black)
            scratch_cnt++;
    }
     if(scratch_cnt>=10)
     {
         scratchflag=1;
         break;
     }
     else scratchflag=0;

  }
  //判断起跑线

}

void start_line(void)
{
    uint8 chack_cnt=0;
    uint8 endline_chu_hang=0;
    uint8 white_left_di=0;
    uint8 white_right_di=0;

  // int aaa[7]={0};
    if(Go_L_or_R==0)
    {
        for(uint8 lie=110;lie<119;lie++)
        {
           for(uint8 hang=40;hang>1;hang--)
          {
             if(Pixle[hang][lie]==black)
             {
                 endline_chu_hang=hang;
               break;
             }
          }
           if(endline_chu_hang_min>endline_chu_hang)
           {
               endline_chu_hang_min=endline_chu_hang;
           }
        }
      //  aaa[0]=endline_chu_hang_min;

                leftline[Row-1]=1;
                leftline[endline_chu_hang_min]=50;


             connect(Row-1,endline_chu_hang_min,leftline);


             for(uint8 hang=Row-1;hang>1;hang--)
             {
                 if(leftlineflag[hang]!=0)
                 {
                     chack_cnt++;

                 }
                 leftlineflag[hang]=1;
                 rightlineflag[hang]=1;
                 rightline[hang]=119;

             }

    }
    else
    {
        for(uint8 lie=10;lie>0;lie--)
            {
               for(uint8 hang=40;hang>1;hang--)
              {
                 if(Pixle[hang][lie]==black)
                 {
                     endline_chu_hang=hang;
                   break;
                 }
              }
               if(endline_chu_hang_min>endline_chu_hang)
               {
                   endline_chu_hang_min=endline_chu_hang;
               }
            }
            //连线
             rightline[Row-1]=119;
             rightline[endline_chu_hang_min]=70;
             connect(Row-1,endline_chu_hang_min,rightline);

             for(uint8 hang=Row-1;hang>1;hang--)
             {
                 if(rightlineflag[hang]!=0)
                 {
                     chack_cnt++;

                 }
                 leftlineflag[hang]=1;
                  rightlineflag[hang]=1;
                  leftline[hang]=1;

             }

    }
    for(uint8 hang=45;hang>35;hang--)
    {
       for(uint8 lie=10;lie>0;lie--)
       {
         if(Pixle[hang][lie]==white)
             white_left_di++;
       }
       for(uint8 lie=110;lie<120;lie++)
       {
         if(Pixle[hang][lie]==white)
             white_right_di++;
       }
    }
   if(chack_cnt>30 )
   {
       if((white_left_di<10 && white_right_di>80)||(white_left_di>80 && white_right_di<10)||(white_left_di<20 && white_right_di<20))
       {

           start_flag = 1 ;//进入第一圈
       }

   }
//   aaa[0]=chack_cnt;
//   aaa[1]=white_left_di;
//   aaa[2]=white_right_di;
//   upper_send_data( aaa,7);

}

void stop_line(void)
{
    uint8 zuo_hang,zuo_lie,you_find_hang,you_find_lie,you_hang,you_lie;//右入库变量
    uint8 zuo_hang_l,zuo_lie_l,you_find_hang_l,you_find_lie_l,you_hang_l,you_lie_l;//左入库变量

    stop_flag=1;

    if(Go_L_or_R==0)
    {
        //右入库

            //寻找左下拐点情况1
            if(Pixle[Row-1][0]==black)
            {
                zuo_hang=Row-1;
                for(uint8 lie=0;lie<Col/2;lie++)
                {
                    if(Pixle[Row-1][lie]==white)
                    {
                        zuo_lie=lie;
                        break;
                    }
                }
            }
            //寻找左下拐点情况2
            else if(Pixle[Row-1][0]==white)
            {
                zuo_lie=0;
                for(uint8 hang=Row-1;hang>0;hang--)
                {
                    if(Pixle[hang][0]==black)
                    {
                        zuo_hang=hang;
                        break;
                    }
                }
            }

            //右拐点搜索位置确定
            for(uint8 hang=Row-4;hang>1;hang--)
            {
                if(Pixle[hang][Col-1]==white&&Pixle[hang-1][Col-1]==black)
                {
                    you_find_hang=hang;
                    break;
                }
            }


            you_lie=Col-1;              //默认右拐点位置
            you_hang=you_find_hang+2;//10///////////////////////////////////////////////////////////
            if(you_find_hang<30)    you_find_hang=30;
            if(you_find_hang>53)    you_find_hang=53;
            for(uint8 hang=you_find_hang;hang>you_find_hang-3;hang--)
            {
                for(uint8 lie=Col-1;lie>Col/2;lie--)
                {
                    if(Pixle[you_find_hang][lie]==white)
                    {
                        you_find_lie=lie;
                        break;
                    }
                }

                if(you_find_lie<you_lie)
                {
                    you_lie=you_find_lie;
                    you_hang=hang;
                }
                if(you_lie<Col/2+20)    you_lie=Col/2+20;
            }

            endline=you_hang;

            end_count=0;
            endend_cnt=0;
            for(uint8 hang=Row-10;hang>20;hang--)
            {
                if(Pixle[hang][Col-12]==white)  end_count++;
            }
            if(end_count<10)
            {
                endflag=1;
//                endend_cnt++;
            }
//            if(endend_cnt>2)
//            {
//                endflag=1;
//            }



            //拐点连线
            leftline[zuo_hang]=0;leftlineflag[zuo_hang]=1;
            if(endflag==0)
            {
                leftline[you_hang+5]=you_lie;leftlineflag[you_hang+5]=1;
            }
            else if(endflag==1)
            {
                leftline[you_hang+5]=5;leftlineflag[you_hang+5]=1;
            }
            connect(zuo_hang, you_hang+5, leftline);

        //    leftline[you_hang]=you_lie;leftlineflag[you_hang]=1;
        //    leftline[0]=Col-10;leftlineflag[0]=1;
        //    connect(you_hang, 0, leftline);


        //    rightline[zuo_hang]=Col-1;rightlineflag[zuo_hang]=1;
        //    rightline[you_hang]=Col-1;rightlineflag[zuo_hang]=1;
        //    connect(zuo_hang, you_hang, rightline);

            rightline[Row-1]=Col-1;rightlineflag[Row-1]=1;
            if(endflag==0)
            {
                rightline[you_hang]=Col-1;rightlineflag[you_hang]=1;
            }
            else if(endflag==1)
            {
                rightline[you_hang]=Col-5;rightlineflag[you_hang]=1;
            }
            connect(Row-1, you_hang, rightline);


            for(uint8 hang=you_hang;hang<zuo_hang;hang++)
            {
                midline[hang]=(leftline[hang]+rightline[hang])/2;
            }



    }
    else
    {
       //左入库

          //寻找右下拐点情况1
          if(Pixle[Row-1][Col-1]==black)
          {
              zuo_hang_l=Row-1;
              for(uint8 lie=Col-1;lie>Col/2;lie--)
              {
                  if(Pixle[Row-1][lie]==white)
                  {
                      zuo_lie_l=lie;
                      break;
                  }
              }
          }
          //寻找右下拐点情况2
          else if(Pixle[Row-1][Col-1]==white)
          {
              zuo_lie_l=Col-1;
              for(uint8 hang=Row-1;hang>0;hang--)
              {
                  if(Pixle[hang][Col-1]==black)
                  {
                      zuo_hang_l=hang;
                      break;
                  }
              }
          }

//          if(zuo_hang_l<30)    endflag=1;
//          if(endflag==1)
//          {
//              zuo_hang_l=Row-1;
//              zuo_lie_l=Col-1;
//          }
//          if(endflag==1&&zuo_hang_l>45)    endflag=2;

          //左拐点搜索位置确定
          for(uint8 hang=Row-4;hang>1;hang--)
          {
              if(Pixle[hang][0]==white&&Pixle[hang-2][0]==black)
              {
                  you_find_hang_l=hang;
                  break;
              }
          }


          you_lie_l=0;              //默认左拐点位置
          you_find_hang_l=Pro_value(you_find_hang_l-3);
          if(you_find_hang_l<15)    you_find_hang_l=15;
          if(you_find_hang_l>45 )    you_find_hang_l=45;
          for(uint8 hang=you_find_hang_l+2;hang>you_find_hang_l-5;hang--)
          {
              for(uint8 lie=0;lie<Col/2;lie++)
              {
                  if(Pixle[you_find_hang_l][lie]==white)
                  {
                      you_find_lie_l=lie;
                      break;
                  }
              }

              if(you_find_lie_l>you_lie_l)
              {
                  you_lie_l=you_find_lie_l;
                  you_hang_l=hang;
              }
              if(you_lie_l>Col/2-20)    you_lie_l=Col/2-20;
          }

          if(you_lie_l<0)      you_lie_l=0;

          endline=you_hang_l;

          end_count=0;
          endend_cnt=0;
          for(uint8 hang=Row-10;hang>20;hang--)
          {
              if(Pixle[hang][0]==white)  end_count++;
          }
          if(end_count<10)
          {
              endflag=1;
//              endend_cnt++;
          }
//          if(endend_cnt>5)
//          {
//              endflag=1;
//          }


          //拐点连线
//          if(!endflag)
//          {
              rightline[zuo_hang_l]=Col-1;rightlineflag[zuo_hang_l]=1;
              rightline[you_hang_l+5]=you_lie_l;rightlineflag[you_hang_l+5]=1;
              connect(zuo_hang_l, you_hang_l+5, rightline);
//          }



      //    leftline[you_hang]=you_lie;leftlineflag[you_hang]=1;
      //    leftline[0]=Col-10;leftlineflag[0]=1;
      //    connect(you_hang, 0, leftline);


      //    rightline[zuo_hang]=Col-1;rightlineflag[zuo_hang]=1;
      //    rightline[you_hang]=Col-1;rightlineflag[zuo_hang]=1;
      //    connect(zuo_hang, you_hang, rightline);

//          //阶段1可以先不连
          leftline[Row-1]=0;leftlineflag[Row-1]=1;
          if(endflag==0)
          {
              leftline[you_hang_l]=0;leftlineflag[you_hang_l]=1;
          }
          else if(endflag==1)
          {
              leftline[you_hang_l]=10;leftlineflag[you_hang_l]=1;
          }
          connect(Row-1, you_hang_l, leftline);


          for(uint8 hang=you_hang_l;hang<zuo_hang_l;hang++)
          {
              midline[hang]=(leftline[hang]+rightline[hang])/2;
          }


   }



}



//void stop_line(void)
//{
//    stop_flag=1;
//
//
//    //    uint8 cheku_flag=0;
//    //    if(start_flag == 3 &&scratchflag == 1)
//    //           {
//                   uint8 end_hang;
//    //               if(scratchflag == 1)
//    //               {
//                       for(uint8 hang=Row;hang>5;hang--)
//                       {
//                           if(rightlineflag[hang]==0)
//                           {
//                               end_hang=hang-5;
//                               break;
//                           }
//                       }
//    //                   end_hang-=15;
//    //                   if(end_hang<15)  end_hang=15;
//
//    //                   if(end_hang>35)
//    //                   {
//    //                       cheku_flag=1;
//                           for(uint8 hang=end_hang;hang<Row;hang++)
//                           {
//                               leftline[hang]=Col-hang;
//                               if(leftline[hang]<60)     leftline[hang]=60;
//                               leftlineflag[hang]=1;
//                               rightline[hang]=Col-1;
//                               rightlineflag[hang]=1;
//                           }
//    //                   }
//
//
//        //                   leftline[end_hang]=rightline[end_hang]-10;
//        //                   connect(Row-1, end_hang, leftline);
//
//    //               }
//
//
//    //           }
//
//
//
//
//
//
//
//
//}




uint8 ramp_find_flag=0;
uint8 ramp_find_last[5]={0};
uint8 ramp_find_lianx=0;
uint8 ramp_find_fff=0;
//坡道识别
void ramp_find_x(void)
{
    ramp_cnt=0;
     //直道
     if(endline<20)
     {
       for(uint8 hang=30;hang<40;hang++)
       {
         if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
          if(leftline[hang] >= leftline[hang+2]&&rightline[hang] <= rightline[hang+2]&&leftline[hang]>leftline[55]&&rightline[hang]<rightline[55])
          {
            //赛道变宽
            if(rightline[hang]-leftline[hang]>track_width[hang]+5)
              ramp_cnt++;
          }
       }
       //斜率变小
       ramp_B_L=regression(30,40,leftline);
       ramp_B_R=regression(30,40,rightline);


     }
   //  oled_printf_int32(80,4,ramp_cnt,3);
   //  oled_printf_int32(80,5,ramp_B_L,3);
   //  oled_printf_int32(80,6,ramp_B_R,3);
     if(ramp_cnt==10&&ramp_B_L<=0&&ramp_B_L>=-10&&ramp_B_R>=0&&ramp_B_R<=10&&Error<=75&&Error>=45)//
     {
         ramp_find_lianx=1;
     }
     else ramp_find_lianx=0;


}

//坡道识别
void ramp_find(void)
{
  //  int aaa[7]={0};
   ramp_find_x();
   if(ramp_find_flag==0||ramp_find_flag==2)
   {
       if(ramp_find_lianx==1)
       {
           ramp_find_flag++;
       }
   }
   if(ramp_find_flag==1||ramp_find_flag==3)
   {
       ramp_find_last[0]=ramp_find_last[1];
       ramp_find_last[1]=ramp_find_last[2];
       ramp_find_last[2]=ramp_find_lianx;
       if((ramp_find_last[2]+ramp_find_last[0]+ramp_find_last[1])==0)
       {
           ramp_find_flag++;
       }

   }
   if(ramp_find_flag==4)
   {
       ramp_find_flag=0;
       for(u8 ramp_i=0;ramp_i<5;ramp_i++)
       {
           ramp_find_last[ramp_i]=0;
       }
   }


   if(ramp_find_flag!=0)
   {
       rampflag=31;
   }
   else rampflag=0;


   if(ramp_find_flag!=2)
     ramp_time=0;
   if(ramp_find_flag==2)
   {
     ramp_time++;
     //保护措施
     if(ramp_time>=20)
     {
         ramp_find_flag=0;
         rampflag=0;
     }

   }

//   aaa[0]=rampflag;
//   aaa[1]=ramp_find_flag;
//   upper_send_data(aaa,7);

}

/**************************************
连线函数
start da
end xiao
**************************************/
void connect(uint8 hang_start,uint8 hang_end,int p[])
{
  float temp=0;
  if((hang_end>0)&&(hang_start>0)&&(hang_start<=Row-1)&&(hang_end<=Row-1))    //防止数组数量不足卡死
    if(hang_start>hang_end)
    {
      temp=(p[hang_end]-p[hang_start])*1.0/(hang_end-hang_start);
      for(uint8 hang=hang_start;hang>hang_end-1;hang--)
        p[hang]=(int)(p[hang_start]-temp*(hang_start-hang));
    }
}
/**************************************
线性回归方程计算斜率
startline小
endline大
**************************************/
int regression(uint8 startline,uint8 endline,int p[])
{
  int i,B;
  int sumX=0,sumY=0,avrX=0,avrY=0 ;
  int num=0,B_up1=0,B_up2=0,B_up,B_down;
   for(i=startline;i<=endline;i++)
   {
            num++;
            sumX+=i;
            sumY+=p[i];
   }
   avrX=sumX/num;
   avrY=sumY/num;
   B_up=0;
   B_down=0;
   for(i=startline;i<=endline;i++)
   {
     B_up1=(p[i]-avrY);
     B_up2=i-avrX;
     B_up+=10*(B_up1*B_up2);
     B_up=B_up/100*100;
     B_down+=10*(i-avrX)*(i-avrX);
   }
   if(B_down==0)
    B=0;
   else
    B=B_up*25/B_down;
   return B;
}
