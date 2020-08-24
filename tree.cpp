#include "tree.h"

void tree::Init()
{
  if(ipt==NULL) return;
  ipt->SetBranchAddress("dgs",&br_dgs);
  ipt->SetBranchAddress("dfma",&br_dfma);
  ipt->SetBranchAddress("xa",&br_xa);
}

void tree::Loop(TTree *opt_)
{
  if(opt_==NULL) return;
    
  opt = opt_;
    
  BranchOpt();
  InitGDS();
  InitXA();
  InitDFMA();


  // for (int i = 0; i < 110; ++i)
  //   for (int j = 0; j < 110; ++j)
  //     {
  // 	hbgo[i][j] = new TH1I(TString::Format("hbgo_%03d_%03d",i+1,j+1),"",1000,-500,500);
  //     }
  
  Long64_t TotalEntry = ipt->GetEntries();

  // if(TotalEntry >= 1000000) TotalEntry = 1000000;
  
  for(Long64_t i = 0 ; i < TotalEntry; i++){
    ipt->GetEntry(i);
    if(i % 10000 == 0) std::cout<<"Process "<<i<<" / "<<TotalEntry<<std::endl;
	
    // if(br_dgs->size()) x1 = (*br_dgs)[0].sum1;
    // if(br_dfma->size()) x2 = (*br_dfma)[0].ehi;
    // if(br_xa->size()) x3 = (*br_xa)[0].ehi;

    dgsevent_vec.clear();
    xaevent_vec.clear();
    dfmaevent_vec.clear();
	
    if(br_dgs->size())
      ProcessDGS();

    if(br_xa->size())
      ProcessXA();

    if(br_dfma->size())
      ProcessDFMA();
	

	
    opt->Fill();
  }

  // for (int i = 0; i < 110; ++i)
  //   for (int j = 0; j < 110; ++j)
  //     {
  // 	if(hbgo[i][j]->GetEntries() >0)
  // 	  hbgo[i][j]->Write();
  //     }
    
}

void tree::BranchOpt()
{
  br_dfma = 0;
  br_dgs = 0;
  br_xa = 0;

  opt->Branch("dgs",&dgsevent_vec);
  opt->Branch("xa",&xaevent_vec);
  // opt->Branch("ca",&xaaddback_vec);//clover addback
  opt->Branch("dfma",&dfmaevent_vec);

  // opt->Branch("x1",&x1,"x1/D");
  // opt->Branch("x2",&x2,"x2/D");
  // opt->Branch("x3",&x3,"x3/D");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void tree::InitGDS()
{
  // 读取参数文件

  for (int i = 0; i < NGE; i++)//能量算法相关
    {
      ith[i] = 0;
      isth[i] = 0;
      BLSth[i] = 0;
      BLTth[i] = 0;

      BLavth[i] = BLPth[i];
    }


  
  for (int i = 0; i < NGE; i++)
    {
      ehigain[i] = 1.0;
      ehioffset[i] = 0.0;
      PZ[i] = 1.0;
      ehibase[i] = 0.0;


      ave_base[i] = 0;
      firstbl2[i] = 1;
    }

  std::ifstream readtxt;
  int tmpi;
  double tmpd1,tmpd2,tmpd3,tmpd4,tmpd5,tmpd6,tmpd7,tmpd8,tmpd9;
  std::string str;
  
  readtxt.open("par/dgs_pz.cal");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - dgs_pz.cal"<<std::endl;
    }
  while(!readtxt.eof())
    {
      readtxt>>tmpi>>tmpd1;
      if(readtxt.eof()) break;//避免最后一个重复读取
      PZ[tmpi-1] = tmpd1;
    }
  readtxt.close();

  readtxt.open("par/dgs_ehi.cal");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - dgs_ehi.cal"<<std::endl;
    }
  while(!readtxt.eof())
    {
      readtxt>>tmpi>>tmpd1>>tmpd2;
      if(readtxt.eof()) break;//避免最后一个重复读取
      ehioffset[tmpi-1] = tmpd1;
      ehigain[tmpi-1] = tmpd2;
    }
  readtxt.close();

  readtxt.open("par/Ge_Md.cal");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - Ge_Md.cal"<<std::endl;
    }
  getline(readtxt,str);
  while(!readtxt.eof())
    {
      readtxt>>tmpi>>tmpd1>>tmpd2>>tmpd3>>tmpd4;
      if(readtxt.eof()) break;//避免最后一个重复读取
      Pth[tmpi-1] = tmpd1;
      BLPth[tmpi-1] = tmpd2;
      ath[tmpi-1] = tmpd3;
      bth[tmpi-1] = tmpd4;
    }
  readtxt.close();

  readtxt.open("par/dT_P2.cal");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - dT_P2.cal"<<std::endl;
    }
  getline(readtxt,str);
  while(!readtxt.eof())
    {
      readtxt>>tmpi>>tmpd1>>tmpd2>>tmpd3>>tmpd4>>tmpd5>>tmpd6>>tmpd7>>tmpd8>>tmpd9;
      if(readtxt.eof()) break;//避免最后一个重复读取
      Pdtth[tmpi-1][0] = tmpd1;
      Pdtth[tmpi-1][1] = tmpd2;
      Pdtth[tmpi-1][2] = tmpd3;
      Pdtth[tmpi-1][3] = tmpd4;
      Pdtth[tmpi-1][4] = tmpd5;
      Pdtth[tmpi-1][5] = tmpd6;
      Pdtth[tmpi-1][6] = tmpd7;
      Pdtth[tmpi-1][7] = tmpd8;
      Pdtth[tmpi-1][8] = tmpd9;
    }
  readtxt.close();
}

