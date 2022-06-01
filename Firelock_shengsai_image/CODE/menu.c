#include "FIRELOCK.h"


uint8 change_enable = 0;
uint8 cwheels=0;
u8 endline_display=30;
u8 Foresight_display=0;
enum key_sign interact_signal = nosign;
enum page_def interact_page = main_page;
uint8 last_page=0;
uint8 page = 0;
//extern int SZ_xie_R_Flag;
//extern int SZ_xie_L_Flag;
//extern int up_hang;
//extern uint8 max_black_hang;
//extern uint8 up_line[Col-20];
extern uint8 sancha_static;
//extern uint8 shang_cnt;
extern int white_l;
extern int black_l;
extern int zuo_xielv;
extern int you_xielv;
//extern int up_flag;
//extern uint8 cnt_black;
extern uint8 angle_hang;
extern uint8 Go_L_or_R;
extern uint8 sancha_endm;
extern int SZ_xie_L_Flag;
extern int SZ_xie_R_Flag;
extern uint8 search_hang;
extern uint8 search_en;
extern int white_zuo;
extern int white_you;
extern int white_m;
extern uint8 BlackEndMR;
extern uint8 BlackEndML;
extern uint8 endflag;
extern uint8 end_count;
extern uint8 black_count;
extern uint8 turn_flag;

void Menu_player()
{
    Menu_Getsign();
    Menu_Key_Page_Handle();
    Menu_Display();
}

enum key_sign Menu_Getsign()  //返回按键消息，更改interact_signal
{
    enum key_sign signflag = nosign;
    KEY_MSG_t keymsg;
    uint8 key_flag = 0;

    key_IRQHandler();

    key_flag=get_key_msg(&keymsg);

    if (key_flag)
    {
        if (keymsg.key == KEY_U && keymsg.status == KEY_DOWN )
        {
            signflag = upsign;
        }
        if (keymsg.key == KEY_D && keymsg.status == KEY_DOWN )
        {
            signflag = downsign;
        }
        if (keymsg.key == KEY_L && keymsg.status == KEY_DOWN )
        {
            signflag = leftsign;
        }
        else if (keymsg.key == KEY_R && keymsg.status == KEY_DOWN )
        {
            signflag = rightsign;
        }
        else if (keymsg.key == KEY_P && keymsg.status == KEY_DOWN)
        {
            signflag = insign;
        }
        else if (keymsg.key == KEY_1 && keymsg.status == KEY_DOWN)
        {
            signflag = outsign;
        }
    }
    interact_signal = signflag;
    return signflag;
}

void Menu_Key_Page_Handle()
{
    if (interact_signal == insign)
    {
        change_enable = !change_enable;
    }
    else if (interact_signal == leftsign)
    {
        oled_fill(0);
        if (interact_page == main_page)
            interact_page = (enum page_def)(max_page-1);
        else    interact_page--;
        change_enable = 0;
    }
    else if (interact_signal == rightsign)
    {
        oled_fill(0);
        if (interact_page == (enum page_def)(max_page-1))
            interact_page = main_page;
        else    interact_page++;
        change_enable = 0;
    }
}

void Menu_Display()
{
    switch (interact_page)
    {
        case main_page:  Menu_Main();       break;
        case Image_page: Menu_Image();      break;
        case Line_page:  Menu_Line();      break;
//        case go_page:    Menu_GO();      break;
        case one_page:   Menu_one();      break;

       default :        Menu_Main();        break;
    }
}


