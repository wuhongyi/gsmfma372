#include "gsang.h"
#include <TTree.h>
#include <TFile.h>
#include <TMath.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define M 350.0  //RC 常数，单位暂不清除
#define xa_MM 350 //RC 常数
#define Kth 146
#define NGE 110 //GS 通道数
#define NGEC 20 //clover 通道数
#define Navth 3000
#define dBLth 500

#define Pars_beta 0.0270









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
  unsigned short int      flag;//反康标记     addback标记

  unsigned long long int  ts;//event_timestamp
  
  unsigned long long int  tscorr;//time walk corr
  int                     dtlast;//当前触发与上个触发的时间差
  int                     dtpeak;//peak_timestamp 未完成，可能参考程序中的数据解码存在问题
  int                     dt;//Ge与BGO的时间差       addback两个晶体的时间差
  
  bool	                  timestamp_match_flag;
  bool	                  cfd_valid_flag;
  bool	                  peak_valid_flag;
  bool	                  pileup_flag;
  double                  cfd;

} DGSEVENT;

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



#define MAXTRACELEN 8192

typedef struct DFMAEVENT
{
  int               ehi;    // WAS SHORT INT
  short int               id;
  unsigned short int      tpe, tid;
  unsigned short int      board_id;
  unsigned short int      chan_id;
  unsigned long long int  LEDts;
  unsigned long long int  CFDts;
  unsigned long long int  PEAKts;
  char                    flag;  
  char 			  pu;
  int			  d2t0;
  int			  d2t1;
  int                     d2t2;
  int wheel;
  unsigned long long int  prevTS;
  int               baseline;
  int               postrisebeg;
  int               prerisebeg;
  int               postriseend;
  int               preriseend;
  int               peaksample;
  int               basesample;
  int		    postrisesum;
  int		    prerisesum;
  int               header_type;
  int               m2_last_beg;
  int               m2_last_end;
  unsigned short int      traceLen;
  short int               trace[MAXTRACELEN];
}  DFMAEVENT;



class tree {
public:
  std::vector<wuDGSEVENT>* br_dgs;
  std::vector<wuDGSEVENT>* br_xa;
  std::vector<DFMAEVENT>* br_dfma;

  DGSEVENT DGSEvent[MAXEV];
  DGSEVENT XAEvent[MAXEV];
  DGSEVENT XAAddback[MAXEV];
  
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

  
};
