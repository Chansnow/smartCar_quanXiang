#include "FIRELOCK.h"

uint8 change_enable = 0;
uint8 cwheels=0;
enum key_sign interact_signal = nosign;
enum page_def interact_page = main_page;

uint8 last_page=0;
uint8 page = 0;
extern float gyro_c;
extern uint8 sancha_static;

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
        case PID_page: Menu_PID();      break;
        case SPEED_page:  Menu_SPEED();    break;
       default :        Menu_Main();        break;
    }
}


void Menu_Main()
{

//    oled_printf_int32(100,0,RF,3);//RF
//    oled_printf_int32(100,7,RB,3);//RB
//    oled_printf_int32(0,7,LB,3);//LB
//    oled_printf_int32(0,0,LF,3);//LF
    oled_printf_float(0,6,gyro_c,2,3);
    oled_printf_float(0,5,sancha_static,2,3);
//    oled_printf_int32(30,7,wheels.v3,3);//LB
//    oled_printf_int32(30,0,wheels.v2,3);//LF
//    oled_printf_int32(70,0,wheels.v1,3);//RF
//    oled_printf_int32(70,7,wheels.v4,3);//RF

    oled_printf_int32(1,3,Track_Line_Num,2);
    if(mpu_set==1) oled_printf_int32(50,3,gyro_z,5);
    else if(mpu_set==0)oled_printf_int32(50,3,mpu_gyro_z+mpu_offset,5);
    oled_printf_int32(52,5,Foresight,3);
    oled_printf_int32(52,6,ALL_flag,3);
    oled_printf_int32(52,7,GO_Speed,3);

    static uint8 arrow = L1;    //箭头方向
        uint8 *name[10] =   //字符串
        {
                "start", "wait"
        };


        if (change_enable == 1)
        {
            if (interact_signal == outsign)
            {
                Skey_flag = !Skey_flag;
                oled_fill(0);
            }
            if (interact_signal == upsign)
            {
                cwheels++;
                if(cwheels>10)
                {
                    cwheels=0;
                }

                ccwheels();

            }

            if (interact_signal == downsign)
            {
                cwheels--;
                if(cwheels==255)
                {
                   cwheels=10;
                }

                ccwheels();
            }


                    oled_p6x8str(35, 1, "*");//反白
                    oled_p6x8str(40, 1, "c_go");
                    oled_p6x8str(66, 1, "*");//反白
                    oled_uint16(76, 1,  cwheels);
        }
        else
        {
            if (interact_signal == upsign)
            {
                arrow--;
                Skey_flag=0;
            }
            else if (interact_signal == downsign)
            {
                arrow++;
                Skey_flag=0;
            }
            if (arrow > L4) arrow = L1;
            if (arrow < L1) arrow = L4;
            run_mode = arrow-1;

            oled_p6x8str(35, 1, " ");//不反白
            oled_p6x8str(40, 1, "c_go");
            oled_p6x8str(66, 1, " ");//不反白
            oled_uint16(76, 1,  cwheels);
        }

        if(change_enable == 0)
        {
            oled_p6x8str(52, 4, Skey_flag ==0? name[1]:name[0]);
            oled_p6x8str(45, 4, " ");//不反白
        }
        else
        {
            oled_p6x8str(45, 4, "*");//反白
            oled_p6x8str(52, 4, Skey_flag ==0? name[1]:name[0]);
        }

}