void Menu_Main()
{
    oled_p6x8str(0, 0,"Foresight");
    oled_p6x8str(0, 1,"Error");
    oled_p6x8str(0, 2,"endline");
    oled_p6x8str(0, 3,"ALL_flag");
    oled_p6x8str(0, 4,"ringflag");
    oled_p6x8str(0, 5,"EndM");


    oled_printf_int32(60,0,Foresight_hang,3);
    oled_printf_int32(90,0,Foresight,3);

    oled_printf_int32(60,1,Error,3);

    oled_printf_int32(60,2,endline,3);
    oled_printf_int32(60,3,ALL_flag,3);

    oled_printf_int32(60,4,ringflag,3);

    oled_printf_int32(30,5,BlackEndM,3);

    oled_printf_int32(30,7,start_flag,3);

//    oled_printf_int32(90,6,SZ_xie_R_Flag,3);
//
//    oled_printf_int32(30,7,scratchflag,3);
//    oled_printf_int32(60,7,SZ_xie_L,3);
//    oled_printf_int32(90,7,SZ_xie_R,3);
    //SZ_xie_L_Flag,SZ_xie_R_Flag,SZ_xie_L,SZ_xie_R,chu_cross_flag,ru_cross_flag,xie_cross_flag

    oled_printf_int32(0,6,sancha_static,3);
//    oled_printf_int32(0,6,SZ_xie_L_Flag,3);
//    oled_printf_int32(30,6,SZ_xie_R_Flag,3);
//    oled_printf_int32(60,6,xie_cross_flag,3);
//    oled_printf_int32(90,6,ru_cross_flag,3);
//    oled_printf_int32(0,7,chu_cross_flag,3);
//    oled_printf_int32(30,7,SZ_xie_L,3);
//    oled_printf_int32(60,7,SZ_xie_R,3);
////    oled_printf_int32(90,7,ALL_flag,3);
//    oled_printf_int32(90,7,up_line[up_hang],3);

    oled_printf_int32(90,5,sancha_endm,3);
//    oled_printf_int32(0,7,up_flag,3);
    oled_printf_int32(60,6,zuo_xielv,3);
    oled_printf_int32(90,6,you_xielv,3);
//    oled_printf_int32(30,6,up_flag,3);
    oled_printf_int32(0,7,white_l,3);
    oled_printf_int32(60,5,black_l,3);
    oled_printf_int32(30,6,angle_hang,3);
//    oled_printf_int32(90,7,cnt_black,3);
    oled_printf_int32(90,7,scratchflag,3);
    oled_printf_int32(90,3,SZ_xie_L_Flag,3);
    oled_printf_int32(90,4,SZ_xie_R_Flag,3);
    oled_printf_int32(90,2,search_hang,3);
//    oled_printf_int32(90,1,search_en,3);
    oled_printf_int32(60,7,white_zuo,3);
    oled_printf_int32(90,1,white_you,3);
//    oled_printf_int32(60,7,white_m,3);

//    oled_printf_int32(60,7,SZ_xie_L_Flag,3);
//    oled_printf_int32(90,7,SZ_xie_R_Flag,3);

    //up_flag==1&&zuo_xielv>=-4&&zuo_xielv<=-1&&you_xielv<=4&&you_xielv>=1&&white_l>115&&BlackEndM<=22

    if(interact_signal == outsign)
        {
            ringflag=0;
            sancha_static=0;

        }



}

void Menu_one()
{
    if(interact_signal == insign)
   {
       ringflag=0;
//       sancha_static=0;
       if(Go_L_or_R==0)
       {
           Go_L_or_R=1;
       }
       else if(Go_L_or_R==1)
       {
           Go_L_or_R=0;
       }


   }
    if(interact_signal == upsign)
       {
           ringflag=0;
    //       sancha_static=0;
           if(turn_flag==0)
           {
               turn_flag=1;
           }
           else if(turn_flag==1)
           {
               turn_flag=0;
           }


       }
    if(turn_flag==0)
    {
        oled_p6x8str(60, 2,"four ");
    }
    if(turn_flag==1)
    {
        oled_p6x8str(60, 2,"eight");
    }

    if(Go_L_or_R==1)
    {
        oled_p6x8str(60, 1,"left ");
    }
    if(Go_L_or_R==0)
    {
        oled_p6x8str(60, 1,"right");
    }

}


