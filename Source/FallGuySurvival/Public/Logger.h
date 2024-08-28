// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <iostream>
using namespace std;

#define LOGPREFACE "\\TFLog_"

enum ErrorLevel
{
	EL_DEBUG = 0,
	EL_WARNING = 1,
	EL_ERROR = 2,
	EL_CRITICAL = 3
};

class Logger
{
private:
	static Logger* PInstance;
	string Path()
	{
		string Ret;
		char ExecPath[FILENAME_MAX];
		GetCurrentDirectoryA(sizeof(ExecPath), ExecPath);
		Ret = ExecPath;
		Ret += LOGPREFACE;
		Ret += TodaysDateAsString();
		Ret += ".txt";
		return Ret;
	}

#pragma warning(disable:4996)
	string TodaysDateAsString()
	{
		string Ret;
		time_t Now;
		time(&Now);

		struct tm* pTime;
		pTime = localtime(&Now);
		Ret += int2string(pTime->tm_year + 1900);
		Ret += "-";
		Ret += int2string(pTime->tm_mon + 1);
		Ret += "-";
		Ret += int2string(pTime->tm_mday);
		return Ret;
	}

	string GetCurrentTimestamp()
	{
		string Ret;
		time_t Now;
		time(&Now);

		struct tm* pTime;
		pTime = localtime(&Now);
		Ret += int2string(pTime->tm_hour);
		Ret += ":";
		Ret += int2string(pTime->tm_min);
		Ret += ":";
		Ret += int2string(pTime->tm_sec);
		return Ret;
	}

#pragma warning(default:4996)
	string int2string(const int& i, bool padded = true)
	{
		ostringstream format_message;
		format_message << i;
		string Ret = format_message.str();
		if (padded && Ret.length() == 1)
		{
			Ret = "0" + Ret;
		}
		return Ret;
	}

	string ErrorLevelAsString(ErrorLevel Level)
	{
		switch (Level)
		{
		case ErrorLevel::EL_DEBUG:
			return "[DEBUGGING] ";
		case ErrorLevel::EL_WARNING:
			return "[WARNING] ";
		case ErrorLevel::EL_ERROR:
			return "[ERROR] ";
		case ErrorLevel::EL_CRITICAL:
			return "[!! CRITICAL ERROR !!] ";
		default:
			return "UNKNOWN ERROR LEVEL";
		}
	}

public:
	static Logger* GetInstance()
	{
		if (PInstance == nullptr)
		{
			PInstance = new Logger();
		}
		return PInstance;
	}

	void AddMessage(string Msg, ErrorLevel Level)
	{
		string LogLine;
		LogLine += TodaysDateAsString();
		LogLine += " ";
		LogLine += GetCurrentTimestamp();
		LogLine += ": ";
		LogLine += ErrorLevelAsString(Level);
		LogLine += Msg;
		LogLine += "\n";
		
		ofstream fout;
		string path = Path();
		fout.open(path, ios_base::app);
		fout << LogLine;
		fout.close();
	}
};