void tree::ProcessDGS()
{
  // tpe => 1 表示 Ge ，2 表示 BGO，3 表示 SIDE（这个暂时不清楚是啥）

  // 需要完成的工作：
  // BGO 反康
  // 能量刻度
  // 多普勒修正
  //
  int gsid;
  
  for (int i = 0; i < br_dgs->size(); ++i)
    {
      if((*br_dgs)[i].tpe == 1)//Ge
	{
	  gsid = (*br_dgs)[i].tid-1;

	  DGSEvent[i].id = gsid;
	  DGSEvent[i].tpe = (*br_dgs)[i].tpe;
	  DGSEvent[i].tid = (*br_dgs)[i].tid;
	  DGSEvent[i].flag = 0;
	  DGSEvent[i].e = 0;
	  DGSEvent[i].e_nodop = 0;
	  
	  DGSEvent[i].ts = (*br_dgs)[i].event_timestamp;
	  
	  DGSEvent[i].timestamp_match_flag = (*br_dgs)[i].timestamp_match_flag;
	  DGSEvent[i].cfd_valid_flag = (*br_dgs)[i].cfd_valid_flag;
	  DGSEvent[i].peak_valid_flag = (*br_dgs)[i].peak_valid_flag;
	  DGSEvent[i].pileup_flag = (*br_dgs)[i].pileup_flag;

	  int Tth, TPth;
	  Tth = (*br_dgs)[i].event_timestamp & 0x3FFFFFFF; 
	  TPth = (*br_dgs)[i].last_disc_timestamp;
	  if(Tth < TPth) { Tth = Tth+1073741823; }  //1073741823=3FFFFFFF
	  dTth = Tth-TPth;//当前事件与前一个触发的时间差
	  DGSEvent[i].dtlast = dTth;
	  DGSEvent[i].dtpeak = (*br_dgs)[i].peak_timestamp-(*br_dgs)[i].event_timestamp;
	  
	  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
	  // 以下部分关于原始能量的计算
	  top = (double)((*br_dgs)[i].sum2*(*br_dgs)[i].m1begin-(*br_dgs)[i].sum1*(*br_dgs)[i].m2begin);
          bot = (*br_dgs)[i].sum2 - (*br_dgs)[i].sum1;
          bot -= M*((*br_dgs)[i].m2begin - (*br_dgs)[i].m1begin);
          base1 = top/bot;

	  top = (double)((*br_dgs)[i].m1end*(*br_dgs)[i].m2begin-(*br_dgs)[i].m1begin*(*br_dgs)[i].m2end);
          bot = ((*br_dgs)[i].m2begin-(*br_dgs)[i].m2end)-((*br_dgs)[i].m1begin-(*br_dgs)[i].m1end);
          base2 = top/bot;

	  // std::cout<<base1<<"  "<<base2<<std::endl;

          rr = base1/base2;// 它的范围在 (0,2) 大部分集中在 1 附近，偏离 1 的那些事件意味着什么？
          if ((base1 < 4000) && (base1 > 0))//研究算法
            if (((*br_dgs)[i].sum2 - (*br_dgs)[i].sum1) > 200)
              if (rr > 0.95 && rr < 1.05)//对在 1 附近的进行
                {
                  if (firstbl2[gsid] == 1)
                    {
                      ave_base[gsid] = base2;
                      firstbl2[gsid] = 0;
                    }
                  else
                    {
                      ave_base[gsid] = ave_base[gsid]*0.99 + base1*0.01;
                    }
                }

          Energy = (*br_dgs)[i].sum2/M-(*br_dgs)[i].sum1*PZ[gsid]/M;//这里是计算的原始能量
          Energy -= (1.0-PZ[gsid])*ave_base[gsid];


	  Bsth = (*br_dgs)[i].base_sample;
          S1th = (*br_dgs)[i].sum1;
          S2th = (*br_dgs)[i].sum2;
	  S0th = (*br_dgs)[i].sampled_baseline;
	  S0th = S0th*64;
	  S1bth = (*br_dgs)[i].m1begin;
          S1eth = (*br_dgs)[i].m1end;
	  S2bth = (*br_dgs)[i].m2begin;
          S2eth = (*br_dgs)[i].m2end;

	  if(dTth <= 500) Pth[gsid] =  Pdtth[gsid][0];//时间差小于 5 us
	  else if(dTth > 500  && dTth <= 1000) Pth[gsid] =  Pdtth[gsid][1];// 5-10 us
	  else if(dTth > 1000 && dTth <= 1500) Pth[gsid] =  Pdtth[gsid][2];// 10-15 us
	  else if(dTth > 1500 && dTth <= 2000) Pth[gsid] =  Pdtth[gsid][3];// 15-20 us
	  else if(dTth > 2000 && dTth <= 2500) Pth[gsid] =  Pdtth[gsid][4];// 20-25 us
	  else if(dTth > 2500 && dTth <= 3000) Pth[gsid] =  Pdtth[gsid][5];// 25-30 us
	  else if(dTth > 3000 && dTth <= 3500) Pth[gsid] =  Pdtth[gsid][6];// 30-35 us
	  else if(dTth > 3500 && dTth <= 4000) Pth[gsid] =  Pdtth[gsid][7];// 35-40 us
	  else  Pth[gsid] =  Pdtth[gsid][8];


	  if((S1eth-S1bth*Pth[gsid])/(1-Pth[gsid]) > -1000)
	    {
	      BLth = (S1eth-S1bth*Pth[gsid])/(1-Pth[gsid]);//raw bl
	      if(BLth < BLPth[gsid]-dBLth || BLth > BLPth[gsid]+dBLth)
		{
		  if(BLTth[gsid] != 0)
		    {
		      BLth = BLTth[gsid];
		    }
		  else
		    {
		      BLth = BLavth[gsid];
		    }
		}
	    }
	  else if(TMath::Abs(BLTth[gsid]) > 1e-6)// != 0
	    {
	      BLth = BLTth[gsid];
	    }
	  else
	    {
	      BLth = BLavth[gsid];
	    }
	  BLTth[gsid] = BLth;
	  if(ith[gsid] == Navth)
	    {
	      ith[gsid] = 0;
	      if(isth[gsid] == 0)
		{
		  isth[gsid] = 1;
		}
	    }
	  if(isth[gsid] == 0)
	    {
	      BLCth[gsid][ith[gsid]] = BLth;
	      BLSth[gsid] = BLSth[gsid]+BLCth[gsid][ith[gsid]];
	      BLavth[gsid] = BLSth[gsid]/(ith[gsid]+1);
	    }
	  else
	    {
	      BLSth[gsid] = BLSth[gsid]-BLCth[gsid][ith[gsid]];
	      BLCth[gsid][ith[gsid]] = BLth;
	      BLSth[gsid] = BLSth[gsid]+BLCth[gsid][ith[gsid]];
	      BLavth[gsid] = BLSth[gsid]/Navth;
	    }
	  BLavfth = BLavth[gsid];
	  ith[gsid]++;
 
	  Energy =  S2th/M - BLavfth - (S1th/M - BLavfth)*TMath::Power(Pth[gsid], (M+Kth)/M);

	  // 以上部分关于原始能量的计算
	  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
	  
	  DGSEvent[i].ch = Energy;//
	  Energy = Energy*ath[gsid]+bth[gsid];//能量刻度

	  // 多普勒修正
	  DGSEvent[i].e_nodop = Energy;

          if (Pars_beta != 0)
            {
	      double tmp = angtheta[gsid]/57.29577951;
              Energy = Energy*(1-Pars_beta*TMath::Cos(tmp))/TMath::Sqrt(1 - Pars_beta*Pars_beta);
            }

          DGSEvent[i].e = Energy;
          


	  
          // d1 = ((*br_dgs)[i].sum2-(*br_dgs)[i].sum1)/M;       /* uncorrected energy */
          // d2 = (*br_dgs)[i].sum1/M;    /* ~ baseline */
          // if (gsid+1 <= NGE)
          //   if (d1 < (double) 8192)
          //     if (d1 < (double) 8192)
          //       {
          //         d1 = (*br_dgs)[i].ehi; /* SZ corrected */
          //       };
	  

	  // SZ's pol zero (raw)
          top = (*br_dgs)[i].m2end - (*br_dgs)[i].m1end;
          bot = (*br_dgs)[i].m2begin - (*br_dgs)[i].m1begin;
          r1 = top / bot;


	  // 反康处理
	  for (int j = 0; j < br_dgs->size(); j++)
            {
	      // if ((*br_dgs)[j].tpe == 2)
	      // 	{
	      // 	  hbgo[(*br_dgs)[i].tid-1][(*br_dgs)[j].tid-1]->Fill((int) ((*br_dgs)[i].event_timestamp - (*br_dgs)[j].event_timestamp));
	      // 	}
	      
              if ((*br_dgs)[j].tpe == 2 && (*br_dgs)[j].tid == (*br_dgs)[i].tid)
                {               // BGO & GE in coincidence
                  int tdiff = (int) ((*br_dgs)[i].event_timestamp - (*br_dgs)[j].event_timestamp);
		  DGSEvent[i].dt = tdiff;
		  
		  
                  if (TMath::Abs(tdiff) <= 50) 
                    DGSEvent[i].flag = 1;       // Mark as Dirty Ge
                }
            }


	  // time walk 修正
	  if(DGSEvent[i].e > 100 && DGSEvent[i].e <= 240)
	    {
	      DGSEvent[i].tscorr = DGSEvent[i].ts -(int)((240-DGSEvent[i].e)/20);
	    }
	  if(DGSEvent[i].e > 0 && DGSEvent[i].e <= 100)
	    {
	      DGSEvent[i].tscorr = DGSEvent[i].ts -(int)((100-DGSEvent[i].e)/6 + 6);
	    }

	  
          // 筛选条件进行存储
	  dgsevent_vec.push_back(DGSEvent[i]);
	  
	}// loop Ge



      
      
    }// loop vector

 
}


