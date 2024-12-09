// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/TFUtilityFunctions.h"

ErrorLevel UTFUtilityFunctions::LogLevelToErrorLevel(const ELogLevel& Level)
{
	switch (Level)
	{
	case ELogLevel::LL_DEBUG:
		return ErrorLevel::EL_DEBUG;
	case ELogLevel::LL_ERROR:
		return ErrorLevel::EL_ERROR;
	case ELogLevel::LL_WARNING:
		return ErrorLevel::EL_WARNING;
	case ELogLevel::LL_CRITICAL:
		return ErrorLevel::EL_CRITICAL;
	default:
		Logger::GetInstance()->AddMessage("UTFUtilityFunctions::LogLevelToErrorLevel - Unknown Log Level", ErrorLevel::EL_CRITICAL);
		return ErrorLevel::EL_CRITICAL;
	}
}

float UTFUtilityFunctions::ConvertCelsiusToFahrenheit(const float& Celsius)
{
	return (Celsius * 9 / 5) + 32;
}

void UTFUtilityFunctions::AddLogMessage(const FString& Message, const ELogLevel& Level)
{
	std::string ConvertedMessage = std::string(TCHAR_TO_UTF8(*Message));
	Logger::GetInstance()->AddMessage(ConvertedMessage, LogLevelToErrorLevel(Level));
}
