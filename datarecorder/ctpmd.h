﻿#ifndef DATARECORDERCTPMD_H
#define DATARECORDERCTPMD_H
#include<string>
#include<set>
#include<fstream>
#include<map>
#include"ThostFtdcMdApi.h"
#include"eventengine.h"
#include"utils.hpp"
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

class Ctpmd : public CThostFtdcMdSpi
{
public:
	Ctpmd(EventEngine *eventengine);

	~Ctpmd();

	void connect();

	void close();

	void login();

	void logout();

	void subscribe(const std::string &symbol);

protected:
	virtual void OnFrontConnected();

	virtual void OnFrontDisconnected(int nReason);

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

private:
	inline void writeLog(const std::string& msg) const;
	inline bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo) const;
	void connect_md(const std::string &userID, const std::string &password, const std::string &brokerID, const std::string &address);

	const std::string gatewayname="ctp";
	EventEngine *eventengine=nullptr;
	CThostFtdcMdApi* mdApi=nullptr;

	std::set<std::string> ninetoeleven;
	std::set<std::string> ninetohalfeleven;
	std::set<std::string> ninetoone;
	std::set<std::string> ninetohalftwo;
	std::set<std::string> treasury_futures;

	std::map<std::string, double>symbol_mapping_volume;

	bool connectStatus=false;
	bool loginStatus=false;
	jsstructs::CtpConnectData ctpData;
	std::set<std::string>subscribedSymbols;
	int req_ID = 0;
};
#endif