void Menu_GO()
{
//        static uint8 arrow = L1;    //箭头方向
//        uint8 *name[25] =   //字符串
//        {
//            "Find", "r_B_R","r_cnt",
//            "START", "r_staU","r_staD","R_err",
//            "   ","   ","  ",
//            "end_Dis","F_Dis",
//            "end-F","Fore_up"
//
//
//           // "@@@@@@", "@@@@@@","@@@@@@""@@@@@@", "@@@@@@","@@@@@@"
//        };
//
//
//
//        if (change_enable == 1) //开启参数更改
//            {
//                if (interact_signal == upsign)
//                {
//
//                    switch (arrow)
//                    {
//                        case L0:  break;
//                        case L1:  slope_R+=2;break;
//                        case L2:  r_cnt0+=1;break;
//                        case L3:  break;
//                        case L4:  r_startU+=2; break;
//                        case L5:  r_startD+=2; break;
//                        case L6:  r_error+=2; break;
//                        case L7:  break;
//                        case L8:    break;
//                        case L9:    break;
//                        case L10:  endline_display+=5;break;
//                        case L11:  Foresight_display=1; break;
//                        case L12:  endline_Foresight+=1; break;
//                        case L13:  Foresight_up+=1; break;
//
//                        default:  break;
//                    }
//
//                }
//                else if (interact_signal == downsign)
//                {
//
//                    switch (arrow)
//                    {
//
//                        case L0: break;
//                        case L1: if (slope_R >=1) slope_R-=1; break;
//                        case L2: if (r_cnt0 >=1) r_cnt0-=1;break;
//                        case L3:  break;
//                        case L4: if (r_startU >=1) r_startU-=1; break;
//                        case L5: if (r_startD >=1)r_startD-=1; break;
//                        case L6: if (r_error >=1) r_error-=1; break;
//                        case L7:  break;
//                        case L8:  break;
//                        case L9:   break;
//                        case L10:  endline_display-=5;break;
//                        case L11:  Foresight_display=0; break;
//                        case L12: if (endline_Foresight>=0)endline_Foresight-=1; break;
//                        case L13: if (Foresight_up>=0) Foresight_up-=1; break;
//                        default:  break;
//                    }
//
//                }
//            }
//            else    //未开启参数更改
//            {
//                if (interact_signal == upsign)
//                    arrow--;
//                else if (interact_signal == downsign)
//                    arrow++;
//
//                if (arrow== L14) arrow = L0;
//                if (arrow > L14) arrow = L13;
//            }
//
//        oled_p6x8str(55, 0,  "GO");
//
//        last_page=page;
//        page = arrow/7*7;
//        if(last_page != page)
//        {
//            oled_fill(0);
//
//        }
//        oled_p6x8str(0, 1,  name[page+0]);
//        oled_p6x8str(0, 2,  name[page+1]);
//        oled_p6x8str(0, 3,  name[page+2]);
//        oled_p6x8str(0, 4,  name[page+3]);
//        oled_p6x8str(0, 5,  name[page+4]);
//        oled_p6x8str(0, 6,  name[page+5]);
//        oled_p6x8str(0, 7,  name[page+6]);
//
//
//
//        switch (page)
//            {
//                case 0:
//                        oled_printf_int32(65,2,slope_R,3);    oled_printf_int32(92,2,ring_B_R,2);
//                        oled_printf_int32(65,3,r_cnt0,3);    oled_printf_int32(92,3,ring_cnt,2);
//                        oled_printf_int32(65,5,r_startU,3);   oled_printf_int32(92,5,ring_start_R,2);
//                        oled_printf_int32(65,6,r_startD,3);   oled_printf_int32(92,6,ring_start_L,2);
//                        oled_printf_int32(65,7,r_error,3);     oled_printf_int32(92,7,Error,2);
//                        break;
//                case 7:
//
//                        oled_printf_int32(90,4,endline_display,2);
//                        oled_printf_int32(90,5,Foresight_display,2);
//                        oled_printf_int32(90,6,endline_Foresight,2);
//                        oled_printf_int32(90,7,Foresight_up,2);
////                        oled_printf_int32(90,6,Width_P_R_L,5);
////                        oled_printf_int32(90,7,Width_P_R_R,5);
//
//                        break;
////             case 14:
////                         oled_printf_int32(90,7,endline_Foresight,5);
//
//    //
//    //                          break;
//                default:break;
//            }
//
//
//            switch (arrow%7)
//            {
//                case L0:    {
//                                if (change_enable == 0)oled_p6x8str(50,1,"*"); else oled_p6x8str(50,1,"&");
//                                oled_p6x8str(50,2," ");
//                                oled_p6x8str(50,7," ");
//                                oled_p6x8str(0, 1,  name[page+0]); break;
//                            }
//
//                case L1:    {
//                                oled_p6x8str(50,1," ");
//                                if (change_enable == 0)oled_p6x8str(50,2,"*"); else oled_p6x8str(50,2,"&");
//                                oled_p6x8str(50,3," ");
//                                oled_p6x8str(0, 2,  name[page+1]); break;
//                            }
//
//                case L2:    {
//                                oled_p6x8str(50,2," ");
//                                if (change_enable == 0)oled_p6x8str(50,3,"*"); else oled_p6x8str(50,3,"&");
//                                oled_p6x8str(50,4," ");
//                                oled_p6x8str(0, 3,  name[page+2]); break;
//                            }
//
//                case L3:    {
//                                oled_p6x8str(50,3," ");
//                                if (change_enable == 0)oled_p6x8str(50,4,"*"); else oled_p6x8str(50,4,"&");
//                                oled_p6x8str(50,5," ");
//                                oled_p6x8str(0, 4,  name[page+3]); break;
//                            }
//
//                case L4:    {
//                                oled_p6x8str(50,4," ");
//                                if (change_enable == 0)oled_p6x8str(50,5,"*"); else oled_p6x8str(50,5,"&");
//                                oled_p6x8str(50,6," ");
//                                oled_p6x8str(0, 5,  name[page+4]); break;
//                            }
//                case L5:    {
//                                oled_p6x8str(50,5," ");
//                                if (change_enable == 0)oled_p6x8str(50,6,"*"); else oled_p6x8str(50,6,"&");
//                                oled_p6x8str(50,7," ");
//                                oled_p6x8str(0, 6,  name[page+5]); break;
//                            }
//                case L6:    {
//                                oled_p6x8str(50,1," ");
//                                oled_p6x8str(50,6," ");
//                                if (change_enable == 0)oled_p6x8str(50,7,"*"); else oled_p6x8str(50,7,"&");
//                               oled_p6x8str(0, 7,  name[page+6]); break;
//                           }
//                default:  break;
//            }

}
void Menu_Image()
{

//    Display(Line_display);

}
void Menu_Line()
{

//   Display(Pixle_display);
//   oled_printf_int32(0,7,BlackEndLL,3);
//   oled_printf_int32(30,7,BlackEndRR,3);
//   oled_printf_int32(60,7,BlackEndML,3);
//   oled_printf_int32(90,7,BlackEndMR,3);

    oled_printf_int32(0,7,endflag,3);
    oled_printf_int32(30,7,end_count,3);
    oled_printf_int32(60,7,black_count,3);

}


void Display(enum display_mode mode)
{
    uint8 hang=0;
    uint8 lie=0;
    if(mode == Line_display)
    {

          for(hang=0;hang<Row;hang++)
          {
            if(hang>endline)//hang>endline
            {
                for(lie=0;lie<Col;lie++)
                {
                    if(lie==leftline[hang])        Pixle[hang][lie]=1;
                    else if(lie==rightline[hang])  Pixle[hang][lie]=1;
                    else if(lie==midline[hang])    Pixle[hang][lie]=1;
                    else Pixle[hang][lie]=0;
                }
            }
            else for(lie=0;lie<Col;lie++) Pixle[hang][lie]=0;
          }

    }

    if(1)//endline_display==1
    {
        for(lie=0;lie<Col;lie++)
        {
            Pixle[endline][lie]=1;
        }
    }
    if(1)//Foresight_display==1
    {
        for(lie=0;lie<Col;lie++)
        {
            Pixle[Foresight_hang][lie]=1;
        }
    }

    oled_dis_bmp(MT9V03X_H, MT9V03X_W, Pixle[0],0);
}
