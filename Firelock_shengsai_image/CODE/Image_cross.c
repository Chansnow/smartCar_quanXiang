#include "FIRELOCK.h"
/******************************************************************************
十字处理
改良版十字 简化了思路
入十字，斜入十字不进行补线，通过找拐点，然后用拐点以下部分。
出十字通过找正常赛道赋值
******************************************************************************/
//记录
int SZ_start_L=Row-1,SZ_start_R=Row-1,SZ_xie_L=Row-1,SZ_xie_R=Row-1,SZ_end_L=Row-1,SZ_end_R=Row-1;
//记标志
int SZ_start_L_Flag=0,SZ_start_R_Flag=0,SZ_xie_L_Flag=0,SZ_xie_R_Flag=0,SZ_end_L_Flag=0,SZ_end_R_Flag=0;
int ru_cross_flag=0,xie_cross_flag=0,chu_cross_flag=0;
int cross_white[Row];
int ru_num=0;
int chu_num=0;
int xie_white=0;
int ru_point=0;
int SZ_xie_point=0;
int SZ_hang=0;
int SZ_search_L_lie=0;
int SZ_search_R_lie=0;
int SZ_xie_L_UP=0;
int SZ_xie_R_UP=0;
int SZ_xie_L_UP_Flag=0;
int SZ_xie_R_UP_Flag=0;
int SZ_xie_L_UP_lie=0;
int SZ_xie_R_UP_lie=0;
uint8 cross_en=0;
uint8 search_en=0;
uint8 search_hang=0;
uint8 coner_left[Col/2];
uint8 coner_right[Col/2];



