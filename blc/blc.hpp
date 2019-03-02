#pragma once

#include "blc/nonCopyable.hpp"
#include "blc/serializable.hpp"
#include "blc/errorHandle.hpp"
#include "blc/Socket.hpp"
#include "blc/Server.hpp"
#include "blc/client2way.hpp"
#include "blc/Client.hpp"
#include "blc/singleServer.hpp"
#include "blc/protocolCaps.hpp"
#include "blc/protocolFactory.hpp"
#include "blc/pipe.hpp"
#include "blc/server2way.hpp"
#include "blc/stream.hpp"
#include "blc/pair.hpp"
#include "blc/blcmain.hpp"
#include "blc/cinReadable.hpp"
#include "blc/global.hpp"
#include "blc/actor.hpp"
#include "blc/bindTest.hpp"
#include "blc/regex.hpp"
#include "blc/float.hpp"
#include "blc/fileSize.hpp"
#include "blc/stringOp.hpp"

namespace blc{
	/// contain basic tools.
	namespace tools{}

	/// contain error managment class.
	namespace error{}

	/// contain networking class.
	namespace network{}

	/// contain mathematical class.
	namespace math{}

	/// contain symbolique class.
	namespace symbole{}
}