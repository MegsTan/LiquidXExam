// Copyright (c) 2017 by CreativeDev.

#pragma once

#define GET_CLASSNAME_WITH_FUNCTION					FString(__FUNCTION__)
#define GET_LINE_NUMBER								FString::FromInt(__LINE__)


// Definition of all global custom log with a target message format Class::Function [Line Number] Message
#define LOG(LogCategory, Message)					UE_LOG(LogCategory, Log, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_DISPLAY(LogCategory, Message)			UE_LOG(LogCategory, Display, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_VERBOSE(LogCategory, Message)			UE_LOG(LogCategory, Verbose, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_VERYVerbose(LogCategory, Message)		UE_LOG(LogCategory, VeryVerbose, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_WARNING(LogCategory, Message)			UE_LOG(LogCategory, Warning, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_ERROR(LogCategory, Message)				UE_LOG(LogCategory, Error, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_FATAL(LogCategory, Message)				UE_LOG(LogCategory, Fatal, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))

/*
	HOW TO USE:

	if(GEngine) // Is GEngine available?
	{
		PRINT(-1, 5.f, FColor::Green, "This is a demo text message."));
	}

*/

#define PRINT(Key, TimeToDisplay, DisplayColor, Message)		GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, FString::Printf(TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))