//三种情况判断
void cross_find(void)
{
  SZ_xie_L_Flag=0,SZ_xie_R_Flag=0;
  SZ_xie_L=Row-1,SZ_xie_R=Row-1;
  chu_cross_flag=0,xie_cross_flag=0,ru_cross_flag=0;
  ru_num=0;
  ru_point=59;
  search_en=0;


  for(uint8 lie=0;lie<Col/2;lie++)
  {
      coner_left[lie]=0;
      coner_right[lie]=0;
  }

  for(uint8 hang=Row-1;hang>endline+5;hang--)
  {
      if(leftlineflag[hang]==0&&rightlineflag[hang]==0)
      {
          search_hang=hang;
          search_en=1;
          break;
      }
      if(hang==endline+6)     search_en=0;
  }

  if(search_en&&search_hang>20)
  {
      //左斜点
      for(uint8 lie=0;lie<Col/2;lie++)
      {
          if(Pixle[Row-1][lie]==black)  coner_left[lie]=Row-1;
          else
          {
              for(uint8 hang=Row-1;hang>search_hang-5;hang--)
              {
                  if(Pixle[hang][lie]==white&&Pixle[hang-2][lie]==black)
                  {
                      coner_left[lie]=hang;
                      break;
                  }
              }
          }
      }

      //右斜点
      for(uint8 lie=Col-1;lie>Col/2;lie--)
        {
            if(Pixle[Row-1][lie]==black)  coner_left[lie]=Row-1;
            else
            {
                for(uint8 hang=Row-1;hang>search_hang-5;hang--)
                {
                    if(Pixle[hang][lie]==white&&Pixle[hang-2][lie]==black)
                    {
                        coner_right[lie]=hang;
                        break;
                    }
                }
            }
        }

      //遍历拐点数组
      for(uint8 lie=0;lie<Col/2;lie++)
      {
          if(coner_left[lie]!=0&&coner_left[lie]!=Row-1&&(coner_left[lie]-coner_left[lie+1])>5)//coner_left[lie]!=0&&coner_left[lie+1]==0
          {
              SZ_xie_L=coner_left[lie];
              SZ_xie_L_Flag=1;
              break;
          }
      }
//      if(SZ_xie_L_Flag)     connect(Pro_value(SZ_xie_L),Pro_value(endline),leftline);

      for(uint8 lie=Col-1;lie>Col/2;lie--)
        {
            if(coner_right[lie]!=0&&coner_right[lie]!=Row-1&&(coner_right[lie]-coner_right[lie-1])>5)
            {
                SZ_xie_R=coner_right[lie];
                SZ_xie_R_Flag=1;
                break;
            }
        }
//        if(SZ_xie_R_Flag)     connect(Pro_value(SZ_xie_R),Pro_value(endline),rightline);

  }

//  if(search_en)
//  {
//      //左斜点
//      for(uint8 hang=Row-1;hang>Pro_value(search_hang-10);hang--)
//      {
//          if(leftlineflag[hang]==1&&leftlineflag[hang]==1&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]==0)
//          {
//                SZ_xie_L=hang;
//                SZ_xie_L_Flag=1;
//                break;
//          }
//      }
//
//      //右斜点
//        for(uint8 hang=Row-1;hang>Pro_value(search_hang-10);hang--)
//        {
//            if(rightlineflag[hang]==1&&rightlineflag[hang]==1&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]==0)
//            {
//                  SZ_xie_R=hang;
//                  SZ_xie_R_Flag=1;
//                  break;
//            }
//        }
//
//        if(SZ_xie_L_Flag)       connect(Pro_value(SZ_xie_L),Pro_value(SZ_xie_L-15), leftline);
//        if(SZ_xie_R_Flag)       connect(Pro_value(SZ_xie_R),Pro_value(SZ_xie_R-15), rightline);
////      //右斜点
////        for(uint8 hang=Row-2;hang>Pro_value(search_hang-5);hang--)//hang>DropRow+1
////        {
////      //    if(leftline[hang]<10&&rightlineflag[hang]!=0&&rightlineflag[hang-1]!=0)
////            if(rightline[hang-3]-rightline[hang]>0)
////      //        if(rightlineflag[hang+2]!=0&&rightlineflag[hang+3]!=0&&rightlineflag[hang+4]!=0)
////                if(rightline[hang+3]-rightline[hang]>0)//rightline[hang+3]-rightline[hang+2]>0&&rightline[hang+4]-rightline[hang+3]>0&&
////            {
////              SZ_xie_R=hang;
////              SZ_xie_R_Flag=1;
////      //        Foresight_hang=SZ_xie_L+2;
////              break;
////            }
////        }
////        //左斜点
////        for(uint8 hang=Row-5;hang>DropRow+1;hang--)
////        {
////      //    if(leftlineflag[hang]!=0&&rightline[hang]>Col-6&&leftlineflag[hang-1]!=0)
////            if(leftline[hang]-leftline[hang-3]>0)
////      //        if(leftlineflag[hang+2]!=0&&leftlineflag[hang+3]!=0&&leftlineflag[hang+4]!=0)
////                if(leftline[hang]-leftline[hang+3]>0)//leftline[hang+2]-leftline[hang+3]>0&&leftline[hang+3]-leftline[hang+4]>0&&
////            {
////              SZ_xie_L=hang;
////              SZ_xie_L_Flag=1;
////      //        Foresight_hang=SZ_xie_L+2;
////              break;
////            }
////        }
////
////        if(SZ_xie_L_Flag||SZ_xie_R_Flag)    xie_cross_flag=1;
////        else                                xie_cross_flag=0;
//  }

//  //存白点
//  for(uint8 hang=Row-1;hang>DropRow;hang--)
//  {
//    for(uint8 lie=0;lie<Col;lie++)
//    {
//      if(Pixle[hang][lie]==white)
//      {
//        cross_white[hang]++;
//      }
//    }
//    if(hang<50)
//    {
//      if(cross_white[hang]>110)
//        ru_num++;
//    }
//  }
//  //入十字起始行
//  for(uint8 hang=50;hang>DropRow;hang--)
//  {
//    if(cross_white[hang]>110)
//    {
//      ru_point=hang;
//      break;
//    }
//  }
//  //底下三行全白 出十字
//  if(leftlineflag[50]==0&&rightlineflag[50]==0&&leftlineflag[51]==0&&rightlineflag[51]==0&&leftlineflag[52]==0&&rightlineflag[52]==0&&endline<30)
//  {
//    chu_cross_flag=1;
//    ru_cross_flag=0;
//    SZ_xie_R_Flag=0;
//    SZ_xie_L_Flag=0;
//  }
//  //斜入判断
//  if((SZ_xie_R_Flag==1&&SZ_xie_R>20&&chu_cross_flag==0)||(SZ_xie_L_Flag==1&&SZ_xie_L>20&&chu_cross_flag==0))
//  {
//    xie_cross_flag=1;
//  }
//  //入十字
//  if(ru_num>=10&&ru_point<50&&chu_cross_flag==0&&endline<30)//&&xie_cross_flag==0
//  {
//    ru_cross_flag=1;
//  }
}