void Menu_PID()
{
    static uint8 save_flag = 0;

    static uint8 arrow = L1;    //箭头方向
    uint8 *name[27] =   //字符串
    {
        "Z_P0   ", "Z_P1   ","Z_speed","Z_PI   ","Z_PD   ",
        "OUT_P   ","OUT_Z   ",
        "S_P    ","S_I    ","S_D    ",
        "K_Q    ","K_R    ","is_fuzzy",
        "pvlr_p","pvlr_d","Z_xp0","Z_xp1","Z_xi","Z_xd"
    };



    if (change_enable == 1) //开启参数更改
        {
            if (interact_signal == upsign)
            {
                save_flag = 1;
                switch (arrow)
                {
                    case L0:  position_zp0+=5;break;
                    case L1:  position_zp1+=5; break;
//                    case L2:  def_speed+=10;break;
                    case L3:  position_zi0+=5; break;
                    case L4:  position_zd0+=5; break;

//                    case L5:  limit_p_out+=5; break;
//                    case L6:  limit_pid_out+=5; break;

                    case L7:  SETmotor_kp+=100; break;
                    case L8:  SETmotor_ki+=100; break;
                    case L9:  SETmotor_kd+=100; break;

//                    case L10:  gyro_kalman_q+=5;break;
//                    case L11: gyro_kalman_r+=5;break;
                    case L12: is_fuzzy+=2;break;
//                    case L13:  pvlr_p+=10;break;
//                    case L14:  pvlr_d+=10;break;

                    case L15:  position_zp0_x+=5;break;
                    case L16:  position_zp1_x+=5; break;
//                    case L17:  position_zi0_x+=5; break;
                    case L18:  position_zd0_x+=5; break;





                    default:  break;
                }
            }
            else if (interact_signal == downsign)
            {
                save_flag = 1;
                switch (arrow)
                {

                    case L0: if (position_zp0 >= 1) position_zp0-=1;break;
                    case L1: if (position_zp1 >=1) position_zp1-=1; break;
                    //case L2: if (def_speed >=1) def_speed-=10;break;
                    case L3: if (position_zi0 >=1) position_zi0-=1; break;
                    case L4: if (position_zd0 >=1) position_zd0-=1; break;
//                    case L5: if (limit_p_out >=1)limit_p_out-=1; break;
//                    case L6: if (limit_pid_out >=1) limit_pid_out-=1; break;
                    case L7: if (SETmotor_kp >=1) SETmotor_kp-=100; break;
                    case L8: if (SETmotor_ki >=1) SETmotor_ki-=100; break;
                    case L9: if (SETmotor_kd >=1) SETmotor_kd-=50; break;
//                    case L10: if (gyro_kalman_q >=1) gyro_kalman_q-=5;break;
//                    case L11: if (gyro_kalman_r >=1) gyro_kalman_r-=5;break;
                    case L12: if (is_fuzzy >=1) is_fuzzy-=1;break;
//                    case L13: if (pvlr_p >=1) pvlr_p-=10;break;
//                    case L14:  if (pvlr_d >=1)pvlr_d-=10;break;

                   case L15: if (position_zp0_x >= 1) position_zp0_x-=1;break;
                   case L16: if (position_zp1_x >=1) position_zp1_x-=1; break;
//                   case L17: if (position_zi0_x >=1) position_zi0_x-=1; break;
//                   case L18: if (position_zd0_x >=1) position_zd0_x-=1; break;


                    default:  break;

                }
                    if(pvlr_p <0) pvlr_p=0;
                    if(pvlr_d <0) pvlr_d=0;
            }
        }
        else    //未开启参数更改
        {
            if (interact_signal == upsign)
                arrow--;
            else if (interact_signal == downsign)
                arrow++;

            if (arrow== L19) arrow = L0;
            if (arrow > L19) arrow = L18;
        }

    oled_p6x8str(55, 0,  "PID");

    last_page=page;
    page = arrow/7*7;
    if(last_page != page)
    {
        oled_fill(0);

    }
    oled_p6x8str(0, 1,  name[page+0]);
    oled_p6x8str(0, 2,  name[page+1]);
    oled_p6x8str(0, 3,  name[page+2]);
    oled_p6x8str(0, 4,  name[page+3]);
    oled_p6x8str(0, 5,  name[page+4]);
    oled_p6x8str(0, 6,  name[page+5]);
    oled_p6x8str(0, 7,  name[page+6]);



    switch (page)
        {
            case 0:
                    oled_printf_int32(90,1,position_zp0,5);
                    oled_printf_int32(90,2,position_zp1,5);
                    oled_printf_int32(90,3,def_speed,5);
                    oled_printf_int32(90,4,position_zi0,5);
                    oled_printf_int32(90,5,position_zd0,5);
                    oled_printf_int32(90,6,limit_p_out,5);
                    oled_printf_int32(90,7,limit_pid_out,5);
                    break;
            case 7: oled_printf_int32(90,1,SETmotor_kp,5);
                    oled_printf_int32(90,2,SETmotor_ki,5);
                    oled_printf_int32(90,3,SETmotor_kd,5);
                    oled_printf_int32(90,4,gyro_kalman_q,5);
                    oled_printf_int32(90,5,gyro_kalman_r,5);
                    oled_printf_int32(90,6,is_fuzzy,5);
                    oled_printf_int32(90,7,pvlr_p,5);
                    break;
         case 14:
                     oled_printf_int32(90,1,pvlr_d,5);
                     oled_printf_int32(90,2,position_zp0_x,5);
                     oled_printf_int32(90,3,position_zp1_x,5);
                     oled_printf_int32(90,4,position_zi0_x,5);
                     oled_printf_int32(90,5,position_zd0_x,5);
//
                          break;
            default:break;
        }

      display_key(arrow,change_enable,name,page);


       if (save_flag == 1)
       {
           oled_p6x8str(120,0,"*");
       }
       else
       {
           oled_p6x8str(120,0," ");
       }
       if (interact_signal == outsign && save_flag == 1)
       {
           save_flag = 0;
           FLASH_WriteALL();
       }





}
void Menu_SPEED()
{
    static uint8 save_flag = 0;

            static uint8 arrow = L1;    //箭头方向
            uint8 *name[30] =   //字符串
            {
                "Set_S ", "mode_S","HIGH_S","LOW_s",
                "steer_go","pvfb  ","S_Limit",
                "MPU_set ","MPU_d   ",
                "ring_e_F","k_curve","k_c_in","k_c_out",
                "Rush_S ", "RING_S","R_ru_S"  ,"X_S",
                "H_icm","K_con","e_F_th"

    //            "K_Q    ","K_R    ",
            };



            if (change_enable == 1) //开启参数更改
                {
                    if (interact_signal == upsign)
                    {
                        save_flag = 1;
                        switch (arrow)
                        {
                            case L0:  Set_Speed+=10;break;
                            case L1:  mode_SP=1; break;
                            case L2:  HIGH_Speed+=10;break;
                            case L3:  LOW_speed+=10; break;
                            case L4:  steer_go+=1; break;

//                          case L5:  pvfb+=5; break;
//                          case L6:  Speed_Limit+=10;break;
                          case L7:  mpu_set=1;break;
                          case L8:  mpu_offset+=2; break;
//                          case L9:  ring_e_F+=1; break;
                          case L10: k_curve+=1; break;
                          case L11: k_curve_in+=1; break;
                          case L12: k_curve_out+=1; break;
                          case L13:  Rush_Speed+=10; break;
                          case L14:  RING_Speed+=10; break;
                          case L15:  RING_ru_Speed+=10; break;
                          case L16:  X_Speed+=10; break;
                          case L17:  high_icm+=10; break;
                          case L18:  K_centre+=1; break;
                          case L19:  e_Foresight_threshold+=1; break;

                        //  case L16:  RING_Speed+=10; break;
    //                        case L9:  SETmotor_kd+=100; break;
    //
    //                        case L10:  gyro_kalman_q+=5;break;
    //                        case L11: gyro_kalman_r+=5;break;

                            default:  break;
                        }
                    }
                    else if (interact_signal == downsign)
                    {
                        save_flag = 1;
                        switch (arrow)
                        {

                            case L0: if (Set_Speed >=1) Set_Speed-=10; break;
                            case L1: mode_SP=0; break;
                            case L2: if (HIGH_Speed >=1) HIGH_Speed-=10;break;
                            case L3: if (LOW_speed >=1) LOW_speed-=5; break;
                            case L4: steer_go-=1; break;
//                            case L5: if (pvfb >=1)pvfb-=1; break;
//                            case L6: if (Speed_Limit >=1) Speed_Limit-=10;break;
                            case L7: mpu_set=0;break;
                            case L8:  mpu_offset-=1; break;

//                            case L9: ring_e_F-=1; break;
                            case L10: if (k_curve >=0) k_curve-=1; break;
                            case L11: if (k_curve_in >=0) k_curve_in-=1; break;
                            case L12: if (k_curve_out >=0) k_curve_out-=1; break;
                            case L13: if (Rush_Speed >=1) Rush_Speed-=10; break;
                            case L14: if (RING_Speed >=0) RING_Speed-=10; break;
                            case L15: if (RING_ru_Speed >=0) RING_ru_Speed-=10; break;
                            case L16: if (X_Speed >=0) X_Speed-=10; break;
                            case L17: if (high_icm >=0) high_icm-=10; break;
                            case L18: if (K_centre >=0) K_centre-=1; break;
                            case L19: if (e_Foresight_threshold >=0) e_Foresight_threshold-=1; break;
    //                        case L9: if (SETmotor_kd >=1) SETmotor_kd-=100; break;
    //                        case L10: if (gyro_kalman_q >=1) gyro_kalman_q-=5;break;
    //                        case L11: if (gyro_kalman_r >=1) gyro_kalman_r-=5;break;
                            default:  break;
                        }

                    }
                }
                else    //未开启参数更改
                {
                    if (interact_signal == upsign)
                        arrow--;
                    else if (interact_signal == downsign)
                        arrow++;

                    if (arrow== L20) arrow = L0;
                    if (arrow > L20) arrow = L19;
                }

            oled_p6x8str(55, 0,  "SPEED");

            last_page=page;
           page = arrow/7*7;
           if(last_page != page)
           {
               oled_fill(0);

           }

            oled_p6x8str(0, 1,  name[page+0]);
            oled_p6x8str(0, 2,  name[page+1]);
            oled_p6x8str(0, 3,  name[page+2]);
            oled_p6x8str(0, 4,  name[page+3]);
            oled_p6x8str(0, 5,  name[page+4]);
            oled_p6x8str(0, 6,  name[page+5]);
            oled_p6x8str(0, 7,  name[page+6]);



            switch (page)
                {
                    case 0:
                            oled_printf_int32(90,1,Set_Speed,5);
                            oled_printf_int32(90,2,mode_SP,5);
                            oled_printf_int32(90,3,HIGH_Speed ,5);
                            oled_printf_int32(90,4,LOW_speed,5);
                            oled_printf_int32(90,5,steer_go,5);
                            oled_printf_int32(90,6,pvfb,5);
                            oled_printf_int32(90,7,Speed_Limit,5);
                            break;
                   case 7:
                           oled_printf_int32(90,1,mpu_set,5);
                           oled_printf_int32(90,2,mpu_offset,5);
                           oled_printf_int32(90,3,ring_e_F,5);
                           oled_printf_int32(90,4,k_curve,3);
                           oled_printf_int32(90,5,k_curve_in,3);
                           oled_printf_int32(90,6,k_curve_out,3);
                           oled_printf_int32(90,7,Rush_Speed,5);
                           break;
                  case 14:
                           oled_printf_int32(90,1,RING_Speed,5);
                           oled_printf_int32(90,2,RING_ru_Speed,5);
                           oled_printf_int32(90,3,X_Speed,5);
                           oled_printf_int32(90,4,high_icm,5);
                           oled_printf_int32(90,5,K_centre,5);
                           oled_printf_int32(90,6,e_Foresight_threshold,5);

                           break;
                    default:break;
                }

               display_key(arrow,change_enable,name,page);

               if (save_flag == 1)
               {
                   oled_p6x8str(120,0,"*");
               }
               else
               {
                   oled_p6x8str(120,0," ");
               }
               if (interact_signal == outsign && save_flag == 1)
               {
                   save_flag = 0;
                   FLASH_WriteALL();
               }
}

