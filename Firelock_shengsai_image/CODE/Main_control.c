#include "FIRELOCK.h"
int Track_Line_Time=0;
int Track_Line_Num=0;
uint8 Foresight=0;
int Foresight_hang=0;
int cutroute_time=0;
u8 endline_Foresight=5;
u8 Foresight_up=31;//28
uint8 ALL_flag=0;
uint8 start_flag=0;
uint8 en_start_flag=0;
uint8 end_flag=0;
uint8 EA=1;
uint8 EB=0;
extern uint8 sancha_static;
extern uint8 SC_flag;
extern uint8 Go_L_or_R;
extern uint8 banmaxian_flag;
extern uint8 BlackEndMR;
extern uint8 BlackEndML;
extern uint8 BlackEndLL;
extern uint8 BlackEndRR;
uint8 black_count=0;
uint8 black_cntcnt=0;
uint8 en_cnt=0;
uint8 turn_flag=0;

/**********************************************
加权平均
***********************************************/
//正常加权
u8 Weight[60]={
                     0,0,0,0,0,0,0,0,0,0,           //0-9行，基本用不到

                     0,0,0,0,0,0,0,0,0,0,            //0-19行，基本用不到

                     5,5,8,7,8,9,8,8,9,9,        //20-29行

                     6,7,7,6,5,4,4,5,5,4,            //30-39行

                     2,2,2,2,2,1,1,1,1,1,           //40-49行

                     0,0,0,0,0,0,0,0,0,0,           //最近十行

                  };
//十字加权
u8 CrossWeight[60]={

                     0,0,0,0,0,0,0,0,0,0,           //0-9行，基本用不到

                     0,0,0,0,0,0,0,0,0,0,            //0-19行，基本用不到

                     0,0,0,0,0,0,0,0,0,0,        //20-29行

                     4,3,3,2,2,3,2,2,3,2,            //30-39行

                     4,3,3,2,2,3,2,2,3,2,           //40-49行

                     1,1,1,1,1,1,1,1,1,1,           //最近十行

                  };
//参数
float Error;
float LastError=0;
float  WeightSum=0;
float  CenterSum=0;

uint8 test=0;
int camera_count=0;
uint8 camera_count_flag=0;
uint8 cnt_black=0;
uint8 shang_cnt=0;
uint8 start_cnt=0;
//extern int up_flag;
//extern uint8 SC_xie_L_Flag;
//extern uint8 SC_xie_R_Flag;
extern uint8 stop_flag;
extern uint8 cnt_EA;
uint8 SC_flag_2=0;
extern int white_zuo;
extern int white_you;
extern uint8 endflag;
//extern int white_l;
//extern int zuo_xielv;
//extern int you_xielv;
//extern uint8 Go_L_or_R;
//extern uint8 SC_flag;

/*start_flag  起跑标志位
 *
 * 0 准备出库
 * 1 第一圈
 * 2 第二圈
 * 3 准备入库
 *
 */


void Control()
{
   if(mt9v03x_finish_flag)//mt9v03x_finish_flag
   {
       Get_Pixle();
       get_route();
       get_deviation();
       Track_Line();
       process_data();
       send_date();
       mt9v03x_finish_flag=0;
//       camera_count++;

//       uint8 t_l[1]={0};
//       t_l[0]=start_flag;
//       for(uint8 hang=0;hang<Row;hang++)
//       {
//           t_l[hang]=rightline[hang]-leftline[hang];
//       }
//               seekfree_wireless_send_buff(t_l, 1);
//       seekfree_wireless_send_buff(leftlineflag, Row);
    }
    Menu_player();
    //Menu_one();
}