//void cross_find(void)
//{
//    SZ_xie_L_Flag=0,SZ_xie_R_Flag=0;
//    SZ_xie_L=Row-1,SZ_xie_R=Row-1;
//    SZ_search_L_lie=0,SZ_search_R_lie=0;
//    SZ_xie_L_UP=0,SZ_xie_R_UP=0,SZ_xie_L_UP_Flag=0,SZ_xie_R_UP_Flag=0,SZ_xie_L_UP_lie=0,SZ_xie_R_UP_lie=0;
//
//    for(uint8 hang=Row-1;hang>0;hang--)
//    {
//        if(rightline[hang]>118&&Pixle[hang][0]==white)
//        {
//            leftline[hang]=1;
//            leftlineflag[hang]=0;
//        }
//    }
//
//    //搜左下拐点
//    for(uint8 lie=0;lie<Col/2;lie++)
//    {
//        for(uint8 hang=Row-1;hang>endline;hang--)
//        {
//            if(Pixle[hang-6][lie]==white&&Pixle[hang-3][lie]==black&&Pixle[hang][lie]==black)
//            {
//                SZ_xie_L=hang-3;
//                SZ_xie_L_Flag=1;
//                SZ_search_L_lie=lie;
//                break;
//            }
//        }
//        if(SZ_xie_L_Flag)  break;
//    }
//
//    //搜右下拐点
//    for(uint8 lie=Col-1;lie>Col/2;lie--)
//    {
//        for(uint8 hang=Row-1;hang>endline;hang--)
//        {
//            if(Pixle[hang-6][lie]==white&&Pixle[hang-3][lie]==black&&Pixle[hang][lie]==black)
//            {
//                SZ_xie_R=hang-3;
//                SZ_xie_R_Flag=1;
//                SZ_search_R_lie=lie;
//                break;
//            }
//        }
//        if(SZ_xie_R_Flag)     break;
//    }
//
////    SZ_xie_L_UP=SZ_xie_L-7;
////    SZ_xie_R_UP=SZ_xie_R-7;
////
////    //搜左上拐点
////    for(uint8 lie=SZ_search_L_lie;lie<Col/2;lie++)
////    {
////        for(uint8 hang=SZ_xie_L;hang>endline;hang--)
////        {
////            if(Pixle[hang-2][lie]==black&&Pixle[hang][lie]==white)
////            {
////                SZ_xie_L_UP=hang;
////                SZ_xie_L_UP_Flag=1;
////                SZ_xie_L_UP_lie=lie;
////                break;
////            }
////        }
////        if(SZ_xie_L_UP_Flag)       break;
////    }
////
////    //搜右上拐点
////    for(uint8 lie=SZ_search_R_lie;lie>Col/2;lie--)
////    {
////        for(uint8 hang=SZ_xie_R;hang>endline;hang--)
////        {
////            if(Pixle[hang-2][lie]==black&&Pixle[hang][lie]==white)
////            {
////                SZ_xie_R_UP=hang;
////                SZ_xie_R_UP_Flag=1;
////                SZ_xie_R_UP_lie=lie;
////                break;
////            }
////        }
////        if(SZ_xie_R_UP_Flag)    break;
////    }
////
//
//}

