
#include "FIRELOCK.h"



/******************************************************************************
圆环函数：
圆环识别 （稳定） 可能大圆环识别不了 或者识别不稳定 需要加强
入圆环 （稳定） 入圆环截止行 补线打角需优化
出圆环 （稳定） 出打角需优化

******************************************************************************/

uint8 slope_L=35,slope_R=35,r_cnt0=4,r_startU=28,r_startD=40,r_error=40;
int R_lost_cnt=0,L_lost_cnt=0,R_find_cnt=0,L_find_cnt=0,ALL_find_cnt=0;
int ring_start_L=Row-1,ring_start_R=Row-1,ring_end_L=Row-1,ring_end_R=Row-1,ring_xie_L=Row-1,ring_xie_R=Row-1;
int ring_start_L_Flag=0,ring_start_R_Flag=0,ring_end_L_Flag=0,ring_end_R_Flag=0,ring_xie_L_Flag=0,ring_xie_R_Flag=0;
int ring_cnt=0;
int ringflag=0;
int ring_tiaobian=0;
int ring_white=0,ring_white_di=0;
int ring_B_L=0,ring_B_R=0;
int smallbigflag=0;
int ring_previous=0;
int ring_time=0;


int ringstarttime=0;
void ring_start(void)
{
  if(ringflag==0)
    ringstarttime=0;
  if(ringflag==6)
  {
    ringstarttime++;
    ring_start_L=Row-1,ring_start_R=Row-1;
    //左起始点
    for(uint8 hang=hstart-2;hang>DropRow+2;hang--)
    {
      if(leftlineflag[hang]!=0&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]==0)
      {
        ring_start_L=hang;
        break;
      }
    }
    if(ringstarttime<=500)
    {
      if(ring_start_L>r_startU&&ring_start_L<r_startD)  //调接行数来控制打角  zuo  &&Error>45&&Error<75
      {
        ringflag=1;
      }
    }
    else
      ringflag=0;
  }
  if(ringflag==7)
  {
    ringstarttime++;
    ring_start_L=Row-1,ring_start_R=Row-1;
    //右起始点
    for(uint8 hang=hstart-2;hang>DropRow+2;hang--)
    {
      if(rightlineflag[hang]!=0&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]==0)
      {
        ring_start_R=hang;
        break;
      }
    }
    if(ringstarttime<=500)
    {
      if(ring_start_R> r_startU &&ring_start_R <r_startD )//  //调接行数来控制打角  you&&Error>38&&Error<72

      {
       // oled_printf_int32(90,1,1111,3);
        ringflag=2;
      }
    }
    else
        ringflag=0;//oled_printf_int32(90,1,0000,3);
  }
}
//圆环识别
void ring_find(void)
{
    R_lost_cnt=0,L_lost_cnt=0,ALL_find_cnt=0,R_find_cnt=0,L_find_cnt=0;
    ring_B_L=0,ring_B_R=0;
    ring_cnt=0;
    ring_start_L=Row-1,ring_start_R=Row-1,ring_end_L=Row-1,ring_end_R=Row-1,ring_xie_L=Row-1,ring_xie_R=Row-1;
    ring_start_L_Flag=0,ring_start_R_Flag=0,ring_end_L_Flag=0,ring_end_R_Flag=0,ring_xie_L_Flag=0,ring_xie_R_Flag=0;
    ring_tiaobian=0;
    ring_white=0,ring_white_di=0;
   // int aaa_test[7];
    int bbb_test[7]={0};

     //int aaaa=0;
  //左起始点
  for(uint8 hang=Row-2;hang>DropRow+2;hang--)
  {
    if(leftlineflag[hang]!=0&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]==0)
    {
      ring_start_L=hang;
      ring_start_L_Flag=1;
     // oled_printf_int32(65,1,ring_start_L,5);
      break;
    }
  }
  //左终点
  if(ring_start_L_Flag==1)
  {
    //左终点
    for(uint8 hang=ring_start_L;hang>DropRow;hang--)
    {
      if(leftlineflag[hang]==0&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]!=0)
      {
        ring_end_L=hang;
        ring_end_L_Flag=1;
       // oled_printf_int32(65,2,ring_end_L,5);

        break;
      }
    }
    //左斜点
    for(uint8 hang=Row-2;hang>ring_start_L;hang--)
    {
      if(leftlineflag[hang]!=0&&leftlineflag[hang-1]!=0)
       if(leftline[hang]-leftline[hang-1]>1)
       {
         ring_xie_L=hang;
         ring_xie_L_Flag=1;
        // oled_printf_int32(65,3,ring_xie_L,5);
         break;
       }
    }
  }
  //右起始点
  for(uint8 hang=Row-2;hang>DropRow+2;hang--)
  {
    if(rightlineflag[hang]!=0&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]==0)
    {
      ring_start_R=hang;
      ring_start_R_Flag=1;
      break;
    }
  }
  //右终点
  if(ring_start_R_Flag==1)
  {
    //右终点
    for(uint8 hang=ring_start_R;hang>DropRow;hang--)
    {
      if(rightlineflag[hang]==0&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]!=0)
      {
        ring_end_R=hang;
        ring_end_R_Flag=1;
        break;
      }
    }
    //右斜点
    for(uint8 hang=Row-2;hang>ring_start_R;hang--)
    {
      if(rightlineflag[hang]!=0&&rightlineflag[hang-1]!=0)
       if(rightline[hang-1]-rightline[hang]>1)
       {
         ring_xie_R=hang;
         ring_xie_R_Flag=1;
         break;
       }
    }
  }


