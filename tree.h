#include "gsang.h"
#include "TH1.h"
#include <TTree.h>
#include <TFile.h>
#include <TMath.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define M 200.0  //RC 常数，单位暂不清楚
#define xa_MM 350 //RC 常数
#define Kth 146
#define NGE 110 //GS 通道数
#define NGEC 20 //clover 通道数
#define Navth 3000
#define dBLth 500

#define Pars_beta 0.0270








#define MAXTRACELEN 8192
#define MAXEV 1000

//新生成数据，用户根据需要自行扩充
typedef struct DGSEVENT
{
  short int               id;//探测器编号 0-109
  double		  ch;//原始能量道址
  double		  e_nodop;//未修正多普勒刻度能量
  double		  e;//多普勒修正能量
  
  unsigned short int      tpe;//探测器类型
  unsigned short int      tid;//探测器编号 1-110
 

  unsigned long long int  ts;//event_timestamp
  
  unsigned long long int  tscorr;//time walk corr
  int                     dtlast;//当前触发与上个触发的时间差
  int                     dtpeak;//peak_timestamp 未完成，可能参考程序中的数据解码存在问题

  unsigned short int      flag;//反康标记     addback标记
  int                     dt;//Ge与BGO的时间差       addback两个晶体的时间差
  
  bool	                  timestamp_match_flag;
  bool	                  cfd_valid_flag;
  bool	                  peak_valid_flag;
  bool	                  pileup_flag;
  double                  cfd;

} DGSEVENT;


typedef struct DFMAEVENT
{
  unsigned short int      flag;//探测器标记 1 Si Front   2 Si Back   3 Si box   4 PPAC   5 MWPC  6 DE
  double                  e;//刻度能量
  int                     ch;//原始能量
  short int               id;// Si 0-159  box 0-55   FP 0/1   MWPC 0/1/2/3
  unsigned short int      tpe;
  unsigned short int      tid;
  short int               tot;//number over threshold
  unsigned long long int  ts;//时间戳
  unsigned long long int  prets;
  int wheel;

  // 如果要分析波形，则需要使用 基线采样/波形长度/波形 三个变量
  
}  DFMAEVENT;


// 原始数据定义，请勿修改
typedef struct wuDGSEVENT
{
  unsigned short int      tpe;//实际的探测器类型 tpe[1Ge/2BGO/3SIDE] 
  unsigned short int      tid;//实际的探测器编号 tid[1-110] 

  unsigned long long int  event_timestamp;//时间戳
  unsigned long long int  last_disc_timestamp;//Timestamp of previous discriminator 上一个触发的时间戳的后30位
  unsigned long long int  peak_timestamp;//Timestamp of peak detect

  // The Timestamp of Previous Discriminator is latched every time the discriminator fires and provides the time differential between the time of the event being read out and the previous discriminator firing, even if that event was not read out. 
  bool                    timestamp_match_flag;//TSM 有用 
  bool                    cfd_valid_flag;//CV  有用	                   
  bool                    peak_valid_flag;//PV  有用
  bool                    pileup_flag ;//PU   有用

  // The Sampled baseline differs from the Base Sample in that it is the current running sum of presumed baseline samples across the 10.24usec buffer; as such it is less filtered than the Base Sample.
  int                     sampled_baseline;// sampled baseline   有用
  int                     cfd_sample_0;//CFD Sample 0   有用
  int                     cfd_sample_1;//CFD Sample 1   有用
  int                     cfd_sample_2;//CFD Sample 2   有用
  
  int                     sum1;//pre-rise sum   有用
  int                     sum2;//post-rise sum   有用

  // The Post‐rise sample is the single ADC data point at the beginning of the post‐rise buffer sampled when the discriminator fired. 
  unsigned short int      m2begin;//post-rise end sample   有用
  unsigned short int      m2end;//post-rise begin sample   有用
  
  //The Pre‐rise enter sample and Pre‐rise leave sample are the single ADC data points at the beginning and end of the pre‐rise buffer sampled when the discriminator fired. 
  unsigned short int      m1begin;//pre-rise begin sample   有用
  unsigned short int      m1end;//pre-rise end sample   有用

  // The Peak Sample value is the single ADC data sample entering the pre‐rise buffer at the moment the peak detector logic has fired; this is intended to provide an amplitude value to go along with the time value Timestamp of Peak detect. 
  unsigned short int      peak_sample;//peak sample   有用

  // The Base Sample value is a sample of the maximally filtered running baseline calculation, captured at the time the discriminator fired. 
  unsigned short int      base_sample;//base sample   有用


  // The Last Post‐Rise enter and Last Post‐Rise leave Samples are the two ADC samples at beginning and end of the post‐rise buffer saved from the previous discriminator firing.
  unsigned short int      m2last_begin_sample;
  unsigned short int      m2last_end_sample;
} wuDGSEVENT;