//void cross(void)
//{
//    uint8 you_cross_hang,you_cross_lie;
//    SZ_xie_L_Flag=0,SZ_xie_R_Flag=0;
//
//    /////////////////////////////////////
//    /////////////////////////////////////
//    //防三岔误判
//    if(ringflag==0&&ALL_flag!=11&&endline<22&&BlackEndM<=35)
//            cross_en=1;
//    else
//            cross_en=0;
//
//    /////////////////////////////////////
//    /////////////////////////////////////
//
//
//    for(uint8 hang=Row-1;hang>endline+5;hang--)
//    {
//        if(leftlineflag[hang]==0&&rightlineflag[hang]==0)
//        {
//            you_cross_hang=hang;break;
//        }
//        if(hang==endline+6)     cross_en=0;//default
//    }
//
//    if(cross_en&&!scratchflag)
//    {
////        for(uint8 lie=0;lie<Col/2;lie++)
////        {
////            if(Pixle[you_cross_hang][lie]==white&&Pixle[Row-1][lie]==white&&Pixle[Row-7][lie]==black)
////            {
////                SZ_xie_L_Flag=1;break;
////            }
////        }
//
//        if(SZ_xie_L_Flag)
//        {
//            connect(Pro_value(SZ_xie_L+5), endline+8, leftline);
//        }
//
//    }
//    if(cross_en&&!scratchflag)
//    {
////        for(uint8 lie=Col-1;lie>Col/2;lie--)
////        {
////            if(Pixle[you_cross_hang][lie]==white&&Pixle[Row-1][lie]==white&&Pixle[Row-7][lie]==black)
////            {
////                SZ_xie_R_Flag=1;break;
////            }
////        }
//        if(SZ_xie_R_Flag)
//        {
//            connect(Pro_value(SZ_xie_R+5), endline+8, leftline);
//        }
//
//    }
//
//
//
//
//
////    if(cross_en&&!scratchflag)
////    {
////        for(uint hang=1;hang<50;hang++)
////        {
////
////            if(leftline[hang]<5&&rightline[hang]>Col-5)
////            {
////                //右斜入
////
////                //寻找右下拐点情况1
////                if(Pixle[Row-1][Col-1]==black)
////                {
////                    you_cross_hang=Row-1;
////                    for(uint8 lie=Col;lie>Col/2;lie--)
////                    {
////                        if(Pixle[Row-1][lie]==white)
////                        {
////                            you_cross_lie=lie;
////                            break;
////                        }
////                    }
////                }
////    //            //寻找左下拐点情况2
////    //            else if(Pixle[Row-1][Col-1]==white)
////    //            {
////    //                you_cross_lie=0;
////    //                for(uint8 hang=Row-1;hang>0;hang--)
////    //                {
////    //                    if(Pixle[hang][Col-1]==black)
////    //                    {
////    //                        you_cross_hang=hang;
////    //                        break;
////    //                    }
////    //                }
////    //            }
////                if(you_cross_lie>Col/2)
////                {
////                    if(leftline[you_cross_hang]<5&&leftline[you_cross_hang-3]<5&&leftline[you_cross_hang-6]<5)
////                    {
////                        for(uint8 hang=endline+1;hang<you_cross_hang-1;hang++)
////                        {
////                            rightline[hang]=rightline[hang-1]+1;
////                            if(rightline[hang]>rightline[you_cross_hang])   rightline[hang]=rightline[you_cross_hang];
////                            rightlineflag[hang]=1;
////                        }
////                        connect(endline+15, endline, rightline);
//////                        connect(Row-1, endline, leftline);
////                    }
////                }
////
////
////                //左斜入
////
////               //寻找左下拐点情况1
////               if(Pixle[Row-1][0]==black)
////               {
////                   you_cross_hang=Row-1;
////                   for(uint8 lie=0;lie<Col/2;lie++)
////                   {
////                       if(Pixle[Row-1][lie]==white)
////                       {
////                           you_cross_lie=lie;
////                           break;
////                       }
////                   }
////               }
////
////               if(you_cross_lie<Col/2)
////               {
////                   if(rightline[you_cross_hang]>Col-5&&rightline[you_cross_hang-3]>Col-5&&rightline[you_cross_hang-6]>Col-5)
////                   {
////                       for(uint8 hang=endline+1;hang<you_cross_hang-1;hang++)
////                       {
////                           leftline[hang]=leftline[hang-1]-1;
////                           if(leftline[hang]<leftline[you_cross_hang])   leftline[hang]=leftline[you_cross_hang];
////                           leftlineflag[hang]=1;
////                       }
////                       connect(endline+15, endline, leftline);
//////                       connect(Row-1, endline, rightline);
////
////                   }
////               }
////
////
////            }
////        }
////    }
//
//}