void tree::InitXA()
{
  for (int i = 0; i < NGEC; i++)
    {
      XAehigain[i] = 1.0;
      XAehioffset[i] = 0.0;
      XAPZ[i] = 1.0;
      XAehibase[i] = 0.0;
      XAave_base[i] = 0;

    }

  std::ifstream readtxt;
  int tmpi;
  double tmpd1,tmpd2;

  readtxt.open("par/xa_pz.cal");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - xa_pz.cal"<<std::endl;
    }
  while(!readtxt.eof())
    {
      readtxt>>tmpi>>tmpd1;
      if(readtxt.eof()) break;//避免最后一个重复读取
      XAPZ[tmpi-1] = tmpd1;
    }
  readtxt.close();

  readtxt.open("par/xa_ehi.cal");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - xa_ehi.cal"<<std::endl;
    }
  while(!readtxt.eof())
    {
      readtxt>>tmpi>>tmpd1>>tmpd2;
      if(readtxt.eof()) break;//避免最后一个重复读取
      XAehioffset[tmpi-1] = tmpd1;
      XAehigain[tmpi-1] = tmpd2;
    }
  readtxt.close();  

}

void tree::ProcessXA()
{
  int gsid;

  for (int i = 0; i < br_xa->size(); ++i)
    {
      gsid = (*br_xa)[i].tid-1;;

      XAEvent[i].id = gsid;
      XAEvent[i].tpe = (*br_xa)[i].tpe;
      XAEvent[i].tid = (*br_xa)[i].tid;
      XAEvent[i].flag = 0;
      XAEvent[i].e = 0;
      XAEvent[i].e_nodop = 0;
	  
      XAEvent[i].ts = (*br_xa)[i].event_timestamp;
	  
      XAEvent[i].timestamp_match_flag = (*br_xa)[i].timestamp_match_flag;
      XAEvent[i].cfd_valid_flag = (*br_xa)[i].cfd_valid_flag;
      XAEvent[i].peak_valid_flag = (*br_xa)[i].peak_valid_flag;
      XAEvent[i].pileup_flag = (*br_xa)[i].pileup_flag;

      int Tth, TPth;
      Tth = (*br_xa)[i].event_timestamp & 0x3FFFFFFF; 
      TPth = (*br_xa)[i].last_disc_timestamp;
      if(Tth < TPth) { Tth = Tth+1073741823; }  //1073741823=3FFFFFFF
      dTth = Tth-TPth;//当前事件与前一个触发的时间差
      XAEvent[i].dtlast = dTth;
      XAEvent[i].dtpeak = (*br_xa)[i].peak_timestamp-(*br_xa)[i].event_timestamp;
	  
      //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
      // 以下部分关于原始能量的计算

      top = (double) ((*br_xa)[i].sum2*(*br_xa)[i].m1begin-(*br_xa)[i].sum1*(*br_xa)[i].m2begin);
      bot = (*br_xa)[i].sum2-(*br_xa)[i].sum1;
      bot -= xa_MM*((*br_xa)[i].m2begin - (*br_xa)[i].m1begin);
      base1 = top/bot;

      top = (double) ((*br_xa)[i].m1end*(*br_xa)[i].m2begin - (*br_xa)[i].m1begin*(*br_xa)[i].m2end);
      bot = ((*br_xa)[i].m2begin - (*br_xa)[i].m2end) - ((*br_xa)[i].m1begin-(*br_xa)[i].m1end);
      base2 = top/bot;

      rr = base1/base2;

      if ((base1 < 40000) && (base1 > 0))
	if (((*br_xa)[i].sum2 - (*br_xa)[i].sum1) > 200)
	  if (rr > 0.95 && rr < 1.05 && i == 0)//为什么是 i==0 ？？？
	    {	
	      if (XAave_base[gsid] > 0)
		{
		  XAave_base[gsid] = XAave_base[gsid]*0.99 + base1*0.01;
		}
	      else
		XAave_base[gsid] = base1;
	    }


      Energy = (*br_xa)[i].sum2/xa_MM-(*br_xa)[i].sum1*XAPZ[gsid]/xa_MM;
      Energy -= (1.0-XAPZ[gsid])*XAave_base[gsid];
   
      // 以上部分关于原始能量的计算
      //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

      XAEvent[i].ch = Energy;
      Energy = Energy*XAehigain[gsid]+XAehioffset[gsid];

      XAEvent[i].e_nodop = Energy;
      XAEvent[i].e = Energy;

      

      top = (*br_xa)[i].m2end - (*br_xa)[i].m1end;
      bot = (*br_xa)[i].m2begin - (*br_xa)[i].m1begin;
      r1 = top / bot;

      

      // time walk 修正
      if(XAEvent[i].e > 100 && XAEvent[i].e <= 180)
	{
	  XAEvent[i].tscorr = XAEvent[i].ts -(int)((180-XAEvent[i].e)/20);
	}
	  
      if(XAEvent[i].e > 0 && XAEvent[i].e <= 100)
	{
	  XAEvent[i].tscorr = XAEvent[i].ts -(int)((100-XAEvent[i].e)/7 + 6);
	}







      // 筛选条件进行存储
      xaevent_vec.push_back(XAEvent[i]);
	  
    }// loop vector
  
  // Add back  这里进行5 个 clover 的 addback
  // 0-3  4-7  8-11  12-15  16-19

  // 变量 XAAddback
  
  
  
}