//  oled_printf_int32(30,0,404,3);
  //左圆环 三点或者两点找到找到
  /*
       * 找丢线情况，正常情况应该左面丢线，右面不丢线
       * 防止斜入十字，去找右面的点，不应该出现白点
       * 防止小弯误判，向上找线，应该在一个合理的区间。小弯误判还要用到右线斜率，斜率不可过大。重要。
       * 找跳变点，黑白跳变，应该是两个
  */
  //左圆环 三点都找到
  if(ring_start_L_Flag==1&&ring_xie_L_Flag==1&&ring_start_R_Flag==0&&ring_end_R_Flag==0&&ring_xie_R_Flag==0&&DropRow<30&&Error>45&&Error<75)//
  {

      if(ring_end_L_Flag==1)//小圆环
      {
         // oled_printf_int32(92,5,1,2);
          //入口左右丢线 左全丢右全不丢
        for(uint8 hang=ring_start_L;hang>ring_end_L;hang--)
        {
          if(rightlineflag[hang]==0)//不应该出现的情况
            R_lost_cnt++;
          if(leftlineflag[hang]==1)
            L_find_cnt++;
          //最底行白点数较少 防止斜入十字误判
          for(uint8 lie=110;lie<Col-1;lie++)
          {
            if(Pixle[hang][lie]==white)//最右边不应该出现白线
              ring_white++;
          }
        }
        //截止行向上找全线 防止小弯误判
        for(uint8 hang=ring_end_L;hang>DropRow;hang--)
        {
          if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
            ALL_find_cnt++;
        }
      }
        else//大圆环
        {
        //入口左右丢线 左全丢右全不丢
           // oled_printf_int32(92,5,2,2);
            for(uint8 hang=ring_start_L;hang>ring_start_L-5;hang--)
            {
              if(rightlineflag[hang]==0)
                R_lost_cnt++;
              if(leftlineflag[hang]==1)
                L_find_cnt++;
              //最底行白点数较少 防止斜入十字误判
              for(uint8 lie=110;lie<Col-1;lie++)
              {
                if(Pixle[hang][lie]==white)
                  ring_white++;
              }
            }
            //截止行向上找全线 防止小弯误判
                for(uint8 hang=DropRow+10;hang>DropRow;hang--)
                {
                  if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
                    ALL_find_cnt++;
                }

         }
    //最底行白点数较少 防止斜入十字误判
    for(uint8 hang=35;hang>30;hang--)//最右边不应该出现白线
    {
      for(uint8 lie=110;lie<Col-1;lie++)
      {
        if(Pixle[hang][lie]==white)
          ring_white_di++;
      }
    }
    //找跳变 白黑黑白跳变 圆环第一特征
    for(uint8 hang=ring_xie_L;hang>DropRow;hang--)
    {
      if(Pixle[hang][leftline[ring_xie_L]/2]==black&&Pixle[hang-1][leftline[ring_xie_L]/2]==white)
        ring_tiaobian++;
      if(Pixle[hang][leftline[ring_xie_L]/2]==white&&Pixle[hang-1][leftline[ring_xie_L]/2]==black)
        ring_tiaobian++;
    }
//    oled_printf_int32(30,0,1,3);
//    int aaa_test[7];
//       aaa_test[0]=ring_tiaobian;
//       aaa_test[1]=R_lost_cnt;
//       aaa_test[2]=L_find_cnt;
//       aaa_test[3]=ring_white ;
//       aaa_test[4]=ring_white_di;
//       aaa_test[5]=ring_start_L-ring_end_L;
//       aaa_test[6]=ALL_find_cnt;
//       upper_send_data( aaa_test,7);
   // aaaa=2;
//             aaa_test[0]=ring_tiaobian;
//              aaa_test[1]=ring_start_L;
//
//              aaa_test[3]=ring_white_di;
//              aaa_test[4]=ALL_find_cnt;
    //进一步检测
    //判断条件找小环标志位
    if(ring_tiaobian>=2&& R_lost_cnt<=1&&L_find_cnt<=2
            &&ring_white<15&&ring_white_di<49
            &&ALL_find_cnt>=5)//&&ring_start_L-ring_end_L>=2
    {
      for(uint8 hang=ring_start_L;hang<ring_start_L+8;hang++)//向下找8行
      {
        if((leftline[hang]-leftline[hang+1])<0)//    "\"这个方向
          if((leftline[hang]-leftline[hang+1])<=(leftline[hang+1]-leftline[hang+2]))//差值逐渐增大
            ring_cnt++;
      }
      ring_B_R=regression(DropRow,Row-2,rightline);
//      aaa_test[5]=ring_cnt;
//             aaa_test[6]=ring_B_R;

      if(ring_cnt>=r_cnt0&&ring_B_R<slope_L)
      {
        ringflag=6;
      }

//      aaa_test[7]=ring_B_R;
//      aaa_test[8]=ring_cnt;
//      aaa_test[9]=ringflag;


    }
//    else{
////        aaa_test[3]=-1;
//        aaa_test[5]=-1;
//        aaa_test[6]=-1;
//    }


  }