//void cross_deal(void)
//{
//    uint8 souxian_xielv_L=0,souxian_xielv_R=0;//搜线用斜率，沿着下拐角的斜率搜上拐角
//    uint8 buff_1,buff_2;
//    uint8 LIE_L,LIE_R;
//    uint8 w_cnt=0;
//    uint8 up_cross_hang=0,up_cross_lie=0;
//    if(SZ_xie_L_Flag&&!SZ_xie_R_Flag)
//    {
//        for(uint8 lie=0;lie<Col/2;lie++)
//        {
//            if(Pixle[SZ_xie_L][lie]==black&&Pixle[SZ_xie_L][lie+1]==white)
//            {
//                buff_1=lie;break;
//            }
//        }
//        for(uint8 lie=0;lie<Col/2;lie++)
//        {
//            if(Pixle[SZ_xie_L+2][lie]==black&&Pixle[SZ_xie_L+2][lie+1]==white)
//            {
//                buff_2=lie;break;
//            }
//        }
//        souxian_xielv_L=buff_1-buff_2;
//
//        LIE_L=buff_2;
//        w_cnt=0;
//        for(uint8 hang=SZ_xie_L;hang>endline;hang--)
//        {
//            LIE_L+=souxian_xielv_L;
//            if(Pixle[hang][LIE_L]==white)   w_cnt++;
//            if(Pixle[hang][LIE_L]==black&&w_cnt>5)
//            {
//                up_cross_hang=hang;
//                up_cross_lie=LIE_L;
//                break;
//            }
//            if(w_cnt>20)
//            {
//                up_cross_hang=SZ_xie_L-10;
//                up_cross_lie=Col/2-10;
//                break;
//            }
//        }
//
//        for(uint8 hang=up_cross_hang;hang<SZ_xie_L;hang++)
//        {
//            if(leftline[hang]<5)
//            {
//                leftline[hang]=up_cross_lie;
//            }
//        }
//
//        leftline[up_cross_hang]=up_cross_lie;
//        connect(SZ_xie_L, up_cross_hang, leftline);
//    }
//
//    if(SZ_xie_R_Flag&&!SZ_xie_L_Flag)
//    {
//        for(uint8 lie=Col-1;lie>Col/2;lie--)
//        {
//            if(Pixle[SZ_xie_R][lie]==black&&Pixle[SZ_xie_R][lie-1]==white)
//            {
//                buff_1=lie;break;
//            }
//        }
//        for(uint8 lie=0;lie<Col/2;lie++)
//        {
//            if(Pixle[SZ_xie_R+2][lie]==black&&Pixle[SZ_xie_R+2][lie-1]==white)
//            {
//                buff_2=lie;break;
//            }
//        }
//        souxian_xielv_R=buff_2-buff_1;
//
//        LIE_L=buff_2;
//        w_cnt=0;
//        for(uint8 hang=SZ_xie_R;hang>endline;hang--)
//        {
//            LIE_R-=souxian_xielv_R;
//            if(Pixle[hang][LIE_R]==white)   w_cnt++;
//            if(Pixle[hang][LIE_R]==black&&w_cnt>5)
//            {
//                up_cross_hang=hang;
//                up_cross_lie=LIE_L;
//                break;
//            }
//            if(w_cnt>20)
//            {
//                up_cross_hang=SZ_xie_R-10;
//                up_cross_lie=Col/2+10;
//                break;
//            }
//        }
//
//        for(uint8 hang=up_cross_hang;hang<SZ_xie_R;hang++)
//        {
//            if(rightline[hang]>Col-5)
//            {
//                rightline[hang]=up_cross_lie;
//            }
//        }
//
//        rightline[up_cross_hang]=up_cross_lie;
//        connect(SZ_xie_R, up_cross_hang, rightline);
//    }
//
////    if(SZ_xie_L_Flag||SZ_xie_R_Flag)
////    {
////        for(uint8 hang=SZ_xie_R;hang>endline;hang--)
////        {
////            rightline[hang]=1;
////        }
////    }
////    if(SZ_xie_L_Flag)//&&SZ_xie_L_UP_Flag
////        {
////            leftline[SZ_xie_L]=SZ_search_L_lie;leftlineflag[SZ_xie_L]=1;
//////            leftline[SZ_xie_L_UP]=SZ_xie_L_UP_lie;leftlineflag[SZ_xie_L_UP]=1;
////            leftline[SZ_xie_L-5]=Col/2-10;leftlineflag[SZ_xie_L-5]=1;
////            connect(SZ_xie_L, SZ_xie_L-5, leftline);
////        }
////        else if(SZ_xie_L_Flag&&!SZ_xie_L_UP_Flag)
////        {
////            leftline[SZ_xie_L]=SZ_search_L_lie;leftlineflag[SZ_xie_L]=1;
////      //      leftline[SZ_xie_L_UP]=SZ_search_L_lie+5;leftlineflag[SZ_xie_L_UP]=1;
////            connect(SZ_xie_L_Flag, SZ_xie_L_UP_Flag, leftline);
////        }
////        if(SZ_xie_R_Flag&&endline<10&&ringflag==0)//&&SZ_xie_R_UP_Flag
////        {
////            for(uint8 hang=SZ_xie_R;hang>endline;hang--)
////            {
////                rightlineflag[hang]=1;
////                leftlineflag[hang]=1;
////            }
////
////
////        }
//
////        if(ru_cross_flag&&endline<10&&ringflag==0)
////        {
////            for(uint8 hang=Row-1;hang>endline;hang--)
////            {
////                if(Pixle[hang][1]==white&&Pixle[hang][Col-1]==white)
////                {
////                    leftline[hang]=1;leftlineflag[hang]=1;
////                    rightline[hang]=Col-1;rightlineflag[hang]=1;
////                }
////            }
////        }
////        else if(SZ_xie_R_Flag&&!SZ_xie_R_UP_Flag)
////        {
////            rightline[SZ_xie_R]=SZ_search_R_lie;rightlineflag[SZ_xie_R]=1;
////            rightline[SZ_xie_R_UP]=SZ_xie_R_UP_lie-5;rightlineflag[SZ_xie_R_UP]=1;
////            connect(SZ_xie_R_Flag, SZ_xie_R_UP_Flag, rightline);
////        }
//}




