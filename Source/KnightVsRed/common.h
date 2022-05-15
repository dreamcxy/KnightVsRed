﻿#pragma once

#define print_err(_s_,...) do{ \
	UE_LOG(LogTemp, Error, TEXT(_s_), ##__VA_ARGS__); \
}while(0)


#define print_temp(_s_, ...) do {\
	UE_LOG(LogTemp, Log, TEXT(_s_), ##__VA_ARGS__); \
}while(0)

#define print_temp(_s_, ...) do {\
UE_LOG(LogTemp, Warning, TEXT(_s_), ##__VA_ARGS__); \
}while(0)