#pragma once

#define print_err(_s_,...) do{ \
	UE_LOG(LogTemp, Error, TEXT(_s_), ##__VA_ARGS__); \
}while(0)


#define print_temp(_s_, ...) do {\
	UE_LOG(LogTemp, Log, TEXT(_s_), ##__VA_ARGS__); \
}while(0)

#define print_warn(_s_, ...) do {\
UE_LOG(LogTemp, Warning, TEXT(_s_), ##__VA_ARGS__); \
}while(0)

#define NULL_ERR(ptr) do {\
	if (ptr == nullptr)\
	{\
		print_err("err to load ptr:%s", *(ptr->GetName()));\
	}\
}while(0)

#define TRUE_ERR(b, reason) do {\
	if (b != true)\
	{\
		print_err("not zero, fail:%s", reason);\
	}\
}while(0)
	
#define MOVE_SPEED 5.0f
#define MOVE_SPEED_MULTI 100.0f


enum PlayerPawnState
{
	IDLE,
	RUN,
	ATTACK
};