//   bbb_test[0]=0;
////   bbb_test[1]=ring_end_L_Flag;
////   bbb_test[2]=ring_xie_L_Flag;
//   bbb_test[3]=ring_start_R_Flag;
//   bbb_test[4]=ring_xie_R_Flag;
//   bbb_test[5]=DropRow;
//   bbb_test[6]=Error;
  //右圆环
  if(ring_start_L_Flag==0&&ring_end_L_Flag==0&&ring_xie_L_Flag==0&&ring_start_R_Flag==1&&ring_xie_R_Flag==1&&DropRow<30&&Error>45&&Error<75)//
  {

      bbb_test[0]=1;
      if(ring_end_R_Flag==1)
      {
          //入口左右丢线 左全丢右全不丢
          for(uint8 hang=ring_start_R;hang>ring_end_R;hang--)
          {
            if(rightlineflag[hang]==1)
              R_find_cnt++;
            if(leftlineflag[hang]==0)
              L_lost_cnt++;
            for(uint8 lie=10;lie>0;lie--)
            {
              if(Pixle[hang][lie]==white)
                ring_white++;
            }
          }
          //截止行向上找全线 防止小弯误判
          for(uint8 hang=ring_end_R;hang>DropRow;hang--)
          {
            if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
              ALL_find_cnt++;
          }

      }
      else
      {                                            //是否是减五，以后再调
          for(uint8 hang=ring_start_R;hang>ring_start_R-5;hang--)
          {
            if(rightlineflag[hang]==1)
              R_find_cnt++;
            if(leftlineflag[hang]==0)
              L_lost_cnt++;
            for(uint8 lie=10;lie>0;lie--)
            {
              if(Pixle[hang][lie]==white)
                ring_white++;
            }
          }
          //截止行向上找全线 防止小弯误判
         for(uint8 hang=DropRow+10;hang>DropRow;hang--)
         {
           if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
             ALL_find_cnt++;
         }


      }

    //最底行白点数较少 防止斜入十字误判
    for(uint8 hang=35;hang>30;hang--)
    {
      for(uint8 lie=10;lie>0;lie--)
      {
        if(Pixle[hang][lie]==white)
          ring_white_di++;
      }
    }
    //找跳变 白黑黑白跳变 圆环第一特征
    for(uint8 hang=ring_xie_R;hang>DropRow;hang--)
    {
      if(Pixle[hang][(Col+rightline[ring_xie_R])/2]==black&&Pixle[hang-1][(Col+rightline[ring_xie_R])/2]==white)
        ring_tiaobian++;
      if(Pixle[hang][(Col+rightline[ring_xie_R])/2]==white&&Pixle[hang-1][(Col+rightline[ring_xie_R])/2]==black)
        ring_tiaobian++;
    }
   // aaaa=1;

//           aaa_test[0]=ring_tiaobian;
//           aaa_test[1]=ring_start_R;
//
//           aaa_test[3]=ring_white_di;
//           aaa_test[4]=ALL_find_cnt;


    bbb_test[3]=1;
    //判断条件找小环标志位
    if(ring_tiaobian>=2&&R_find_cnt<=1&&
            L_lost_cnt<=2&&ring_white<15&&ALL_find_cnt>=5&&ring_white_di<49)//
    {
      //  bbb_test[3]=2;
      for(uint8 hang=ring_start_R;hang<ring_start_R+8;hang++)
      {
        if((rightline[hang+1]-rightline[hang])<0)
          if((rightline[hang+1]-rightline[hang])<=(rightline[hang+2]-rightline[hang+1]))
            ring_cnt++;
      }
      ring_B_L=regression(DropRow,Row-2,leftline);
//       aaa_test[5]=ring_cnt;
//      bbb_test[4]=DropRow;
//      bbb_test[5]=Row-2;
//      bbb_test[6]=ring_B_L;
      if(ring_cnt>=r_cnt0&&ring_B_L>-slope_R)
      {
        ringflag=7;
      }
     // aaa_test[3]=1;

    }
    else{
//        bbb_test[4]=-1;
//        bbb_test[5]=-1;
//        bbb_test[6]=-1;
    }






  }
