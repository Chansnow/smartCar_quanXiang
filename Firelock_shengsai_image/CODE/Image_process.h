
#ifndef CODE_IMAGE_PROCESS_H_
#define CODE_IMAGE_PROCESS_H_

extern int midline[Row];
extern int leftline[Row];
extern int rightline[Row];
extern uint8 endline;
extern uint8 leftlineflag[Row];
extern uint8 rightlineflag[Row];
extern uint8 track_width[Row];







void GetBlackEndParam(void);

extern uint8 BlackEndLL;
extern uint8 BlackEndM;
extern uint8 BlackEndRR;
extern uint8 scratchflag;

extern uint8 BlackEndMaxMax;
extern uint8 DropRow;

extern int scratch_cnt;


#define  hstart     55

////取最大值
//#define max(a,b)                ((a)>(b)?(a):(b));
//取绝对值
#define Abs(a)               ((a)>(0)?(a):(-a));
void get_route_one(uint8 hang,uint8 start);
void get_route_all(void);
void get_route_endline(void);
void get_route_midline(void);
int regression(uint8 startline,uint8 endline,int p[]);
void connect(uint8 hang_start,uint8 hang_end,int p[]);
void scratch_line(void);
void ramp_find(void);
void ramp_deal(void);
 void stop_line(void);



#endif /* CODE_IMAGE_PROCESS_H_ */
