
#include "FIRELOCK.h"



/******************************************************************************
Բ��������
Բ��ʶ�� ���ȶ��� ���ܴ�Բ��ʶ���� ����ʶ���ȶ� ��Ҫ��ǿ
��Բ�� ���ȶ��� ��Բ����ֹ�� ���ߴ�����Ż�
��Բ�� ���ȶ��� ��������Ż�

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
    //����ʼ��
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
      if(ring_start_L>r_startU&&ring_start_L<r_startD)  //�������������ƴ��  zuo  &&Error>45&&Error<75
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
    //����ʼ��
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
      if(ring_start_R> r_startU &&ring_start_R <r_startD )//  //�������������ƴ��  you&&Error>38&&Error<72

      {
       // oled_printf_int32(90,1,1111,3);
        ringflag=2;
      }
    }
    else
        ringflag=0;//oled_printf_int32(90,1,0000,3);
  }
}
//Բ��ʶ��
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
  //����ʼ��
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
  //���յ�
  if(ring_start_L_Flag==1)
  {
    //���յ�
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
    //��б��
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
  //����ʼ��
  for(uint8 hang=Row-2;hang>DropRow+2;hang--)
  {
    if(rightlineflag[hang]!=0&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]==0)
    {
      ring_start_R=hang;
      ring_start_R_Flag=1;
      break;
    }
  }
  //���յ�
  if(ring_start_R_Flag==1)
  {
    //���յ�
    for(uint8 hang=ring_start_R;hang>DropRow;hang--)
    {
      if(rightlineflag[hang]==0&&rightlineflag[hang-1]==0&&rightlineflag[hang-2]!=0)
      {
        ring_end_R=hang;
        ring_end_R_Flag=1;
        break;
      }
    }
    //��б��
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
  //��Բ�� ������������ҵ��ҵ�
  /*
       * �Ҷ���������������Ӧ�����涪�ߣ����治����
       * ��ֹб��ʮ�֣�ȥ������ĵ㣬��Ӧ�ó��ְ׵�
       * ��ֹС�����У��������ߣ�Ӧ����һ����������䡣С�����л�Ҫ�õ�����б�ʣ�б�ʲ��ɹ�����Ҫ��
       * ������㣬�ڰ����䣬Ӧ��������
  */
  //��Բ�� ���㶼�ҵ�
  if(ring_start_L_Flag==1&&ring_xie_L_Flag==1&&ring_start_R_Flag==0&&ring_end_R_Flag==0&&ring_xie_R_Flag==0&&DropRow<30&&Error>45&&Error<75)//
  {

      if(ring_end_L_Flag==1)//СԲ��
      {
         // oled_printf_int32(92,5,1,2);
          //������Ҷ��� ��ȫ����ȫ����
        for(uint8 hang=ring_start_L;hang>ring_end_L;hang--)
        {
          if(rightlineflag[hang]==0)//��Ӧ�ó��ֵ����
            R_lost_cnt++;
          if(leftlineflag[hang]==1)
            L_find_cnt++;
          //����а׵������� ��ֹб��ʮ������
          for(uint8 lie=110;lie<Col-1;lie++)
          {
            if(Pixle[hang][lie]==white)//���ұ߲�Ӧ�ó��ְ���
              ring_white++;
          }
        }
        //��ֹ��������ȫ�� ��ֹС������
        for(uint8 hang=ring_end_L;hang>DropRow;hang--)
        {
          if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
            ALL_find_cnt++;
        }
      }
        else//��Բ��
        {
        //������Ҷ��� ��ȫ����ȫ����
           // oled_printf_int32(92,5,2,2);
            for(uint8 hang=ring_start_L;hang>ring_start_L-5;hang--)
            {
              if(rightlineflag[hang]==0)
                R_lost_cnt++;
              if(leftlineflag[hang]==1)
                L_find_cnt++;
              //����а׵������� ��ֹб��ʮ������
              for(uint8 lie=110;lie<Col-1;lie++)
              {
                if(Pixle[hang][lie]==white)
                  ring_white++;
              }
            }
            //��ֹ��������ȫ�� ��ֹС������
                for(uint8 hang=DropRow+10;hang>DropRow;hang--)
                {
                  if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
                    ALL_find_cnt++;
                }

         }
    //����а׵������� ��ֹб��ʮ������
    for(uint8 hang=35;hang>30;hang--)//���ұ߲�Ӧ�ó��ְ���
    {
      for(uint8 lie=110;lie<Col-1;lie++)
      {
        if(Pixle[hang][lie]==white)
          ring_white_di++;
      }
    }
    //������ �׺ںڰ����� Բ����һ����
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
    //��һ�����
    //�ж�������С����־λ
    if(ring_tiaobian>=2&& R_lost_cnt<=1&&L_find_cnt<=2
            &&ring_white<15&&ring_white_di<49
            &&ALL_find_cnt>=5)//&&ring_start_L-ring_end_L>=2
    {
      for(uint8 hang=ring_start_L;hang<ring_start_L+8;hang++)//������8��
      {
        if((leftline[hang]-leftline[hang+1])<0)//    "\"�������
          if((leftline[hang]-leftline[hang+1])<=(leftline[hang+1]-leftline[hang+2]))//��ֵ������
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
  //��Բ��
  if(ring_start_L_Flag==0&&ring_end_L_Flag==0&&ring_xie_L_Flag==0&&ring_start_R_Flag==1&&ring_xie_R_Flag==1&&DropRow<30&&Error>45&&Error<75)//
  {

      bbb_test[0]=1;
      if(ring_end_R_Flag==1)
      {
          //������Ҷ��� ��ȫ����ȫ����
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
          //��ֹ��������ȫ�� ��ֹС������
          for(uint8 hang=ring_end_R;hang>DropRow;hang--)
          {
            if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
              ALL_find_cnt++;
          }

      }
      else
      {                                            //�Ƿ��Ǽ��壬�Ժ��ٵ�
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
          //��ֹ��������ȫ�� ��ֹС������
         for(uint8 hang=DropRow+10;hang>DropRow;hang--)
         {
           if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
             ALL_find_cnt++;
         }


      }

    //����а׵������� ��ֹб��ʮ������
    for(uint8 hang=35;hang>30;hang--)
    {
      for(uint8 lie=10;lie>0;lie--)
      {
        if(Pixle[hang][lie]==white)
          ring_white_di++;
      }
    }
    //������ �׺ںڰ����� Բ����һ����
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
    //�ж�������С����־λ
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
//��Բ������
void ring_ru(void)
{
  //��Բ��
  if(ringflag==1)
  {
      ring_R=Col/2,ring_L=Col/2;
      ring_R=Col/2;
      ring_end_L=Row-1,ring_end_L_Flag=0;
    uint8 ring_hang_L[Col];
//    uint8 ru_bed_point=0; //Ĭ�Ϻϸ񣬼�鲻�ϸ�ĵ�
    xieflag=0;
    //���յ�
    for(uint8 hang=Row-2;hang>endline+3;hang--)
    {
      if(leftlineflag[hang]==0&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]!=0)
      {
        ring_end_L=hang;
        ring_end_L_Flag=1;
        break;
      }
    }
    //��ֹ�в���
    //����߰׵���
    int lost=0;
    for(uint8 hang=55;hang>45;hang--)  //�������10�У����ߵĶ�����
    {
      if(leftlineflag[hang]==0||leftline[hang]<5)
      {
        lost++;
      }
    }
    if(lost>=7)
    {
      //��ֹ�б궨 (���жȼ���)
      for(uint8 hang=50;hang>endline;hang--)   //�Ե�20��Ϊ��ֹ�вο���
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
      //��ֹ�б궨 (���жȼ���)
      for(uint8 hang=50;hang>endline;hang--)//�Ե�45��Ϊ��ֹ�вο���
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

    //����
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
  //��Բ��
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
    //��ֹ�в���
    //����߰׵���
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
      //��ֹ�б궨 (���жȼ���)
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
      //��ֹ�б궨 (���жȼ���)
      for(uint8 hang=50;hang>endline;hang--)
      {
        if(Pixle[hang][Col-45]==black&&Pixle[hang+1][Col-45]==black)
        {
          endline=hang+2;
          break;
        }
      }
    }

    //�ҹյ����־λ
    //ԭʼͼ����ɨ�� �ֲ�����ȷ��Щ��û�ҵ� �Ժ��Ż�
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
    //����
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

  //��Բ��
  if(ringflag==3)
  {
      uint8 ring_xie_R=0;
      uint8 ring_chu_num=0;
      uint8 ring_end_L=Row-1;
      uint8 R_lost_cnt=0,ALL_find_cnt=0,L_find_cnt=0;
      uint8 ring_kong[Row]={0};
      ring_end_L_Flag=0;
    //�����ҹ�
    for(uint8 hang=Row-2;hang>endline+5;hang--)   //�ҵ��ұߵ��Ǹ�б��
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
    if((ring_xie_R==0||ring_xie_R>35)&&xieflag!=0) //��б���Ҫ��
    {
        //aaa_test[2]=1;
      for(uint8 hang=Row-5;hang>endline;hang--)
      {
        for(uint8 lie=0;lie<Col;lie++)
        {
          if(Pixle[hang][lie]==white&&(leftline[hang]<5||leftlineflag[hang]==0)&&(rightline[hang]>Col-5||rightlineflag[hang]==0))
            ring_kong[hang]++; //���Ϊ��ɫ�������е��������߶�����
        }
        if(ring_kong[hang]>Col-10)//��Ϊ���ܳ��������������Χ���һ��
          ring_chu_num++;//��һ�м���ȫ��Ϊ��ɫ
      }

      if(ring_chu_num>5) //����ȡ��������ȫ��Ϊ��ɫ���д���5
      {


        for(uint8 hang=Row-1;hang>endline;hang--)//ֱ��ȷ�����ߺ�����
        {
          leftline[hang]=0;
          rightline[hang]=75-endline;//110
          leftlineflag[hang]=1;
          rightlineflag[hang]=1;
        }
        xieflag=2;
      }
      else//���������ٴ���5ʱ����ʱ����ringflag
      {


        if(DropRow<30)
        {
          uint8 temp=0;
          for(uint8 hang=Row-2;hang>DropRow+2;hang--)
          {
            if(leftlineflag[hang+2]==0&&leftlineflag[hang+1]==0&&leftlineflag[hang]==0&&leftlineflag[hang-1]==0&&leftlineflag[hang-2]!=0)
            {//�ҵ������������һ��

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

          for(uint8 hang=ring_end_L-1;hang>ring_end_L-6;hang--)//�������������У��ҵ������ ring_end_L ���������
          {
            if(leftlineflag[hang]==1&&rightlineflag[hang]==1)
              ALL_find_cnt++;//Ѱ�����������ұ�û�ж��ߵ�����
          }
          if(ring_end_L>50) ring_end_L=50;
          temp=ring_end_L+6;//��� ring_end_L ����ĵ�����
          if(temp>60) temp=60;
          for(uint8 hang=ring_end_L+1;hang<temp;hang++)//�������������У��ҵ������ ring_end_L ���������
          {
            if(leftlineflag[hang]==1)//��Ӧ�ó��ֵ����
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
          if(L_find_cnt<=2&&R_lost_cnt<=2&&ALL_find_cnt>=3)//�������

          {

            if(xieflag==2)
            {
               // aaa_test[8]=1;
              ringflag=5;
            }

          }
          else//���������
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
    else//�ҵ�б�㣬��������Ҫ��ʱ������
        //����û���ҵ�б�㣬��ʱ����ͨ�������
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
  //��Բ��
  else if(ringflag==4)
  {
      uint8 ring_xie_L=0;
      uint8 ring_chu_num=0;
      uint8 ring_end_R=Row-1;
      uint8 L_lost_cnt=0,ALL_find_cnt=0,R_find_cnt=0;
      uint8 ring_kong[Row]={0};
      ring_end_R_Flag=0;
    //��б��
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