void number_of_turns()
{
//    int test[1];
//    test[0]=start_flag;
//    upper_send_data(test, 1);

    if(turn_flag==0)//四次三岔必入
    {
        if(sancha_static==4&&scratchflag == 1)
        {
            start_flag=3;
        }
        if(start_flag==3&&sancha_static!=4)
        {
            start_flag=2;
        }
    }
    if(turn_flag==1)//八次三岔必入
    {
        if(sancha_static==8&&scratchflag == 1)
        {
            start_flag=3;
        }
        if(start_flag==3&&sancha_static!=8)
        {
            start_flag=2;
        }
    }


   if(start_flag == 0)
   {
       start_line();
   }
   else if (start_flag  == 1 || start_flag == 2)
   {
       if(ringflag==0&&rampflag==0&&(sancha_static%2==0)&&cnt_EA&&(white_zuo+white_you)>330)//&&cnt_EA==1//banmaxian_flagen_start_flag==0&&
       {
           scratch_line();
       }

       if(ringflag != 0 && en_start_flag == 0 )    //在过三叉后开始检测起跑线
       {
           en_start_flag = 1;
       }

       if(en_start_flag == 1)
       {
           if(scratchflag == 1 )//&& ALL_flag == 0
           {

               en_start_flag = 0;
               if(Go_L_or_R==0)
              {
//                   connect(55, Pro_scratch(endline+10), rightline);
                  for(uint8 hang=15;hang<55;hang++)
                  {
                      rightlineflag[hang]=0;

                  }
              }
              if(Go_L_or_R==1)
              {
//                  connect(55, Pro_scratch(endline+10), leftline);
                  for(uint8 hang=15;hang<55;hang++)
                  {
                     leftlineflag[hang]=0;

                  }
              }

               if(start_flag == 1)//&&sancha_static==2
               {
                   start_flag = 2;
//                   en_start_flag=1;
               }
               else if (start_flag==2) //&&sancha_static==4
               {
                   start_flag = 3;//&&end_flag==1
//                   en_start_flag=1;
               }


                          }
       }
//       if(start_flag == 2 && en_start_flag )
//       {
//           start_cnt++;
//       }
//       if(start_cnt>100)
//       {
//           en_start_flag=0;
//           end_flag=1;
//       }
//       if( start_flag == 2 && scratchflag == 1&& ALL_flag == 0)
//       {
//           if(Go_L_or_R==0)
//           {
//               for(uint8 hang=15;hang<40;hang++)
//               {
//                   rightlineflag[hang]=0;
//
//               }
//           }
//           if(Go_L_or_R==1)
//           {
//               for(uint8 hang=15;hang<40;hang++)
//               {
//                  leftlineflag[hang]=0;
//
//               }
//           }
//
//
//       }
   }
   else if (start_flag == 3 )
   {
       black_count=0;
       for(uint8 lie=0;lie<Col;lie++)
       {
           if(Pixle[33][lie]==black)   black_count++;
       }

       if(endflag==1&&black_count>113)//endflag==1&&endline>45&&BlackEndM < 15&&BlackEndM>8//BlackEndM < 15&&BlackEndLL<15&&BlackEndRR<16//BlackEndMaxMax < 15  //&&BlackEndML<15&&BlackEndMR<15//&&BlackEndLL<15&&BlackEndRR<15
       {
           black_cntcnt++;
       }
       if(endflag==1&&black_cntcnt>10)
       {
           ALL_flag=241;
       }
       else
       {
           ALL_flag=243;
           gpio_set(C10,1);
           stop_line();
       }
   }



}
uint8 white_flag=0;
void scratch_white(void)
  {
      uint8 white_hang=0;
      white_flag=0;
      for(uint8 hang=Row-1;hang>45;hang++)
      {
          white_hang=0;
          for(uint8 lie=0;lie<Col;lie++)
          {
              if(Pixle[hang][lie]==white) white_hang++;
          }
          if(white_hang>110)
          {
              white_flag=1;
              break;
          }
      }
  }