//  aaa_test[4]=ringflag;
//  if( aaaa==1 || aaaa==2)
// upper_send_data( bbb_test,7);
}

uint8 ring_R=Col-1,ring_L=Col-1;
uint8 xieflag=0;
u8 ring_hang_last=0;
//入圆环补线
void ring_ru(void)
{
  //左圆环
  if(ringflag==1)
  {
      ring_R=Col/2,ring_L=Col/2;
      ring_R=Col/2;
      ring_end_L=Row-1,ring_end_L_Flag=0;
    uint8 ring_hang_L[Col];
//    uint8 ru_bed_point=0; //默认合格，检查不合格的点
    xieflag=0;
    //找终点
    for(uint8 hang=Row-2;hang>endline+3;hang--)
    {
      if(leftlineflag[hang]==0&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]!=0)
      {
        ring_end_L=hang;
        ring_end_L_Flag=1;
        break;
      }
    }
    //截止行查找
    //找左边白点数
    int lost=0;
    for(uint8 hang=55;hang>45;hang--)  //找最底下10行，左线的丢线数
    {
      if(leftlineflag[hang]==0||leftline[hang]<5)
      {
        lost++;
      }
    }
    if(lost>=7)
    {
      //截止行标定 (可行度极高)
      for(uint8 hang=50;hang>endline;hang--)   //以第20列为截止行参考列
      {
        if(Pixle[hang][20]==black&&Pixle[hang+1][20]==black)
        {
          endline=hang+2;
          break;
        }
      }
    }
    else
    {
      //截止行标定 (可行度极高)
      for(uint8 hang=50;hang>endline;hang--)//以第45列为截止行参考列
      {
        if(Pixle[hang][45]==black&&Pixle[hang+1][45]==black)
        {
          endline=hang+2;
          break;
        }
      }
    }


    for(uint8 lie=119;lie>60;lie--)
    {
      for(uint8 hang=55;hang>endline;hang--)
      {
        if(Pixle[hang][lie]==black)
        {
          ring_hang_L[lie]=hang;
          break;
        }
        else
        {
            ring_hang_L[lie]=0;

        }
      }
    }
//    oled_printf_int32(60,3,ring_hang_L[118],3);
//    oled_printf_int32(60,4,ring_hang_L[117],3);
//    oled_printf_int32(60,5,ring_hang_L[116],3);
//    oled_printf_int32(60,6,ring_hang_L[115],3);
//    oled_printf_int32(60,7,ring_hang_L[114],3);
    for(uint8 lie=110;lie>60;lie--)
    {
      if(ring_hang_L[118]==0&&ring_hang_L[117]==0)
      {
        if(ring_hang_L[lie]!=0&&ring_hang_L[lie-1]!=0)
        {
          ring_L=lie;
//          oled_printf_int32(60,0,ring_L,3);

             break;
        }
      }

    }


     if(ring_L>90)
              ringflag=3;

    //连线
    rightline[endline]=(int)(90-endline*2);//90
    rightline[59]=119;
    connect(59,endline,rightline);
    for(uint8 hang=59;hang>endline;hang--)
    {
      rightlineflag[hang]=1;
      leftlineflag[hang]=1;
      leftline[hang]=0;


    }

  }
  //右圆环
  else if(ringflag==2)
  {
      ring_R=Col/2,ring_L=Col/2;
      ring_end_R=Row-1,ring_end_R_Flag=0;
     uint8 ring_hang_R[Col];
    xieflag=0;
    for(uint8 hang=Row-2;hang>endline+3;hang--)
    {
      if(rightlineflag[hang]==0&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]!=0)
      {
        ring_end_R=hang;
        ring_end_R_Flag=1;
        break;
      }
    }
    //截止行查找
    //找左边白点数
    int lost=0;
    for(uint8 hang=55;hang>45;hang--)
    {
      if(rightlineflag[hang]==0||rightline[hang]>Col-5)
      {
        lost++;
      }
    }
    if(lost>=7)
    {
      //截止行标定 (可行度极高)
      for(uint8 hang=50;hang>endline;hang--)
      {
        if(Pixle[hang][Col-20]==black&&Pixle[hang+1][Col-20]==black)
        {
          endline=hang+2;
          break;
        }
      }
    }
    else
    {
      //截止行标定 (可行度极高)
      for(uint8 hang=50;hang>endline;hang--)
      {
        if(Pixle[hang][Col-45]==black&&Pixle[hang+1][Col-45]==black)
        {
          endline=hang+2;
          break;
        }
      }
    }

    //找拐点清标志位
    //原始图像列扫描 局部不正确有些点没找到 以后优化
    for(uint8 lie=0;lie<60;lie++)
    {
      for(uint8 hang=55;hang>endline;hang--)
      {
        if(Pixle[hang][lie]==black)
        {
          ring_hang_R[lie]=hang;
          break;
        }
        else
          {
              ring_hang_R[lie]=0;
          }
      }

    }

    for(uint8 lie=10;lie<60;lie++)
    {
      if(ring_hang_R[2]==0&&ring_hang_R[3]==0)
        if(ring_hang_R[lie]!=0&&ring_hang_R[lie+1]!=0)
        {
          ring_R=lie;
           break;

        }
    }
    if(ring_R<30)
          ringflag=4;
    //连线
    leftline[endline]=(int)(30+endline*2);//30
    leftline[59]=0;
    connect(59,endline,leftline);
    for(uint8 hang=59;hang>endline;hang--)
    {
        leftlineflag[hang]=1;
        rightlineflag[hang]=1;
        rightline[hang]=Col-1;
    }


  }
}

