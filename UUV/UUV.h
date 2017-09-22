#include <memory>
#include <sstream>
#include <fstream>

#include "UUV_Command.h"
#include "UUV_Command_Param.h"
#include "UUV_ErrCode.h"
#include "ROV_Control.h"
#include "IUUVObject.h"

#include "StringUtil.h"
#include "Path.h"

#include "BaseFunc.h"
#include "PacketizedTcp.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "winmm.lib")
#pragma warning(disable:4786)