void tree::InitDFMA()
{
  std::ifstream readtxt;
  int tmpi1, tmpi2, tmpi3, tmpi4;
  double tmpd1,tmpd2;

  readtxt.open("par/dssd_fr_calib_zwq.map");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - dssd_fr_calib_zwq.map"<<std::endl;
    }
  while(!readtxt.eof())
    {
      readtxt>>tmpi1>>tmpi2>>tmpi3>>tmpd1>>tmpd2>>tmpi4;
      // std::cout<<tmpi1<<"  "<<tmpi2<<"  "<<tmpi3<<"  "<<tmpd1<<"  "<<tmpd2<<"  "<<tmpi4<<std::endl;
      if(readtxt.eof()) break;//避免最后一个重复读取
      map_fr[tmpi1-1].thr = tmpi3;
      map_fr[tmpi1-1].phystrip = tmpi2-1;
      map_fr[tmpi1-1].off = tmpd1; 
      map_fr[tmpi1-1].gain = tmpd2; 
      map_fr[tmpi1-1].baseline = tmpi4;
    }
  readtxt.close();
  
  readtxt.open("par/dssd_ba_calib_zwq.map");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - dssd_ba_calib_zwq.map"<<std::endl;
    }
  while(!readtxt.eof())
    {
      readtxt>>tmpi1>>tmpi2>>tmpi3>>tmpd1>>tmpd2>>tmpi4;
      // std::cout<<tmpi1<<"  "<<tmpi2<<"  "<<tmpi3<<"  "<<tmpd1<<"  "<<tmpd2<<"  "<<tmpi4<<std::endl;
      if(readtxt.eof()) break;//避免最后一个重复读取
      map_ba[tmpi1-161].thr = tmpi3;
      map_ba[tmpi1-161].phystrip = tmpi2-1;
      map_ba[tmpi1-161].off = tmpd1; 
      map_ba[tmpi1-161].gain = tmpd2; 
      map_ba[tmpi1-161].baseline = tmpi4;
    }
  readtxt.close();


  readtxt.open("par/sibox_calib_th.map");// sibox_calib_th.map 
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file - sibox_calib_th.map"<<std::endl;
    }
  while(!readtxt.eof())
    {
      readtxt>>tmpi1>>tmpi2>>tmpi3>>tmpd1>>tmpd2>>tmpi4;
      if(readtxt.eof()) break;//避免最后一个重复读取
      map_box[tmpi1-1].thr = tmpi3;
      map_box[tmpi1-1].phystrip = tmpi2-1;
      map_box[tmpi1-1].off = tmpd1; 
      map_box[tmpi1-1].gain = tmpd2; 
      map_box[tmpi1-1].baseline = tmpi4;
    }
  readtxt.close();
    
}
  