// 原始数据定义，请勿修改
typedef struct wuDFMAEVENT
{
  // tpe 5=DSSD 6:FP  12:SIBOX
  // tid  1-160 front   161-320 back
  
  int                     ch;    // 计算得到 (postrisesum-prerisesum)/10
  unsigned short int      tpe, tid;//通过变量 id 转换而来。实际的探测器编号
  unsigned long long int  ts;

  int wheel;//extract wheel
  unsigned long long int  prets;//上一个事件的ts
  
  int               baseline;//基线
  int		    postrisesum;//
  int		    prerisesum;//
  int               m2_last_beg;//
  int               m2_last_end;//
  int               prerisebeg;//
  int               preriseend;//
  int               postrisebeg;//
  int               postriseend;//not used
  int               peaksample;//
  int               basesample;//

  unsigned short int      traceLen;
  short int               trace[MAXTRACELEN];
}  wuDFMAEVENT;



struct strip_type {
   int phystrip;
   int thr;
   double off;
   double gain;
   int baseline;
};


class tree {
public:
  std::vector<wuDGSEVENT>* br_dgs;
  std::vector<wuDGSEVENT>* br_xa;
  std::vector<wuDFMAEVENT>* br_dfma;

  DGSEVENT DGSEvent[MAXEV];
  DGSEVENT XAEvent[MAXEV];
  DGSEVENT XAAddback[MAXEV];
  DFMAEVENT DFMAEvent[MAXEV];
  
  std::vector<DGSEVENT> dgsevent_vec;
  std::vector<DGSEVENT> xaevent_vec;
  std::vector<DGSEVENT> xaaddback_vec;
  std::vector<DFMAEVENT> dfmaevent_vec;
  
  tree(){ipt = NULL; opt = NULL;}
  tree(TTree *ipt_){
    ipt = ipt_;
    Init();
  }

  void Loop(TTree *opt_);

  void Init();

  void BranchOpt();


  void InitGDS();
  void InitXA();
  void InitDFMA();
  
  void ProcessDGS();//数据分析
  void ProcessXA();
  void ProcessDFMA();

  
  TTree *ipt;
  TTree *opt;
    
  Double_t x1,x2,x3;

  double top, bot;
  double base1, base2, base1_av = 0;
  double rr, r1;
  double Energy;
  int dTth;
  
  // pars for DGS
  int firstbl2[NGE];
  double ave_base[NGE];
  int ith[NGE];
  int isth[NGE];
  double BLTth[NGE];
  double BLCth[NGE][Navth];
  double BLSth[NGE];
  double BLavth[NGE];
  double BLavfth;
  double BLth;//raw bl
  double bsth[NGE];
  double S0th, S1th, S2th;
  double Bsth, S1bth, S1eth, S2bth, S2eth;

  

  double ehibase[NGE];

  
  double PZ[NGE];
  double ehigain[NGE];
  double ehioffset[NGE];
  double ath[NGE], bth[NGE];
  double Pth[NGE], BLPth[NGE];
  double Pdtth[NGE][9];
  

  
  // pars for XA
  double XAave_base[NGEC];
  double XAehibase[NGEC];
  
  double XAPZ[NGEC];
  double XAehigain[NGEC];
  double XAehioffset[NGEC];



  
  // DFMA
  struct strip_type map_fr[160];
  struct strip_type map_ba[160];
  struct strip_type map_box[56];


  int sib_wn_table[56]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			2,2,2,2,2,2,2,2,2,2,2,2,2,2,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  int sib_detn_table[56]={1,1,1,1,1,1,1,2,2,2,2,2,2,2,
			  1,1,1,1,1,1,1,2,2,2,2,2,2,2,
			  2,2,2,2,2,2,2,1,1,1,1,1,1,1,
			  2,2,2,2,2,2,2,1,1,1,1,1,1,1};
  int sib_stripn_table[56]={1,2,3,4,5,6,7,1,2,3,4,5,6,7,
			    1,2,3,4,5,6,7,1,2,3,4,5,6,7,
			    1,2,3,4,5,6,7,1,2,3,4,5,6,7,
			    1,2,3,4,5,6,7,1,2,3,4,5,6,7};


  // TH1I *hbgo[110][110];
};