uint8 check_flag=0;
void get_route(void)
{
//  uint8 white_cnt;
  //基础寻线
  get_route_one(Row-1,Col/2);
  get_route_all();
  //赛道信息提取
  GetBlackEndParam();
  //截止行判断
  get_route_endline();
  number_of_turns();

        if(scratchflag==1)    gpio_set(C10,1);
        else                  gpio_set(C10,0);

  if(start_flag==1|start_flag==2)//第一圈和第二圈的时候进行判断
  {

      if(ringflag==0&&scratchflag==0&&sancha_static!=1&&sancha_static!=3&&cnt_EA==1)
       {
           ramp_find();
       }
      if(ringflag==0&&rampflag==0&&scratchflag==0&&sancha_static!=1&&sancha_static!=3&&sanchaflag!=10&&cnt_EA==1)//&&rampflag==0
      {
          ring_find();
      }
      if(ringflag==0&&rampflag==0&&scratchflag==0&&sancha_static!=1&&sancha_static!=3&&cnt_EA==1)
      {
        //十字
          cross_find();
      }
      if(EA&&endline>8&&scratchflag==0&&rampflag==0)//&&ringflag==0
      {
          sancha_find();
      }



      if(rampflag!=0||ringflag==6||ringflag==7)//(ringflag==6||ringflag==7||ringflag==5)||||scratchflag==1
      {
//          gpio_set(C10,1);

      }
      else
      {
//          gpio_set(C10,0);

      }
        //元素处理
//     if(ringflag==0&&start_flag!=3)
//         cross();
//            cross_deal();
      //sancha_deal();

      ring_start();
      ring_ru();
      ring_chu();
  }
  get_route_midline();//拟合中线
}

void get_deviation(void)
{
  CenterSum=0;
  WeightSum=0;
    //十字偏差处理
    //入十字
    if(ru_cross_flag==1)
    {
      //取点以下
      if(ru_point<55)
      {
        for(uint8 hang=55;hang>ru_point;hang--)
        {
          CenterSum+=midline[hang]*CrossWeight[hang];
          WeightSum+=CrossWeight[hang];
        }
        //算出加权平均后中线的值
        if(WeightSum!=0)
        {
            Error=(CenterSum/WeightSum);
        }
        else
        {
            Error=0;
        }

      }
      else
      {
        Error=LastError;
      }
    }
    //斜入十字
    else if(xie_cross_flag==1)
    {
      //取拐点以下
      if(SZ_xie_point<45)
      {
        for(uint8 hang=55;hang>SZ_xie_point;hang--)
        {
          CenterSum+=midline[hang]*CrossWeight[hang];
          WeightSum+=CrossWeight[hang];
        }
        //算出加权平均后中线的值
        if(WeightSum!=0)
           {
               Error=(CenterSum/WeightSum);
           }
           else
           {
               Error=0;
           }
      }
      else
      {
        Error=LastError;
      }
    }
    else
    {
      if(endline<45)
      {
        for(uint8 hang=50;hang>endline;hang--)
        {
          CenterSum+=midline[hang]*Weight[hang];
          WeightSum+=Weight[hang];
        }
        //算出加权平均后中线的值
        if(WeightSum!=0)
        {
            Error=(CenterSum/WeightSum);
        }
        else
        {
            Error=0;
        }
      }
      else
      {
        Error=midline[hstart];
      }
    }
    if(ringflag==1||ringflag==3)
    {
      if(endline>=45)
        Error=20;
    }
    else if(ringflag==2||ringflag==4)
    {
      if(endline>=45)
        Error=100;
    }

}

/*规定ALL_flagd 内容
 *
 *
 *
 *
 */