void ring_chu(void)
{
     //  int aaa_test[9];

  //左圆环
  if(ringflag==3)
  {
      uint8 ring_xie_R=0;
      uint8 ring_chu_num=0;
      uint8 ring_end_L=Row-1;
      uint8 R_lost_cnt=0,ALL_find_cnt=0,L_find_cnt=0;
      uint8 ring_kong[Row]={0};
      ring_end_L_Flag=0;
    //右线右拐
    for(uint8 hang=Row-2;hang>endline+5;hang--)   //找到右边的那个斜点
    {
        if((rightline[hang-1]-rightline[hang]>1)&&rightlineflag[hang-1]==1&&rightlineflag[hang]==1)
        {
          ring_xie_R=hang;
          xieflag=1;
         //aaa_test[0]=hang;

          break;
        }
//          else{
//              aaa_test[0]=70;
//
//          }

    }
    //aaa_test[1]=xieflag;
    if((ring_xie_R==0||ring_xie_R>35)&&xieflag!=0) //对斜点的要求，
    {
        //aaa_test[2]=1;
      for(uint8 hang=Row-5;hang>endline;hang--)
      {
        for(uint8 lie=0;lie<Col;lie++)
        {
          if(Pixle[hang][lie]==white&&(leftline[hang]<5||leftlineflag[hang]==0)&&(rightline[hang]>Col-5||rightlineflag[hang]==0))
            ring_kong[hang]++; //这点为白色，所在行的左右两边都丢线
        }
        if(ring_kong[hang]>Col-10)//因为可能出现左下弯道，范围变宽一点
          ring_chu_num++;//这一行几乎全部为白色
      }

      if(ring_chu_num>5) //补线取决条件是全部为白色的行大于5
      {


        for(uint8 hang=Row-1;hang>endline;hang--)//直接确定左线和右线
        {
          leftline[hang]=0;
          rightline[hang]=75-endline;//110
          leftlineflag[hang]=1;
          rightlineflag[hang]=1;
        }
        xieflag=2;
      }
      else//当行数不再大于5时，此时更改ringflag
      {


        if(DropRow<30)
        {
          uint8 temp=0;
          for(uint8 hang=Row-2;hang>DropRow+2;hang--)
          {
            if(leftlineflag[hang+2]==0&&leftlineflag[hang+1]==0&&leftlineflag[hang]==0&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]!=0)
            {//找到左线最上面的一行

              ring_end_L=hang;
              ring_end_L_Flag=1;
//              aaa_test[3]=DropRow+2;
//              aaa_test[4]=ring_end_L;
              break;
            }
//            else {
//                aaa_test[4]=0;
//            }
          }

          for(uint8 hang=ring_end_L-1;hang>ring_end_L-6;hang--)//从下往上找五行，找的是左边 ring_end_L 上面的五行
          {
            if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
              ALL_find_cnt++;//寻找着五行中右边没有丢线的行数
          }
          if(ring_end_L>50) ring_end_L=50;
          temp=ring_end_L+6;//左边 ring_end_L 下面的第六行
          if(temp>60) temp=60;
          for(uint8 hang=ring_end_L+1;hang<temp;hang++)//从上往下找五行，找的是左边 ring_end_L 下面的五行
          {
            if(leftlineflag[hang]==1)//不应该出现的情况
              L_find_cnt++;
            if(rightlineflag[hang]==0)
              R_lost_cnt++;
          }
//          oled_printf_int32(80,0,L_find_cnt,3);
//          oled_printf_int32(80,1,R_lost_cnt,3);
//          oled_printf_int32(80,2,ALL_find_cnt,3);
//          aaa_test[5]=ALL_find_cnt;
//          aaa_test[6]=L_find_cnt;
//          aaa_test[7]=R_lost_cnt;
          if(L_find_cnt<=2&&R_lost_cnt<=2&&ALL_find_cnt>=3)//满足情况

          {

            if(xieflag==2)
            {
               // aaa_test[8]=1;
              ringflag=5;
            }

          }
          else//不满足情况
          {

            ring_cnt=0;
            int num=0;
            for(uint8 hang=50;hang>endline;hang--)
            {
              if(rightlineflag[hang]==0)
                num++;
            }

            for(uint8 hang=40;hang<50;hang++)
            {
              if((leftline[hang]-leftline[hang+1])<0)
               if((leftline[hang]-leftline[hang+1])<=(leftline[hang+1]-leftline[hang+2]))
                 ring_cnt++;
            }
            if(ring_cnt>=4&&num<=3&&xieflag==2)
            {
               // aaa_test[8]=2;
              ringflag=5;
            }
          }
        }
      }
    }
    else//找到斜点，但不符合要求时，补线
        //或者没有找到斜点，此时按普通弯道处理
    {
       // aaa_test[2]=2;

      if(xieflag==1)
      {
         // aaa_test[2]=3;

          for(uint8 hang=ring_xie_R+5;hang>endline;hang--)
          {
            rightline[hang]=rightline[ring_xie_R+5]-1.2*(ring_xie_R+5-hang);
            rightlineflag[hang]=1;
            leftlineflag[hang]=1;
            leftline[hang]=0;
          }
      }



    }
  //     if(aaa_test[2]==1)
  //  upper_send_data( aaa_test,9);
  }
  //右圆环
  else if(ringflag==4)
  {
      uint8 ring_xie_L=0;
      uint8 ring_chu_num=0;
      uint8 ring_end_R=Row-1;
      uint8 L_lost_cnt=0,ALL_find_cnt=0,R_find_cnt=0;
      uint8 ring_kong[Row]={0};
      ring_end_R_Flag=0;
    //左斜点
    for(uint8 hang=Row-2;hang>endline+1;hang--)
    {
      if(leftline[hang]-leftline[hang-1]>1)
        if(leftlineflag[hang]==1&&leftlineflag[hang-1]==1)
      {
        ring_xie_L=hang;
        xieflag=1;
        break;
      }
    }
    if((ring_xie_L==0||ring_xie_L>35)&&xieflag!=0)
    {
      for(uint8 hang=Row-5;hang>endline;hang--)
      {
        for(uint8 lie=0;lie<Col-1;lie++)
        {
          if(Pixle[hang][lie]==white&&(leftline[hang]<5||leftlineflag[hang]==0)&&(rightline[hang]>Col-5||rightlineflag[hang]==0))
            ring_kong[hang]++;
        }
        if(ring_kong[hang]>Col-5)
          ring_chu_num++;
      }
      if(ring_chu_num>5)
      {
        for(uint8 hang=Row-1;hang>endline;hang--)
        {
          leftline[hang]=45+endline;
          rightline[hang]=Col-1;
          leftlineflag[hang]=1;
          rightlineflag[hang]=1;
        }
        xieflag=2;
      }
      else
      {
        if(DropRow<30)//
        {
          int temp=0;
          for(uint8 hang=Row-2;hang>DropRow+2;hang--)
          {
            if(rightlineflag[hang]==0&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]!=0)
            {
              ring_end_R=hang;
              ring_end_R_Flag=1;
              break;
            }
          }
          for(uint8 hang=ring_end_R-1;hang>ring_end_R-6;hang--)
          {
            if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
              ALL_find_cnt++;
          }
          if(ring_end_R>50) ring_end_R=50;
          temp=ring_end_R+6;
          if(temp>60) temp=60;
          for(uint8 hang=ring_end_R+1;hang<temp;hang++)
          {
            if(leftlineflag[hang]==0)
              L_lost_cnt++;
            if(rightlineflag[hang]==1)
              R_find_cnt++;
          }
          if(L_lost_cnt<=2&&R_find_cnt<=2&&ALL_find_cnt>=3)
          {
            if(xieflag==2)
            {
              ringflag=5;

            }

          }
          else
          {
            ring_cnt=0;
            int num=0;
            for(uint8 hang=50;hang>endline;hang--)
            {
              if(leftlineflag[hang]==0)
                num++;
            }
            for(uint8 hang=40;hang<50;hang++)
            {
              if((rightline[hang+1]-rightline[hang])<0)
               if((rightline[hang+1]-rightline[hang])<=(rightline[hang+2]-rightline[hang+1]))
                 ring_cnt++;
            }
            if(ring_cnt>=4&&num<=3&&xieflag==2)
            {
              ringflag=5;

            }
          }
        }
      }
    }
    else
    {
      if(xieflag==1)
      {
          for(uint8 hang=ring_xie_L+5;hang>endline;hang--)
          {
            leftline[hang]=leftline[ring_xie_L+5]+1.2*(ring_xie_L+5-hang);
            rightlineflag[hang]=1;
            leftlineflag[hang]=1;
            rightline[hang]=Col-1;
          }
      }

    }
  }
  if(ringflag==5)
  {
    ring_time++;
    if(ring_time>25)
    {
      ringflag=0;
      ring_time=0;
    }
  }
}










