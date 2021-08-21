#pragma once
#include <game_sdk/classes/c_client_class.h>


enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

class VBaseClient
{
public:
	virtual void init() = 0;
	virtual void unknown1() = 0;
	virtual void unknown2() = 0;
	virtual void unknown3() = 0;
	virtual void unknown4() = 0;
	virtual void unknown5() = 0;
	virtual void unknown6() = 0;
	virtual void unknown7() = 0;
	virtual ClientClass* get_all_classes() = 0;

	bool dispatch_user_message(int messageType, int arg, int arg1, void* data)
	{
		using fn = bool(__thiscall*)(VBaseClient*, int, int, int, void*);
		return (*(fn**)this)[38](this, messageType, arg, arg1, data);
	}
};