//void cross_deal(void)
//{
//  SZ_end_L=Row-1,SZ_end_R=Row-1;
//  SZ_end_L_Flag=0,SZ_end_R_Flag=0;
//  SZ_xie_point=0;
//  chu_cross_flag=0;
//  chu_num=0;
//  xie_white=0;
//
////  //入十字
////  if(ru_cross_flag==1&&ringflag==0)
////  {
////    for(uint8 hang=Row-1;hang>DropRow;hang--)
////    {
////      if(leftlineflag[hang]==0)
////      {
////        leftline[hang]=1;
////        leftlineflag[hang]=1;
////      }
////      if(rightlineflag[hang]==0)
////      {
////        rightline[hang]=Col-1;
////        rightlineflag[hang]=1;
////      }
////    }
////  }
//
//  for(uint8 lie=Col/2-20;lie<Col/2+20;lie++)
//  {
//      if(Pixle[endline+3][lie]==white)  xie_white++;
//  }
//
//
//  //斜入
//   if(SZ_xie_R_Flag==1&&SZ_xie_R>20&&xie_white>10)//&&SZ_xie_R>30&&ru_cross_flag&&!chu_cross_flag
//   {
//     SZ_xie_point=SZ_xie_R;
//
////     //连线
////         rightline[SZ_xie_point]=rightline[SZ_xie_point-1];
////         rightline[1]=5;
////         connect(SZ_xie_point,1,rightline);
//
////         uint8 xx=rightline[SZ_xie_point+3]-rightline[SZ_xie_point];
////         uint8 yy=rightline[SZ_xie_point];
////         uint8 x_x=1,y_y=1;//x_x记录出十字的行,y_y记录出十字的列
////         for(uint8 hang=SZ_xie_point;hang>0;hang-=3)
////         {
////             if(Pixle[hang][yy]==black)
////             {
////                 x_x=hang;
////                 y_y=yy;
////                 break;
////             }
////             yy-=xx;
////         }
//
////         oled_printf_int32(63,6,x_x,2);
////         oled_printf_int32(73,6,y_y,2);
////         rightline[x_x]=y_y;
//
//         connect(SZ_xie_point,endline+3,rightline);//+3
//
////         leftline[x_x]=0;
////         leftline[SZ_xie_point]=0;
////         connect(SZ_xie_point,x_x,leftline);
//
//   }
//
//   if(SZ_xie_L_Flag==1&&SZ_xie_L>30&&xie_white>10)//&&ru_cross_flag&&!chu_cross_flag
//   {
//     SZ_xie_point=SZ_xie_L;
//     if(leftline[endline+3]<40)
//     {
//
//          connect(SZ_xie_point,endline+3,leftline);//+3
//
//
//     }
//   }
//
////   if((SZ_xie_L_Flag==1|SZ_xie_R_Flag==1)&&ru_cross_flag&&!chu_cross_flag)
////   {
////       SZ_hang=0;
////       for(uint8 hang=Row-1;hang>endline-5;hang--)
////          {
////               if((leftlineflag[hang]==0)&&(rightlineflag[hang]!=0))
////               {
////                   SZ_hang=hang;break;
////               }
////          }
////       if(SZ_hang<30)   SZ_hang=30;
////       for(uint8 hang=SZ_hang;hang<Row-10;hang++)
////       {
////           rightline[hang]=Col-1;
////           leftline[hang]=rightline[hang]-track_width[hang+10]-5;
////       }
////   }
//
//
////   if((SZ_xie_L_Flag==1|SZ_xie_R_Flag==1)&&SZ_xie_L>40&&SZ_xie_R>40&&xie_white>10)
////   {
////       if(leftline[endline+3]<40)
////       {
////           connect(Row-1,endline+3,leftline);//+3
////           connect(Row-1,endline+3,rightline);//+3
////       }
//////       else
//////       {
//////           connect(Row-1,endline+3,leftline);//+3
//////       }
////
////
////   }
//
////  //出十字补线
////  if(chu_cross_flag==1)
////  {
////    //找十字终点
////    for(uint8 hang=Row-2;hang>endline+1;hang--)
////    {
////      if(leftlineflag[hang]==0&&leftlineflag[hang-1]!=0&&leftlineflag[hang-2]!=0)
////      {
////        SZ_end_L=hang-2;
////        SZ_end_L_Flag=1;
////        break;
////      }
////    }
////    for(uint8 hang=Row-2;hang>endline+1;hang--)
////    {
////      if(rightlineflag[hang]==0&&rightlineflag[hang-1]!=0&&rightlineflag[hang-2]!=0)
////      {
////        SZ_end_R=hang-2;
////        SZ_end_R_Flag=1;
////        break;
////      }
////    }
////    //如果找到左右终点
////    if(SZ_end_L_Flag==1&&SZ_end_R_Flag==1)
////    {
////      //更为准确
////      if(SZ_end_L>SZ_end_R)
////        SZ_end_L=SZ_end_R;
////      else if(SZ_end_L<SZ_end_R)
////        SZ_end_R=SZ_end_L;
////      //增加准确度
////      SZ_end_L-=5;
////      SZ_end_R-=5;
////      //补线
////      for(uint8 hang=SZ_end_L;hang<Row;hang++)
////      {
////        leftline[hang]=leftline[SZ_end_L];
////        leftlineflag[hang]=2;
////      }
////      for(uint8 hang=SZ_end_R;hang<Row;hang++)
////      {
////        rightline[hang]=rightline[SZ_end_R];
////        rightlineflag[hang]=2;
////      }
////    }
////  }
//
//
////  for(uint8 hang=Row-1;hang>DropRow;hang--)
////  {
////      cross_white[hang]=0;
////  }
////  //存白点
////    for(uint8 hang=Row-5;hang>DropRow;hang--)
////    {
////      for(uint8 lie=0;lie<Col;lie++)
////      {
////        if(Pixle[hang][lie]==white)
////        {
////          cross_white[hang]++;
////        }
////      }
////      if(hang>35)
////      {
////        if(cross_white[hang]>110)
////          chu_num++;
////      }
////    }
////    if(chu_num>15)
////    {
////        chu_cross_flag=1;
////
////    }
////
////    if(chu_cross_flag)
////    {
////        for(uint8 hang=Row-1;hang<DropRow;hang--)
////        {
////            leftline[hang]=1;leftlineflag[hang]=1;
////            rightline[hang]=Col-1;rightlineflag[hang]=1;
////        }
////    }
//
//}


