#include "FIRELOCK.h"

int white_l=0;
int white_m=0;
int black_l=0;
int white_zuo=0;
int white_you=0;
int zuo_xielv;
int you_xielv;
//uint8 right_flag;
//uint8 left_flag;
int up_flag=0;
//int up_hang;
//uint8 hang_flag;
uint8 up_line[Col-20]={0};
uint8 zuo_line[Row]={0};
uint8 you_line[Row]={0};
uint8 sancha_static=0;//0,2不在里面，1,3在里面
uint8 cnt_EA=1;
uint8 sancha_cnt=0;
//uint8 up_black[20]={0};
//uint8 max_black_hang=0;
uint8 sancha_en=0;
//uint8 SC_xie_L_Flag;
//uint8 SC_xie_R_Flag;
uint8 turn_cnt=0;
uint8 angle_hang=0;
uint8 SC_flag=0;
//extern uint8 cnt_black;
extern uint8 SC_flag_2;
uint8 sancha_endm=0;
extern uint8 cross_en;
uint8 banmaxian_cnt=0;
uint8 banmaxian_cnt_en=1;
uint8 banmaxian_flag=1;
extern uint8 search_hang;
extern int SZ_xie_L_Flag;
extern int SZ_xie_R_Flag;


void sancha_find(void)
{
//    SC_xie_L_Flag=0,SC_xie_R_Flag=0;
//    SC_xie_L=Row-1,SC_xie_R=Row-1;

    uint8 eleven_flag=0,eleven_cnt=0;

    up_flag=0;

    if(SC_flag)     sanchaflag=11;
    else            sanchaflag=0;

    white_l=0;
    white_m=0;
    black_l=0;
    white_zuo=0;
    white_you=0;

    if(ALL_flag==11)      gpio_set(C10,1);
    else                  gpio_set(C10,0);

    if(ringflag!=0)     eleven_flag=1;
    else                eleven_flag=0;

    if(scratchflag!=1)  eleven_flag=1;
    else                eleven_flag=0;


    if(eleven_flag)     eleven_cnt++;
    if(eleven_cnt>200)
    {
        eleven_cnt=0;
        eleven_flag=0;
    }

//    sancha_en=0;//不实时更新

//    //右斜点
//          for(uint8 hang=Row-2;hang>DropRow+1;hang--)
//          {
//            if(rightlineflag[hang]!=0&&rightlineflag[hang-1]!=0)
//              if(rightline[hang-2]-rightline[hang]>0)
//                if(rightlineflag[hang+1]!=0&&rightlineflag[hang+2]!=0)
//                  if(rightline[hang+2]-rightline[hang]>0)
//              {
////                SC_xie_R=hang;
//                SC_xie_R_Flag=1;
//                break;
//              }
//          }
//          //左斜点
//          for(uint8 hang=Row-5;hang>DropRow+1;hang--)
//          {
//            if(leftlineflag[hang]!=0&&leftlineflag[hang-1]!=0)
//              if(leftline[hang]-leftline[hang-2]>0)
//                if(leftlineflag[hang+1]!=0&&leftlineflag[hang+2]!=0)
//                  if(leftline[hang]-leftline[hang+2]>0)
//              {
////                SC_xie_L=hang;
//                SC_xie_L_Flag=1;
//                break;
//              }
//          }

//      for(uint8 lie=0;lie<Col-20;lie++)
//      {
//          up_line[lie]=0;
//      }

//      //搜上边线,再看中间线白色数目判断是否为十字，若不是找拐点
//      for(uint8 lie=0;lie<Col;lie++)
//      {
////              up_line[lie]=0;
//          for(uint8 hang=Row-10;hang>2;hang--)
//          {
//
//              if(Pixle[hang-1][lie]==black&&Pixle[hang][lie]==white)
//              {
//                  up_line[lie]=hang;break;
//              }
//          }
//      }


//    if(endline>20&&Pixle[Pro_value(endline-10)][midline[57]]==black&&Pixle[Pro_value(endline+10)][midline[57]]==white)
//    {
//        if( (leftline[57]>5&&rightline[57]>Col-5) || (leftline[57]<5&&rightline[57]<Col-5) )
//            SC_flag=1;
//    }

    uint8 sancha_black=0;
    for(uint8 hang=Pro_value(endline+15);hang>Pro_value(endline-10);hang--)
    {
        sancha_black=0;
        for(uint8 lie=10;lie<Col-10;lie++)
        {
            if(Pixle[hang][lie]==black)     sancha_black++;
        }

        if(sancha_black>2&&sancha_black<10)
        {
            sancha_endm=hang;break;
        }
    }


          for(uint8 hang=0;hang<Row;hang++)
          {
              zuo_line[hang]=0;
              you_line[hang]=Col-1;
          }
      //搜上边线左右两侧
        for(uint8 hang=Pro_value(endline+3);hang>Pro_value(endline-5);hang--)
        {
            for(uint8 lie=1;lie<Col-1;lie++)
            {
                if(Pixle[hang][lie-1]==white&&Pixle[hang][lie]==black)
                {
                    zuo_line[hang]=lie;break;
                }
            }

        }

        for(uint8 hang=Pro_value(endline+3);hang>Pro_value(endline-5);hang--)
        {
            for(uint8 lie=Col-1;lie>0;lie--)
            {
                if(Pixle[hang][lie-1]==black&&Pixle[hang][lie]==white)
                {
                    you_line[hang]=lie;break;
                }
            }
        }


//          //上拐角
//            for(uint8 lie=10;lie<Col-20;lie++)
//            {
//                if(up_line[lie]-up_line[lie-5]>0)
//                    if(up_line[lie]-up_line[lie+5]>0)
//                    {
//                        up_hang=lie;
//                        up_flag=1;
//                        break;
//                    }
//
//            }


            zuo_xielv=zuo_line[endline-9]-zuo_line[endline-3];
            you_xielv=you_line[endline-9]-you_line[endline-3];

            /////////////////////////////////////////////
            /////////////////////////////////////////////
//            if(zuo_xielv==0&&you_xielv>10)       zuo_xielv=-5;
//            if(you_xielv==0&&zuo_xielv<-10)      you_xielv=5;
//            if(you_xielv<=-105)     you_xielv=20;
            /////////////////////////////////////////////
            /////////////////////////////////////////////


//            zuo_xielv=(up_line[up_hang-10]-up_line[up_hang]);
//            you_xielv=(up_line[up_hang]-up_line[up_hang+10]);


            for(uint8 hang=50;hang<Row;hang++)
            {
                for(uint8 lie=0;lie<30;lie++)
                {
                    if(Pixle[hang][lie]==white)     white_zuo++;
                }
            }
            for(uint8 hang=50;hang<Row;hang++)
            {
                for(uint8 lie=Col-1;lie>Col-30;lie--)
                {
                    if(Pixle[hang][lie]==white)     white_you++;
                }
            }


            for(uint8 lie=0;lie<Col;lie++)
            {
//                if(Pixle[55][lie]==white)        white_m++;
                if(Pixle[endline-9][lie]==black) black_l++;

                if(sancha_static==1||sancha_static==5)//||sancha_static==3||sancha_static==7
                {
                    if(Pixle[57][lie]==white)  white_l++;
                }
                else if(sancha_static==3||sancha_static==7)
                {
                    if(Pixle[52][lie]==white)  white_l++;
                }
                else if(sancha_static==0||sancha_static==2||sancha_static==4||sancha_static==6)
                {
                    if(Pixle[Pro_value(endline+5)][lie]==white)  white_l++;
                }
//                else if(sancha_static==2)
//                {
//                    if(Pixle[Pro_value(endline+3)][lie]==white)  white_l++;
//                }

            }

            if(sanchaflag==11)
            {
                SC_flag=1;
            }
            if(SC_flag==1)
            {
                if(sanchaflag!=10)  sanchaflag=11;
            }

//            if(white_l>=110)
//            {
//                if(Pixle[Pro_value(Foresight_hang-10)][midline[55]]==black)     SC_flag=1;
//                else        SC_flag=0;
//            }

//            if(up_flag==0)      sanchaflag=0;

            //减速措施
            if(ringflag==0&&(sancha_static==0||sancha_static==2||sancha_static==4||sancha_static==6)&&rampflag==0)//&&ru_cross_flag  ||sancha_static==4
            {
//                cnt_black=0;
               //                for(uint8 hang=endline-3;hang>3;hang--)
               //                {
               //                    if(Pixle[hang][Col/2-10]==black) cnt_black++;
               //                }
                if(ringflag==0&&sanchaflag!=10&&zuo_xielv<=-3&&you_xielv>=2&&white_l>103&&BlackEndM>25&&BlackEndM<43)//&&BlackEndM>27&&BlackEndM<40
                {
//                    if(cross_en==0&&Pixle[Pro_value(endline+25)][5]==white&&Pixle[Pro_value(endline+25)][Col-5]==white)
//                        if(eleven_flag==0)
                    if(black_l>80)
                        if(endline<=38&&endline>=16)
                            if(SZ_xie_L_Flag==1||SZ_xie_R_Flag==1)
                                if((white_zuo+white_you)>330)//white_m>97
                                    sanchaflag=11;
                }
//                if(xie_cross_flag)
//                {
//                    sanchaflag=0;
//                }

//                if(zuo_xielv<=-1&&zuo_xielv>=-20&&you_xielv>=1&&you_xielv<=25&&white_l>=110)//zuo_xielv<=-1&&you_xielv>=1&&up_flag==1&&zuo_xielv>=-4&&you_xielv<=4&&
//                {
//                    if(cnt_black>5&&cnt_black<24)
//                    {
//                        sanchaflag=11;
//    //                    EB=1;
//                    }
//                }
            }

//            if(ringflag==0&&sancha_static==2&&rampflag==0)
//            {
//                if(ringflag==0&&sanchaflag!=10&&zuo_xielv<=-3&&you_xielv>=2&&white_l>110&&BlackEndM>27&&BlackEndM<40)
//                {
////                    if(cross_en==0&&Pixle[Pro_value(endline+25)][5]==white&&Pixle[Pro_value(endline+25)][Col-5]==white)
////                        if(eleven_flag==0)
//                    if(endline<=34&&endline>=25 )
//                            sanchaflag=11;
//                }
//            }

            if(sancha_static==0||sancha_static==2||sancha_static==4||sancha_static==6)
            {
//                turn_cnt++;
//                angle_hang=endline;
//                for(uint8 hang=Pro_value(endline+20);hang>endline;hang--)
//                {
//                    for(uint8 lie=15;lie<Col-15;lie++)
//                    {
//                        if(Pixle[hang][lie]==black&&Pixle[hang][lie+1]==black)
//                            if(Pixle[hang-3][lie]==black&&Pixle[hang-3][lie-5]==black&&Pixle[hang-3][lie+5]==black)
//                                angle_hang=hang;break;
//                    }
//                    if(angle_hang>endline)   break;
//                }
//
//                if(sanchaflag==11&&angle_hang>=33&&BlackEndM<=25&&turn_cnt>50&&white_l>110)
//                {
//                    SC_flag_2=0;
//                    SC_flag=0;
//                    sanchaflag=10;
//                    turn_cnt=0;
//                }
                if(ALL_flag==11&&zuo_xielv<=-1&&you_xielv>=1&&white_l>110&&sancha_endm>=31)//ALL_flag==11&&//&&BlackEndM<=20//zuo_xielv<=-5&&you_xielv>=2you_xielv<=4&&zuo_xielv>=-4&&up_flag==1&&&&zuo_xielv>=-5&&you_xielv<=7
                {
                   up_flag=0;
    //               sancha_en=1;
                   SC_flag=0;
                   SC_flag_2=0;
                   sanchaflag=10;
                }
            }

            if(sancha_static==1||sancha_static==3||sancha_static==5||sancha_static==7)
            {


                turn_cnt++;
                angle_hang=endline;
                for(uint8 hang=Pro_value(endline+20);hang>endline;hang--)
                {
                    for(uint8 lie=15;lie<Col-15;lie++)
                    {
                        if(Pixle[hang][lie]==black&&Pixle[hang][lie+1]==black)
                            if(Pixle[hang-3][lie]==black&&Pixle[hang-3][lie-5]==black&&Pixle[hang-3][lie+5]==black)
                                angle_hang=hang;break;
                    }
                    if(angle_hang>endline)   break;
                }

//                //减速措施
//                if(angle_hang<38&&angle_hang>25&&BlackEndM>20&&BlackEndM<30&&turn_cnt>50&&white_l>110)
//                {
//                    sanchaflag=11;
//                }

                if(angle_hang>=40&&BlackEndM<=19&&turn_cnt>50&&white_l>105)
                {
//                    up_flag=0;
                    SC_flag_2=0;
                    sanchaflag=10;
                    turn_cnt=0;
                }
            }

//            if(sancha_static==1)//三岔内识别
//            {
//                if(zuo_xielv<=-5&&you_xielv>=0&&white_l>115&&BlackEndM<=21)//up_flag==1&&zuo_xielv>=-4&&you_xielv<=4&&&&zuo_xielv>=-5&&you_xielv<=7
//                {
//                   up_flag=0;
//    //               sancha_en=1;
//                   sanchaflag=10;
//                }
//            }
//
//            if(sancha_static==3)//三岔内识别
//            {
//                if(zuo_xielv<=-5&&you_xielv>=0&&white_l>115&&BlackEndM<=21)//up_flag==1&&zuo_xielv>=-4&&you_xielv<=4&&&&zuo_xielv>=-5&&you_xielv<=7
//                {
//                   up_flag=0;
//    //               sancha_en=1;
//                   sanchaflag=10;
//                }
//            }


//            if(sancha_static>=4)    sancha_static=4;
//            if(sancha_static!=4)    banmaxian_cnt=0;
//            if(sancha_static==4&&banmaxian_cnt_en)
//            {
//                banmaxian_flag=0;
//                banmaxian_cnt++;
//            }
//            if(banmaxian_cnt>30)
//            {
//                banmaxian_cnt=0;
//                banmaxian_cnt_en=0;
//                banmaxian_flag=1;
//            }

            if(sanchaflag==10&&cnt_EA)
            {
                sancha_static++;
                cnt_EA=0;
            }
            if(cnt_EA==0)                     sancha_cnt++;
             if(sancha_cnt>=20)
             {
                 sancha_cnt=0;
                 cnt_EA=1;
             }

//             for(uint8 lie=Col-10;lie<Col+10;lie++)
//             {
//               for(uint8 hang=55;hang>endline-5;hang--)
//               {
//                 if(Pixle[hang][lie]==black)
//                 {
//                   up_black[lie]=hang;
//                   break;
//                 }
//               }
//             }
//             max_black_hang=up_black[Col-10];
//             for(uint8 i=0;i<20;i++)
//             {
//                 if(up_black[Col-10+i]>max_black_hang)  max_black_hang=up_black[Col-10+i];
//             }
//             if(sancha_en&&up_line[up_hang]>45&&up_line[up_hang]<51)
//             {
//                 sancha_en=0;
//                 sanchaflag=10;
//             }

}

//(行)数值越界保护函数
uint8 Pro_value(uint8 value)
{
    if (value >= Row-1)
        value = Row-1;
    else if (value <= 5)
        value = 5;
    return (uint8)value;
}

//斑马线检测(行)数值越界保护函数
uint8 Pro_scratch(uint8 value)
{
    if (value >= 30)
        value = 30;
    else if (value <= 15)
        value = 15;
    return (uint8)value;
}

//斑马线检测(列)数值越界保护函数
uint8 Pro_lie(uint8 value)
{
    if (value >= Col-15)
        value = Col-15;
    else if (value <= 15)
        value = 15;
    return (uint8)value;
}

