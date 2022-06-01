

#ifndef CODE_MENU_H_
#define CODE_MENU_H_






enum display_mode
{
    Pixle_display,
    Line_display,

};

enum key_sign
{
    nosign,
    upsign,
    downsign,
    leftsign,
    rightsign,
    insign,
    outsign,
};

enum row_x
{
  row_1 = 0*12,
  row_2 = 1*12,
  row_3 = 2*12,
  row_4 = 3*12,
  row_5 = 4*12,

};

enum page_def
{
  main_page,
  PID_page,
  SPEED_page,

//  blt_page,
//  mic_page,
    max_page,
};
enum Run_mode
{
  bcn_mode,
  blt_mode,
  pwm_mode,
  cln_mode,
  max_mode,
};
enum extra_line
{
    L0,L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,
    L15,L16,L17,L18,L19,L20,L21,L22,L23,
    LMAX,
};
enum key_sign Menu_Getsign(void);
void Menu_Key_Page_Handle(void);
void Menu_Display(void);
void Menu_Main(void);
void Menu_PID(void);
void Menu_SPEED(void);
void Display(enum display_mode mode);
void Menu_player(void);
void Menu_MODE(void);
void display_key(int arrow,uint8 change_enable,uint8 **name,uint8 page);
#endif /* CODE_MENU_H_ */