void display_key(int arrow,uint8 change_enable,uint8 **name,uint8 page)
{
    switch (arrow%7)
                    {
                        case L0:    {
                                        if (change_enable == 0)oled_p6x8str(50,1,"*"); else oled_p6x8str(50,1,"&");
                                        oled_p6x8str(50,2," ");
                                        oled_p6x8str(50,3," ");
                                        oled_p6x8str(50,4," ");
                                        oled_p6x8str(50,5," ");
                                        oled_p6x8str(50,6," ");
                                        oled_p6x8str(50,7," ");
                                        oled_p6x8str(0, 1,  name[page+0]);
                                        break;
                                    }

                        case L1:    {
                                        oled_p6x8str(50,1," ");
                                        if (change_enable == 0)oled_p6x8str(50,2,"*"); else oled_p6x8str(50,2,"&");
                                        oled_p6x8str(50,3," ");
                                        oled_p6x8str(50,4," ");
                                        oled_p6x8str(50,5," ");
                                        oled_p6x8str(50,6," ");
                                        oled_p6x8str(50,7," ");
                                        oled_p6x8str(0, 2,  name[page+1]);
                                        break;
                                    }

                        case L2:    {
                                        oled_p6x8str(50,1," ");
                                        oled_p6x8str(50,2," ");
                                        if (change_enable == 0)oled_p6x8str(50,3,"*"); else oled_p6x8str(50,3,"&");
                                        oled_p6x8str(50,4," ");
                                        oled_p6x8str(50,5," ");
                                        oled_p6x8str(50,6," ");
                                        oled_p6x8str(50,7," ");
                                        oled_p6x8str(0, 3,  name[page+2]);
                                        break;
                                    }

                        case L3:    {
                                        oled_p6x8str(50,1," ");
                                        oled_p6x8str(50,2," ");
                                        oled_p6x8str(50,3," ");
                                        if (change_enable == 0)oled_p6x8str(50,4,"*"); else oled_p6x8str(50,4,"&");
                                        oled_p6x8str(50,5," ");
                                        oled_p6x8str(50,6," ");
                                        oled_p6x8str(50,7," ");
                                        oled_p6x8str(0, 4,  name[page+3]);
                                        break;
                                    }

                        case L4:    {
                                        oled_p6x8str(50,1," ");
                                        oled_p6x8str(50,2," ");
                                        oled_p6x8str(50,3," ");
                                        oled_p6x8str(50,4," ");
                                        if (change_enable == 0)oled_p6x8str(50,5,"*"); else oled_p6x8str(50,5,"&");
                                        oled_p6x8str(50,6," ");
                                        oled_p6x8str(50,7," ");
                                        oled_p6x8str(0, 5,  name[page+4]);
                                        break;
                                    }
                        case L5:    {
                                        oled_p6x8str(50,1," ");
                                        oled_p6x8str(50,2," ");
                                        oled_p6x8str(50,3," ");
                                        oled_p6x8str(50,4," ");
                                        oled_p6x8str(50,5," ");
                                        if (change_enable == 0)oled_p6x8str(50,6,"*"); else oled_p6x8str(50,6,"&");
                                        oled_p6x8str(50,7," ");
                                        oled_p6x8str(0, 6,  name[page+5]);
                                        break;
                                    }
                        case L6:    {
                                        oled_p6x8str(50,1," ");
                                        oled_p6x8str(50,2," ");
                                        oled_p6x8str(50,3," ");
                                        oled_p6x8str(50,4," ");
                                        oled_p6x8str(50,5," ");
                                        oled_p6x8str(50,6," ");
                                        if (change_enable == 0)oled_p6x8str(50,7,"*"); else oled_p6x8str(50,7,"&");
                                       oled_p6x8str(0, 7,  name[page+6]);
                                       break;
                                   }
                        default:  break;
                    }

}