void tree::ProcessDFMA()
{
  int gsid;
  
  for (int i = 0; i < br_dfma->size(); ++i)
    {
      gsid = (*br_dfma)[i].tid-1;

      DFMAEvent[i].id = gsid;
      DFMAEvent[i].tpe = (*br_dfma)[i].tpe;
      DFMAEvent[i].tid = (*br_dfma)[i].tid;
      DFMAEvent[i].ch = (*br_dfma)[i].ch;
      DFMAEvent[i].e = 0;
      DFMAEvent[i].ts = (*br_dfma)[i].ts;
      DFMAEvent[i].prets = (*br_dfma)[i].prets;
      DFMAEvent[i].wheel = (*br_dfma)[i].wheel;
      DFMAEvent[i].flag = 0;
      DFMAEvent[i].tot = 0;
      
      if((*br_dfma)[i].tpe == 5)//DSSD
	{
	  // front
	  if(gsid < 160)
	    {
	      DFMAEvent[i].id = map_fr[gsid].phystrip;//真实位置
	      DFMAEvent[i].flag = 1;
	      if((((*br_dfma)[i].postrisesum-(*br_dfma)[i].prerisesum)/10) <= 0)//add 20200824
		DFMAEvent[i].e = 0;
	      else
		DFMAEvent[i].e = double(map_fr[gsid].gain)*((*br_dfma)[i].ch + double(rand())/RAND_MAX-0.5) + double(map_fr[gsid].off);


	      for (unsigned short int  j = 0; j < (*br_dfma)[i].traceLen; ++j)//add 20200824
		{
		  if((*br_dfma)[i].trace[j]>16000)
		    {
		      if((*br_dfma)[i].trace[j+1]<16000)
			{
			  (*br_dfma)[i].trace[j] = ((*br_dfma)[i].trace[j-1]+(*br_dfma)[i].trace[j+1])/2;
			}
		      else
			{
			  (*br_dfma)[i].trace[j] = (*br_dfma)[i].trace[j-1];
			}
		    }
		}
	      int baseline = 0;
	      for (int j = 0; j < 40; ++j)
		{
		  baseline += (*br_dfma)[i].trace[j];
		}
	      baseline /= 40;
	      for (unsigned short int j = 40; j < (*br_dfma)[i].traceLen; ++j)
		{
		  if((*br_dfma)[i].trace[j]-baseline > 10) DFMAEvent[i].tot++;
		}

	      
	      
	    } 

	  // back
	  if(gsid >= 160)
	    {
	      DFMAEvent[i].id = map_fr[gsid-160].phystrip;//真实位置
	      DFMAEvent[i].flag = 2;
	      if((((*br_dfma)[i].prerisesum-(*br_dfma)[i].postrisesum)/10) <= 0)//add 20200824
		DFMAEvent[i].e = 0;
	      else
		DFMAEvent[i].e = double(map_ba[gsid-160].gain)*((*br_dfma)[i].ch + double(rand())/RAND_MAX-0.5) + double(map_ba[gsid-160].off);

	      for (unsigned short int  j = 0; j < (*br_dfma)[i].traceLen; ++j)//add 20200824
		{
		  if((*br_dfma)[i].trace[j]>16000)
		    {
		      if((*br_dfma)[i].trace[j+1]<16000)
			{
			  (*br_dfma)[i].trace[j] = ((*br_dfma)[i].trace[j-1]+(*br_dfma)[i].trace[j+1])/2;
			}
		      else
			{
			  (*br_dfma)[i].trace[j] = (*br_dfma)[i].trace[j-1];
			}
		    }
		}
	      int baseline = 0;
	      for (int j = 0; j < 40; ++j)
		{
		  baseline += (*br_dfma)[i].trace[j];
		}
	      baseline /= 40;
	      for (unsigned short int j = 40; j < (*br_dfma)[i].traceLen; ++j)
		{
		  if(baseline-(*br_dfma)[i].trace[j] > 10) DFMAEvent[i].tot++;
		}

	      
	    }
    

	}//DSSD


      if((*br_dfma)[i].tpe == 12)//SIBOX
	{
	  DFMAEvent[i].id = gsid;
	  DFMAEvent[i].flag = 3;
	  
	  DFMAEvent[i].e = double(map_box[gsid].gain)*((*br_dfma)[i].ch + double(rand())/RAND_MAX-0.5) + double(map_box[gsid].off); 

	  // 真实的条位置，程序中的这个信息可能有错。需要通过打在条间的事件来检验
	  // sib_wn = sib_wn_table[gsid];
	  // sib_stripn = sib_stripn_table[gsid];
	  // sib_detn = sib_detn_table[gsid];

	  
	  
	}//SIBOX


      if((*br_dfma)[i].tpe == 6)//FP  左右两端读出 id=0为左端 =1为右端
	{
	  // 需要判断是否多次打火

	  // PPAC
	  if((*br_dfma)[i].tid == 9)
	    {
	      DFMAEvent[i].id = 0;
	      DFMAEvent[i].flag = 4;
	    }
	  else if((*br_dfma)[i].tid == 8)
	    {
	      DFMAEvent[i].id = 1;
	      DFMAEvent[i].flag = 4;
	    }

	  // DE  这个应该是 PPAC的阳极
	  if((*br_dfma)[i].tid == 7)
	    {
	      DFMAEvent[i].id = 0;
	      DFMAEvent[i].flag = 6;
	    }

	  

	  // MWPC
	  if((*br_dfma)[i].tid == 3)//LCH
	    {
	      DFMAEvent[i].id = 0;
	      DFMAEvent[i].flag = 5;
	    }
	  else if((*br_dfma)[i].tid == 4)//RCH
	    {
	      DFMAEvent[i].id = 1;
	      DFMAEvent[i].flag = 5;
	    }
	  else if((*br_dfma)[i].tid == 5)//UPCH  这路信号应该没有
	    {
	      DFMAEvent[i].id = 2;
	      DFMAEvent[i].flag = 5;
	    }
	  else if((*br_dfma)[i].tid == 6)//DOWNCH 这路信号应该没有
	    {
	      DFMAEvent[i].id = 3;
	      DFMAEvent[i].flag = 5;
	    }



	  
	  DFMAEvent[i].e = DFMAEvent[i].ch; 
	}//FP


      
      // 筛选条件进行存储
      dfmaevent_vec.push_back(DFMAEvent[i]);

    }// loop vector
}