void Track_Line(void)
{
  //前瞻
  if(endline<Foresight_up)
    {
//        if(sancha_static==2)
//        {
//            Foresight_hang=40;
//        }
//        else if(sancha_static==0||sancha_static==4)
//        {
          Foresight_hang=33;
//        }
    }
  else
  {
       Foresight_hang=endline+endline_Foresight;
  }

  if(Foresight_hang>50)
    Foresight_hang=50;

  if(start_flag==0)
  {
     Foresight_hang=endline_chu_hang_min+3;
  }

  ///////////////////////////////////////
//  if(up_flag&&SC_xie_L_Flag&&SC_xie_L_Flag)
//    {
//        Foresight_hang=55;
//    }
//    if(xie_cross_flag&&SZ_xie_R>30&&SZ_xie_L>30)
//    {
//        Foresight_hang=55;
//    }
  if(ringflag==0)
      {
    //      for(uint8 hang=5;hang<40;hang++)
    //      {
    //          if(leftlineflag[hang]==0&&leftline[hang-5]-leftline[hang]>50)
    //          {
    //              Foresight_hang=hang+5;
    //              break;
    //          }
    //      }

  //      shang_cnt=0;
  //      for(uint8 hang=endline-3;hang=endline+10;hang++)
  //      {
  //          if(Pixle[hang][0]==white&&Pixle[hang][Col-1]==white)
  //          {
  //              if(Pixle[hang][Col/2]==black)     shang_cnt++;
  //          }
  //      }
  //      if(shang_cnt>5)       Foresight_hang=53;

          shang_cnt=0;
          for(uint8 hang=endline-3;hang<endline+3;hang++)
            {
              for(uint8 lie=Col/2-20;lie<Col;lie++)
              {
                  if(Pixle[hang][lie-1]==black&&Pixle[hang][lie]==white)
                  {
                      shang_cnt++;
                      break;
                  }
              }

            }
          if(endline<13&&shang_cnt>=5)
          {
              Foresight_hang=endline+12;
              if(Foresight_hang>53)     Foresight_hang=53;
          }
//          if(up_flag)
//         {
//            Foresight_hang=endline+12;
//            if(Foresight_hang>55)     Foresight_hang=55;
//         }


          if(stop_flag==1)
          {
              Foresight_hang=33;
          }


      }

  //////////////////////////////////////

//  //前瞻
//  if(endline<Foresight_up)
//  {
//      if(sancha_static==2)
//      {
//          Foresight_hang=40;
//      }
//      else if(sancha_static==0||sancha_static==4)
//      {
//        Foresight_hang=33;
//      }
//
//  }

  if(sancha_static==1|sancha_static==3|sancha_static==5|sancha_static==7)
      {
          Foresight_hang=54;
//          if(BlackEndM<22)    Foresight_hang=55;
      }

//  if(SC_flag)   Foresight_hang=58;
  if(ALL_flag==11)   Foresight_hang=Pro_value(endline+22);
  if(rampflag==31)
  {
      Foresight_hang=45;

  }

  Foresight=(uint8)(0.2*Error+0.8*midline[Foresight_hang]);

  if(Foresight>120)
    Foresight=119;

  if(ALL_flag!=241)//没有冲出赛道时

  {
      ALL_flag=ringflag+sanchaflag+rampflag;


      if(ALL_flag==11)
      {
          SC_flag_2=1;
      }
      if(SC_flag_2)     ALL_flag=11;


      if(start_flag == 0)
      {
          ALL_flag=242;
      }
      if(start_flag == 3)
      {
          ALL_flag=243;
//          ALL_flag=241;
      }
//      if(ringflag==0&&(sancha_static==0||sancha_static==2||sancha_static==4)&&rampflag==0)//ru_cross_flag&&
//        {
//            cnt_black=0;
//            for(uint8 hang=endline-3;hang>3;hang--)
//            {
//                if(Pixle[hang][Col/2-10]==black) cnt_black++;
//            }
//            if(zuo_xielv<=-1&&zuo_xielv>=-4&&you_xielv>=0&&you_xielv<=4&&white_l>=100)//up_flag==1&&
//            {
//                if(cnt_black>5&&cnt_black<22)
//                {
//                    ALL_flag=11;
////                    EB=1;
//                }
//            }
//        }

  }



}
